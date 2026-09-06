# **Preprocessor, Namespaces & Streams**

The machinery that surrounds your code: how the preprocessor rewrites your source before the compiler sees it, how include guards and `#pragma once` prevent double-inclusion, how namespaces organize names, and how to read/write with `iostream` and `iomanip`.

---

## **Table of Contents**

1. The preprocessor and its directives
2. `#include` — system vs user headers
3. `#define` — object-like and function-like macros
4. Conditional compilation — `#if`, `#ifdef`, `#ifndef`, `#elif`, `#else`, `#endif`
5. Predefined macros and `__has_include`
6. Stringify (`#`) and token-paste (`##`)
7. Header guards — `#ifndef` and `#pragma once`
8. Preprocessor best practices
9. Namespaces — `std::`, `using`, nesting, alias
10. Anonymous namespaces
11. `iostream` — `cin`, `cout`, `cerr`, `clog`
12. `iomanip` — manipulators
13. Reading whole lines with `getline`
14. The `>>` / `getline` pitfall
15. Practice problems

---

## **1. The Preprocessor and Its Directives**

The preprocessor runs before the compiler. It does text substitution, file inclusion, and conditional inclusion. It is **not** the C++ language — it's a separate, dumb text-rewriter.

To see what the preprocessor produces:

```bash
g++ -E main.cpp -o main.i        # full preprocessed source
g++ -E main.cpp | head -50       # peek at the first 50 lines
```

### **Directives**

| Directive | What it does |
|-----------|--------------|
| `#include <file>` / `#include "file"` | Paste the contents of `file` here. |
| `#define NAME value` | Define an object-like macro. |
| `#define NAME(args) body` | Define a function-like macro. |
| `#undef NAME` | Remove a macro. |
| `#if expr` / `#ifdef NAME` / `#ifndef NAME` | Conditionally include code. |
| `#elif` / `#else` / `#endif` | The rest of the conditional. |
| `#error "message"` | Halt compilation with an error. |
| `#warning "message"` | Emit a warning (C++23 standardized; non-portable before). |
| `#pragma once` | Hint to include the file only once (non-standard but universal). |
| `#pragma GCC diagnostic ...` | Compiler-specific diagnostic controls. |
| `#line N "file"` | Pretend the next line came from `file: N`. |

---

## **2. `#include` — System vs User Headers**

### **Angle brackets vs quotes**

- `#include <header>` — system header, searched in compiler / standard library include paths (`-I`).
- `#include "header.h"` — user header, searched relative to the including file first, then the system paths.

```cpp
#include <iostream>        // system header
#include <vector>          // system header
#include "my_class.h"      // project header
#include "config/utils.h"  // project subdirectory
```

### **Search paths**

```bash
g++ -Iinclude -Ithird_party/headers main.cpp -o app
```

This tells g++ to also look in `./include` and `./third_party/headers` for `<...>` includes.

### **What gets included?**

`<iostream>` is large — pulling it in compiles and links thousands of lines of stream machinery. Prefer lighter headers when you can:

- `<iosfwd>` — forward declarations of stream types (header-friendly).
- `<string_view>` — read-only string view without owning.
- `<cstdint>` — fixed-width integers.

```cpp
// In a header that only needs to declare I/O params:
#include <iosfwd>
#include <cstdint>

void write_record(std::ostream& os, std::uint32_t id);
```

### **Include what you use (IWYU)**

If your code calls `std::size_t`, include `<cstddef>` (or `<cstdint>` etc.). Don't rely on it being pulled in by another header. Makes your code resilient to changes in those other headers.

---

## **3. `#define` — Object-Like and Function-Like Macros**

### **Object-like — simple substitution**

```cpp
#include <iostream>

#define PI       3.14159265358979
#define VERSION  "1.0.0"
#define MAX_CONN 100

int main() {
    std::cout << "PI=" << PI << " v=" << VERSION << " max=" << MAX_CONN << "\n";
    return 0;
}
```

### **Function-like — arguments substituted textually**

