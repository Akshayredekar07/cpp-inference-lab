# **Introduction & Program Structure**

## **Table of Contents**

1. Why learn C++
2. What is C++
3. How C++ relates to C
4. How a C++ program is laid out
5. Comments
6. Function basics
7. Splitting code into header and source files
8. Compiling and linking
9. `using namespace std;` and why we skip it
10. Practice problems

---

## **1. Why Learn C++**

### **Read this before you look at any syntax**

- Python and JS hide a lot from you: memory, and how your code becomes something that runs. C++ doesn't hide it. You get to see how a program actually turns into an executable. That helps later when you debug, tune speed, or read low-level code.
- C++ is not "Python but harder." It works differently. You choose the types, you decide how memory is used, and you decide how long things live. In return you get speed and control. The price is more rules up front.
- Right now, don't try to memorize every rule. Just get a rough picture of three things: compiler vs linker, declaration vs definition, and pass-by-value vs pass-by-reference. Everything else builds on these.

### **Who this is for**

- If you know C, Python or JS: loops, variables and functions will feel familiar. What's different is that C++ makes you fix types up front and lets you touch memory directly.
- If this is your first language: don't skip ahead. `main()`, functions and compilation are the base for everything later (classes, templates, memory).

---

## **2. What is C++**

### **Definition**

- C++ is a **compiled**, **statically-typed**, **multi-paradigm** language. Three big words, so here is each one in plain terms:
- **Compiled**: a tool called a compiler turns your source code into machine code *before* you run it. Python works differently: it reads and runs your code line by line while the program is running.
- **Statically-typed**: every variable, parameter and return value has a type that is fixed when you write the code. The compiler catches type mistakes before the program ever runs.
- **Multi-paradigm**: you can write in several styles (step-by-step procedures, objects, generic code, functional style). You are not stuck with one.

### **Where C++ is used**

- Operating systems, drivers, and code inside devices (embedded). It gives low-level control without wasting speed.
- Game engines, real-time graphics, simulations (Unreal Engine, most big game studios).
- Fast backends, databases, compilers, search engines.
- Trading and finance, scientific computing, web browsers (Chrome, Firefox), high-frequency trading.
- ML inference runtimes. The C++ track in `cpp_inference_roadmap.md` continues from here.

### **Hello, C++ (using `std::`, which is the right default)**

```cpp
// hello.cpp
#include <iostream>

int main() {
    std::cout << "Hello, C++\n";
    return 0;
}
```

```bash
# Build with g++ 14.2.0 (MinGW64 / MSYS2 confirmed)
g++ -std=c++17 -Wall -Wextra hello.cpp -o hello.exe
./hello.exe
```

```text
Hello, C++
```

### **What each line does**

- `#include <iostream>`: brings in the input/output tools (`std::cout`, `std::cin`). Without this line, the compiler has never heard of `std::cout`.
- `int main()`: where the program starts. The operating system calls this function to run your program.
- `std::cout << "..."`: `cout` means "character output." The `<<` sends the text into it. `std` is the namespace (a named box) that `cout` lives in. More on this in Section 9.
- `return 0;`: tells the OS "I finished fine." Any non-zero number means "something went wrong."

### **Names of the tools that build your program**

- **Preprocessor**: does simple text find-and-replace jobs (`#include`, `#define`, `#ifdef`). Runs first.
- **Compiler**: turns the preprocessed C++ into assembly / object code.
- **Assembler**: turns assembly into an object file (`.o` / `.obj`).
- **Linker**: joins object files and libraries together, matches up names, and produces the final executable.
- **Standard library**: comes with your compiler (`libstdc++` for GCC). It gives you `std::cout`, `std::string`, containers, algorithms, threads, filesystem, and more.

---

## **3. How C++ Relates to C**

### **C is mostly a subset of C++**

Most valid C code also compiles as C++. There are differences, but in daily work they are small.

```cpp
// Valid in C90, still valid in C++17
#include <stdio.h>
int main(void) {
    printf("ok\n");
    return 0;
}
```

