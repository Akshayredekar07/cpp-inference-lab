# **Strings in C++**

A *string* is a sequence of characters. C++ gives you three main
ways to work with them, in increasing order of safety and
ergonomics:

1. **C-style strings** — arrays of `char` terminated by a `'\0'`.
   The original string type, inherited from C. Powerful and
   dangerous.
2. **`std::string`** — the modern C++ string class. Manages memory,
   grows on demand, and offers a rich API. The default choice.
3. **`std::string_view`** (C++17) — a non-owning "look at" a string.
   Perfect for function parameters that just need to read.

Pick `std::string` by default. Reach for `std::string_view` when a
function only reads its input. Avoid C-style strings unless you are
interfacing with C APIs.

---

## **1. C-style strings — the `char` array**

A C-style string is just a `char` array whose last element is the
**null terminator** `'\0'`. That single zero byte is how every C
string function knows where the string ends.

```cpp
char greeting[] = "hello";
//   contents: 'h' 'e' 'l' 'l' 'o' '\0'
//   size: 6
```

The string literal `"hello"` is an array of 6 characters including
the `'\0'`. If you copy the contents, you must copy the terminator
too — every C-string function relies on it.

```cpp
char greeting[6] = {'h', 'e', 'l', 'l', 'o', '\0'};   // explicit form
```

### **Forgetting the terminator**

If you forget the `'\0'`, every function that walks the string will
keep reading past the end until it finds a zero byte somewhere —
possibly far away — in memory.

```cpp
char bad[5] = {'h', 'e', 'l', 'l', 'o'};   // NO '\0' — undefined behavior
std::cout << bad;                          // may print garbage, may crash
```

### **`sizeof` vs length**

For a C-string, `sizeof(arr)` includes the `'\0'`; the *string
length* does not.

```cpp
char s[] = "hello";
std::cout << sizeof(s);     // 6 — includes terminator
std::cout << std::strlen(s);  // 5 — actual character count
```

---

## **2. C-string functions — `<cstring>`**

The C standard library provides a set of functions for working with
null-terminated `char` arrays. They are fast and ubiquitous; they
are also the source of countless buffer overflows.

| Function | Purpose |
|---|---|
| `std::strlen(s)` | Number of characters before `'\0'` |
| `std::strcmp(a, b)` | Compare two strings; 0 if equal |
| `std::strcpy(dst, src)` | Copy `src` into `dst` (including `'\0'`) |
| `std::strncpy(dst, src, n)` | Copy at most `n` chars — safer |
| `std::strcat(dst, src)` | Append `src` to `dst` |
| `std::strncat(dst, src, n)` | Append at most `n` chars — safer |
| `std::strchr(s, c)` | Find first occurrence of `c` in `s` |
| `std::strstr(s, sub)` | Find first occurrence of substring |

### **Example**

```cpp
#include <cstring>
#include <iostream>

char a[32] = "Hello, ";
char b[]   = "world!";

std::cout << std::strlen(a);   // 7
std::cout << std::strcmp(a, b);  // negative — "Hello, " < "world!"

std::strcat(a, b);
std::cout << a;                // "Hello, world!"
```

### **The classic bug**

`strcpy` and `strcat` will happily write past the end of the
destination buffer. Use the `n`-variants or, better, `std::string`.

```cpp
char small[10];
std::strcpy(small, "This string is much longer than 10 chars");  // BUFFER OVERFLOW
```

---

## **3. `std::string` — the modern choice**

Include `<string>`. `std::string` owns its characters, resizes
automatically, and provides a large, safe API.

```cpp
#include <string>

std::string s = "Hello";
std::cout << s.size();        // 5
std::cout << s.length();      // 5 (same as size for std::string)
std::cout << s.empty();       // false
std::cout << s.capacity();    // at least 5, often more
```

### **Construction**

```cpp
std::string a;                // empty string
std::string b = "hello";      // from a C-string literal
std::string c("hello");       // same thing, parenthesized
std::string d(5, 'x');        // "xxxxx" — 5 copies of 'x'
std::string e = b;            // copy of b
std::string f(b, 1, 3);       // "ell" — from b, starting at index 1, length 3
std::string g(b.begin(), b.end());  // copy whole b via iterators
```

### **Assignment**

```cpp
std::string s;
s = "hello";
s = std::string(3, '?');      // s becomes "???"
```

---

## **4. Concatenation and append**

### **`+` and `+=`**

```cpp
std::string a = "Hello, ";
std::string b = "world";
std::string c = a + b;                // "Hello, world"
a += b;                               // a becomes "Hello, world"
a += '!';                             // a becomes "Hello, world!"
```

Mixing a `std::string` with a string literal on either side of `+`
works because of implicit conversion. Mixing *two literals* does not
work — they are both `const char*` and there is no `operator+` for
two pointers.

```cpp
auto bad = "Hello, " + "world";   // ERROR — pointer + pointer
auto ok  = std::string("Hello, ") + "world";   // OK
```

### **`.append()`**

