# **Operators & Control Flow**

The two halves of actually doing things: every operator C++ inherits from C plus the C++-specific ones (scope resolution, casts, three-way, etc.), and every control-flow construct including range-`for` and structured bindings.

---

## **Table of Contents**

1. Operators overview and precedence
2. Arithmetic operators
3. Relational and equality operators
4. Logical operators
5. Bitwise operators
6. Assignment and compound assignment
7. Increment and decrement
8. Member access and pointer operators
9. Conditional (ternary) and comma
10. `sizeof`, `alignof`, `typeid`, `noexcept`
11. Scope resolution `::` and the unconditional goto-less forms
12. Cast operators (preview)
13. Operator overloading (preview)
14. `if` / `else`
15. `switch` / `case` / `default`
16. `while` and `do-while`
17. `for` and range-`for`
18. `break`, `continue`
19. `goto` and labels
20. Structured bindings (C++17)
21. Practice problems

---

## **1. Operators Overview and Precedence**

C++ has every C operator, plus a few of its own. Operator precedence determines grouping; associativity determines direction.

### **Precedence table (high to low)**

| Level | Operators | Associativity |
|-------|-----------|---------------|
| 1 (highest) | `::` (scope resolution) | left-to-right |
| 2 | `()` `[]` `->` `.` `++` `--` (postfix) | left-to-right |
| 3 | `++` `--` `+` `-` `!` `~` `*` `&` `(type)` `sizeof` `noexcept` `co_await` (prefix) | right-to-left |
| 4 | `*` `/` `%` | left-to-right |
| 5 | `+` `-` | left-to-right |
| 6 | `<<` `>>` | left-to-right |
| 7 | `<=>` (C++20) | left-to-right |
| 8 | `<` `<=` `>` `>=` | left-to-right |
| 9 | `==` `!=` | left-to-right |
| 10 | `&` (bitwise) | left-to-right |
| 11 | `^` | left-to-right |
| 12 | `|` | left-to-right |
| 13 | `&&` | left-to-right |
| 14 | `\|\|` | left-to-right |
| 15 | `?:` (ternary) | right-to-left |
| 16 | `=` `+=` `-=` `*=` `/=` `%=` `<<=` `>>=` `&=` `^=` `\|=` | right-to-left |
| 17 | `,` | left-to-right |

When in doubt, parenthesize. Precedence bugs are a top source of subtle logic errors.

---

## **2. Arithmetic Operators**

```cpp
#include <iostream>

int main() {
    int a = 7, b = 2;
    std::cout << "a + b = " << (a + b) << "\n";    // 9
    std::cout << "a - b = " << (a - b) << "\n";    // 5
    std::cout << "a * b = " << (a * b) << "\n";    // 14
    std::cout << "a / b = " << (a / b) << "\n";    // 3  (integer division)
    std::cout << "a % b = " << (a % b) << "\n";    // 1
    return 0;
}
```

### **Integer division vs floating division**

```cpp
#include <iostream>

int main() {
    int    i = 7, j = 2;
    double d = 7.0 / 2.0;        // 3.5
    std::cout << (i / j) << "\n";      // 3
    std::cout << (d)      << "\n";     // 3.5
    return 0;
}
```

### **Unary `+`, `-`**

```cpp
int a = 5;
int b = -a;             // -5
int c = +a;             // 5 (also used to promote char to int for printing)
```

### **Pitfalls**

- `a / b` for integers truncates toward zero. `-7 / 2 == -3` (not `-4`).
- `a % b` is undefined if `b == 0`.
- Unary minus on `unsigned` can wrap: `-1u` is a huge positive value.

---

## **3. Relational and Equality Operators**

Return `bool`.

```cpp
#include <iostream>

int main() {
    int a = 3, b = 5;
    std::cout << std::boolalpha;
    std::cout << "a == b = " << (a == b) << "\n";   // false
    std::cout << "a != b = " << (a != b) << "\n";   // true
    std::cout << "a <  b = " << (a <  b) << "\n";   // true
    std::cout << "a >= b = " << (a >= b) << "\n";   // false
    return 0;
}
```