### **Example: C code that fails to compile as C++**

```c
// bad_as_cpp.c
#include <stdlib.h>
int main(void) {
    int* p = malloc(4 * sizeof(int));   // C: implicit void* -> int* OK
    for (int i = 0; i < 4; ++i) p[i] = i;
    free(p);
    return 0;
}
```

```bash
g++ bad_as_cpp.c -o bad          # ERROR: cannot initialize 'int*' with 'void*'
```

**Fix:** add a cast, `(int*)malloc(...)`, or use `new int[4]{0,1,2,3};` and `delete[] p;`.

### **Same logic, C style vs C++ style**

```cpp
// c_style.cpp — works, but not the normal C++ way
#include <cstdio>
int main() {
    int arr[3] = {1, 2, 3};
    for (int i = 0; i < 3; i++) printf("%d\n", arr[i]);
    return 0;
}
```

```cpp
// cpp_style.cpp — the C++ way: std::array + range-based for
#include <array>
#include <iostream>

int main() {
    std::array<int, 3> arr = {1, 2, 3};
    for (int v : arr) std::cout << v << "\n";
    return 0;
}
```

### **What C++ added over the years (short list)**

- C++98/03: classes, templates, STL containers and algorithms, exceptions, RTTI.
- C++11: move semantics, `auto`, range-`for`, lambdas, `nullptr`, smart pointers, `constexpr`, threads, `std::array` / `std::unordered_map`.
- C++14: generic lambdas, `std::make_unique`.
- C++17: `std::optional`, `std::variant`, `std::string_view`, structured bindings, `if constexpr`, `inline` variables, filesystem.
- Newer versions (C++20, 23, 26) add more. We'll cover them together at the end, after the core material. For now, stick to C++11/14/17.

---

## **4. How a C++ Program Is Laid Out**

### **The parts, top to bottom**

A normal C++ source file has these parts, in this order:

- **Preprocessor lines**: `#include`, `#define`, `#ifdef`. These run before the compiler does.
- **Using lines**: bring names from a namespace into scope. Usually left out of headers.
- **Global declarations**: constants, type aliases, function prototypes, class/struct declarations.
- **Function definitions**: including `main`, where the program starts.

```cpp
// anatomy.cpp
#include <iostream>                  // 1. Preprocessor directive
#include <string>

constexpr double PI = 3.14159;       // 2. Global constant
using Meters = double;               // 3. Type alias

int area(int radius);                // 4. Function prototype (declaration)

int main() {                         // 5. Entry point
    Meters r = 5.0;
    std::cout << "area = " << area(static_cast<int>(r)) << "\n";
    return 0;
}

int area(int radius) {               // 6. Function definition
    return static_cast<int>(PI * radius * radius);
}
```

### **Rules for `main`**

- `main` is where the program starts. Every C++ program has exactly one.
- It must return `int`. That number becomes the exit code (0 = success, anything else = error).
- Two allowed forms: `int main()` and `int main(int argc, char* argv[])`.
- If you leave out `return 0;` in `main`, the compiler adds it for you. This is the one function where a missing return is fine.
- Other functions can return `void`. `main` cannot.

```cpp
// Two legal main signatures you will actually use
int main() { return 0; }

int main(int argc, char* argv[]) {
    // argc = number of command-line arguments (including program name)
    // argv = array of those arguments as C-strings
    std::cout << "Program name: " << argv[0] << "\n";
    std::cout << "Arg count: " << argc << "\n";
    return 0;
}
```

### **Statements, expressions and blocks**

- A **statement** does something and ends with `;`.
- An **expression** produces a value (a literal, a variable, a function call, a chain of operators).
- A **block** is a group of statements inside `{ }`. Each block has its own scope, meaning names declared inside it are not visible outside.

```cpp
int main() {
    int x = 10;            // declaration statement
    x = x + 1;             // expression statement
    {                      // nested block — own scope
        int y = 20;
        std::cout << y;
    }
    // y is not visible here — this line would fail to compile:
    // std::cout << y;
    return 0;
}
```

