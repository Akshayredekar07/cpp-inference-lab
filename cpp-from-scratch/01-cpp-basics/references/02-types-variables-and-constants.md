# **Variables, Types & Constants**

Data: how to declare variables, every fundamental type you need, all the ways to initialize, const correctness, type inference, type aliases, storage classes, and user-defined aggregate types (enums, structs, unions).

---

## **Table of Contents**

1. Variables
2. Initialization forms and narrowing
3. Fundamental data types
4. Type modifiers and fixed-width integers
5. Character types and encodings
6. `std::string` basics
7. References and pointers
8. Constants — `const`, `constexpr`, `constinit`, `consteval`
9. Type inference — `auto`, `decltype`, `decltype(auto)`
10. Type aliases — `typedef` and `using`
11. Storage classes
12. Enums — unscoped vs `enum class`
13. `struct`
14. `union`
15. `sizeof`, `alignof`, `std::numeric_limits`, `std::is_same_v`
16. Practice problems

---

## **1. Variables**

### **Definition**

- A variable is a named, typed region of storage.
- The type is fixed at compile time (statically typed) and determines size, layout, and operations.
- A **declaration** introduces the name; a **definition** also allocates storage.

```cpp
int x;          // declaration + definition (uninitialized)
int y = 5;      // copy-initialization
int z{7};       // direct-list-initialization
```

### **Object lifetime**

- **Automatic** — local variable in a function. Constructed on entry, destroyed on exit.
- **Static** — namespace-scope, `static` locals, `static` class members. Constructed once, lives until program end.
- **Dynamic** — `new` / `delete`. Programmer controls lifetime. (Covered later.)
- **Thread** — `thread_local` variables. One instance per thread.

### **Scope and name lookup**

- **Block scope** — local variables inside `{ }`.
- **Function scope** — labels (the only things with function scope).
- **Function-parameter scope** — function parameter names.
- **Namespace scope** — names declared at file level.
- **Class scope** — class/struct members.

```cpp
#include <iostream>

int x = 1;                                  // namespace scope

void f() {
    int x = 2;                              // shadows the global
    {
        int x = 3;                          // shadows the function-local
        std::cout << x << "\n";             // 3
    }
    std::cout << x << "\n";                 // 2
}

int main() {
    f();
    std::cout << x << "\n";                 // 1 (the global)
    return 0;
}
```

---

## **2. Initialization Forms and Narrowing**

### **Five forms of initialization**

```cpp
int a = 5;        // copy-initialization
int b(5);          // direct-initialization
int c{5};          // direct-list-initialization
int d = {5};       // copy-list-initialization
int e{};           // value-initialization (zero)
```

### **Why prefer `{}` (brace) initialization**

- It's the only form that **rejects narrowing** at compile time.
- Works for every type — fundamental, class, array, aggregate, container.
- No ambiguity with the "most vexing parse" (`Widget w();` is a function declaration).

```cpp
double d = 3.14;
int n{d};          // COMPILE ERROR: narrowing conversion
int m(d);          // OK at compile time, value is truncated
int k = d;         // OK at compile time, value is truncated
```

### **Value-initialization with `{}`**

```cpp
int i{};                   // 0
double d{};                // 0.0
bool b{};                  // false
char c{};                  // '\0'
int* p{};                  // nullptr
std::string s{};           // empty string
std::vector<int> v{};      // empty vector
```

### **Default member initializers**

```cpp
struct Config {
    int    port   = 8080;
    bool   debug  = false;
    double ratio  = 1.0;
};
```

---

## **3. Fundamental Data Types**

### **The core type table**