```cpp
std::string s = "abc";
s.append("def");              // "abcdef"
s.append(3, '!');             // "abcdef!!!"
s.append("xyz", 1, 2);        // "abcdef!!!yz" — from "xyz", starting at 1, length 2
```

### **`.push_back()`**

Adds a single character:

```cpp
std::string s = "abc";
s.push_back('d');             // "abcd"
```

---

## **5. Comparison**

`std::string` overloads the comparison operators to do
lexicographic (dictionary-order) comparison.

```cpp
std::string a = "apple";
std::string b = "banana";

a == b;     // false
a != b;     // true
a <  b;     // true — "apple" < "banana"
a <= b;     // true
```

Comparison with a string literal also works thanks to implicit
conversion:

```cpp
std::string name;
std::cin >> name;
if (name == "quit") { /* ... */ }
```

For case-insensitive comparison, you have to convert both sides to
the same case first.

---

## **6. Length, capacity, and the small-string optimization**

- `.size()` / `.length()` — current number of characters.
- `.capacity()` — how many characters fit before the next reallocation.
- `.empty()` — true if `size() == 0`.
- `.resize(n)` — change `size` to `n`, padding with `'\0'` if growing.
- `.reserve(n)` — ask for at least `n` capacity up front.

Most modern C++ libraries use a **small-string optimization (SSO)**:
short strings (typically up to 15 or 22 chars, depending on the
library) are stored inside the `std::string` object itself with no
heap allocation at all.

```cpp
std::string short_str = "abc";   // no heap allocation on most implementations
std::string long_str(1000, 'x'); // one heap allocation
long_str.reserve(10000);         // pre-allocate to avoid repeated reallocations
```

---

## **7. Accessing characters**

### **By index**

```cpp
std::string s = "hello";
char c = s[0];          // 'h' — no bounds check
char d = s.at(0);       // 'h' — throws std::out_of_range if invalid

s[0] = 'H';             // "Hello"
s.at(100) = 'x';        // throws
```

Prefer `.at()` when the index might be wrong; prefer `[]` when you
know it is in range and want speed.

### **Front and back**

```cpp
char first = s.front();
char last  = s.back();
s.front() = 'H';
s.back()  = '!';
```

### **As a C-string**

```cpp
const char* cstr = s.c_str();      // read-only, null-terminated
// cstr is valid only as long as s is unchanged
```

Use `.c_str()` when calling C APIs that take a `const char*`.

### **Raw data**

```cpp
const char* p = s.data();          // C++17: null-terminated like c_str()
```

---

## **8. Substring, find, and replace**

### **`substr`**

```cpp
std::string s = "Hello, world";
std::string t = s.substr(7);        // "world" — from index 7 to end
std::string u = s.substr(7, 5);     // "world" — from 7, length 5
```

### **`find`**

Returns the index of the first occurrence, or `std::string::npos`
if not found.

```cpp
std::string s = "Hello, world";
std::size_t pos = s.find('o');       // 4
std::size_t pos2 = s.find("world");  // 7
std::size_t pos3 = s.find('z');      // std::string::npos
```

There is also `rfind` (search from the end), `find_first_of`,
`find_last_of`, `find_first_not_of`, and `find_last_not_of`.

### **`replace`**

```cpp
std::string s = "I hate C++";
s.replace(2, 4, "love");    // start at 2, replace 4 chars with "love"
                             // result: "I love C++"
```

### **A complete example**

```cpp
std::string s = "the quick brown fox";
auto pos = s.find("brown");
if (pos != std::string::npos) {
    s.replace(pos, 5, "red");
}
std::cout << s;   // "the quick red fox"
```

---

## **9. Modifiers — insert, erase, clear**

```cpp
std::string s = "Hello world";

s.insert(5, ",");            // "Hello, world"
s.erase(5, 1);               // "Hello world" — remove 1 char at index 5

s.clear();                   // empty

s = "abc";
s.erase(s.begin() + 1);      // "ac" — erase by iterator
```

### **Removing characters**

```cpp
std::string s = "a,b,c,d";
s.erase(std::remove(s.begin(), s.end(), ','), s.end());
// "abcd" — remove all commas
```

The `remove` + `erase` idiom is the standard way to drop matching
characters; `std::remove` shuffles keepers to the front and returns
an iterator to the new "end," and `erase` chops off the tail.

---

## **10. Iteration**

### **Range-based `for`**

```cpp
std::string s = "hello";
for (char c : s) {
    std::cout << c << "\n";
}
```

### **Index loop**

```cpp
for (std::size_t i = 0; i < s.size(); ++i) {
    std::cout << s[i] << "\n";
}
```

### **Iterator loop**

```cpp
for (auto it = s.begin(); it != s.end(); ++it) {
    std::cout << *it << "\n";
}
```

### **Reverse**

```cpp
for (auto it = s.rbegin(); it != s.rend(); ++it) {
    std::cout << *it;     // prints in reverse
}
```

---

## **11. Numeric conversions**

`<string>` provides conversions both ways.

### **String → number**

