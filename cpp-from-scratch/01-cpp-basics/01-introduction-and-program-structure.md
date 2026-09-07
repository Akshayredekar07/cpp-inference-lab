# **Introduction & Program Structure**

## **Table of Contents**

1. Why learn C++ (and why now)
2. What is C++
3. How C++ relates to C
4. Structure of a C++ program
5. Comments
6. Function basics
7. Header and source file separation
8. Compilation and linking
9. `using namespace std;` — what it does and why we avoid it
10. Practice problems

---

## **1. Why Learn C++ (and Why Now)**

### **Why this matters before you touch syntax**

- Every other language you've used (Python, JS) hides memory management and compilation from you. C++ does not — you will see *how a program actually becomes an executable*. That understanding transfers to debugging, performance, and reading any lower-level system later.
- C++ is not "harder Python." It is a different mental model: you decide types, memory, and lifetimes explicitly. The payoff is speed and control; the cost is more upfront rules.
- As a beginner, the goal in this file is NOT to memorize every rule. It's to get a working mental model of: compiler vs linker, declaration vs definition, and pass-by-value vs pass-by-reference. Everything else builds on these three.

### **What "new" means when learning C++**

- If you know C, Python, or JS: the concepts (variables, functions, loops) are familiar — but C++ enforces static types and gives you direct memory control, which those languages don't.
- If you're a first-time programmer: don't skip ahead. `main()`, functions, and compilation are the foundation every later topic (classes, templates, memory management) depends on.

---

## **2. What is C++**

### **Definition**

- C++ is a compiled, statically-typed, multi-paradigm programming language.
- "Compiled" — the source is translated to machine code by a compiler before you run it. (Contrast: Python is interpreted line-by-line at runtime.)
- "Statically-typed" — every variable, parameter, and return value has a type known at compile time. The compiler catches type errors before the program ever runs.
- "Multi-paradigm" — supports procedural, object-oriented, generic, and functional styles. You are not forced into one way of structuring code.

### **Where C++ is used**

- Operating systems, drivers, embedded firmware (low-level control + zero-cost abstractions).
- Game engines, real-time graphics, simulation (Unreal Engine, most AAA studios).
- High-performance backends, databases, compilers, search engines.
- Quantitative finance, scientific computing, browser engines (Chrome/Firefox), HFT systems.
- Inference / ML runtimes (the C++ track in `cpp_inference_roadmap.md` continues from here).

### **Hello, C++ (with `std::` — the correct default)**

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

### **What each piece means, line by line**

- `#include <iostream>` — pulls in declarations for input/output (`std::cout`, `std::cin`). Without this line, `std::cout` does not exist as far as the compiler knows.
- `int main()` — the entry point. The operating system calls this function to start your program.
- `std::cout << "..."` — `cout` is "character output," the `<<` operator sends the string to it. `std` is the namespace `cout` lives in (see Section 9).
- `return 0;` — tells the OS the program finished successfully. Non-zero means "something went wrong."

### **Toolchain components you should know the names of**

- **Preprocessor** — text substitution (`#include`, `#define`, `#ifdef`). Runs first.
- **Compiler** — translates preprocessed C++ to assembly / object code.
- **Assembler** — turns assembly into an object file (`.o` / `.obj`).
- **Linker** — combines object files and libraries, resolves symbols, produces an executable.
- **Standard library** — ships with the toolchain (`libstdc++` for GCC). Provides `std::cout`, `std::string`, containers, algorithms, threads, filesystem, etc.

---

## **3. How C++ Relates to C**

### **C is mostly a subset of C++**

Most valid C compiles as C++. The differences are real but small in practice.

```cpp
// Valid in C90, still valid in C++17
#include <stdio.h>
int main(void) {
    printf("ok\n");
    return 0;
}
```

### **Practical: a C file that fails to compile as C++**

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

**Fix:** cast (`(int*)malloc(...)`) or use `new int[4]{0,1,2,3};` and `delete[] p;`.

### **Beginner example: same logic, C style vs C++ style**

```cpp
// c_style.cpp — works, but not idiomatic C++
#include <cstdio>
int main() {
    int arr[3] = {1, 2, 3};
    for (int i = 0; i < 3; i++) printf("%d\n", arr[i]);
    return 0;
}
```

```cpp
// cpp_style.cpp — idiomatic: use std::array + range-based for
#include <array>
#include <iostream>

int main() {
    std::array<int, 3> arr = {1, 2, 3};
    for (int v : arr) std::cout << v << "\n";
    return 0;
}
```

### **What's new in C++ (the short list)**