| Category | Types | Typical size (64-bit Linux/Windows) |
|----------|-------|-------------------------------------|
| Boolean | `bool` | 1 byte |
| Character | `char`, `signed char`, `unsigned char` | 1 byte |
| Wide char | `wchar_t` | 2 (Windows) / 4 (Linux/macOS) bytes |
| Unicode | `char8_t`, `char16_t`, `char32_t` | 1, 2, 4 bytes |
| Signed integer | `short`, `int`, `long`, `long long` | 2, 4, 8, 8 bytes |
| Unsigned integer | `unsigned short`, `unsigned int`, `unsigned long`, `unsigned long long` | 2, 4, 8, 8 bytes |
| Floating | `float`, `double`, `long double` | 4, 8, 16 bytes |
| Void | `void` | no storage |
| Null pointer | `std::nullptr_t` | pointer size |

### **Basic — declare, initialize, print**

```cpp
#include <iostream>
#include <string>

int main() {
    bool        flag   = true;
    char        letter = 'A';
    int         count  = 42;
    double      ratio  = 0.5;
    std::string text   = "hello";

    std::cout << std::boolalpha
              << flag   << " "
              << letter << " "
              << count  << " "
              << ratio  << " "
              << text   << "\n";
    return 0;
}
```

### **`bool` rules**

- `bool` is either `true` or `false`.
- Implicit conversions: `0`, `0.0`, `nullptr` become `false`; anything else becomes `true`.
- Use `std::boolalpha` to print `true`/`false` instead of `1`/`0`.

```cpp
#include <iostream>

int main() {
    bool a = true;
    bool b = 0;            // false
    bool c = 42;           // true
    std::cout << std::boolalpha << a << " " << b << " " << c << "\n";
    return 0;
}
```

### **Integer and floating basics**

```cpp
#include <iostream>

int main() {
    int    i = -7;
    unsigned u = 7u;
    float  f = 3.14f;          // f suffix = float
    double d = 3.14;           // default = double
    long double ld = 3.14L;    // L suffix = long double

    std::cout << i  << " " << u  << " "
              << f  << " " << d  << " " << ld << "\n";
    return 0;
}
```

### **Literals**

```cpp
int         dec  = 42;
int         hex  = 0x2A;       // hex
int         oct  = 052;        // octal
int         bin  = 0b101010;   // binary (C++14)
unsigned    u    = 42u;
long        l    = 42L;
long long   ll   = 42LL;
unsigned long long ull = 42ull;
float       f    = 1.0f;
double      d    = 1.0;
long double ld   = 1.0L;

long long big = 1'000'000'000'000LL;   // digit separators (C++14)
```

---

## **4. Type Modifiers and Fixed-Width Integers**

### **Modifiers**

- `signed` / `unsigned` — for integer types.
- `short` / `long` / `long long` — adjust width.
- `int` is the default if you say `signed` or `unsigned` alone.

```cpp
#include <iostream>

int main() {
    short           s  = 1;
    long            l  = 1L;
    long long       ll = 1LL;
    unsigned        u  = 1u;
    unsigned long   ul = 1ul;
    signed int      si = -1;     // same as int, explicit sign

    std::cout << sizeof(s)  << " " << sizeof(l)  << " "
              << sizeof(ll) << " " << sizeof(ul) << "\n";
    return 0;
}
```

### **Fixed-width integers (`<cstdint>`)**

If you need exactly N bits, use the fixed-width typedefs. They exist in `<cstdint>` and `<cstddef>`.

| Type | Width | Range |
|------|-------|-------|
| `int8_t`, `uint8_t` | 8 | -128..127 / 0..255 |
| `int16_t`, `uint16_t` | 16 | -32768..32767 / 0..65535 |
| `int32_t`, `uint32_t` | 32 | ~ -2.1e9..2.1e9 / 0..4.3e9 |
| `int64_t`, `uint64_t` | 64 | ~ -9.2e18..9.2e18 / 0..1.8e19 |
| `int_leastN_t` | at least N bits | usually same as fixed-width |
| `int_fastN_t` | at least N bits, fastest type | platform-dependent |