```cpp
#include <iostream>

#define SQR(x) ((x) * (x))         // parens around every use of every argument
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int main() {
    int x = 5;
    std::cout << SQR(x)        << "\n";   // 25
    std::cout << SQR(x + 1)    << "\n";   // 36  — note the parens
    std::cout << MAX(3, 7)     << "\n";   // 7
    return 0;
}
```

### **Why the parentheses matter**

```cpp
#define BAD(x) x * x

int a = BAD(1 + 2);     // expands to: 1 + 2 * 1 + 2 = 5, not 9
int b = SQR(1 + 2);     // expands to: ((1+2) * (1+2)) = 9
```

### **Pitfall — macro arguments are not typed**

```cpp
#define DOUBLE(x) ((x) * 2)

std::cout << DOUBLE("hi") << "\n";      // compiles, weird runtime behavior
```

Prefer `inline` functions and `constexpr` functions:

```cpp
#include <iostream>

constexpr int  sqr(int x)    { return x * x; }
constexpr auto dbl (double x) { return x * 2; }

int main() {
    std::cout << sqr(5) << " " << dbl(3.14) << "\n";
    return 0;
}
```

### **Side effects in macro arguments**

```cpp
#include <iostream>

#define SQR(x) ((x) * (x))

int i = 0;
std::cout << SQR(++i) << "\n";     // ++i evaluated TWICE
```

With an inline function, `++i` is evaluated once. Macros don't know about side effects.

### **Multi-line macros with `\`**

```cpp
#define LOG(level, msg)                       \
    do {                                       \
        std::cerr << "[" #level "] "          \
                  << msg << "\n";              \
    } while (0)
```

The `do { } while (0)` idiom makes the macro behave like a single statement, safe after `if (...) LOG(...);`.

```cpp
#include <iostream>

#define LOG(level, msg)                       \
    do {                                       \
        std::cerr << "[" #level "] "          \
                  << msg << "\n";              \
    } while (0)

int main() {
    LOG(INFO, "starting");
    LOG(ERROR, "file not found");
    return 0;
}
```

### **`#undef`**

```cpp
#include <iostream>

#define DEBUG 1
int main() {
#ifdef DEBUG
    std::cout << "debug on\n";
#endif
    // ...
}
#undef DEBUG
```

---

## **4. Conditional Compilation**

### **Basic**

```cpp
#include <iostream>

#define DEBUG 1

int main() {
#ifdef DEBUG
    std::cout << "[debug] starting\n";
#endif

#if DEBUG > 0
    std::cout << "verbose on\n";
#endif
    return 0;
}
```

### **Platform detection**

```cpp
#include <iostream>

int main() {
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

### **Compiler detection**

```cpp
#if defined(__GNUC__) && !defined(__clang__)
    // GCC specifically
#elif defined(__clang__)
    // Clang specifically
#elif defined(_MSC_VER)
    // MSVC
#endif
```

### **`#if 0` to disable code**

```cpp
#if 0
int abandoned() {
    return 0;
}
#endif
```

This is safer than `/* ... */` because it can contain `*/` and nested comments.

### **`#error` for configuration checks**

```cpp
#if __cplusplus < 201703L
    #error "This file requires C++17 or later"
#endif
```

---

## **5. Predefined Macros**

The preprocessor defines these automatically. Use them for logging, version stamps, and platform-specific code.

| Macro | Meaning |
|-------|---------|
| `__FILE__` | Current source file name (string literal). |
| `__LINE__` | Current line number. |
| `__func__` | Current function name (C++11, not strictly a macro). |
| `__cplusplus` | C++ standard value (e.g. `201703L` for C++17). |
| `__DATE__` | Build date. |
| `__TIME__` | Build time. |
| `__has_include(<header>)` | 1 if the header can be included, 0 otherwise. |

```cpp
#include <iostream>

int main() {
    std::cout << "file: " << __FILE__ << "\n";
    std::cout << "line: " << __LINE__ << "\n";
    std::cout << "func: " << __func__ << "\n";
    std::cout << "cxx:  " << __cplusplus << "\n";
    return 0;
}
```

```cpp
#if __has_include(<filesystem>)
    #include <filesystem>
    namespace fs = std::filesystem;
#elif __has_include(<experimental/filesystem>)
    #include <experimental/filesystem>
    namespace fs = std::experimental::filesystem;
#endif
```