- C++98/03 — classes, templates, STL containers/algorithms, exceptions, RTTI.
- C++11 — move semantics, `auto`, range-`for`, lambdas, `nullptr`, smart pointers, `constexpr`, threads, `std::array`/`std::unordered_map`.
- C++14 — generic lambdas, `std::make_unique`.
- C++17 — `std::optional`, `std::variant`, `std::string_view`, structured bindings, `if constexpr`, `inline` variables, filesystem.
- C++20 — concepts, ranges, coroutines, modules, `consteval`/`constinit`, three-way comparison `<=>`, `std::span`.
- C++23 — `std::expected`, `std::flat_map`, deducing `this`, `if consteval`.
- C++26 — contracts, reflection, pattern matching (in progress).

---

## **4. Structure of a C++ Program**

### **Anatomy of a C++ program**

A typical C++ source file has these parts, top to bottom:

- **Preprocessor directives** — `#include`, `#define`, `#ifdef`. Run before the compiler.
- **Using declarations / directives** — bring names from a namespace into scope (often omitted in headers).
- **Global declarations** — constants, type aliases, function prototypes, class/struct declarations.
- **Function definitions** — including `main`. `main` is the entry point.

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

### **The `main` function rules**

- `main` is the entry point called by the runtime. Every C++ program has exactly one `main`.
- Return type must be `int`. The value becomes the process exit code (0 = success, non-zero = error).
- Two legal forms: `int main()` and `int main(int argc, char* argv[])`.
- If you omit `return 0;` in `main`, the compiler inserts it for you (special case — this is the ONE function in C++ where a missing return is not an error).
- Other functions can return `void`; `main` cannot.

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

### **Statements and expressions**

- A **statement** performs an action and ends with `;`.
- An **expression** produces a value (a literal, a variable, a function call, an operator chain).
- A **block** is a sequence of statements inside `{ }`. Blocks introduce scope.

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

- `;` ends a statement (REQUIRED).
- `{ }` groups statements into a block / function / class body.
- `()` are for function calls, parameter lists, and grouping expressions.
- `,` separates items in lists; it's also a low-precedence operator.

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

### **Important rules and pitfalls**

- Block comments **do not nest** in C or C++. The first `*/` ends the comment.

```cpp
/* outer /* inner */ still outer */     // ERROR: the first */ ends the comment
```

- Use `//` for most cases. Reserve `/* */` for temporarily disabling code blocks.

```cpp
// Temporarily disable code:
/*
int broken() {
    return 0;
}
*/
```

### **Documentation comments**

- `///` and `/** */` are recognized by Doxygen, Standardese, and most editors as documentation comments.
- They sit immediately above the declaration they document.

```cpp
/**
 * Computes the area of a circle.
 * @param radius Non-negative radius.
 * @return The area, rounded to an int.
 */
int area(int radius);
```

### **Comments and the preprocessor**

`#if 0` / `#endif` is a robust alternative to `/* */` for disabling code, because it can hold code containing `*/` and nested comments.

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

A function is a named, parameterized block of code that returns a value (or `void`).

### **Declaration vs definition**

- A **declaration** tells the compiler the function's signature: name, return type, parameter types. Ends with `;`.
- A **definition** is a declaration plus the body. Exactly one definition must exist for each function in the program (the one-definition rule, ODR).

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

- Parameters are local variables initialized by the caller's arguments.
- The return type must be specified; use `void` for "no return value".
- A non-void function that falls off the end without `return` is undefined behavior (UB) — except `main`, which returns 0 implicitly.

```cpp
void log_msg(const char* s) {
    if (!s) return;          // early return ok
    std::cerr << s << "\n";
}
```

### **Function overloading**

- Same name, different parameter list. The compiler picks the right one by argument types.
- Return type alone doesn't distinguish overloads.

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
                        // Without a const char* overload, this either fails to compile
                        // or silently matches the wrong overload depending on your compiler.
    return 0;
}
```

### **Default arguments**

- Parameters with default values must come **after** parameters without defaults.
- Default values are filled in by the compiler at the call site.

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

This is the single most important beginner concept in this file. Get this right and half of C++'s "confusing" behavior stops being confusing.

| Style | Caller sees the change? | Copies the argument? | Use when |
|-------|--------------------------|----------------------|----------|
| `void f(T x)` | No | Yes | Small types (`int`, `double`, pointer) |
| `void f(T& x)` | Yes | No | Callee must mutate the caller's object |
| `void f(const T& x)` | No | No | Large object you only read |
| `void f(T* x)` | Yes (via dereference) | No (pointer copies) | Optional input, C interop, nullable |

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

### **Beginner walk-through: why `by_value` doesn't change `a`**

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

### **`[[nodiscard]]`, `noexcept`, attributes**

- `[[nodiscard]]` — the compiler warns if the caller ignores the return value.
- `noexcept` — the function promises not to throw; enables some compiler optimizations.

```cpp
#include <iostream>

[[nodiscard]] int compute(int x) noexcept { return x * 2; }