### **Punctuation that matters**

- `;` ends a statement. Required.
- `{ }` groups statements into a block, a function body or a class body.
- `()` are used for function calls, parameter lists and grouping expressions.
- `,` separates items in a list. It is also an operator with very low priority.

---

## **5. Comments**

### **Single-line `//`**

```cpp
#include <iostream>

int main() {
    int x = 10;    // simple trailing comment
    // whole line comment
    std::cout << x; // can also put on same line
    return 0;
}
```

### **Block `/* ... */`**

```cpp
#include <iostream>

/*
   Block comment.
   Can span multiple lines.
*/
int main() {
    int x = 10; /* can also be inline */
    std::cout << x << "\n";
    return 0;
}
```

### **Rules and traps**

- Block comments **do not nest** in C or C++. The first `*/` ends the comment, no matter what.

```cpp
/* outer /* inner */ still outer */     // ERROR: the first */ ends the comment
```

- Use `//` most of the time. Keep `/* */` for switching off a chunk of code for a while.

```cpp
// Temporarily disable code:
/*
int broken() {
    return 0;
}
*/
```

### **Documentation comments**

- `///` and `/** */` are picked up by Doxygen and by most editors as documentation.
- Put them right above the thing they describe.

```cpp
/**
 * Computes the area of a circle.
 * @param radius Non-negative radius.
 * @return The area, rounded to an int.
 */
int area(int radius);
```

### **Comments and the preprocessor**

`#if 0` ... `#endif` is a safer way to switch off code than `/* */`. It works even if the code inside already contains `*/` or other comments.

```cpp
#if 0
int broken() {
    /* this would confuse a block comment */
    return 0;
}
#endif
```

---

## **6. Function Basics**