---

## **6. Stringify (`#`) and Token-Paste (`##`)**

### **`#` — turn a macro arg into a string literal**

```cpp
#include <iostream>

#define STR(x) #x

int main() {
    std::cout << STR(Hello)      << "\n";   // Hello
    std::cout << STR(3.14)       << "\n";   // 3.14
    std::cout << STR(x + y)      << "\n";   // x + y
    return 0;
}
```

### **`##` — concatenate tokens before they reach the compiler**

```cpp
#include <iostream>

#define CONCAT(a, b) a##b

int main() {
    int CONCAT(my, Var) = 42;            // expands to: int myVar = 42;
    std::cout << myVar << "\n";
    return 0;
}
```

### **Use case — enum-to-string**

```cpp
#include <iostream>

#define COLOR_ENUM(name) name,
enum Color { COLOR_ENUM(Red) COLOR_ENUM(Green) COLOR_ENUM(Blue) };
#undef COLOR_ENUM

#define COLOR_ENUM(name) case name: return #name;
const char* color_name(Color c) {
    switch (c) {
        COLOR_ENUM(Red) COLOR_ENUM(Green) COLOR_ENUM(Blue)
    }
    return "?";
}
#undef COLOR_ENUM

int main() {
    std::cout << color_name(Green) << "\n";   // Green
    return 0;
}
```

**Prefer `constexpr` and templates when you can.** Macros are last resort for code generation.

---

## **7. Header Guards — `#ifndef` and `#pragma once`**

A header may be included from many `.cpp` files. If it's included twice into the same translation unit (directly or indirectly), non-`inline` definitions cause a compile error.

### **Traditional — `#ifndef` / `#define` / `#endif`**

```cpp
// my_header.h
#ifndef MY_HEADER_H
#define MY_HEADER_H

int add(int a, int b);

#endif // MY_HEADER_H
```

Each header picks a unique guard macro, typically `PROJECT_PATH_FILE_H`.

### **Modern — `#pragma once`**

```cpp
// my_header.h
#pragma once

int add(int a, int b);
```

- Non-standard, but supported by every major compiler (GCC, Clang, MSVC, MinGW, Intel, IBM).
- Shorter and slightly faster (the compiler can remember the include instead of parsing guards).
- Use it by default. The only reason to use `#ifndef` is if you target a compiler that genuinely doesn't support it (none, in 2025+).

### **Combine both for paranoia**

```cpp
// robust.h
#if !defined(ROBUST_H) && !defined(__INTELLISENSE__)
#define ROBUST_H

inline int add(int a, int b) { return a + b; }

#endif
```

The `__INTELLISENSE__` exclusion stops Visual Studio's IntelliSense from re-evaluating the guard.

### **What's a "unique enough" guard?**

The guard macro is per-header. The convention is upper snake case derived from the path:

```cpp
// src/utils/strings.h
#ifndef SRC_UTILS_STRINGS_H
#define SRC_UTILS_STRINGS_H
// ...
#endif
```

For most projects, `#pragma once` makes the guard macro unnecessary.

---

## **8. Preprocessor Best Practices**

- Prefer `const` / `constexpr` / `inline` / templates over macros.
- Never put logic in macros if you can avoid it.
- If you must, parenthesize every argument and every expression.
- Avoid `##` — it's rarely necessary and hard to read.
- Use `#pragma once` for include guards.
- Use `#if 0` to disable code temporarily (keeps `*/` and nested comments working).
- Don't put `using namespace std;` in a header.

---

## **9. Namespaces**

A namespace is a named scope. Its job is to prevent name collisions.

### **Basic — `std::`**

```cpp
#include <iostream>

int main() {
    std::cout << "qualified\n";
    return 0;
}
```

### **Intermediate — `using` declarations and directives**

- `using std::cout;` — brings **one** name into the current scope.
- `using namespace std;` — brings **every** name from `std` into the current scope.