```cpp
#include <cstdint>
#include <iostream>

int main() {
    std::int8_t  i8  = -128;
    std::uint8_t u8  = 255;
    std::int64_t i64 = -9'223'372'036'854'775'807LL;
    std::uint64_t u64 = 18'446'744'073'709'551'615ULL;

    std::cout << +i8  << "\n";          // promote to int for printing
    std::cout << +u8  << "\n";
    std::cout << i64  << "\n";
    std::cout << u64  << "\n";
    return 0;
}
```

**Pitfall:** `int8_t` / `uint8_t` are usually typedefs for `signed char` / `unsigned char`. They print as a character on some systems. Cast to `int` with the unary `+` for numeric output.

### **`size_t` and `ptrdiff_t`**

- `size_t` — unsigned, sizeof-anything, returned by `sizeof`, used for sizes and counts.
- `ptrdiff_t` — signed, result of subtracting two pointers.
- `std::ssize(v)` (C++20) — signed size of a container.

```cpp
#include <cstddef>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v{1, 2, 3};
    std::size_t n = v.size();
    std::cout << "size=" << n << "\n";

    int* a = v.data();
    int* b = a + 2;
    std::ptrdiff_t diff = b - a;
    std::cout << "diff=" << diff << "\n";
    return 0;
}
```

---

## **5. Character Types and Encodings**

### **`char`**

- `char` is exactly 1 byte. It may be `signed` or `unsigned` — **implementation-defined**.
- Use `char` for byte data and ASCII.
- Use `signed char` / `unsigned char` when you need arithmetic or bit ops on small integers.

```cpp
#include <cstdint>
#include <iostream>

int main() {
    char        c  = 'A';
    signed char sc = -1;
    std::cout << c << " " << +sc << "\n";    // A -1
    return 0;
}
```

### **`wchar_t`, `char16_t`, `char32_t`**

- `wchar_t` — wide character, **platform-dependent** width (16-bit on Windows, 32-bit on Linux/macOS). Avoid for portable Unicode.
- `char16_t` — exactly 16 bits, holds one UTF-16 code unit.
- `char32_t` — exactly 32 bits, holds one Unicode code point (or UTF-32 code unit).
- `char8_t` (C++20) — exactly 8 bits, holds one UTF-8 code unit. Distinct from `char`.

```cpp
#include <iostream>
#include <string>
#include <codecvt>   // deprecated in C++17; use third-party ICU for real Unicode

int main() {
    const char*    s8  = "UTF-8 string";
    const wchar_t* sw  = L"wide";
    const char16_t* s16 = u"UTF-16";
    const char32_t* s32 = U"UTF-32";

    std::cout << "s8 length  = " << std::char_traits<char>::length(s8)  << "\n";
    std::cout << "s16 length = " << std::char_traits<char16_t>::length(s16) << "\n";
    std::cout << "s32 length = " << std::char_traits<char32_t>::length(s32) << "\n";

    std::wcout << L"wide: " << sw << L"\n";
    return 0;
}
```

### **Encoding gotchas**

- `L"..."` literals and `std::wstring` are not portable across OSes.
- For real Unicode work, store as `std::string` (UTF-8) or `std::u8string` (C++20).
- `std::u8string` is the modern type for UTF-8 text.

```cpp
#include <iostream>
#include <string>

int main() {
    std::u8string s = u8"こんにちは";    // UTF-8 bytes
    std::cout << "bytes=" << s.size() << "\n";     // 15 (5 chars * 3 bytes)
    return 0;
}
```

---

## **6. `std::string` (Basics)**

`std::string` is a mutable, owning sequence of `char` (or `char8_t` for `std::u8string`).

```cpp
#include <iostream>
#include <string>

int main() {
    std::string s = "roadmap";
    s += " C++";                 // append C-string
    s.push_back('!');            // append single char
    s.append(" 2025");           // append another C-string

    std::cout << s << "\n";                          // roadmap C++! 2025
    std::cout << "size=" << s.size() << "\n";        // 18
    std::cout << "empty=" << std::boolalpha << s.empty() << "\n";
    std::cout << "substr=" << s.substr(0, 7) << "\n";// roadmap
    std::cout << "find C++ at " << s.find("C++") << "\n";
    return 0;
}
```

