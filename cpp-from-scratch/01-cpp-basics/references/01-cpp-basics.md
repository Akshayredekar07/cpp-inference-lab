# **C++ Basics**

---

## **Topics**

- What C++ is and how it relates to C
- Structure of a C++ program
- Comments (`//`, `/* */`)
- Preprocessor directives (`#include`, `#define`, macros, header guards)
- Header/source file separation (`.h` / `.cpp`) and the compile/link model
- `iostream` library: `std::cin`, `std::cout`, `std::cerr`, `std::clog`
- Namespaces (`std::`, `using namespace std;`, `using` declarations)
- Variables and fundamental data types (`bool`, `char`, `wchar_t`, integer types, floating-point types, `void`)
- Type modifiers (`signed`, `unsigned`, `short`, `long`, `long long`)
- Derived/compound types: arrays, pointers, references (`T&`, `T&&`)
- `std::string` basics
- Type inference: `auto`, `decltype`, `std::declval`
- Constants: `const`, `constexpr`, `constinit`, `consteval`
- Operators (arithmetic, relational, logical, bitwise, assignment, member access, ternary, comma, `sizeof`, `alignof`, `typeid`, scope resolution `::`)
- Control flow: `if` / `else`, `switch`, `while`, `do-while`, `for`, range-`for`, `break`, `continue`, `goto`
- Enums: unscoped `enum` and scoped `enum class`
- `struct` and `union`
- Typedef / type aliases (`typedef`, `using`)
- Type casting: implicit, C-style cast, `static_cast`, `const_cast`, `reinterpret_cast`, `dynamic_cast` (preview)
- Function basics: declaration, definition, parameters, return type, overloading, default arguments, pass-by-value vs reference vs pointer
- Storage classes: `auto` (legacy), `register` (removed in C++17), `static`, `extern`, `mutable`, `thread_local`
- `sizeof`, `alignof`, `std::numeric_limits`

---

## **What is C++**