```cpp
#include <iostream>
#include <string>

using std::cout;          // declaration
using namespace std;      // directive (avoid in headers)

int main() {
    cout << "declaration + directive\n";
    string s = "hi";      // works because of the directive
    cout << s << "\n";
    return 0;
}
```

**Rules**

- OK in `.cpp` files (especially small ones / examples).
- NEVER put `using namespace std;` in a header — it pollutes every includer.

### **Advanced — custom namespaces, nesting, alias**

```cpp
#include <iostream>

namespace math {
    constexpr double PI = 3.14159265358979;

    double circle_area(double r) { return PI * r * r; }

    namespace detail {
        inline double square(double x) { return x * x; }
    }
}

namespace md = math::detail;          // alias
namespace app = math;                // alias

int main() {
    std::cout << app::PI                       << "\n";
    std::cout << app::circle_area(2.0)         << "\n";
    std::cout << md::square(3.0)               << "\n";
    return 0;
}
```

### **Namespaces in multiple files**

```cpp
// app.h
#pragma once
namespace app {
    int  version();
    void run();
}
```

```cpp
// app.cpp
#include "app.h"
#include <iostream>

namespace app {
    int version() { return 1; }

    void run() {
        std::cout << "v" << version() << "\n";
    }
}
```

```cpp
// main.cpp
#include <iostream>
#include "app.h"

int main() {
    std::cout << "version: " << app::version() << "\n";
    app::run();
    return 0;
}
```

```bash
g++ -std=c++17 -Wall -Wextra main.cpp app.cpp -o app
./app
```

### **Argument-dependent lookup (ADL, Koenig lookup)**

When you call a function with an argument, the compiler also searches the namespaces of the argument's type. This is why you can write `std::cout << x;` and have `operator<<` found automatically.

```cpp
#include <iostream>
#include <string>

namespace my {
    struct Tag {};
    void print(Tag) { std::cout << "my::print(Tag)\n"; }
}

int main() {
    my::Tag t;
    print(t);            // ADL: my::print found because t is my::Tag
    return 0;
}
```

---

## **10. Anonymous Namespaces**

An unnamed namespace makes everything inside it translation-unit-local — the C++ replacement for C's `static` at file scope.

```cpp
// file.cpp
#include <iostream>

namespace {
    int file_local = 42;     // only visible in this .cpp

    void helper() {           // only callable in this .cpp
        std::cout << "helper\n";
    }
}

int main() {
    std::cout << file_local << "\n";
    helper();
    return 0;
}
```

**Anonymous namespace vs `static`**

| Use | Prefer |
|-----|--------|
| File-scope variable that's TU-local | `namespace { ... }` |
| File-scope function that's TU-local | `namespace { ... }` |
| Class member function with internal linkage | `static` |
| Const variable at namespace scope | `inline constexpr` |

The anonymous namespace can also be used to give a type a unique name for ADL suppression.

---

## **11. `iostream` — `cin`, `cout`, `cerr`, `clog`**

`<iostream>` declares four standard stream objects:

| Stream | Type | Buffered? | Use for |
|--------|------|-----------|---------|
| `std::cin`  | `std::istream`  | yes | reading standard input |
| `std::cout` | `std::ostream`  | yes | normal output |
| `std::cerr` | `std::ostream`  | no  | error output, diagnostics |
| `std::clog` | `std::ostream`  | yes | logging |

### **Basic — read and write**

```cpp
#include <iostream>
#include <string>

int main() {
    std::cout << "Enter your name: ";
    std::string name;
    std::cin >> name;
    std::cout << "Hello, " << name << "!\n";
    return 0;
}
```

### **`std::endl` vs `"\n"`**

- `std::endl` inserts `\n` and **flushes** the stream. Slower in hot loops.
- `"\n"` inserts `\n` only. Faster.

```cpp
#include <iostream>
#include <chrono>

int main() {
    auto t0 = std::chrono::steady_clock::now();
    for (int i = 0; i < 1'000'000; ++i) std::cout << "x" << "\n";
    auto t1 = std::chrono::steady_clock::now();
    std::cout << "with \\n: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count()
              << " ms\n";
    return 0;
}
```

### **Chaining**

`operator<<` returns the stream, so you can chain.