### **String vs `string_view`**

- `std::string` — owns its characters, manages memory.
- `std::string_view` (C++17) — a non-owning, cheap-to-copy view. Perfect for read-only function parameters.

```cpp
#include <iostream>
#include <string>
#include <string_view>

void print(std::string_view sv) {            // accepts string, literal, char*
    std::cout << "[" << sv << "] size=" << sv.size() << "\n";
}

int main() {
    std::string s = "owned";
    const char* lit = "literal";

    print(s);                                 // copies the view
    print(lit);
    print("another");
    return 0;
}
```

**Caution:** `string_view` does not extend the lifetime of the data it views. Don't store one past the lifetime of the underlying string.

---

## **7. References and Pointers**

### **`T&` — lvalue reference**

- A reference is an alias for an existing object. Must be initialized at declaration.
- Cannot be reseated. Always refers to the same object.
- Cannot be null.

```cpp
#include <iostream>

int main() {
    int  x = 10;
    int& r = x;             // r is an alias for x
    r = 20;                 // x is now 20
    std::cout << x << "\n"; // 20
    return 0;
}
```

### **`T*` — pointer**

- A pointer holds an address. Can be `nullptr`.
- Can be reseated.
- Dereference with `*`, member access with `->`.

```cpp
#include <iostream>

int main() {
    int  v = 5;
    int* p = &v;
    *p = 7;
    std::cout << v << "\n";           // 7

    int* q = nullptr;
    if (q) std::cout << "non-null\n";
    else   std::cout << "null\n";
    return 0;
}
```

### **`const` with pointers (the four combinations)**

```cpp
#include <iostream>

int main() {
    int        v  = 5;
    int*       p1 = &v;            // pointer to int
    const int* p2 = &v;            // pointer to const int    (can't modify v through p2)
    int* const p3 = &v;            // const pointer to int    (can't reseat p3)
    const int* const p4 = &v;      // const pointer to const int

    *p3 = 10;                      // ok
    // p3 = nullptr;              // error
    std::cout << v << "\n";
    return 0;
}
```

Read right-to-left:

- `const int*` — pointer to a const int.
- `int* const` — const pointer to an int.

### **`T&&` — rvalue reference (preview)**

- Binds to temporaries. Used for move semantics (covered in the move-semantics topic).
- `std::move(x)` casts an lvalue to an rvalue.

```cpp
#include <iostream>
#include <string>
#include <utility>

void sink(std::string&& s) { std::cout << "rvalue: " << s << "\n"; }
void sink(const std::string& s) { std::cout << "lvalue: " << s << "\n"; }

int main() {
    std::string name = "Ada";
    sink(name);                     // lvalue overload
    sink(std::move(name));         // rvalue overload
    sink(std::string("temp"));     // rvalue overload
    return 0;
}
```

---

## **8. Constants — `const`, `constexpr`, `constinit`, `consteval`**

### **`const` — runtime immutability**

```cpp
#include <iostream>

int main() {
    const int max = 100;
    // max = 200;                 // ERROR: assignment of read-only variable
    std::cout << max << "\n";
    return 0;
}
```

- `const` at namespace scope has **internal linkage** in C++ (the opposite of C).
- `extern const int X = 5;` in a header + `extern const int X;` in a source gives external linkage.

### **`constexpr` — usable in constant expressions**

```cpp
#include <iostream>

constexpr int square(int x) { return x * x; }     // may run at compile time

int main() {
    constexpr int a = square(5);                 // computed at compile time
    int b = 7;
    int c = square(b);                           // runtime if b is not constexpr
    std::cout << a << " " << c << "\n";          // 25 49
    return 0;
}
```