```cpp
std::string a = "42";
std::string b = "3.14";
std::string c = "1010";
std::string d = "ff";

int    i = std::stoi(a);          // 42
double f = std::stod(b);         // 3.14
int    bin = std::stoi(c, nullptr, 2);  // 10  — base 2
int    hex = std::stoi(d, nullptr, 16); // 255 — base 16
```

If the string is not a valid number, these throw `std::invalid_argument`
or `std::out_of_range`.

### **Number → string**

```cpp
std::string s1 = std::to_string(42);        // "42"
std::string s2 = std::to_string(3.14);      // "3.140000"
std::string s3 = std::to_string(255);       // "255"
```

For precise formatting (fixed decimals, hex, etc.) use `<iomanip>`
or `<format>` (C++20).

---

## **12. `std::string_view` (C++17) — read-only, non-owning**

A `string_view` is a pointer-plus-length pair that *looks at* a
string owned by something else. It does not copy, does not allocate,
and does not own the characters — so the underlying string must
stay alive as long as the view does.

```cpp
#include <string_view>

void printTwice(std::string_view s) {
    std::cout << s << " " << s << "\n";
}

std::string owned = "hello";
const char* literal = "world";
char raw[] = "raw";

printTwice(owned);     // works — std::string implicitly converts
printTwice(literal);   // works — const char* implicitly converts
printTwice(raw);       // works — char array converts too
```

### **Why it's useful**

- **Function parameters**: zero overhead for both `std::string` and
  `const char*`, no copy, no allocation.
- **Substring without copy**: `s.substr(...)` on a string_view
  returns another view in O(1).

```cpp
std::string path = "/home/user/file.txt";
std::string_view filename = path;
filename.remove_prefix(filename.find_last_of('/') + 1);
// filename now views "file.txt" without allocating
```

### **The danger**

A view becomes a dangling pointer the moment the underlying string
is destroyed.

```cpp
std::string_view bad() {
    std::string local = "temporary";
    return local;       // BUG: local dies at function end, view dangles
}
```

Rule of thumb: use `std::string_view` for **parameters**; use
`std::string` for **storage** and **return values**.

---

## **13. Input — reading strings from streams**

`operator>>` reads one whitespace-delimited word.

```cpp
std::string word;
std::cin >> word;           // stops at the first whitespace
```

`std::getline` reads an entire line including spaces.

```cpp
std::string line;
std::getline(std::cin, line);
```

Be careful mixing the two — after a formatted read like `>>`, a
trailing newline is left in the stream, so the first `getline` will
return an empty string. Discard it:

```cpp
int n;
std::cin >> n;
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
std::string line;
std::getline(std::cin, line);
```

---

## **14. Wide and Unicode strings**

For text beyond ASCII, C++ offers a handful of types:

| Type | Use |
|---|---|
| `std::string` | UTF-8 bytes (the default recommendation) |
| `std::wstring` | Wide characters, platform-dependent size |
| `std::u8string` (C++20) | Explicit UTF-8 |
| `std::u16string` | UTF-16 code units |
| `std::u32string` | UTF-32 code units |

Modern C++ practice: store text as UTF-8 in `std::string` or
`std::u8string`, and convert at the edges when talking to APIs that
expect UTF-16 (Windows `LPCWSTR`, for example).

---

## **15. Common pitfalls**

### **Dangling `c_str()`**

```cpp
const char* p;
{
    std::string s = "hello";
    p = s.c_str();    // p points into s
}                     // s is destroyed
std::cout << p;      // UNDEFINED BEHAVIOR — p dangles
```

### **Returning a `string_view` to a local `std::string`**

```cpp
std::string_view v() {
    std::string s = "hi";
    return s;        // dangles
}
```

### **Mixing `>>` and `getline`**

The leftover newline from `>>` makes the next `getline` return
empty. Discard it explicitly.

### **Modifying a string while iterating by index**

```cpp
std::string s = "abc";
for (std::size_t i = 0; i < s.size(); ++i) {
    if (s[i] == 'b') {
        s.erase(i, 1);    // 'i' is now wrong — 'c' shifts into position i
    }
}
```

Either walk from the end, or use `remove` + `erase`, or iterate with
a `std::string::iterator` and use the iterator returned by `erase`.

### **Assuming `==` is case-insensitive**

```cpp
std::string a = "Hello";
std::string b = "hello";
a == b;          // false — case matters
```

Convert both sides to the same case first if you want case-insensitive
matching.

---

## **16. Quick reference**

| Operation | `std::string` | C-string |
|---|---|---|
| Length | `s.size()` / `s.length()` | `std::strlen(s)` |
| Concatenate | `s + t`, `s += t` | `std::strcat(dst, src)` |
| Compare | `s == t`, `s < t` | `std::strcmp(a, b) == 0` |
| Find | `s.find(sub)` | `std::strstr(s, sub)` |
| Substring | `s.substr(pos, n)` | manual loop |
| Modify | `s[i]`, `s.at(i)` | `s[i]` only |
| Resize | automatic | manual `realloc` |
| Null-terminated? | yes (`.c_str()`) | must include `'\0'` |

Default to `std::string`. Use `std::string_view` for read-only
function parameters. Use C-style strings only when forced by a C API
or a fixed-size buffer.