```cpp
std::cout << "x=" << 42 << " y=" << 3.14 << "\n";
```

### **Error reporting**

`std::cerr` is unbuffered, so even if the program crashes, the message is written.

```cpp
#include <iostream>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "[error] usage: " << argv[0] << " FILE\n";
        return 1;
    }
    std::clog << "[info] processing " << argv[1] << "\n";
    std::cout << "ok\n";
    return 0;
}
```

### **Stream state**

After a read, the stream has flags: `goodbit`, `eofbit`, `failbit`, `badbit`. Always check after reading.

```cpp
#include <iostream>

int main() {
    int x;
    if (std::cin >> x) {
        std::cout << "got " << x << "\n";
    } else {
        std::cerr << "read failed\n";
    }
    return 0;
}
```

Reset state with `std::cin.clear();` and skip bad input with `std::cin.ignore(...)`.

---

## **12. `iomanip` — Manipulators**

`<iomanip>` provides functions that change the stream's formatting state. They return the stream so they can be chained.

### **Basic — precision and width**

```cpp
#include <iomanip>
#include <iostream>

int main() {
    double pi = 3.14159265358979;
    std::cout << "default     : " << pi                 << "\n";
    std::cout << "fixed 2     : " << std::fixed << std::setprecision(2) << pi << "\n";
    std::cout << "scientific  : " << std::scientific     << pi << "\n";

    int n = 42;
    std::cout << "padded      : [" << std::setw(8) << std::setfill('0') << n << "]\n";
    std::cout << "left-aligned: [" << std::left << std::setw(8) << n << "]\n";
    return 0;
}
```

### **Intermediate — bases and booleans**

```cpp
#include <iomanip>
#include <iostream>

int main() {
    std::cout << std::hex << std::showbase << 255        << "\n";   // 0xff
    std::cout << std::oct << std::showbase << 8          << "\n";   // 010
    std::cout << std::dec                                 << 255    << "\n";  // back to decimal
    std::cout << std::boolalpha << true                  << "\n";  // true
    std::cout << std::noboolalpha << true                << "\n";  // 1
    return 0;
}
```

### **Advanced — custom money / table formatter**

```cpp
#include <iomanip>
#include <iostream>
#include <vector>
#include <string>

struct Row { std::string name; double price; int qty; };

int main() {
    std::vector<Row> rows{
        {"Apple",  0.50, 3},
        {"Banana", 0.30, 5},
        {"Cherry", 2.75, 1},
    };

    std::cout << std::left << std::setw(10) << "Item"
              << std::right << std::setw(8)  << "Price"
              << std::setw(6)               << "Qty"
              << std::setw(10)              << "Total" << "\n";

    std::cout << std::string(34, '-') << "\n";

    for (const auto& r : rows) {
        std::cout << std::left  << std::setw(10) << r.name
                  << std::fixed << std::setprecision(2)
                  << std::right << std::setw(8) << r.price
                  << std::setw(6)              << r.qty
                  << std::setw(10)             << r.price * r.qty
                  << "\n";
    }
    return 0;
}
```

### **Manipulator cheatsheet**

| Manipulator | Effect |
|-------------|--------|
| `std::setw(n)` | Set width of next field only. |
| `std::setfill(c)` | Set fill character. |
| `std::setprecision(n)` | Decimal digits (or significant digits in default mode). |
| `std::fixed` | Fixed-point notation. |
| `std::scientific` | Scientific notation. |
| `std::hex` / `std::dec` / `std::oct` | Integer base. |
| `std::showbase` / `std::noshowbase` | Prefix base (`0x`, `0`). |
| `std::boolalpha` / `std::noboolalpha` | `true`/`false` vs `1`/`0`. |
| `std::left` / `std::right` / `std::internal` | Alignment. |
| `std::uppercase` | `1e6` vs `1E6`, `0xff` vs `0xFF`. |
| `std::endl` | Newline + flush. |
| `std::flush` | Flush without newline. |

---

## **13. Reading Whole Lines with `getline`**

`std::getline` reads until a delimiter (default `\n`) into a `std::string`.