### **Advanced — `constinit` (C++20) and `consteval` (C++20)**

```cpp
#include <iostream>

constinit int        g_value = 42;                        // compile-time init, runtime mutable
consteval int        must_compile_time(int x) { return x * 2; }

int main() {
    // g_value = 100;                                  // ok, mutable at runtime
    constexpr int v = must_compile_time(5);             // 10, computed at compile time
    int b = 5;
    // int w = must_compile_time(b);                    // ERROR: must be a constant
    std::cout << v << "\n";
    return 0;
}
```

### **The full hierarchy**

| Spec | When initialized | When evaluated | Mutability |
|------|-------------------|----------------|------------|
| `const T x = e;` | runtime or compile time | either | immutable |
| `constexpr T x = e;` | compile time | compile time | immutable |
| `constinit T x = e;` | compile time | compile time | mutable at runtime |
| `consteval F` | — | always at compile time | function is immediate |

### **`const` member functions**

A member function marked `const` promises not to modify the object's observable state. It can be called on `const` objects.

```cpp
#include <iostream>

struct Counter {
    int n = 0;
    int get() const { return n; }            // const: read-only
    void inc()       { ++n; }                // non-const: mutates
};

int main() {
    const Counter c;
    std::cout << c.get() << "\n";
    // c.inc();                              // ERROR
    Counter m;
    m.inc();
    std::cout << m.get() << "\n";
    return 0;
}
```

### **Pitfall — `const` on the pointer, not the pointee**

```cpp
int       v = 0;
const int* p = &v;        // can't modify v *through* p
// *p = 5;                // ERROR

int* const q = &v;        // q is fixed to v, but you can modify v
*q = 5;                   // ok
// q = nullptr;           // ERROR
```

---

## **9. Type Inference — `auto`, `decltype`, `decltype(auto)`**

### **`auto` — let the compiler deduce the type**

```cpp
#include <iostream>
#include <vector>

int main() {
    auto i   = 42;                  // int
    auto d   = 3.14;                // double
    auto s   = std::string("hi");   // std::string
    auto v   = std::vector<int>{1,2,3};

    for (auto it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
    return 0;
}
```

### **`auto` strips references and top-level `const`**

```cpp
#include <iostream>
#include <type_traits>

int main() {
    const int x = 10;
    auto a = x;             // int (const stripped)
    decltype(x) b = x;      // const int (preserved)

    static_assert(!std::is_const_v<decltype(a)>);
    static_assert(std::is_const_v<decltype(b)>);
    return 0;
}
```

### **`decltype(expr)` — the type of an expression**

```cpp
#include <iostream>
#include <type_traits>

int main() {
    int  x = 0;
    int& r = x;
    decltype(x)  a = 1;     // int
    decltype(r)  b = x;     // int&  (reference preserved)
    decltype((x)) c = x;    // int&  (parenthesized lvalue expression is a reference)

    static_assert(std::is_same_v<decltype(a), int>);
    static_assert(std::is_same_v<decltype(b), int&>);
    static_assert(std::is_same_v<decltype(c), int&>);
    return 0;
}
```

### **`decltype(auto)` — deduce using `decltype` rules, return whatever shape**

```cpp
#include <iostream>

int  v = 0;
decltype(auto) read_ref()  { return (v); }   // returns int& — the parens force lvalue
decltype(auto) read_value(){ return  v;  }   // returns int

int main() {
    read_ref() = 7;
    std::cout << v << "\n";                  // 7
    return 0;
}
```

### **`std::declval` — produce a value of any type for compile-time use**

```cpp
#include <type_traits>
#include <utility>

template <typename T>
auto add(T a, T b) -> decltype(a + b) { return a + b; }

int main() {
    static_assert(std::is_same_v<decltype(add(1, 2)), int>);
    static_assert(std::is_same_v<decltype(add(1.0, 2.0)), double>);
}
```

### **When to use what**