A function is a named piece of code that takes inputs (parameters) and gives back a value (or nothing, if it's `void`).

### **Declaration vs definition**

- A **declaration** tells the compiler what the function looks like: its name, return type and parameter types. It ends with `;`.
- A **definition** is the declaration plus the body. Each function must have exactly one definition in the whole program. This is called the one-definition rule (ODR).

```cpp
// declaration
int add(int a, int b);

// definition
int add(int a, int b) {
    return a + b;
}
```

### **Calling a function**

```cpp
#include <iostream>

int add(int a, int b);    // declaration

int main() {
    int s = add(2, 3);
    std::cout << s << "\n";   // 5
    return 0;
}

int add(int a, int b) {   // definition
    return a + b;
}
```

### **Parameters and return values**

- Parameters are local variables. They start out with the values the caller passed in.
- You must state a return type. Use `void` when nothing is returned.
- If a non-void function reaches the end without a `return`, the behavior is undefined (UB), meaning anything can happen. `main` is the only exception; it returns 0 automatically.

```cpp
void log_msg(const char* s) {
    if (!s) return;          // early return ok
    std::cerr << s << "\n";
}
```

### **Function overloading**

- You can reuse the same function name with different parameter lists. The compiler picks the right one based on the arguments you pass.
- A different return type alone is not enough to make two overloads.

```cpp
#include <iostream>
#include <string>

void print(int x)                  { std::cout << "int: "    << x   << "\n"; }
void print(double x)               { std::cout << "double: " << x   << "\n"; }
void print(bool x)                 { std::cout << "bool: "   << x   << "\n"; }
void print(const std::string& s)   { std::cout << "str: "    << s   << "\n"; }

int main() {
    print(7);
    print(3.14);
    print(true);
    print(std::string("Ada"));
    // print("Ada");   // Careful: a string literal is const char*, not std::string.
                        // With the four overloads above, this quietly calls print(bool),
                        // because a pointer converts to bool more easily than it
                        // converts to std::string. It compiles, but gives the wrong result.
    return 0;
}
```

### **Default arguments**

- Parameters that have default values must come **after** the ones that don't.
- The compiler fills in the defaults at the place where you call the function.

```cpp
#include <iostream>
#include <string>

void greet(const std::string& name, const std::string& prefix = "Hello") {
    std::cout << prefix << ", " << name << "!\n";
}

int main() {
    greet("Lin");                 // Hello, Lin!
    greet("Lin", "Hi");           // Hi, Lin!
    return 0;
}
```

### **Pass-by-value vs pass-by-reference vs pass-by-pointer**

This is the most important idea in this file for a beginner. Get this right and a lot of "confusing" C++ behavior stops being confusing.

| Style | Does caller see the change? | Is the argument copied? | Use it when |
|-------|-----------------------------|-------------------------|-------------|
| `void f(T x)` | No | Yes | Small types (`int`, `double`, pointer) |
| `void f(T& x)` | Yes | No | The function must change the caller's object |
| `void f(const T& x)` | No | No | Big object that you only read |
| `void f(T* x)` | Yes (through the pointer) | No (only the pointer is copied) | Optional input, C interop, can be null |

```cpp
#include <iostream>
#include <string>

void by_value(int x)              { x = 0; }     // does NOT modify caller
void by_ref(int& x)               { x = 0; }     // DOES modify caller
void by_const_ref(const std::string& s) { std::cout << "read: " << s << "\n"; }
void by_ptr(int* x)               { if (x) *x = 0; }

int main() {
    int a = 1, b = 1, c = 1;
    by_value(a);
    by_ref(b);
    by_ptr(&c);
    std::cout << a << " " << b << " " << c << "\n";  // 1 0 0
    by_const_ref("big payload");   // temporary bound to const ref
    return 0;
}
```

### **Walk-through: why `by_value` doesn't change `a`**

```cpp
#include <iostream>

void increment_wrong(int x) {
    x = x + 1;          // this changes the LOCAL COPY only
}

void increment_right(int& x) {
    x = x + 1;           // this changes the CALLER's variable
}

int main() {
    int n = 5;
    increment_wrong(n);
    std::cout << n << "\n";   // still 5 — the copy was thrown away
    increment_right(n);
    std::cout << n << "\n";   // 6 — reference points at the real variable
    return 0;
}
```

Think of it like this: pass-by-value hands the function a photocopy of your paper. It can scribble on the copy all it wants, and your original stays clean. A reference hands over the original.

### **`[[nodiscard]]` and `noexcept`**

- `[[nodiscard]]`: the compiler warns you if you call the function and ignore what it returns.
- `noexcept`: promises the function will never throw an exception. This lets the compiler optimize better.

```cpp
#include <iostream>

[[nodiscard]] int compute(int x) noexcept { return x * 2; }

int main() {
    std::cout << compute(21) << "\n";
    // compute(5);    // warning: ignoring return value of 'compute'
    return 0;
}
```

### **`static` variables inside a function**

A `static` local variable keeps its value between calls. It is set up only once, the first time the function runs.

```cpp
#include <iostream>

int counter() {
    static int n = 0;       // initialized once
    return ++n;
}

int main() {
    std::cout << counter() << "\n";   // 1
    std::cout << counter() << "\n";   // 2
    std::cout << counter() << "\n";   // 3
    return 0;
}
```

---

## **7. Splitting Code Into Header and Source Files**

Real programs are split across many files. The usual habit:

- `.h` / `.hpp` (header): holds **declarations**: prototypes, class/struct definitions, templates, `inline` functions, `constexpr` variables.
- `.cpp` / `.cc` / `.cxx` (source): holds **definitions**: function bodies, non-inline member functions, file-level statics.

### **Why split?**

- Faster builds: if you edit one `.cpp`, only that file needs to be compiled again.
- Sharing: many `.cpp` files can include the same header.
- Hiding details: the header shows what's available, the source hides how it works.

### **Basic example: math utilities**

```cpp
// math_utils.h
#pragma once

int add(int a, int b);
int sub(int a, int b);
int mul(int a, int b);
int div_int(int a, int b);
```

```cpp
// math_utils.cpp
#include "math_utils.h"

int add(int a, int b)     { return a + b; }
int sub(int a, int b)     { return a - b; }
int mul(int a, int b)     { return a * b; }
int div_int(int a, int b) { return a / b; }
```

```cpp
// main.cpp
#include <iostream>
#include "math_utils.h"

int main() {
    std::cout << add(2, 3)     << "\n";  // 5
    std::cout << sub(10, 4)    << "\n";  // 6
    std::cout << mul(3, 7)     << "\n";  // 21
    std::cout << div_int(20, 6)<< "\n";  // 3
    return 0;
}
```

```bash
g++ -std=c++17 -Wall -Wextra main.cpp math_utils.cpp -o app
./app
```

### **What goes wrong without `#pragma once`**

Say `math_utils.h` gets included twice into the same `.cpp` (for example, two different headers both include it). The compiler then sees the same declarations twice and fails with a "redefinition" error. `#pragma once` (or the older `#ifndef` / `#define` guards) tells the preprocessor: "paste this file in only once."

```cpp
// The old-style equivalent of #pragma once, if your toolchain lacks it:
#ifndef MATH_UTILS_H
#define MATH_UTILS_H

int add(int a, int b);

#endif // MATH_UTILS_H
```

### **Next step: `inline` functions in a header**

If you put a normal function definition in a header and include it from two `.cpp` files, the linker complains about multiple definitions. Mark the function `inline` and that problem goes away.

```cpp
// math_utils.h
#pragma once

inline int add(int a, int b)     { return a + b; }
inline int sub(int a, int b)     { return a - b; }
inline int mul(int a, int b)     { return a * b; }
inline int div_int(int a, int b) { return a / b; }
```

```cpp
// main.cpp
#include <iostream>
#include "math_utils.h"

int main() {
    std::cout << add(2, 3) << "\n";
    return 0;
}
```

```bash
g++ -std=c++17 -Wall -Wextra main.cpp -o app
./app
```

### **Advanced: `inline` variables (C++17)**

Since C++17 you can define a global variable in a header using `inline`. Every file that includes the header then shares the same single object.

```cpp
// config.h
#pragma once
#include <string>

inline constexpr int         MAX_CONN  = 100;
inline const std::string      APP_NAME = "roadmap";
```

```cpp
// main.cpp
#include <iostream>
#include "config.h"

int main() {
    std::cout << APP_NAME << " max=" << MAX_CONN << "\n";
    return 0;
}
```

### **Good habits for headers**

- Always use include guards or `#pragma once`.
- Never put `using namespace std;` in a header (Section 9 explains why it hurts more there than in a `.cpp`).
- Forward-declare when you can, instead of including the full header.
- Templates, `inline` functions and `constexpr` variables belong in headers, because the compiler needs to see their full definitions.

---

## **8. Compiling and Linking**

### **The pipeline**

```text
   .cpp + headers
        |
        |  (preprocessor: #include, #define, #ifdef)
        v
   translation unit (one .cpp after preprocessing)
        |
        |  (compiler)
        v
   object file (.o / .obj)   <-- contains machine code + unresolved symbols
        |
        |  (linker)
        v
   executable (or library)
```

### **Step by step: what the compiler does**

```bash
# 1. Preprocess only
g++ -E main.cpp -o main.i

# 2. Compile to assembly
g++ -S main.cpp -o main.s

# 3. Assemble to object
g++ -c main.cpp -o main.o

# 4. Compile both, then link
g++ -c main.cpp -o main.o
g++ -c math_utils.cpp -o math_utils.o
g++ main.o math_utils.o -o app

# Or in one shot
g++ main.cpp math_utils.cpp -o app
```

### **Translation unit (TU)**

A TU is one `.cpp` file plus every header it includes (directly or through other headers), after the preprocessor is done. Each TU becomes one object file.

### **Object file basics**

```bash
# Inspect symbols in an object file
g++ -c math_utils.cpp -o math_utils.o
nm math_utils.o           # lists defined and undefined symbols
```

Sample output:

```text
0000000000000000 T _Z3addii
0000000000000014 T _Z3subii
                 U __cxa_atexit
```

- `T`: a symbol (function) that is defined in this file.
- `U`: an undefined symbol. The linker will look for it elsewhere.
- `_Z3addii`: the "mangled" name for `add(int, int)`. The compiler scrambles names like this so overloads can be told apart. Linker error messages usually turn it back into readable form for you.

### **What the linker does**

- Finds a definition (`T`) for each `U` symbol, in another object file or in a library.
- Reports "undefined reference" if something is used but never defined.
- Reports "multiple definition" if a non-`inline` symbol is defined twice.
- Produces the final executable (or a `.a` / `.so` / `.dll` library).

### **Common linker errors and what they mean**

```text
undefined reference to `foo()'
collect2: error: ld returned 1 exit status
```

- You declared `foo()` (probably in a header) but never wrote its body. Either add the definition, or link in the object file or library that has it.

```text
multiple definition of `bar'
```

- A non-`inline` symbol is defined in more than one TU. Fix it by marking it `inline`, or by keeping the definition in only one `.cpp`, or by declaring it `extern` in the header and defining it once.

### **A realistic build: compile each file, then link**

```bash
# One .cpp -> one .o, then link
g++ -std=c++17 -Wall -Wextra -O2 -c main.cpp        -o main.o
g++ -std=c++17 -Wall -Wextra -O2 -c math_utils.cpp  -o math_utils.o
g++ main.o math_utils.o -o app
./app
```

```cmake
# Equivalent CMakeLists.txt (later topic)
cmake_minimum_required(VERSION 3.16)
project(app LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(app main.cpp math_utils.cpp)
```

```bash
cmake -S . -B build
cmake --build build
./build/app
```

### **Optimization levels**

| Flag | What it does |
|------|--------------|
| `-O0` | No optimization (the default). Compiles fastest, runs slowest. Use it for debugging. |
| `-O1` | Basic optimization. |
| `-O2` | Standard choice for release builds. Safe. |
| `-O3` | Aggressive: inlining, vectorization, loop tricks. Can make the binary bigger. |
| `-Os` | Optimize for small size. |
| `-Og` | Optimize while keeping debugging pleasant (GCC 4.8+). |
| `-march=native` | Use special instructions of the CPU you build on (AVX, SSE). |

### **Warnings worth turning on**

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wold-style-cast \
    main.cpp math_utils.cpp -o app
```

- `-Wall`, `-Wextra`: the common warnings. Keep them always on.
- `-Wpedantic`: warns when you use non-standard compiler extensions.
- `-Wshadow`: warns when a local variable hides another variable with the same name.
- `-Wconversion`: warns about implicit conversions that may lose data.
- `-Wold-style-cast`: flags C-style casts (use `static_cast` and friends instead).
- In CI, turn warnings into errors with `-Werror`.

### **Static vs dynamic libraries (quick preview)**

- Static library (`.a` / `.lib`): joined into your executable at build time. The code is copied in.
- Dynamic library (`.so` / `.dll`): loaded when the program runs. Executables are smaller and updates are easier, but deploying gets more complicated.

```bash
# Build a static library
g++ -c math_utils.cpp -o math_utils.o
ar rcs libmath_utils.a math_utils.o

# Link against it
g++ main.cpp -L. -lmath_utils -o app
```

---

## **9. `using namespace std;` and Why We Skip It**

### **What it does**

- `std::cout`, `std::string`, `std::vector` and the rest all live inside a namespace called `std`. A namespace is a named box that stops the standard library's names from clashing with yours.
- `using namespace std;` says to the compiler: "let me use everything in `std` without typing `std::`", for the rest of that scope.

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "no std:: prefix needed here\n";
    return 0;
}
```

### **Why these notes always write `std::`**

- `std` has thousands of names (`count`, `sort`, `distance`, `max`, `min`, `move`, `data`, `swap`...). If you name your own variable or function one of these while `using namespace std;` is on, you can hit name clashes.

```cpp
#include <algorithm>
#include <iostream>
using namespace std;

int count = 5;              // your global 'count' now competes with std::count

int main() {
    cout << count << "\n";  // ERROR: ambiguous — is it ::count or std::count?
    return 0;
}
```

- In a header file it is even worse. `using namespace std;` leaks into every `.cpp` that includes that header, including ones that never asked for it. That is why almost every style guide bans it in headers.
- As your project grows, it gets hard to tell where a name came from. Writing `std::` is free documentation.

### **When people still use it**

- Competitive programming and tiny one-file scratch programs (around 30 lines) that nobody will reuse.
- Even then, there is a safer middle option: pull in only the specific names you need.

```cpp
#include <iostream>
#include <string>

using std::cout;     // only this name is exposed, no wildcard risk
using std::string;

int main() {
    string name = "Aria";
    cout << "Hello, " << name << "\n";
    return 0;
}
```

### **The rule we follow**

- Write `std::` explicitly in every example, every project, every topic folder. It's one extra word per line, and it removes a whole group of bugs before they can happen.

---

## **10. Practice Problems**

- [ ] **Build a Hello program** three ways: single file (one g++ command), compile to an object file then link, and with CMake. Compare the files each one produces.
- [ ] **Type sizes**: write a program that prints `sizeof(bool)`, `sizeof(char)`, `sizeof(wchar_t)`, `sizeof(int)`, `sizeof(long)`, `sizeof(long long)`, `sizeof(float)`, `sizeof(double)`, `sizeof(long double)`, `sizeof(std::string)`, `sizeof(void*)`. Build it on your machine and write down the values.
- [ ] **Comment playground**: put a `/*` inside a `/* ... */` block and see the error. Then fix it using `#if 0`.
- [ ] **Overload `print`**: write four overloads: `print(int)`, `print(double)`, `print(const std::string&)`, `print(bool)`. Test that `print(0)`, `print(0.0)` and `print("hi")` pick the overloads you expect. (Hint: `print("hi")` is a `const char*`, not a `std::string`. Fix it by adding a `const char*` overload, or by calling `print(std::string("hi"))`.)
- [ ] **Default arguments**: write `make_window(width, height, title = "App", fullscreen = false)` that prints its parameters. Call it with 1, 2, 3 and 4 arguments.
- [ ] **Pass-by-value vs reference**: write a `swap` for `int` and for `std::string` that takes references. Check that the caller sees the change.
- [ ] **Reference confusion drill**: write `increment_wrong(int x)` and `increment_right(int& x)` yourself from scratch (don't copy this file). Predict the output on paper, then compile and check.
- [ ] **Separate compilation**: split a `vector3` struct (3 doubles, length, dot, cross) into `vec3.h` and `vec3.cpp`. Compile each with `g++ -c`, then link. Then move `length` into the header as `inline` and confirm it still builds.
- [ ] **Include guard drill**: remove `#pragma once` from a header, include it twice in one `.cpp` (once directly, once through a second header), and read the "redefinition" error. Then fix it.
- [ ] **Preprocessor tour**: run `g++ -E file.cpp | head -50` on a small program and read what the preprocessor produced. Find the spot where `<iostream>` got pasted in.
- [ ] **Symbol inspection**: build a small multi-file project and run `nm` on each `.o`. Find a `T` symbol in one file and the matching `U` reference in another.
- [ ] **Linker error drill**: declare a function in a header, forget to define it, and build. Read the error. Then add the definition and confirm it links.
- [ ] **`using namespace std;` clash drill**: write a program that declares a global `int count` and also calls `std::count()` from `<algorithm>`, with `using namespace std;` on. Look at the ambiguity error, then fix it by removing `using namespace std;` and writing `std::` on the library calls.
- [ ] **CMake basics**: turn your multi-file project into a `CMakeLists.txt` that builds an executable. Build it from an empty `build/` folder.
- [ ] **Optimization comparison**: write a tight loop (for example, sum 1 to 1e9). Time it with `-O0`, `-O2`, `-O3` and `-O3 -march=native`. Write down the time for each.
- [ ] **Warning tour**: compile with `-Wall -Wextra -Wpedantic -Wshadow` and fix every warning in your existing code.