**Pitfall — assignment vs comparison**

```cpp
int x = 0;
if (x = 5) {                  // BUG: assigns 5, always true
    // ...
}
if (x == 5) {                 // correct
    // ...
}
```

Compilers warn about this with `-Wparentheses`. Some teams force it on with `-Werror=parentheses`.

---

## **4. Logical Operators**

- `&&` — logical AND (short-circuit).
- `||` — logical OR (short-circuit).
- `!` — logical NOT.

Short-circuit means the right operand is **not evaluated** if the left decides.

```cpp
#include <iostream>

int side_effect(int x) {
    std::cout << "called with " << x << "\n";
    return x;
}

int main() {
    if (side_effect(0) && side_effect(1)) {    // second NOT called
        std::cout << "both nonzero\n";
    }
    if (side_effect(1) || side_effect(2)) {    // second NOT called
        std::cout << "at least one nonzero\n";
    }
    return 0;
}
```

**Pitfall — `&` vs `&&`**

```cpp
int x = 0;
if (x & 1)  { }     // bitwise — non-zero => true, but no short-circuit
if (x && 1) { }     // logical — short-circuits, returns bool
```

---

## **5. Bitwise Operators**

- `&` — bitwise AND.
- `|` — bitwise OR.
- `^` — bitwise XOR.
- `~` — bitwise NOT (one's complement).
- `<<` — left shift (multiplies by 2^N for unsigned).
- `>>` — right shift (signed: implementation-defined sign extension; unsigned: zero fill).

```cpp
#include <cstdint>
#include <iostream>

int main() {
    std::uint8_t x = 0b1010'1100;
    std::uint8_t y = 0xF0;

    std::cout << "x & y = " << (x & y)  << "\n";      // 0xA0 = 160
    std::cout << "x | y = " << (x | y)  << "\n";      // 0xFC = 252
    std::cout << "x ^ y = " << (x ^ y)  << "\n";      // 0x5C = 92
    std::cout << "~x    = " << (~x)     << "\n";      // 0x53 = 83 (with promotion)
    std::cout << "x<<2  = " << (x << 2) << "\n";      // 0x2B0 = 688

    // Mask off low nibble
    std::uint8_t low = x & 0x0F;                      // 0x0C
    std::uint8_t high = (x >> 4) & 0x0F;              // 0x0A
    std::cout << "low=" << +low << " high=" << +high << "\n";
    return 0;
}
```

### **Bit flags**

```cpp
#include <cstdint>
#include <iostream>

enum Perms : std::uint8_t { None=0, Read=1, Write=2, Exec=4 };

int main() {
    std::uint8_t p = Read | Write;
    std::cout << "can read? " << bool(p & Read)  << "\n";
    std::cout << "can exec? " << bool(p & Exec)  << "\n";
    p |= Exec;                                          // add flag
    std::cout << "now can exec? " << bool(p & Exec) << "\n";
    return 0;
}
```

**Pitfall — shifting**

- `x << n` is undefined if `n >= width` or negative.
- `x >> n` on a negative signed value is implementation-defined.
- Don't shift by a runtime value unless you've checked the bounds.

---

## **6. Assignment and Compound Assignment**

- `=` — plain assignment.
- `+=` `-=` `*=` `/=` `%=` — arithmetic.
- `<<=` `>>=` `&=` `^=` `|=` — bitwise.

```cpp
#include <iostream>

int main() {
    int x = 10;
    x += 5;     // x = 15
    x *= 2;     // x = 30
    x >>= 1;    // x = 15
    std::cout << x << "\n";
    return 0;
}
```

**Pitfall — chained assignment**

```cpp
int a, b, c;
a = b = c = 5;          // all three are 5, but reads right-to-left
```

**Pitfall — confusing `=` and `==`**

- `if (x = 0)` is assignment, always evaluates to 0 (false).
- `if (x == 0)` is comparison.

---

## **7. Increment and Decrement**

- `++x` (prefix) — increment, return new value.
- `x++` (postfix) — increment, return old value.
- Same for `--`.

```cpp
#include <iostream>

int main() {
    int i = 5;
    int a = ++i;     // i is 6, a is 6
    int b = i++;     // i is 7, b is 6
    std::cout << a << " " << b << " " << i << "\n";   // 6 6 7
    return 0;
}
```

**Pitfall — undefined behavior**

- `int i = 0; i = i++ + 1;` is UB (modifying a variable twice between sequence points).
- Don't use `++` on a variable more than once in the same expression.

---

## **8. Member Access and Pointer Operators**

- `.` — member of an object.
- `->` — member of an object through a pointer.
- `*` — dereference.
- `&` — address-of (or bitwise AND in expression context).

```cpp
#include <iostream>
#include <string>

struct User { std::string name; int age; };

int main() {
    User u{"Ada", 36};
    User* p = &u;

    std::cout << u.name    << "\n";     // Ada (.)
    std::cout << p->age    << "\n";     // 36 (->)
    std::cout << (*p).name << "\n";     // Ada (dereference then .)
    return 0;
}
```

**Pitfall — `->` and `.` precedence**

`p->name.size()` parses as `(p->name).size()` — correct. Be careful with templates and smart pointers.

---

## **9. Conditional (Ternary) and Comma**

### **Ternary `? :`**

```cpp
#include <iostream>

int main() {
    int a = 10, b = 20;
    int max = (a > b) ? a : b;
    std::cout << max << "\n";                       // 20

    const char* sign = (a > 0) ? "positive" : (a < 0) ? "negative" : "zero";
    std::cout << sign << "\n";
    return 0;
}
```

- Returns either the second or third operand (a value).
- Use for short decisions. Avoid chaining — it kills readability.

### **Comma operator**

The comma operator evaluates both operands and returns the right one. Lowest precedence.

```cpp
#include <iostream>

int main() {
    int a = (1, 2, 3);          // a = 3
    int b = (std::cout << "x", 5);
    std::cout << a << " " << b << "\n";    // 3 5
    return 0;
}
```

- Most commas in C++ are **not** the comma operator — they're separators in declaration lists, function call argument lists, and initializer lists.

---

## **10. `sizeof`, `alignof`, `typeid`, `noexcept`**

### **`sizeof`**

Compile-time size of a type or expression. Result is `size_t`.

```cpp
#include <iostream>
#include <vector>

int main() {
    std::cout << sizeof(int)           << "\n";   // 4
    std::cout << sizeof(std::string)   << "\n";   // implementation-defined
    int x = 0;
    std::cout << sizeof(x)             << "\n";   // 4 (parentheses optional for variables)
    return 0;
}
```

### **`alignof` (C++11)**

Alignment requirement of a type.

```cpp
#include <iostream>

struct alignas(16) Vec4 { float x, y, z, w; };

int main() {
    std::cout << "alignof(int)     = " << alignof(int)     << "\n";
    std::cout << "alignof(double)  = " << alignof(double)  << "\n";
    std::cout << "alignof(Vec4)    = " << alignof(Vec4)    << "\n";
    return 0;
}
```

### **`typeid` (RTTI)**

Returns a `std::type_info` describing the dynamic type of an expression.

```cpp
#include <iostream>
#include <typeinfo>
#include <vector>

int main() {
    int x = 0;
    std::vector<int> v;
    std::cout << typeid(x).name() << "\n";       // i (GCC)
    std::cout << typeid(v).name() << "\n";       // St6vectorIiSaIiEE
    return 0;
}
```

**Use sparingly** — `typeid` requires RTTI. For a stable, portable name, use `typeid(x).name()` and demangle with `abi::__cxa_demangle` (GCC/Clang) or just compare types via `std::is_same_v` at compile time.

### **`noexcept` operator**

`noexcept(expr)` is a compile-time `bool` indicating whether `expr` is declared non-throwing.

```cpp
#include <iostream>

void f() noexcept {}
void g()         {}

int main() {
    std::cout << noexcept(f()) << "\n";   // 1
    std::cout << noexcept(g()) << "\n";   // 0
    return 0;
}
```

---

## **11. Scope Resolution `::` and `using` Mechanics**

`::` is the C++-specific "name lookup" operator.

```cpp
#include <iostream>

int x = 1;

namespace app {
    int x = 2;
    namespace inner {
        int x = 3;
    }
    struct S { static int x; };
    int S::x = 4;
}

int main() {
    std::cout << x                      << "\n";   // 1 (global)
    std::cout << ::x                    << "\n";   // 1 (explicit global)
    std::cout << app::x                 << "\n";   // 2
    std::cout << app::inner::x          << "\n";   // 3
    std::cout << app::S::x              << "\n";   // 4
    return 0;
}
```

### **`::` with classes and enums**

```cpp
#include <iostream>

struct Counter {
    static int total;
    int value = 0;
    enum class Mode { Up, Down };
};

int Counter::total = 0;       // define static member

int main() {
    Counter c;
    Counter::total++;
    std::cout << Counter::total << "\n";
    Counter::Mode m = Counter::Mode::Up;
    std::cout << static_cast<int>(m) << "\n";
    return 0;
}
```

---

## **12. Cast Operators (Preview)**

C-style `(T)x` is a single operator that can mean four different things. Prefer the named C++ casts.

| Cast | Use |
|------|-----|
| Implicit | Trivial conversions (int ↔ double, derived* → base*). |
| `static_cast<T>(x)` | Compile-time-checked conversions between related types. |
| `const_cast<T>(x)` | Add or strip `const` / `volatile`. |
| `reinterpret_cast<T>(x)` | Low-level bit reinterpretation (pointer ↔ integer, unrelated pointer types). |
| `dynamic_cast<T>(x)` | Safe downcast in a polymorphic hierarchy; needs RTTI. |
| `std::bit_cast<T>(x)` (C++20) | Type-punning with the same size. |

```cpp
#include <iostream>

struct Base { virtual ~Base() = default; };
struct Derived : Base { void hello() { std::cout << "hi\n"; } };

int main() {
    double d = 3.99;
    int    i = static_cast<int>(d);                      // 3
    std::cout << i << "\n";

    const int c = 42;
    int& r = const_cast<int&>(c);                        // strip const (only if c was not actually const-initialized)
    r = 43;
    std::cout << c << " " << r << "\n";

    Base*    b = new Derived;
    Derived* p = dynamic_cast<Derived*>(b);
    if (p) p->hello();

    std::uintptr_t addr = reinterpret_cast<std::uintptr_t>(b);
    Base* back = reinterpret_cast<Base*>(addr);
    std::cout << (b == back) << "\n";

    delete b;
    return 0;
}
```

**Rules**

- Never use C-style casts in modern C++.
- `reinterpret_cast` is almost always wrong outside OS / driver code and serialization.
- `dynamic_cast` adds a runtime check; prefer `std::variant` or virtual dispatch.

---

## **13. Operator Overloading (Preview)**

You can define what most operators do for your own types. (Full coverage in the operator-overloading topic.)

```cpp
#include <iostream>

struct Vec2 {
    double x{0}, y{0};
    Vec2 operator+(const Vec2& o) const { return {x + o.x, y + o.y}; }
    Vec2& operator+=(const Vec2& o)     { x += o.x; y += o.y; return *this; }
};

std::ostream& operator<<(std::ostream& os, const Vec2& v) {
    return os << "(" << v.x << ", " << v.y << ")";
}

int main() {
    Vec2 a{1, 2}, b{3, 4};
    Vec2 c = a + b;
    std::cout << c << "\n";           // (4, 6)
    a += b;
    std::cout << a << "\n";           // (4, 6)
    return 0;
}
```

**Rules**

- Don't overload operators whose meaning would be surprising (`&&`, `||`, `,`).
- Make `operator==` and `operator<<` free functions when possible.
- After defining `==`, define `!=` and (C++20) `<=>` to keep them consistent.

---

## **14. `if` / `else`**

### **Basic**

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

### **Init-statement (C++17)**

```cpp
#include <iostream>
#include <map>

int main() {
    std::map<std::string, int> ages{{"Ada", 36}, {"Lin", 41}};

    if (auto it = ages.find("Lin"); it != ages.end()) {   // `it` is scoped to both branches
        std::cout << it->first << "=" << it->second << "\n";
    } else {
        std::cout << "not found\n";
    }
    return 0;
}
```

### **`const`/`constexpr` in conditions**

```cpp
#include <iostream>

int main() {
    if (const int x = 7; x > 0) {       // C++17 init-statement + condition
        std::cout << "yes " << x << "\n";
    }
    return 0;
}
```

### **`if constexpr` (C++17) — for templates**

`if constexpr` discards the non-taken branch at compile time. No instantiation of the discarded branch.

```cpp
#include <iostream>
#include <type_traits>

template <typename T>
auto format(T v) {
    if constexpr (std::is_integral_v<T>) {
        return std::to_string(v);
    } else if constexpr (std::is_floating_point_v<T>) {
        return std::to_string(static_cast<long double>(v));
    } else {
        return std::string(v);
    }
}

int main() {
    std::cout << format(7)    << "\n";
    std::cout << format(3.14) << "\n";
    std::cout << format("hi") << "\n";
    return 0;
}
```

---

## **15. `switch` / `case` / `default`**

### **Basic**

```cpp
#include <iostream>

int main() {
    int day = 3;
    switch (day) {
        case 1: std::cout << "Monday\n";    break;
        case 2: std::cout << "Tuesday\n";   break;
        case 3: std::cout << "Wednesday\n"; break;
        case 4: std::cout << "Thursday\n";  break;
        case 5: std::cout << "Friday\n";    break;
        case 6: std::cout << "Saturday\n";  break;
        case 7: std::cout << "Sunday\n";    break;
        default: std::cout << "Invalid\n";
    }
    return 0;
}
```

### **Fall-through (intentional)**

```cpp
#include <iostream>

int main() {
    int month = 4;
    switch (month) {
        case 12: case 1: case 2:
            std::cout << "Winter\n"; break;
        case 3: case 4: case 5:
            std::cout << "Spring\n"; break;
        case 6: case 7: case 8:
            std::cout << "Summer\n"; break;
        case 9: case 10: case 11:
            std::cout << "Autumn\n"; break;
        default:
            std::cout << "Invalid\n";
    }
    return 0;
}
```

Mark intentional fall-through with `[[fallthrough]];` (C++17) so the compiler doesn't warn.

```cpp
switch (cmd) {
    case 1:
        // do A
        [[fallthrough]];
    case 2:
        // do A and B
        break;
}
```

### **`switch` rules**

- The condition is converted to integer or enum.
- `case` values must be constant expressions.
- `default` is optional; put it where it makes sense.
- Use `-Wswitch` to catch missing cases.

### **`switch` vs `if-else-if`**

- `switch` — single variable compared against several constant values.
- `if-else-if` — range checks, complex boolean expressions, runtime-typed values.

### **Init-statement in `switch` (C++17)**

```cpp
#include <iostream>

int main() {
    switch (int x = 3; x) {
        case 1: std::cout << "one\n";   break;
        case 3: std::cout << "three\n"; break;
        default: std::cout << "other\n";
    }
    return 0;
}
```

---

## **16. `while` and `do-while`**

### **`while` — test first, may not run at all**

```cpp
#include <iostream>

int main() {
    int i = 1;
    while (i <= 5) {
        std::cout << i << " ";
        ++i;
    }
    std::cout << "\n";
    return 0;
}
```

### **Input validation pattern**

```cpp
#include <iostream>

int main() {
    int n;
    std::cout << "Enter positive: ";
    std::cin >> n;
    while (n <= 0) {
        std::cout << "Invalid. Try again: ";
        std::cin >> n;
    }
    std::cout << "Got " << n << "\n";
    return 0;
}
```

### **`do-while` — test after, runs at least once**

```cpp
#include <iostream>

int main() {
    int choice = 0;
    do {
        std::cout << "\n1) Hello\n2) Quit\n> ";
        std::cin >> choice;
    } while (choice != 2);
    return 0;
}
```

Use `do-while` when the loop body must execute at least once — typical for menu prompts and "try, then check" patterns.

---

## **17. `for` and range-`for`**

### **Classic `for`**

```cpp
#include <iostream>

int main() {
    for (int i = 0; i < 5; ++i) {
        std::cout << i << " ";
    }
    std::cout << "\n";
    return 0;
}
```

### **Multiple variables and a step**

```cpp
#include <iostream>

int main() {
    for (int i = 0, j = 10; i < j; ++i, --j) {
        std::cout << "i=" << i << " j=" << j << "\n";
    }
    return 0;
}
```

### **Infinite `for`**

```cpp
for (;;) {
    // break out when condition met
}
```

### **Range-`for` (C++11) — iterate over a range**

```cpp
#include <iostream>
#include <vector>
#include <map>

int main() {
    std::vector<int> v{1, 2, 3, 4, 5};
    for (int x : v) {                       // copy
        std::cout << x << " ";
    }
    std::cout << "\n";

    for (const auto& x : v) {               // read-only, no copy
        std::cout << x * 2 << " ";
    }
    std::cout << "\n";

    std::map<std::string, int> ages{{"Ada", 36}, {"Lin", 41}};
    for (const auto& [name, age] : ages) {  // structured binding (C++17)
        std::cout << name << "=" << age << " ";
    }
    std::cout << "\n";
    return 0;
}
```

### **Init-statement in `for` (C++20)**

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v{1, 2, 3};
    for (auto it = v.begin(); auto x : {10, 20, 30}) {
        (void)it;  // init-statement runs once before the loop
        std::cout << x << " ";
    }
    std::cout << "\n";
    return 0;
}
```

---

## **18. `break`, `continue`**

### **`break` — exit the nearest enclosing loop or `switch`**

```cpp
#include <iostream>