- `auto` — local variables, range-`for`, lambdas. Saves typing and avoids unintended conversions.
- `decltype` — when you need the exact type, especially with templates.
- `decltype(auto)` — perfect-forwarding return types.
- Be explicit with type when the deduced type is not obvious to the reader.

---

## **10. Type Aliases — `typedef` and `using`**

### **`typedef` — the C-style alias**

```cpp
#include <vector>
typedef std::vector<int> IntVec;
```

### **`using` — the C++11 alias (preferred)**

```cpp
#include <vector>
using IntVec = std::vector<int>;
```

### **Alias templates — `typedef` cannot do this**

```cpp
#include <vector>
#include <list>

template <typename T>
using Vec = std::vector<T>;

int main() {
    Vec<int>    a{1, 2, 3};
    Vec<double> b{1.1, 2.2};
    (void)a; (void)b;
}
```

### **Why prefer `using`**

- Reads left-to-right (`using Foo = Bar;`).
- Works for templates.
- Compatible with template metaprogramming.

---

## **11. Storage Classes**

| Specifier | Where | Meaning |
|-----------|-------|---------|
| `auto` (legacy) | local | Default since C++11 — same word, different meaning (type inference). |
| `register` | local | Hint to put in a register. **Removed in C++17** — still accepted as a no-op. |
| `static` | namespace scope | Internal linkage — name is local to this TU. |
| `static` | block scope | One instance across all calls; initialized once. |
| `static` | class scope | Shared by all instances of the class (covered in the OOP topic). |
| `extern` | namespace scope | Declares a name with external linkage, defined in another TU. |
| `mutable` | class member | Can be modified even in a `const` object or `const` method. |
| `thread_local` | any | One instance per thread. |

```cpp
#include <iostream>

static int file_local = 1;       // internal linkage — only this TU sees it
extern int shared_counter;       // declared, defined in another TU

void counter_demo() {
    static int calls = 0;        // persists across calls
    ++calls;
    std::cout << "called " << calls << " times\n";
}

struct Cache {
    mutable int hits = 0;        // modified even in const methods
    void touch() const { ++hits; }
};

int main() {
    counter_demo();
    counter_demo();

    const Cache c;
    c.touch(); c.touch();
    std::cout << "hits=" << c.hits << "\n";

    thread_local int tls = 0;     // one per thread
    ++tls;
    std::cout << "tls=" << tls << "\n";
    return 0;
}
```

### **`thread_local` example with two threads**

```cpp
#include <iostream>
#include <thread>

thread_local int tls = 0;

void work() {
    ++tls;
    std::cout << "thread-local tls = " << tls << "\n";
}

int main() {
    std::thread t1(work);
    std::thread t2(work);
    t1.join();
    t2.join();
    return 0;
}
```

```bash
g++ -std=c++17 main.cpp -o app -pthread
```

---

## **12. Enums — Unscoped vs `enum class`**

### **Unscoped `enum`**

```cpp
#include <iostream>

enum Color { RED, GREEN, BLUE };     // underlying type is implementation-defined

int main() {
    Color c = GREEN;
    std::cout << "c=" << c << "\n";  // 1 (implicit conversion to int)
    return 0;
}
```

- Names leak into the enclosing scope (`RED`, `GREEN`, `BLUE` are visible globally).
- Implicit conversion to `int` is allowed.
- Specifying values and underlying type:

```cpp
#include <cstdint>
enum class Status : std::uint8_t { OK = 0, Warn = 10, Error = 20 };
```

### **`enum class` (scoped, strongly typed) — preferred**

```cpp
#include <cstdint>
#include <iostream>

enum class Http : std::uint16_t { OK = 200, NotFound = 404, ServerError = 500 };

int main() {
    Http code = Http::NotFound;
    std::cout << "size=" << sizeof(code) << " val=" << static_cast<int>(code) << "\n";

    switch (code) {
        case Http::OK:          std::cout << "ok\n";  break;
        case Http::NotFound:    std::cout << "404\n"; break;
        case Http::ServerError: std::cout << "500\n"; break;
    }
    return 0;
}
```