int main() {
    std::cout << compute(21) << "\n";
    // compute(5);    // warning: ignoring return value of 'compute'
    return 0;
}
```

### **Function-local `static`**

A `static` local variable persists across calls and is initialized only on the first call.

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

## **7. Header and Source File Separation**

Real programs split into multiple files. The convention:

- `.h` / `.hpp` (header) — **declarations**: prototypes, class/struct definitions, templates, `inline` functions, `constexpr` variables.
- `.cpp` / `.cc` / `.cxx` (source) — **definitions**: function bodies, non-inline member definitions, file-scope statics.

### **Why split?**

- Compilation speed: edit one `.cpp` and only that file recompiles.
- Sharing: multiple `.cpp` files can include the same header.
- Encapsulation: header exposes interface, source hides implementation.

### **Basic split — math utilities**

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

### **What happens if you forget `#pragma once`**

If `math_utils.h` gets `#include`d twice into the same `.cpp` (e.g., through two different headers that both include it), the compiler sees the declarations twice and errors out with "redefinition." `#pragma once` (or classic `#ifndef`/`#define` guards) tells the preprocessor "only paste this file's contents in once per translation unit."

```cpp
// The old-style equivalent of #pragma once, if your toolchain lacks it:
#ifndef MATH_UTILS_H
#define MATH_UTILS_H

int add(int a, int b);

#endif // MATH_UTILS_H
```

### **Intermediate — `inline` definitions in a header**

If you put a non-`inline` function definition in a header and include it in two `.cpp` files, you get a linker error (multiple definitions). Mark it `inline` to allow that.

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

### **Advanced — `inline` variables (C++17)**

C++17 lets you define a global variable in a header (with `inline`) and every translation unit that includes the header sees the same object.

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

### **Best practices for headers**

- Always use include guards or `#pragma once`.
- Never put `using namespace std;` in a header (see Section 9 for why this is worse in headers than in `.cpp` files).
- Forward-declare what you can instead of including the full header.
- Put templates, `inline` functions, and `constexpr` variables in headers (their definitions must be visible to the compiler).

---

## **8. Compilation and Linking**

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

### **Step-by-step: what the compiler actually does**

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

A TU is one `.cpp` file plus every header it (transitively) `#include`s, after preprocessing. Each TU compiles to one object file.

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

- `T` — defined text (code) symbol.
- `U` — undefined (will be resolved by the linker).
- `_Z3addii` — name-mangled version of `add(int, int)`. The linker demangles for you in errors.

### **What the linker does**

- Resolves `U` symbols by finding their `T` definition in another object file or library.
- Reports undefined references if a symbol is used but never defined.
- Reports multiple definitions if a non-`inline` symbol is defined twice.
- Produces the final executable (or `.a` / `.so` / `.dll` library).

### **Common linker errors and how to read them**

```text
undefined reference to `foo()'
collect2: error: ld returned 1 exit status
```

- You declared `foo()` (probably via a header) but never defined it. Either add the definition, or link the object/library that defines it.

```text
multiple definition of `bar'
```

- A non-`inline` symbol is defined in more than one TU. Mark it `inline`, or move the definition to a single `.cpp`, or declare it `extern` in the header and define it once.

### **Building with separate compilation (the realistic workflow)**

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

### **Build with optimization levels**

| Flag | What it does |
|------|--------------|
| `-O0` | No optimization (default). Fastest to compile, slowest to run. Use for debugging. |
| `-O1` | Basic optimization. |
| `-O2` | Standard release optimization. Safe. |
| `-O3` | Aggressive: inlining, vectorization, loop transforms. May increase binary size. |
| `-Os` | Optimize for size. |
| `-Og` | Optimize for debugging experience (GCC 4.8+). |
| `-march=native` | Enable CPU-specific instructions (AVX, SSE) on the build host. |

### **Useful warnings to turn on**

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wold-style-cast \
    main.cpp math_utils.cpp -o app
```

- `-Wall`, `-Wextra` — common warnings. Always on.
- `-Wpedantic` — warn about non-standard extensions.
- `-Wshadow` — warn when a local shadows another.
- `-Wconversion` — warn about implicit narrowing conversions.
- `-Wold-style-cast` — flag C-style casts (use `static_cast` etc.).
- Treat warnings as errors in CI: `-Werror`.

### **Static vs dynamic libraries (preview)**

- Static library (`.a` / `.lib`) — linked at build time. Code is copied into the executable.
- Dynamic library (`.so` / `.dll`) — loaded at runtime. Smaller executables, easier to update, but introduces deployment complexity.

```bash
# Build a static library
g++ -c math_utils.cpp -o math_utils.o
ar rcs libmath_utils.a math_utils.o