int main() {
    for (int i = 1; i <= 100; ++i) {
        if (i % 7 == 0) {
            std::cout << "first multiple of 7: " << i << "\n";
            break;
        }
    }
    return 0;
}
```

In nested loops, `break` only exits the innermost loop. To exit multiple levels, use a flag, a lambda, or `goto`.

### **`continue` — skip to the next iteration**

```cpp
#include <iostream>

int main() {
    for (int i = 1; i <= 10; ++i) {
        if (i % 2 == 0) continue;            // skip even
        std::cout << i << " ";
    }
    std::cout << "\n";
    return 0;
}
```

---

## **19. `goto` and Labels**

`goto` jumps unconditionally to a labeled statement in the same function.

```cpp
#include <iostream>

int main() {
    int n = 0, sum = 0;
input:
    std::cout << "Enter number (0 to stop): ";
    std::cin >> n;
    if (n == 0) goto end;
    sum += n;
    goto input;
end:
    std::cout << "Sum: " << sum << "\n";
    return 0;
}
```

### **Breaking out of nested loops**

```cpp
#include <iostream>

int main() {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (i * j > 6) goto done;
            std::cout << "(" << i << "," << j << ") ";
        }
    }
done:
    std::cout << "\nexited\n";
    return 0;
}
```

**Use sparingly.** Modern C++ prefers:

- Extract the inner work into a function and `return` from it.
- Use a flag variable.
- Use a `do { ... } while(0)` with `break` (one level only).

```cpp
bool found = false;
for (...) {
    for (...) {
        if (cond) { found = true; break; }
    }
    if (found) break;
}
```

---

## **20. Structured Bindings (C++17)**

Structured bindings let you destructure tuples, pairs, arrays, and aggregates.

```cpp
#include <iostream>
#include <map>
#include <string>
#include <utility>