```cpp
#include <iostream>
#include <string>

int main() {
    std::cout << "Enter a line: ";
    std::string line;
    std::getline(std::cin, line);
    std::cout << "you said: \"" << line << "\"\n";
    std::cout << "length=" << line.size() << "\n";
    return 0;
}
```

### **Custom delimiter**

```cpp
#include <iostream>
#include <string>

int main() {
    std::string csv = "one,two,three,four";
    std::string token;
    std::size_t pos = 0;

    while ((pos = csv.find(',')) != std::string::npos) {
        token = csv.substr(0, pos);
        std::cout << "[" << token << "]\n";
        csv.erase(0, pos + 1);
    }
    std::cout << "[" << csv << "]\n";
    return 0;
}
```

### **Read all lines from stdin**

```cpp
#include <iostream>
#include <string>

int main() {
    std::string line;
    int n = 0;
    while (std::getline(std::cin, line)) {
        std::cout << ++n << ": " << line << "\n";
    }
    return 0;
}
```

```bash
./app < input.txt
```

---

## **14. The `>>` / `getline` Pitfall**

`operator>>` leaves the trailing delimiter in the buffer. If you then call `getline`, you read an empty string.

```cpp
#include <iostream>
#include <string>

int main() {
    int n;
    std::cin >> n;                      // user types: 42<Enter>
    // The \n is still in the input buffer.

    std::string line;
    std::getline(std::cin, line);       // reads the leftover \n -> line is ""!
    std::cout << "n=" << n << " line='" << line << "'\n";
    return 0;
}
```

### **Fix 1 — discard the rest of the line**

```cpp
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
```

### **Fix 2 — use `getline` throughout and parse**

```cpp
#include <iostream>
#include <string>

int main() {
    std::string line;
    std::getline(std::cin, line);
    int n = std::stoi(line);

    std::getline(std::cin, line);       // now it works
    std::cout << "n=" << n << " line='" << line << "'\n";
    return 0;
}
```

### **Resetting state on bad input**

```cpp
#include <iostream>
#include <limits>

int main() {
    int x;
    while (true) {
        std::cout << "Enter int: ";
        if (std::cin >> x) break;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Invalid; try again.\n";
    }
    std::cout << "got " << x << "\n";
    return 0;
}
```

---

## **15. Practice Problems**

- [ ] **Preprocessor peek** — run `g++ -E small.cpp | head -50` on a tiny program. Find the line where `<iostream>` was expanded in.
- [ ] **Macro vs `constexpr`** — implement `SQR` as a macro and `constexpr int sqr(int)`. Try `SQR(++i)` and `sqr(++i)`. Explain the difference.
- [ ] **Stringify + token-paste** — write a `MAKE_PAIR(NAME)` macro that declares two variables `NAME_a` and `NAME_b`. Test it with `MAKE_PAIR(point)`.
- [ ] **Conditional compile** — write a program that prints the OS, compiler, and build time using predefined macros.
- [ ] **`#pragma once` everywhere** — convert three of your existing headers to use `#pragma once` instead of `#ifndef`. Verify they still build in both orders.
- [ ] **Namespace collision** — write two libraries that each define a `connect()` function in different namespaces. Use them from `main` without collision.
- [ ] **Anonymous namespace** — put a helper function in an anonymous namespace in one `.cpp` and try to call it from another `.cpp`. Read the linker error.
- [ ] **`cerr` vs `clog`** — write a program that does a lot of work, prints intermediate progress to `clog`, and prints a final error to `cerr`. Redirect both to separate files and verify the error appears even if the program crashes.
- [ ] **Formatter** — print a table of `(name, age, salary)` rows using `iomanip`. Right-align numerics, left-align names, two decimal places for salary.
- [ ] **`getline` drill** — read a CSV line and split it into a `std::vector<std::string>`. Use a hand-rolled split, not a library.
- [ ] **Stream state machine** — write a loop that reads `int`s until EOF or invalid, prints the sum and count, and recovers from a bad input.
- [ ] **`>>` / `getline` bug** — write the broken version, run it, see the empty-line bug, then fix it with `ignore` or pure `getline`.