- No name leakage — `Http::OK` not `OK`.
- No implicit conversion to `int` — must use `static_cast`.
- Forward-declarable: `enum class E : int;`.

### **When to use which**

- Default to `enum class`.
- Use unscoped `enum` only for plain integer flags where implicit conversion is desired (rare, mostly in C-interop code).

---

## **13. `struct`**

A `struct` is a class whose default access is `public`. Use it for plain data aggregates.

### **Basic — POD aggregate**

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
#include <cmath>
#include <iostream>

struct Vec2 {
    double x{0.0};
    double y{0.0};

    Vec2() = default;
    Vec2(double a, double b) : x(a), y(b) {}

    double length() const { return std::sqrt(x * x + y * y); }
    Vec2 operator+(const Vec2& o) const { return {x + o.x, y + o.y}; }
};

int main() {
    Vec2 a(3.0, 4.0);
    Vec2 b(1.0, 2.0);
    Vec2 c = a + b;
    std::cout << a.length() << " " << c.x << "," << c.y << "\n";
    return 0;
}
```

### **Advanced — designated initializers (C++20) and aggregate init**

```cpp
#include <iostream>

struct Config {
    int    port;
    bool   tls;
    int    timeout_ms;
    double ratio;
};

int main() {
    Config c1{8080, true, 500, 1.5};                  // positional
    Config c2{.port = 9090, .tls = false,
               .timeout_ms = 1000, .ratio = 0.25};    // designated (C++20)
    std::cout << c1.port << " " << c2.port << "\n";
    return 0;
}
```

### **Best practices for `struct`**

- Keep data members public.
- Provide a default constructor either explicitly or via in-class initializers.
- Use `[[nodiscard]]` on accessors that return important values.
- Add a `to_string()` or `operator<<` overload for logging.

---

## **14. `union`**

A `union` declares several members in the same memory. Only one member is "active" at a time.

### **Basic — type-punning a 32-bit value into bytes**

```cpp
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>

union U32 {
    std::uint32_t word;
    std::uint8_t  bytes[4];
};

int main() {
    U32 u;
    u.word = 0x12345678;
    std::cout << std::hex << std::setfill('0');
    for (int i = 0; i < 4; ++i) {
        std::cout << std::setw(2) << static_cast<int>(u.bytes[i]) << " ";
    }
    std::cout << "\n";
    return 0;
}
```

**Output (little-endian):** `78 56 34 12`

### **Intermediate — tagged union with `std::variant` (preferred)**

A raw `union` is error-prone because you can read the wrong member. C++17's `std::variant` is the type-safe alternative.

```cpp
#include <iostream>
#include <string>
#include <variant>

int main() {
    std::variant<int, double, std::string> v;

    v = 42;
    std::cout << "int: "    << std::get<int>(v)       << "\n";

    v = 3.14;
    std::cout << "double: " << std::get<double>(v)    << "\n";

    v = "hello"s;
    std::cout << "string: " << std::get<std::string>(v) << "\n";

    std::visit([](auto&& x) {
        using T = std::decay_t<decltype(x)>;
        if constexpr (std::is_same_v<T, int>)        std::cout << "got int\n";
        else if constexpr (std::is_same_v<T, double>) std::cout << "got double\n";
        else                                          std::cout << "got string\n";
    }, v);
    return 0;
}
```

### **When to use raw `union`**

- Embedded / OS work where you need a fixed layout and exact size.
- Type-punning via `std::bit_cast` (C++20) is the modern, safer alternative.

```cpp
#include <bit>
#include <cstdint>
#include <iostream>