- C++ is a compiled, statically-typed, multi-paradigm language extending C with classes, templates, and a type system.
- Most valid C is valid C++ with minor differences (`void*` doesn't auto-convert, stricter prototypes, new keywords like `class`).
- C++ source compiles to object files (`.o` / `.obj`), then a linker combines them into an executable or library.
- A C++ program needs at least one `main` function — that's the entry point the runtime calls.

```cpp
// Minimal C++ program
#include <iostream>

int main() {
    std::cout << "Hello, C++\n";
    return 0;
}
```

```bash
# Compile + run (MinGW g++ 14.2.0 confirmed working)
g++ -std=c++17 -Wall -Wextra hello.cpp -o hello
./hello
```

---

## **Structure of a C++ Program**

A typical C++ source file has these parts, top to bottom:

- **Preprocessor directives** — `#include`, `#define`, `#ifdef` (run before compilation).
- **Using declarations / directives** — bring names from a namespace into scope.
- **Global declarations** — constants, type aliases, function prototypes, class declarations.
- **Function definitions** — including `main`.

```cpp
// Anatomy of a C++ program
#include <iostream>      // 1. Preprocessor directive
#include <string>

constexpr double PI = 3.14159;  // 2. Global constant
using Meters = double;          // 3. Type alias

int area(int radius);           // 4. Function prototype (declaration)

int main() {                    // 5. Entry point
    Meters r = 5.0;
    std::cout << "area = " << area(r) << "\n";
    return 0;
}

int area(int radius) {          // 6. Function definition
    return static_cast<int>(PI * radius * radius);
}
```

---

## **Comments**

- `//` — single-line comment, runs to end of line.
- `/* ... */` — block comment, can span lines. **Does not nest** in standard C++.
- Use `///` or `/** */` for documentation tools (Doxygen).

```cpp
#include <iostream>

int main() {
    // Single-line comment

    /* Block comment
       spanning multiple lines */

    int x = 10; ///< Trailing doc comment
    int y = 20; /** Another doc comment */

    std::cout << x + y << "\n"; // inline
    return 0;
}
```

**Common pitfalls**

- Block comments do not nest: `/* /* inner */ outer */` is malformed — the first `*/` ends the comment.
- Don't put `*/` inside a string literal inside a block comment (still terminates the comment).

---

## **Preprocessor Directives**

The preprocessor is a text-substitution step that runs before the compiler proper.

- `#include <file>` — system header, searched in include paths.
- `#include "file"` — user header, searched relative to current file first.
- `#define NAME value` — macro substitution (avoid for anything complex).
- `#define NAME(args) body` — function-like macro (prefer inline functions).
- `#undef NAME` — remove a macro.
- `#ifdef`, `#ifndef`, `#if`, `#else`, `#elif`, `#endif` — conditional compilation.
- `#pragma once` — non-standard but widely supported alternative to include guards.

### **Basic — `#include` and object-like macros**

```cpp
#include <iostream>
#include "myheader.h"

#define PI 3.14159
#define VERSION "1.0.0"

int main() {
    std::cout << "PI=" << PI << " v=" << VERSION << "\n";
    return 0;
}
```

### **Intermediate — conditional compilation**

```cpp
#include <iostream>

#define DEBUG 1

int main() {
#ifdef DEBUG
    std::cout << "[debug] starting\n";
#endif

#if defined(__linux__)
    std::cout << "Linux\n";
#elif defined(_WIN32)
    std::cout << "Windows\n";
#elif defined(__APPLE__)
    std::cout << "macOS\n";
#else
    std::cout << "Unknown\n";
#endif
    return 0;
}
```

### **Advanced — function-like macro and `#` / `##` operators**

```cpp
#include <iostream>

// Stringify operator `#` and token-paste operator `##`
#define STR(x) #x
#define CONCAT(a, b) a##b
#define LOG(level, msg) std::cerr << "[" #level "] " << msg << "\n"

int main() {
    std::cout << STR(Hello) << "\n";          // prints: Hello
    int CONCAT(num, 1) = 42;                   // expands to: int num1 = 42;
    std::cout << num1 << "\n";
    LOG(ERROR, "file not found");
    return 0;
}
```

**Prefer `constexpr`, `inline`, and templates over macros** — macros bypass the type system and the debugger can't see inside them.

---

## **Header Guards and `#pragma once`**

Headers get included into multiple translation units, so you must prevent multiple definitions of the same declaration.

### **Basic — traditional include guards**

```cpp
// myheader.h
#ifndef MYHEADER_H
#define MYHEADER_H

int add(int a, int b);

#endif // MYHEADER_H
```

### **Intermediate — `#pragma once` (non-standard but universal)**

```cpp
// myheader.h
#pragma once

int add(int a, int b);
```

- `#pragma once` is shorter, slightly faster to compile, supported by every major compiler (GCC, Clang, MSVC, MinGW).
- Use it unless you target a compiler that genuinely doesn't support it.

### **Advanced — guarding with both for safety**

```cpp
// robust.h
#if !defined(ROBUST_H) && !defined(__INTELLISENSE__)
#define ROBUST_H

inline int square(int x) { return x * x; }

#endif
```

---

## **Header / Source File Separation and the Compile/Link Model**

- A **header (`.h` / `.hpp`)** holds declarations: function prototypes, class/struct definitions, template definitions, inline functions, constants.
- A **source (`.cpp`)** holds definitions: function bodies, non-inline member definitions, static globals.
- **Translation unit** = one `.cpp` + every header it (transitively) includes, after preprocessing.
- **Object file** = compiled translation unit (`.o` / `.obj`).
- **Linker** combines object files and libraries, resolves symbols, produces the executable.

### **Basic — declaration in header, definition in source**

```cpp
// math_utils.h
#pragma once
int add(int a, int b);
int sub(int a, int b);
```

```cpp
// math_utils.cpp
#include "math_utils.h"

int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
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
# Compile each .cpp to .o, then link
g++ -std=c++17 -Wall -Wextra -c main.cpp      -o main.o
g++ -std=c++17 -Wall -Wextra -c math_utils.cpp -o math_utils.o
g++ main.o math_utils.o -o app
./app
```

### **Intermediate — `inline` definitions in headers**

Multiple translation units can include a header only if definitions are `inline` (or `constexpr` / template).

```cpp
// math_utils.h
#pragma once
inline int add(int a, int b) { return a + b; }
inline int sub(int a, int b) { return a - b; }
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

### **Advanced — one-definition rule (ODR) and `inline` variables**

C++17 lets you define a variable in a header with `inline` so every TU sees the same address.

```cpp
// config.h
#pragma once
#include <string>
inline constexpr int MAX_CONN = 100;
inline const std::string APP_NAME = "roadmap";
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

**ODR rules**

- Non-inline functions/variables must be defined in **exactly one** translation unit.
- `inline` functions/variables may be defined in **multiple** translation units (must be identical).
- Class and template definitions may appear in multiple TUs (no ODR violation).

---

## **`iostream`: `cin`, `cout`, `cerr`, `clog`**

`<iostream>` provides the four standard streams:

- `std::cout` — buffered standard output.
- `std::cerr` — unbuffered standard error (use for diagnostics — won't be lost if the program crashes).
- `std::clog` — buffered standard error (use for logging).
- `std::cin` — buffered standard input.

`std::endl` flushes the stream; `"\n"` does not (faster in hot loops).

### **Basic — read and write**

```cpp
#include <iostream>

int main() {
    std::cout << "Enter your name: ";
    std::string name;
    std::cin >> name;
    std::cout << "Hello, " << name << "!\n";
    return 0;
}
```

### **Intermediate — formatted output and stream manipulators**

```cpp
#include <iomanip>
#include <iostream>

int main() {
    double pi = 3.14159265358979;
    std::cout << "default: "   << pi                  << "\n";
    std::cout << "fixed 2:  "  << std::fixed << std::setprecision(2) << pi << "\n";
    std::cout << "hex:      "  << std::hex << std::showbase << 255   << "\n";
    std::cout << "bool:     "  << std::boolalpha << true            << "\n";

    int width = 8;
    std::cout << "padded:   [" << std::setw(width) << std::setfill('0') << 42 << "]\n";
    return 0;
}
```

### **Advanced — error reporting to `cerr` and reading a whole line**

```cpp
#include <iostream>
#include <string>

int main() {
    std::cout << "Enter a line: ";
    std::string line;
    std::getline(std::cin, line);

    if (line.empty()) {
        std::cerr << "[error] empty input\n";
        return 1;
    }
    std::clog << "[info] got " << line.size() << " chars\n";
    std::cout << "you said: " << line << "\n";
    return 0;
}
```

**Tip:** Mixing `>>` with `getline` leaves a trailing `\n` in the buffer. Either call `std::cin.ignore()` after `>>` or use `getline` throughout.

---

## **Namespaces**

Namespaces prevent name collisions across libraries.

- `std::` — fully-qualified access.
- `using namespace std;` — brings every name from `std` into the current scope (avoid in headers, fine in tiny `.cpp` examples).
- `using std::cout;` — brings one specific name.

### **Basic — qualified access**

```cpp
#include <iostream>

int main() {
    std::cout << "qualified\n";
    return 0;
}
```

### **Intermediate — `using` directive vs declaration**

```cpp
#include <iostream>

using std::cout;       // declaration: only cout
using namespace std;   // directive: everything in std

int main() {
    cout << "declaration + directive\n";
    return 0;
}
```

### **Advanced — custom namespaces and `namespace` blocks**

```cpp
#include <iostream>

namespace math {
    constexpr double PI = 3.14159;
    double circle_area(double r) { return PI * r * r; }

    namespace detail {          // nested namespace
        double square(double x) { return x * x; }
    }
}

// Namespace alias
namespace md = math::detail;

int main() {
    std::cout << math::PI                       << "\n";
    std::cout << math::circle_area(2.0)         << "\n";
    std::cout << md::square(3.0)                << "\n";
    return 0;
}
```

**Rules of thumb**

- Never put `using namespace std;` in a header file — it leaks into every includer.
- Anonymous namespace `namespace { ... }` makes a name translation-unit-local (replaces C's `static` for non-member declarations).

---

## **Variables and Fundamental Data Types**

C++ is statically typed: every variable has a type known at compile time, and the size is fixed (per platform).

### **Type summary**

| Category | Types | Typical size (64-bit) |
|----------|-------|------------------------|
| Boolean | `bool` | 1 byte |
| Character | `char`, `signed char`, `unsigned char`, `wchar_t`, `char16_t`, `char32_t` | 1, 1, 1, 2/4, 2, 4 bytes |
| Integer | `short`, `int`, `long`, `long long` (and unsigned variants) | 2, 4, 8, 8 bytes |
| Floating | `float`, `double`, `long double` | 4, 8, 16 bytes |
| Void | `void` | no storage |
| Null pointer | `std::nullptr_t` | platform pointer size |

Use `<cstdint>` for fixed-width integers: `int8_t`, `int16_t`, `int32_t`, `int64_t`, `uint8_t`, …

### **Basic — declare and initialize**

```cpp
#include <iostream>

int main() {
    bool        flag   = true;
    char        letter = 'A';
    int         count  = 42;
    double      ratio  = 0.5;
    std::string text   = "hello";

    std::cout << std::boolalpha << flag << " " << letter << " "
              << count << " " << ratio << " " << text << "\n";
    return 0;
}
```

### **Intermediate — modifiers, fixed-width, sizes**

```cpp
#include <cstdint>
#include <iostream>
#include <limits>

int main() {
    unsigned int        u  = 4000000000u;        // wider positive range
    int8_t              i8 = -128;               // exactly 8 bits
    uint64_t            u64 = 18'446'744'073'709'551'615ull;  // digit separators

    std::cout << "u  = " << u   << "\n";
    std::cout << "i8 = " << +i8 << "\n";  // promote to int for printing
    std::cout << "u64= " << u64 << "\n";

    std::cout << "int  range: [" << std::numeric_limits<int>::min()
              << ", "           << std::numeric_limits<int>::max() << "]\n";
    return 0;
}
```

### **Advanced — character encodings, `wchar_t`, `char8_t/16_t/32_t`**

```cpp
#include <iostream>
#include <string>

int main() {
    const char*   s   = "UTF-8 bytes";          // narrow string
    const wchar_t* ws  = L"wide string";         // platform-dependent width
    const char16_t* u16 = u"UTF-16";
    const char32_t* u32 = U"UTF-32";

    std::wcout     << L"ws  size=" << std::wcslen(ws)  << L"\n";
    std::cout << "u16 size=" << std::char_traits<char16_t>::length(u16) << "\n";
    std::cout << "u32 size=" << std::char_traits<char32_t>::length(u32) << "\n";
    return 0;
}
```

**Notes**

- `wchar_t` is **not** portable width — Windows is 16-bit, Linux/macOS are 32-bit. Use `char16_t` / `char32_t` for explicit encoding.
- `char8_t` (C++20) is a distinct type for UTF-8 code units.
- `char` may be `signed` or `unsigned` depending on platform — use `signed char` / `unsigned char` when you care.

### **Variable declarations and initialization forms**

```cpp
int a = 5;        // copy-initialization
int b(5);          // direct-initialization
int c{5};          // brace / list-initialization (narrowing rejected)
int d = {5};       // copy-list-initialization

// Brace init prevents narrowing:
double d2 = 3.14;
int n{d2};         // COMPILE ERROR: narrowing from double to int
```

**Prefer `{}` (brace) initialization** — it's safer and consistent across all types.

---

## **`std::string` (introductory)**

`std::string` is a mutable, owning sequence of `char`. It's not fundamental but every beginner uses it.

```cpp
#include <iostream>
#include <string>

int main() {
    std::string s = "roadmap";
    s += " C++";                       // append
    s.push_back('!');
    std::cout << s << " size=" << s.size() << "\n";

    std::cout << "substr=" << s.substr(0, 7) << "\n";
    std::cout << "find='C' at " << s.find('C') << "\n";

    // raw literals and string_view preview:
    using namespace std::string_view_literals;
    std::string_view sv = "read-only view"sv;
    std::cout << "sv=" << sv << "\n";
    return 0;
}
```

`std::string_view` (C++17) is a non-owning, cheap-to-copy view — useful for function parameters that only read.

---

## **References and Pointers**

These belong here because every C++ program uses them.

### **Basic — `&` reference and `*` pointer**

```cpp
#include <iostream>

int main() {
    int x = 10;

    int&  r = x;        // reference: alias for x
    int*  p = &x;       // pointer: holds address of x

    r = 20;             // modifies x
    *p = 30;            // also modifies x

    std::cout << "x=" << x << " r=" << r << " *p=" << *p << "\n";
    return 0;
}
```

### **Intermediate — `nullptr`, const pointers**

```cpp
#include <iostream>

int main() {
    int v = 5;

    int*  p1 = nullptr;          // C++11: prefer nullptr over 0/NULL
    int*  p2 = &v;               // non-const pointer to non-const
    const int* p3 = &v;          // pointer to const (can't modify v through p3)
    int* const p4 = &v;          // const pointer (can't reseat p4)
    const int* const p5 = &v;    // const pointer to const

    if (p1 == nullptr) std::cout << "p1 is null\n";
    std::cout << "*p2=" << *p2 << "\n";
    return 0;
}
```

### **Advanced — references to temporaries and rvalue refs preview**

```cpp
#include <iostream>
#include <string>

void foo(const std::string& s) { std::cout << "lvalue ref: " << s << "\n"; }
void bar(std::string&& s)      { std::cout << "rvalue ref: " << s << "\n"; }

int main() {
    std::string name = "Ada";
    foo(name);            // binds to const lvalue ref
    foo("literal");       // binds to const lvalue ref (string literal -> temporary)
    bar(std::move(name)); // binds to rvalue ref
    return 0;
}
```

---

## **Type Inference: `auto`, `decltype`**

### **Basic — `auto`**

```cpp
#include <iostream>
#include <vector>

int main() {
    auto i = 42;              // int
    auto d = 3.14;            // double
    auto s = std::string("x");// std::string

    std::vector<int> v{1,2,3};
    for (auto it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
    return 0;
}
```

### **Intermediate — `auto` strips references and const**

```cpp
#include <iostream>

int main() {
    const int x = 10;
    auto a = x;          // int, not const int
    decltype(x) b = x;   // const int, exact type

    static_assert(!std::is_const_v<decltype(a)>);
    static_assert(std::is_const_v<decltype(b)>);
    return 0;
}
```

### **Advanced — `decltype(auto)` and trailing return types**

```cpp
#include <iostream>

decltype(auto) identity(int& x) { return (x); }   // returns int& (note the parentheses)
decltype(auto) copy_of(int x)   { return x; }     // returns int

int main() {
    int v = 7;
    int& r = identity(v);   // r binds to v
    r = 9;
    std::cout << v << "\n"; // 9
    return 0;
}
```

---

## **Constants: `const`, `constexpr`, `constinit`, `consteval`**

### **Basic — `const`**

```cpp
#include <iostream>

int main() {
    const int max = 100;
    // max = 200;  // error: assignment of read-only variable
    std::cout << max << "\n";
    return 0;
}
```

### **Intermediate — `constexpr` (compile-time)**

```cpp
#include <iostream>

constexpr int square(int x) { return x * x; }

int main() {
    constexpr int a = square(5);      // evaluated at compile time
    int b = 7;
    int c = square(b);                // runtime if b not constexpr
    std::cout << a << " " << c << "\n";
    return 0;
}
```

### **Advanced — `constinit` (C++20) and `consteval` (C++20)**

```cpp
#include <iostream>

constinit int g_value = 42;          // must be initialized at compile time
consteval int must_compile_time(int x) { return x * 2; }  // immediate function

int main() {
    // g_value = 10;  // ok at runtime, constinit only fixes initialization
    constexpr int v = must_compile_time(5);
    // int w = must_compile_time(b);  // error: requires constant arg
    std::cout << v << "\n";
    return 0;
}
```

**Distinction**

- `const` — runtime immutable value.
- `constexpr` — value OR function usable in constant expressions; can run at runtime too.
- `constinit` — variable initialized with a constant expression (no thread-safe init fiasco).
- `consteval` — function that **must** run at compile time.

---

## **Operators**

C++ has every C operator plus `::` (scope resolution), type-casts, and user-definable operators (covered later).

### **Basic — arithmetic, relational, logical**

```cpp
#include <iostream>

int main() {
    int a = 7, b = 2;
    std::cout << "a + b = " << (a + b) << "\n";
    std::cout << "a % b = " << (a % b) << "\n";
    std::cout << "a > b = " << std::boolalpha << (a > b) << "\n";
    std::cout << "a && b = " << (a && b) << "\n";
    return 0;
}
```

### **Intermediate — bitwise, assignment, ternary, comma, sizeof**

```cpp
#include <cstdint>
#include <iostream>

int main() {
    uint8_t x = 0b1010'1100;       // binary literal + digit separator
    uint8_t y = 0xF0;

    std::cout << "x & y = " << (x & y) << "\n";
    std::cout << "x | y = " << (x | y) << "\n";
    std::cout << "~x    = " << (~x)    << "\n";
    std::cout << "x<<2  = " << (x << 2) << "\n";

    int n = 5;
    n += 3;     // compound assignment
    int m = (n > 5) ? 100 : 200;  // ternary
    int k = (1, 2, 3);            // comma: result is 3
    std::cout << n << " " << m << " " << k << "\n";

    std::cout << "sizeof(int) = " << sizeof(int) << "\n";
    std::cout << "alignof(double) = " << alignof(double) << "\n";
    return 0;
}
```

### **Advanced — scope resolution, member access, `typeid`**

```cpp
#include <iostream>
#include <typeinfo>

namespace app {
    int value = 10;
    struct Point { int x, y; };
}

int app::value = 42;        // define a namespace-scope variable

int main() {
    int v = 10;
    ::v = 20;                // global scope (no enclosing namespace)
    std::cout << "v=" << v << "\n";

    app::Point p{1, 2};
    std::cout << "p.x=" << p.x << " p.y=" << p.y << "\n";
    std::cout << "type: " << typeid(p).name() << "\n";
    return 0;
}
```

**Operator precedence (high to low, common subset)**

- `::` (scope resolution)
- `()` `[]` `->` `.` `++` `--` (postfix)
- `++` `--` `+` `-` `!` `~` `*` `&` `(type)` `sizeof` (prefix)
- `*` `/` `%`
- `+` `-`
- `<<` `>>`
- `<` `<=` `>` `>=`
- `==` `!=`
- `&` (bitwise AND)
- `^`
- `|`
- `&&`
- `||`
- `?:` (ternary)
- `=` `+=` `-=` `*=` `/=` `%=` `<<=` `>>=` `&=` `^=` `|=`
- `,` (comma)

When in doubt, parenthesize.

---

## **Control Flow**

### **Basic — `if` / `else`**

```cpp
#include <iostream>

int main() {
    int x = 5;
    if (x > 0) {
        std::cout << "positive\n";
    } else if (x < 0) {
        std::cout << "negative\n";
    } else {
        std::cout << "zero\n";
    }
    return 0;
}
```

### **Intermediate — `switch`, `while`, `do-while`, classic `for`**

```cpp
#include <iostream>

int main() {
    int cmd = 2;
    switch (cmd) {
        case 1: std::cout << "one\n"; break;
        case 2: std::cout << "two\n"; break;
        case 3: std::cout << "three\n"; break;
        default: std::cout << "other\n";
    }

    int i = 0;
    while (i < 3) { std::cout << "w" << i++; }
    std::cout << "\n";

    int j = 0;
    do { std::cout << "d" << j++; } while (j < 3);
    std::cout << "\n";

    for (int k = 0; k < 3; ++k) std::cout << "f" << k;
    std::cout << "\n";
    return 0;
}
```

### **Advanced — range-`for` and structured bindings**

```cpp
#include <iostream>
#include <map>
#include <string>
#include <vector>

int main() {
    std::vector<int> nums{1, 2, 3, 4, 5};
    for (int n : nums) std::cout << n << " ";
    std::cout << "\n";

    for (const auto& n : nums) std::cout << n * 2 << " ";
    std::cout << "\n";

    std::map<std::string, int> ages{{"Ada", 36}, {"Lin", 41}};
    for (const auto& [name, age] : ages) {     // structured binding
        std::cout << name << "=" << age << " ";
    }
    std::cout << "\n";
    return 0;
}
```

---

## **Enums**

### **Basic — unscoped `enum`**

```cpp
#include <iostream>

enum Color { RED, GREEN, BLUE };     // values 0, 1, 2

int main() {
    Color c = GREEN;
    std::cout << "c=" << c << "\n";  // prints 1 (underlying integer)
    return 0;
}
```

### **Intermediate — specifying underlying type and values**

```cpp
#include <iostream>

enum class Status : uint8_t { OK = 0, Warn = 10, Error = 20 };

int main() {
    Status s = Status::Warn;
    std::cout << "size=" << sizeof(s) << " val=" << static_cast<int>(s) << "\n";
    return 0;
}
```

### **Advanced — `enum class` vs unscoped, scoped constants**

```cpp
#include <iostream>

enum class HttpCode { OK = 200, NotFound = 404, ServerError = 500 };

int main() {
    auto code = HttpCode::NotFound;

    // Must cast to compare with int:
    if (static_cast<int>(code) == 404) {
        std::cout << "not found\n";
    }

    // Compile-time exhaustive switch
    switch (code) {
        case HttpCode::OK:          std::cout << "ok\n"; break;
        case HttpCode::NotFound:    std::cout << "404\n"; break;
        case HttpCode::ServerError: std::cout << "500\n"; break;
    }
    return 0;
}
```

**Prefer `enum class`** — unscoped enums leak names into the enclosing scope and implicitly convert to int.

---

## **`struct` and `union`**

### **Basic — `struct`**

```cpp
#include <iostream>
#include <string>

struct Point {
    int x;
    int y;
};

int main() {
    Point p{3, 4};
    std::cout << "(" << p.x << ", " << p.y << ")\n";
    return 0;
}
```

### **Intermediate — member functions and constructors**

```cpp
#include <iostream>
#include <cmath>

struct Vec2 {
    double x{0.0};
    double y{0.0};

    Vec2() = default;                         // defaulted
    Vec2(double a, double b) : x(a), y(b) {}  // member-init list

    double length() const { return std::sqrt(x*x + y*y); }
};

int main() {
    Vec2 a;
    Vec2 b(3.0, 4.0);
    std::cout << a.length() << " " << b.length() << "\n";
    return 0;
}
```

### **Advanced — `union` for type punning / variant storage**

```cpp
#include <cstring>
#include <iostream>
#include <iomanip>

union Bytes {
    std::uint32_t as_u32;
    std::uint8_t  as_bytes[4];
};

int main() {
    Bytes b;
    b.as_u32 = 0x12345678;
    std::cout << std::hex << std::setfill('0');
    for (int i = 0; i < 4; ++i) {
        std::cout << std::setw(2) << static_cast<int>(b.as_bytes[i]) << " ";
    }
    std::cout << "\n";
    return 0;
}
```

**`union` rules**

- All non-static data members share the same memory.
- You can read only the member most recently written (type punning via `std::memcpy` / `std::bit_cast` is safer).
- For a type-safe alternative, use `std::variant` (C++17).

---

## **Type Aliases: `typedef` and `using`**

```cpp
#include <iostream>
#include <vector>

typedef std::vector<int> IntVec;     // C-style
using  IntVec2 = std::vector<int>;   // C++11: preferred

template <typename T>
using Vec = std::vector<T>;          // alias template

int main() {
    IntVec  a{1, 2, 3};
    IntVec2 b{4, 5, 6};
    Vec<double> c{1.1, 2.2};

    std::cout << a.size() << " " << b.size() << " " << c.size() << "\n";
    return 0;
}
```

`using` works for templates; `typedef` does not (until C++11 `using` arrived).

---

## **Type Casting (preview)**

| Cast | Purpose |
|------|---------|
| Implicit | Trivial conversions (int ↔ double, derived* → base*). |
| `(T)x` | C-style, combines static/const/reinterpret. Avoid. |
| `static_cast<T>(x)` | Compile-time-checked conversions between related types. |
| `const_cast<T>(x)` | Add or strip `const` / `volatile`. |
| `reinterpret_cast<T>(x)` | Low-level bit reinterpretation (pointers ↔ integers, unrelated types). |
| `dynamic_cast<T>(x)` | Safe downcast in a polymorphic hierarchy; needs RTTI. |

```cpp
#include <iostream>

struct Base { virtual ~Base() = default; };
struct Derived : Base { void hello() { std::cout << "hi\n"; } };

int main() {
    double d = 3.14;
    int    i = static_cast<int>(d);      // 3
    std::cout << i << "\n";

    Base*    b = new Derived;
    Derived* p = dynamic_cast<Derived*>(b);
    if (p) p->hello();
    delete b;
    return 0;
}
```

---

## **Function Basics**

### **Basic — declaration, definition, call**

```cpp
#include <iostream>

int square(int x);                 // declaration

int main() { std::cout << square(5) << "\n"; return 0; }

int square(int x) { return x * x; } // definition
```

### **Intermediate — overloading and default arguments**

```cpp
#include <iostream>
#include <string>

void print(int x)                  { std::cout << "int: "    << x << "\n"; }
void print(double x)               { std::cout << "double: " << x << "\n"; }
void print(const std::string& s)   { std::cout << "str: "    << s << "\n"; }

void greet(const std::string& name, const std::string& greet = "Hello") {
    std::cout << greet << ", " << name << "!\n";
}

int main() {
    print(7);
    print(3.14);
    print(std::string("Ada"));
    greet("Lin");
    greet("Lin", "Hi");
    return 0;
}
```

### **Advanced — pass-by-value vs reference vs pointer, and `[[nodiscard]]`**

```cpp
#include <iostream>
#include <string>

[[nodiscard]] int compute(int x) { return x * 2; }    // caller must use the result

void by_value(int x)              { x = 0; }   // does NOT modify caller
void by_ref(int& x)               { x = 0; }   // DOES modify caller
void by_ptr(int* x)               { if (x) *x = 0; }

struct Heavy { std::string data[1000]; };

void read_only(const Heavy& h)     { (void)h.data[0]; }   // no copy, no mutation

int main() {
    int a = 1, b = 1, c = 1;
    by_value(a);
    by_ref(b);
    by_ptr(&c);
    std::cout << a << " " << b << " " << c << "\n";  // 1 0 0

    Heavy h;
    read_only(h);
    std::cout << compute(21) << "\n";
    return 0;
}
```

**Rules of thumb**

- Pass by `const&` for large objects you only read.
- Pass by `T&` or `T*` when the callee must mutate.
- Pass small types (`int`, `double`, pointers) by value.

---

## **Storage Classes**

| Specifier | Meaning |
|-----------|---------|
| `auto` (legacy) | Default for local variables; deduced by initializer in C++11+. |
| `register` | Hint to put in a register — **removed in C++17**. |
| `static` (at file scope) | Internal linkage (TU-local). |
| `static` (at function scope) | Persistent across calls. |
| `static` (at class scope) | One per class, not per object (covered later). |
| `extern` | Declares a name defined in another TU. |
| `mutable` | Allows modification of a member even in a `const` object. |
| `thread_local` | One instance per thread. |

```cpp
#include <iostream>

static int tu_local = 1;            // internal linkage
extern int shared_counter;          // defined elsewhere (e.g. another .cpp)

void counter_demo() {
    static int calls = 0;           // persists across calls
    ++calls;
    std::cout << "called " << calls << " times\n";
}

struct Cache {
    mutable int hits = 0;           // can be modified in const methods
    void touch() const { ++hits; }  // const method, but mutable allows hit++
};

int main() {
    counter_demo();
    counter_demo();
    counter_demo();

    const Cache c;
    c.touch(); c.touch();
    std::cout << "hits=" << c.hits << "\n";

    thread_local int tls = 0;        // per-thread
    ++tls;
    std::cout << "tls=" << tls << "\n";
    return 0;
}
```

---

## **`sizeof`, `alignof`, `std::numeric_limits`, `std::is_same_v`**

```cpp
#include <iostream>
#include <limits>
#include <type_traits>

int main() {
    std::cout << "sizeof(int)         = " << sizeof(int)                 << "\n";
    std::cout << "alignof(std::max_align_t) = " << alignof(std::max_align_t) << "\n";
    std::cout << "int min/max         = "
              << std::numeric_limits<int>::min() << " / "
              << std::numeric_limits<int>::max() << "\n";
    static_assert(std::is_same_v<int, int>);
    return 0;
}
```

---

## **Practice / Project**

- [ ] Compile and run the minimal `Hello, C++` program with both `g++` and `clang++` (if available). Diff the binaries' size.
- [ ] Write a `math_utils.h` / `math_utils.cpp` / `main.cpp` split with `add`, `sub`, `mul`, `div`. Build it both as one `g++` line and as separate object files linked together.
- [ ] Convert one of your existing single-file programs to a header + source split, then to a separate compilation with `-c` and a final link step.
- [ ] Implement a CLI converter that reads a temperature in Celsius (`double`) and prints Fahrenheit, Kelvin — using only `std::cin` / `std::cout`.
- [ ] Read a full line with `std::getline`, then echo it reversed (manually reverse a `std::string`).
- [ ] Write a program that prints the sizes of `bool`, `char`, `wchar_t`, `char16_t`, `char32_t`, `short`, `int`, `long`, `long long`, `float`, `double`, `long double`, plus a `std::string` and a raw pointer. Compare 32-bit vs 64-bit output if you can.
- [ ] Build a tiny "enum-driven menu" — `enum class Choice { Add, List, Quit }`, switch on user input, route to handlers.
- [ ] Use `static_cast`, `dynamic_cast`, `const_cast`, `reinterpret_cast` once each, with comments explaining why each is the right one.
- [ ] Write a `Vec2` struct with `+`, `-`, `dot`, `length` (member functions only — operator overloading comes later).
- [ ] Add `[[nodiscard]]` and `noexcept` to a function and read the compiler warning/error when you ignore the return value.
- [ ] Open a `.cpp` in your editor and use the debugger to step from `main` into a function defined in a separate `.cpp`. Verify the linker resolves the symbol.
- [ ] Profile a tight loop: build with `-O0` vs `-O2` vs `-O3 -march=native` and time the difference on at least 100 million iterations.
- [ ] Run `g++ -E file.cpp | head -50` on a sample to see what the preprocessor actually produces.
- [ ] Demonstrate the `using namespace std;` leak by putting it in a header and watching the conflict in a downstream file.

---

## **Cross-references**

- See `../docs/compiler-setup.md` for installing g++/clang on Windows, Linux, macOS.
- See `../docs/instructions.md` for the Windows terminal encoding fix (`chcp.com 65001`) and why Unicode section separators in code files can mojibake under MSYS2/MinGW64.
- See `../docs/style-guide.md` for the formatting rules used in this file.
- See `../resources/cheatsheets/` for a one-page operator-precedence and type-size reference.