std::pair<int, int> divide(int a, int b) {
    return {a / b, a % b};
}

int main() {
    auto [q, r] = divide(17, 5);                // pair
    std::cout << "q=" << q << " r=" << r << "\n";

    int arr[]{1, 2, 3};
    auto [a, b, c] = arr;                       // array
    std::cout << a << b << c << "\n";

    struct Point { double x, y; };
    Point p{3.0, 4.0};
    auto [x, y] = p;                            // aggregate
    std::cout << "(" << x << "," << y << ")\n";

    std::map<std::string, int> ages{{"Ada", 36}, {"Lin", 41}};
    for (const auto& [name, age] : ages) {
        std::cout << name << "=" << age << " ";
    }
    std::cout << "\n";
    return 0;
}
```

**Rules**

- The number of identifiers must equal the number of elements.
- Use `auto&` (or `const auto&`) to avoid copies.
- For arrays, the type must be a plain array (decay doesn't apply for binding).

---

## **21. Practice Problems**

- [ ] **Operator playground** — for every operator category in this file, write a one-line program that uses it and prints the result.
- [ ] **Bit flag parser** — define `enum Perms : uint8_t { None=0, Read=1, Write=2, Exec=4 }`. Write functions `has(perms, flag)`, `add(perms, flag)`, `remove(perms, flag)`. Test combinations.
- [ ] **Integer division bug** — write a program that averages two ints. It must output a `double`. Show how integer division breaks the result and how to fix it.
- [ ] **Precedence drill** — write 10 expressions and parenthesize them so they compile to what you intend. Verify by reading them aloud: e.g. `1 << 2 + 3`.
- [ ] **`switch` with `[[fallthrough]]`** — write a `switch (priority)` that explicitly falls through from `High` to `Medium` to `Low`. Mark the fall-through with `[[fallthrough]]` and verify no warning.
- [ ] **Menu with `do-while`** — write a loop that prints a 3-option menu, reads a choice, and exits on option 3. Add input validation.
- [ ] **Nested loop exit** — generate a 10x10 multiplication table but `break` both loops when you hit `7*7`. Try all three techniques (flag, function, `goto`).
- [ ] **`if constexpr` with a template** — write `template<class T> std::string name()` that returns `"int"`, `"double"`, or `"other"` using `if constexpr`. Instantiate it with `int`, `double`, `std::string`.
- [ ] **Structured bindings** — implement a function that returns `std::tuple<int, double, std::string>` and bind the result.
- [ ] **Const correctness in casts** — write code that fails to compile with a C-style cast but compiles with `static_cast` or `const_cast` as appropriate. Read the error.
- [ ] **Operator overloading** — define `operator+`, `operator-`, and `operator<<` for a `Complex` struct (real, imag). Verify `(a + b) - a == b`.
- [ ] **Ternary chain refactor** — take a nested ternary expression and rewrite it as an `if` / `else if` chain. Note the readability difference.
- [ ] **`for` with init-statement** — write a `for (auto it = m.find(key); it != m.end(); ++it)` style loop using the C++20 init-statement form.
- [ ] **Range-`for` and mutation** — write a `vector<int>` and double every element using both index-`for` and range-`for`. Note the difference (you must use `&` in the range-`for`).