int main() {
    float f = 3.14f;
    std::uint32_t bits = std::bit_cast<std::uint32_t>(f);
    float back = std::bit_cast<float>(bits);
    std::cout << std::hex << bits << " " << back << "\n";
    return 0;
}
```

---

## **15. `sizeof`, `alignof`, `std::numeric_limits`, `std::is_same_v`**

### **Sizes and alignment**

```cpp
#include <iostream>

int main() {
    std::cout << "sizeof(int)        = " << sizeof(int)        << "\n";
    std::cout << "sizeof(double)     = " << sizeof(double)     << "\n";
    std::cout << "alignof(int)       = " << alignof(int)       << "\n";
    std::cout << "alignof(long long) = " << alignof(long long) << "\n";
    return 0;
}
```

### **Numeric limits**

```cpp
#include <iostream>
#include <limits>

int main() {
    std::cout << "int min  = " << std::numeric_limits<int>::min()        << "\n";
    std::cout << "int max  = " << std::numeric_limits<int>::max()        << "\n";
    std::cout << "dbl eps  = " << std::numeric_limits<double>::epsilon()  << "\n";
    std::cout << "dbl min  = " << std::numeric_limits<double>::min()      << "\n";
    std::cout << "dbl max  = " << std::numeric_limits<double>::max()      << "\n";
    std::cout << "is int signed? " << std::numeric_limits<int>::is_signed << "\n";
    return 0;
}
```

### **Compile-time type queries (`<type_traits>`)**

```cpp
#include <iostream>
#include <type_traits>

int main() {
    static_assert(std::is_same_v<int, int>);
    static_assert(std::is_integral_v<int>);
    static_assert(std::is_floating_point_v<double>);
    static_assert(!std::is_pointer_v<int>);

    std::cout << "int is_integral = " << std::is_integral_v<int>        << "\n";
    std::cout << "int* is_pointer  = " << std::is_pointer_v<int*>       << "\n";
    return 0;
}
```

---

## **16. Practice Problems**

- [ ] **Type-size reporter** — print `sizeof` for every fundamental type and a raw pointer. Save the output; this is your machine's type-size cheat sheet.
- [ ] **Narrowing detector** — write a program that uses brace-init with narrowing. Confirm the compile error, then fix with explicit `static_cast`.
- [ ] **Wide-char comparison** — print `sizeof(wchar_t)`, `sizeof(char16_t)`, `sizeof(char32_t)`. If you have access to both Windows and Linux, run on each and compare.
- [ ] **UTF-8 string** — write `"hello"` and a 3-character CJK string into `std::u8string`. Print `size()` for both. Explain the byte count.
- [ ] **Const correctness drill** — write a struct with several methods, mark some `const`, then call them on both `const` and non-`const` objects. Read every compile error.
- [ ] **`constexpr` factorial** — write `constexpr int factorial(int n)` and call it in a `static_assert` for `n = 5` and `n = 10`.
- [ ] **`auto` vs `decltype`** — write a small template helper `template <class T> T&& my_forward(T& x) { return static_cast<T&&>(x); }`. Inside `main`, use `decltype` to print the deduced type of `my_forward(x)`.
- [ ] **Enum class switch** — define `enum class Command { Quit, Save, Load, Edit }`. Write a `switch` on it that prints the command and rejects unknown values. The compiler should warn if you forget a case (`-Wswitch`).
- [ ] **Tagged union** — implement a small `Value` type that can be `int`, `double`, or `std::string` using `std::variant` and `std::visit`. Add a `print` visitor.
- [ ] **Storage classes** — write one program with a function-local `static` counter, a file-scope `static` int, an `extern` int (defined in another TU), a `mutable` member, and a `thread_local` int. Build as two TUs and link.
- [ ] **`numeric_limits` formatters** — print min/max for `int`, `long`, `long long`, `float`, `double`. Format the float min in scientific notation.
- [ ] **`bit_cast`** — take a `float`, `bit_cast` it to `uint32_t`, then back. Compare with the C-style punning via `union` from section 14.

