// ════════════════════════════════════════════════════════════
// Practice Problems — Section 10
// Single runnable file. Shell-only drills (nm, g++ -E, CMake,
// timing flags) are documented at the bottom with exact commands.
// ════════════════════════════════════════════════════════════

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <cmath>


// ════════════════════════════════════════════════════════════
// FILE: vec3.h   (declarations)
// ════════════════════════════════════════════════════════════
// #pragma once

struct Vector3 {
    double x;
    double y;
    double z;
};

// length() moved into the header as inline — definition must be
// visible in every TU, and inline satisfies the ODR.
inline double length(const Vector3& v) {
    return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

double dot(const Vector3& a, const Vector3& b);     // defined in vec3.cpp
Vector3 cross(const Vector3& a, const Vector3& b);  // defined in vec3.cpp


// ════════════════════════════════════════════════════════════
// FILE: vec3.cpp   (definitions)
// ════════════════════════════════════════════════════════════

double dot(const Vector3& a, const Vector3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 cross(const Vector3& a, const Vector3& b) {
    return Vector3{
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}


// ════════════════════════════════════════════════════════════
// Problem 4 — overload print
// ════════════════════════════════════════════════════════════
// print("hi") is const char[3] -> decays to const char*.
// Without a const char* overload it converts to bool (pointer->bool
// is a standard conversion) and prints "bool". Two fixes below.

void print(int x) {
    std::cout << "print(int): " << x << "\n";
}

void print(double x) {
    std::cout << "print(double): " << x << "\n";
}

void print(const std::string& x) {
    std::cout << "print(string): " << x << "\n";
}

void print(bool x) {
    std::cout << "print(bool): " << (x ? "true" : "false") << "\n";
}

// Fix A: give the literal an exact match so it never falls to bool.
void print(const char* x) {
    std::cout << "print(const char*): " << x << "\n";
}


// ════════════════════════════════════════════════════════════
// Problem 5 — default arguments
// ════════════════════════════════════════════════════════════
// Defaults bind at the CALL SITE, not inside the function.
// Only trailing parameters may have defaults.

void makeWindow(int width,
                int height = 480,
                const std::string& title = "App",
                bool fullscreen = false) {
    std::cout << "window w=" << width
              << " h=" << height
              << " title=" << title
              << " fullscreen=" << (fullscreen ? "true" : "false") << "\n";
}


// ════════════════════════════════════════════════════════════
// Problem 6 — swap overloads (by reference)
// ════════════════════════════════════════════════════════════

void mySwap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void mySwap(std::string& a, std::string& b) {
    std::string temp = a;
    a = b;
    b = temp;
}

// The template version — one definition, any type with copy semantics.
template <typename T>
void swapAny(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}


// ════════════════════════════════════════════════════════════
// Problem 7 — pass by value vs pass by reference
// ════════════════════════════════════════════════════════════

void incrementWrong(int x) {
    x = x + 1;   // mutates a COPY; caller sees nothing
}

void incrementRight(int& x) {
    x = x + 1;   // mutates the caller's object
}


// ════════════════════════════════════════════════════════════
// Problem 13 — using namespace std; collision drill
// ════════════════════════════════════════════════════════════
// BROKEN version (kept as a comment because it does not compile):
//
//     using namespace std;
//     void tally() {
//         vector<int> marks{7, 3, 7, 9, 7};
//         int count = 0;                       // shadows std::count
//         count = count(marks.begin(), marks.end(), 7);
//         //      ^^^^^ error: 'count' cannot be used as a function
//     }
//
// The local int hides the function name. The name lookup finds the
// variable first and stops — it never reaches std::count.
//
// FIX: drop `using namespace std;` and qualify the call.

void tallyFixed() {
    std::vector<int> marks{7, 3, 7, 9, 7};
    int count = 0;                                        // ordinary variable
    count = static_cast<int>(
        std::count(marks.begin(), marks.end(), 7));       // qualified call
    std::cout << "sevens=" << count << "\n";
}


// ════════════════════════════════════════════════════════════
// Problem 15 — optimization comparison workload
// ════════════════════════════════════════════════════════════
// Measured on this machine, n = 3e8:
//
//   n as a compile-time constant:
//       -O0  ~796 ms      loop runs, one add per iteration
//       -O2  ~0.0001 ms   loop GONE
//     GCC recognises the induction variable and substitutes the closed
//     form n*(n+1)/2. A volatile SINK does not stop this — the result is
//     still stored, it just never iterated. That 5,000,000x "speedup" is
//     deletion of your benchmark, not optimization of your code.
//
//   n read through a volatile (what this file does):
//       -O0  ~793 ms   |  -O2  ~107 ms  |  -O3  ~107 ms   (sumTo)
//       -O0 ~1092 ms   |  -O2  ~636 ms  |  -O3  ~634 ms   (sumOpaque)
//     Now the value is unknown at compile time, so the closed form is not
//     substituted. -O2 instead unrolls and SIMD-vectorizes: a real ~7x.
//
// sumOpaque has a serial dependency (each iteration needs the previous
// total), so it cannot be vectorized or closed. Its ~1.7x is the floor —
// what you get from register allocation and unrolling alone.

std::uint64_t sumTo(std::uint64_t n) {
    std::uint64_t total = 0;
    for (std::uint64_t i = 1; i <= n; ++i) {
        total += i;
    }
    return total;
}

std::uint64_t sumOpaque(std::uint64_t n) {
    std::uint64_t total = 1;
    for (std::uint64_t i = 1; i <= n; ++i) {
        total = total * 6364136223846793005ULL + i;
        total ^= total >> 29;
    }
    return total;
}


int main() {

    // ──── Problem 1: three build paths ────
    std::cout << "──── build paths ────\n";

    std::cout << "Namaste, Karan!\n";
    std::cout << "one-shot : g++ -std=c++17 main.cpp -o app\n";
    std::cout << "two-step : g++ -c main.cpp -o main.o  then  g++ main.o -o app\n";
    std::cout << "cmake    : cmake -S . -B build && cmake --build build\n";
    std::cout << "artifacts: .cpp -> .o (object) -> app (linked executable)\n";


    // ──── Problem 2: type sizes ────
    std::cout << "\n──── type sizes ────\n";

    std::cout << "sizeof(bool)        = " << sizeof(bool)        << "\n";
    std::cout << "sizeof(char)        = " << sizeof(char)        << "\n";
    std::cout << "sizeof(wchar_t)     = " << sizeof(wchar_t)     << "\n";
    std::cout << "sizeof(int)         = " << sizeof(int)         << "\n";
    std::cout << "sizeof(long)        = " << sizeof(long)        << "\n";
    std::cout << "sizeof(long long)   = " << sizeof(long long)   << "\n";
    std::cout << "sizeof(float)       = " << sizeof(float)       << "\n";
    std::cout << "sizeof(double)      = " << sizeof(double)      << "\n";
    std::cout << "sizeof(long double) = " << sizeof(long double) << "\n";
    std::cout << "sizeof(std::string) = " << sizeof(std::string) << "\n";
    std::cout << "sizeof(void*)       = " << sizeof(void*)       << "\n";
    std::cout << "note: only sizeof(char)==1 is guaranteed; rest are ABI-dependent\n";


    // ──── Problem 3: comment nesting ────
    std::cout << "\n──── comment nesting ────\n";

    // Broken: /* block comments do NOT nest */
    //
    //     /* outer
    //        /* inner */
    //        still outer?
    //     */          <-- error: stray '*/' ; the first */ closed the block
    //
    // Fix with #if 0 — the preprocessor handles it and nesting is legal.

#if 0
    std::cout << "this line is removed by the preprocessor\n";
    /* a block comment inside #if 0 causes no trouble */
#endif

    std::cout << "block comments do not nest; use #if 0 ... #endif\n";
    std::cout << "the #if 0 block above never reached the compiler\n";


    // ──── Problem 4: overload resolution ────
    std::cout << "\n──── overload print ────\n";

    print(0);                    // int
    print(0.0);                  // double
    print("hi");                 // const char*  (without that overload -> bool)
    print(std::string("hi"));    // string, explicit
    print(true);                 // bool
    print('A');                  // char -> promotes to int

    std::string tanvi = "Tanvi";
    print(tanvi);


    // ──── Problem 5: default arguments ────
    std::cout << "\n──── default arguments ────\n";

    makeWindow(800);
    makeWindow(800, 600);
    makeWindow(800, 600, "Editor");
    makeWindow(800, 600, "Editor", true);


    // ──── Problem 6: swap by reference ────
    std::cout << "\n──── swap ────\n";

    int rollA = 21;
    int rollB = 22;

    std::cout << "before: rollA=" << rollA << " rollB=" << rollB << "\n";
    mySwap(rollA, rollB);
    std::cout << "after : rollA=" << rollA << " rollB=" << rollB << "\n";

    std::string first = "Rohit";
    std::string second = "Drishya";

    std::cout << "before: first=" << first << " second=" << second << "\n";
    mySwap(first, second);
    std::cout << "after : first=" << first << " second=" << second << "\n";

    double cgpaA = 8.15;
    double cgpaB = 9.02;

    swapAny(cgpaA, cgpaB);
    std::cout << "template swap: cgpaA=" << cgpaA << " cgpaB=" << cgpaB << "\n";


    // ──── Problem 7: value vs reference ────
    std::cout << "\n──── value vs reference ────\n";

    int marks = 10;

    std::cout << "start          : " << marks << "\n";
    incrementWrong(marks);
    std::cout << "after wrong(x) : " << marks << "   <- unchanged, copy mutated\n";
    incrementRight(marks);
    std::cout << "after right(&x): " << marks << "   <- caller sees the change\n";


    // ──── Problem 8: separate compilation (vec3) ────
    std::cout << "\n──── vec3 separate compilation ────\n";

    Vector3 a{1.0, 2.0, 3.0};
    Vector3 b{4.0, 5.0, 6.0};

    std::cout << "length(a) = " << length(a) << "\n";
    std::cout << "dot(a,b)  = " << dot(a, b) << "\n";

    Vector3 c = cross(a, b);
    std::cout << "cross(a,b)= (" << c.x << ", " << c.y << ", " << c.z << ")\n";
    std::cout << "length inline in header -> still one definition, links fine\n";


    // ──── Problem 9: include guard drill ────
    std::cout << "\n──── include guards ────\n";

    std::cout << "no guard + double include -> error: redefinition of 'struct Vector3'\n";
    std::cout << "fix: #pragma once  or  #ifndef VEC3_H / #define VEC3_H / #endif\n";


    // ──── Problem 12: linker error drill ────
    std::cout << "\n──── linker errors ────\n";

    std::cout << "declared-but-undefined function:\n";
    std::cout << "  undefined reference to `missingFn()'  (ld, not the compiler)\n";
    std::cout << "compiler errors = syntax/types; linker errors = missing symbols\n";


    // ──── Problem 13: using namespace std; collision ────
    std::cout << "\n──── namespace collision ────\n";

    tallyFixed();
    std::cout << "local `int count` shadows std::count when `using namespace std;`\n";
    std::cout << "fix: drop the using-directive, qualify as std::count\n";


    // ──── Problem 15: optimization timing ────
    std::cout << "\n──── optimization timing ────\n";

    // volatile read so n is not a compile-time constant
    volatile std::uint64_t nIn = 300000000ULL;
    const std::uint64_t n = nIn;

    auto s1 = std::chrono::steady_clock::now();
    volatile std::uint64_t sink1 = sumTo(n);
    auto e1 = std::chrono::steady_clock::now();
    double ms1 = std::chrono::duration<double, std::milli>(e1 - s1).count();

    auto s2 = std::chrono::steady_clock::now();
    volatile std::uint64_t sink2 = sumOpaque(n);
    auto e2 = std::chrono::steady_clock::now();
    double ms2 = std::chrono::duration<double, std::milli>(e2 - s2).count();

    std::cout << "sumTo     result=" << sink1 << "  time=" << ms1 << " ms\n";
    std::cout << "sumOpaque result=" << sink2 << "  time=" << ms2 << " ms\n";
    std::cout << "sumTo is vectorizable      -> big -O2 win (~7x here)\n";
    std::cout << "sumOpaque is serial         -> small -O2 win (~1.7x here)\n";
    std::cout << "make n a literal and -O2 deletes sumTo entirely (closed form)\n";
    std::cout << "rebuild at -O0 / -O2 / -O3 / -O3 -march=native and compare both\n";


    // ──── Problem 16: warning tour ────
    std::cout << "\n──── warnings ────\n";

    std::cout << "this file builds clean under:\n";
    std::cout << "  -Wall -Wextra -Wpedantic -Wshadow\n";
    std::cout << "-Wshadow is why no inner block reuses an outer variable name\n";


    std::cout << "\n──── done ────\n";

    return 0;
}


// ════════════════════════════════════════════════════════════
// SHELL DRILLS — run these; they are not C++
// ════════════════════════════════════════════════════════════
//
// [1] Three build paths, compare artifacts
//     g++ -std=c++17 -Wall -Wextra practice.cpp -o app_oneshot
//     g++ -std=c++17 -c practice.cpp -o practice.o
//     g++ practice.o -o app_linked
//     ls -l practice.o app_oneshot app_linked
//     file practice.o app_oneshot
//     # .o = relocatable object, unresolved symbols, not runnable
//     # app = fully linked ELF executable
//
// [1c] CMake path
//     # CMakeLists.txt
//     #   cmake_minimum_required(VERSION 3.16)
//     #   project(practice CXX)
//     #   set(CMAKE_CXX_STANDARD 17)
//     #   set(CMAKE_CXX_STANDARD_REQUIRED ON)
//     #   add_executable(app practice.cpp)
//     cmake -S . -B build
//     cmake --build build
//     ./build/app
//
// [10] Preprocessor tour
//     g++ -std=c++17 -E practice.cpp | head -50
//     g++ -std=c++17 -E practice.cpp | wc -l        # ~40k lines from <iostream>
//     g++ -std=c++17 -E practice.cpp | grep -n 'iostream' | head
//     # look for line markers:  # 1 "/usr/include/c++/13/iostream" 1 3
//
// [11] Symbol inspection
//     g++ -std=c++17 -c vec3.cpp -o vec3.o
//     g++ -std=c++17 -c main.cpp -o main.o
//     nm -C vec3.o | grep ' T '     # T = defined in .text  -> dot, cross
//     nm -C main.o | grep ' U '     # U = undefined, expects the linker
//     g++ main.o vec3.o -o app      # linker binds U -> T
//
// [12] Linker error drill
//     # header:  void missingFn();
//     # main:    missingFn();
//     g++ -std=c++17 main.cpp -o app
//     # /usr/bin/ld: undefined reference to `missingFn()'
//     # compiles fine (declaration seen), fails at link (no definition)
//
// [15] Optimization comparison
//     for f in "-O0" "-O2" "-O3" "-O3 -march=native"; do
//       g++ -std=c++17 $f practice.cpp -o bench
//       echo "flags: $f"; ./bench | grep 'wall time'
//     done
//
// [16] Warning tour
//     g++ -std=c++17 -Wall -Wextra -Wpedantic -Wshadow practice.cpp -o app
//
// ──── build this file ────
// g++ -std=c++17 -Wall -Wextra -Wpedantic -Wshadow practice_problems.cpp -o app
// ./app