# Link against it
g++ main.cpp -L. -lmath_utils -o app
```

---

## **9. `using namespace std;` — What It Does and Why We Avoid It**

### **What it actually does**

- `std::cout`, `std::string`, `std::vector`, etc. all live inside a namespace called `std` — a container that prevents name clashes between the standard library and your own code.
- `using namespace std;` tells the compiler "make every name in `std` available without the `std::` prefix," for the rest of that scope.

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "no std:: prefix needed here\n";
    return 0;
}
```

### **Why this file uses `std::` everywhere instead**

- `std` contains thousands of names (`count`, `sort`, `distance`, `max`, `min`, `move`, `data`, `swap`...). The moment you write a variable, function, or parameter with one of those names, `using namespace std;` creates ambiguity the compiler may or may not catch.

```cpp
#include <algorithm>
#include <iostream>
using namespace std;

int count = 5;              // shadows std::count — compiles, but now
                             // any later call to the algorithm std::count()
                             // in this scope needs the full std:: form anyway,
                             // defeating the point and confusing future you.

int main() {
    cout << count << "\n";
    return 0;
}
```

- In a header file, `using namespace std;` pollutes every `.cpp` that includes it — even ones that never wanted it. This is why it is banned in headers by essentially every style guide, including the practice this roadmap follows.
- As your files grow past a single-file demo, tracing "where did this name come from" gets harder without the `std::` marker. Explicit `std::` is free documentation.

### **When people reach for it anyway**

- Competitive programming / single-file scratch scripts where the whole program is 30 lines and will never be reused or extended.
- Even then, a safer middle ground exists: bring in only the specific names you need.

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

### **The rule this roadmap follows**

- Write `std::` explicitly in every example, every project, every topic folder. It is one extra word per line and it removes an entire category of bugs before they exist.

---

## **10. Practice Problems**

- [ ] **Build a Hello program** in 3 ways: single file (g++ one-shot), precompiled object + link, and with CMake. Compare artifacts.
- [ ] **Type sizes** — write a program that prints `sizeof(bool)`, `sizeof(char)`, `sizeof(wchar_t)`, `sizeof(int)`, `sizeof(long)`, `sizeof(long long)`, `sizeof(float)`, `sizeof(double)`, `sizeof(long double)`, `sizeof(std::string)`, `sizeof(void*)`. Build it on your machine and note the values.
- [ ] **Comment playground** — try to compile a file with a `/*` inside a `/* ... */` block and observe the error. Fix it using `#if 0`.
- [ ] **Overload `print`** — write four overloads: `print(int)`, `print(double)`, `print(const std::string&)`, `print(bool)`. Test that `print(0)`, `print(0.0)`, `print("hi")` pick the right ones. (Hint: `print("hi")` is a `const char*`, not `std::string` — fix by adding that overload or by explicit `print(std::string("hi"))`.)
- [ ] **Default arguments** — write a `make_window(width, height, title = "App", fullscreen = false)` that prints the params. Call it with 1, 2, 3, and 4 args.
- [ ] **Pass-by-value vs reference** — write a `swap(T&, T&)` template-like overload for `int` and `std::string`. Verify the caller sees the change.
- [ ] **Reference confusion drill** — write `increment_wrong(int x)` and `increment_right(int& x)` yourself from scratch (don't copy this file), predict the output on paper, then compile and check.
- [ ] **Separate compilation** — split a `vector3` struct (3 doubles, length, dot, cross) into `vec3.h` and `vec3.cpp`. Build with `g++ -c` for each, then link. Then move `length` into the header as `inline` and confirm it still builds.
- [ ] **Include guard drill** — remove `#pragma once` from a header, include it twice in one `.cpp` (directly and via a second header), and read the "redefinition" error. Then fix it.
- [ ] **Preprocessor tour** — run `g++ -E file.cpp | head -50` on a small program and read what the preprocessor actually produced. Identify the line where `<iostream>` was substituted in.
- [ ] **Symbol inspection** — build a small project with separate compilation and run `nm` on each `.o`. Find a `T` symbol in one and its `U` reference in another.
- [ ] **Linker error drill** — declare a function in a header, forget to define it, and build. Read the error. Then add a definition and confirm it links.
- [ ] **`using namespace std;` collision drill** — write a program that declares an `int count` variable AND calls `std::count()` from `<algorithm>` in the same scope, with `using namespace std;` active. Observe the ambiguity or shadowing, then fix it by removing the `using namespace std;` line and prefixing the standard library call.
- [ ] **CMake basics** — convert your multi-file project to a `CMakeLists.txt` that produces an executable. Build it from a clean `build/` directory.
- [ ] **Optimization comparison** — write a tight loop (e.g. sum 1..1e9). Time it under `-O0`, `-O2`, `-O3`, `-O3 -march=native`. Record the wall time of each.
- [ ] **Warning tour** — compile with `-Wall -Wextra -Wpedantic -Wshadow` and fix every warning in your existing code.