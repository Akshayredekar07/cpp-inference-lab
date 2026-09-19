# **References in C++**

A reference is another **name** for an existing variable — not a copy,
not an address you can print and inspect, just an alias. Once bound,
a reference and the variable it refers to are indistinguishable: they
are the same object under two names.

---

## 1. What a reference is

```cpp
int marks = 90;
int& scoreRef = marks;    // scoreRef is ANOTHER NAME for marks
```

`scoreRef` is not a separate variable holding marks's value — it *is*
marks, just reachable through a second name.

```cpp
scoreRef = 95;
std::cout << marks;       // 95 — because scoreRef and marks are the same object
```

```mermaid
flowchart LR
    A["marks (int, value = 95)"]
    B["scoreRef"] -->|another name for| A
```

Unlike a pointer, a reference does not store an address you can see
or change — the compiler handles that internally. You use `scoreRef`
exactly like you would use `marks`, with no `*` needed.

---

## 2. Declaring and initializing a reference

### Syntax

```cpp
type& referenceName = existingVariable;
```

### The two hard rules

**A reference must be initialized at the moment it is declared.**
```cpp
int& r;          // ERROR: references cannot be left uninitialized
int x = 5;
int& r2 = x;      // fine
```

**A reference can never be rebound to refer to something else.**
```cpp
int a = 1, b = 2;
int& r = a;

r = b;            // this does NOT make r refer to b —
                  // it ASSIGNS b's VALUE (2) into a, through r
std::cout << a;   // 2
std::cout << (&r == &a);   // true — r is still bound to a
```

This is the single biggest difference from a pointer, which can be
reseated at any time (`p = &b;`).

---

## 3. Example — reference in action

```cpp
#include <iostream>

int main() {
    int rollNumber = 21;
    int& rollRef = rollNumber;

    std::cout << "rollNumber = " << rollNumber << "\n";
    std::cout << "rollRef    = " << rollRef << "\n";

    rollRef = 22;                     // changes rollNumber too
    std::cout << "after rollRef = 22, rollNumber = " << rollNumber << "\n";

    std::cout << "&rollNumber == &rollRef : "
              << (&rollNumber == &rollRef) << "\n";   // true, same object

    return 0;
}
```

Output:
```
rollNumber = 21
rollRef    = 21
after rollRef = 22, rollNumber = 22
&rollNumber == &rollRef : 1
```

`&rollNumber` and `&rollRef` are the same address — proof that no new
object was created; `rollRef` is just another handle on `rollNumber`.

---

## 4. References vs pointers

| | Reference | Pointer |
|---|---|---|
| Can be null | No — must refer to something real | Yes (`nullptr`) |
| Can be reseated | No — bound once, forever | Yes |
| Needs `&` to bind | Only at the point of declaration | Yes, explicit, every time |
| Needs `*` to use | No — used like the original | Yes, explicit, every time |
| Can form an array of them | No | Yes (`int* arr[5]`) |
| Typical use | "give me a real alias, it must exist" | Optional data, dynamic memory, arrays |

```cpp
int a = 5;
int& r = a;      // r IS a, nothing more to write
int* p = &a;     // p holds a's address, must dereference to reach a

r = 10;          // writes to a directly
*p = 10;         // writes to a THROUGH the pointer
```

Rule of thumb: reach for a reference by default; drop to a pointer
only when you specifically need "no value" as an option, need to
change what is being referred to later, or need an array of handles.

---

## 5. Reference parameters — pass by reference

The most common real use of references: letting a function operate on
the caller's actual variable, with clean syntax (no `&`/`*` at the
call site).

```cpp
#include <iostream>

void addTen(int& value) {
    value = value + 10;      // modifies the CALLER's variable directly
}

int main() {
    int marks = 50;
    addTen(marks);            // no & needed here — unlike a pointer call
    std::cout << "marks = " << marks << "\n";   // 60
    return 0;
}
```

Compare the three ways to write a function that changes the caller's
value:

```cpp
void byValue(int x)      { x = 99; }        // caller sees NO change
void byPointer(int* x)   { *x = 99; }       // caller sees a change, needs &var at call site
void byReference(int& x) { x = 99; }        // caller sees a change, plain var at call site
```

### Classic example — `swap`

```cpp
#include <iostream>

void mySwap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    int rollA = 21, rollB = 22;
    mySwap(rollA, rollB);
    std::cout << rollA << " " << rollB << "\n";   // 22 21
    return 0;
}
```

Without references, `swap` would need pointers (`int*`) and every call
site would need to remember to pass addresses with `&rollA, &rollB` —
references make the call site read like ordinary variables while
still allowing the function to modify them.

---

## 6. `const` references — read-only, but efficient

A `const` reference parameter promises the function will not modify
the argument, while still avoiding a copy — important for large
objects like `std::string` or `std::vector`.

```cpp
#include <iostream>
#include <string>

void printName(const std::string& name) {   // no copy made, cannot modify name
    std::cout << "Name: " << name << "\n";
    // name += "!";   // ERROR: name is const here
}

int main() {
    std::string student = "Karan";
    printName(student);
    return 0;
}
```

Passing `std::string` **by value** (`void printName(std::string name)`)
would copy the entire string every call. Passing `const std::string&`
gives the function direct access to the original data with zero
copying, while the `const` keeps it safe from accidental modification.

**Rule of thumb:** for parameters that are cheap to copy (`int`,
`char`, `bool`, `double`), just pass by value. For anything larger
(`std::string`, `std::vector`, your own structs/classes) that the
function only needs to read, pass by `const&`.

### `const` references can bind to temporaries

```cpp
const int& boundTemp = 5 + 5;   // 5 + 5 has no named variable, yet this is legal
std::cout << boundTemp;          // 10
```

A plain (non-const) reference **cannot** bind to a temporary:
```cpp
int& bad = 5 + 5;   // ERROR: cannot bind non-const reference to a temporary
```
Binding a `const` reference to a temporary also extends that
temporary's lifetime to match the reference's — it will not be
destroyed early.

---

## 7. Returning references from functions

A function can return a reference, letting the caller act on the
original object rather than a copy.

```cpp
#include <iostream>
#include <vector>

int& firstElement(std::vector<int>& v) {
    return v[0];       // returns a REFERENCE to the actual element
}

int main() {
    std::vector<int> marks{90, 80, 70};

    firstElement(marks) = 100;    // writes THROUGH the returned reference
    std::cout << marks[0] << "\n";  // 100

    return 0;
}
```

### The dangerous version — never return a reference to a local

```cpp
int& dangerous() {
    int local = 5;
    return local;      // local is DESTROYED when the function returns
}                        // the returned reference now refers to nothing valid
```
This compiles (often with a warning), but using the returned reference
afterward is undefined behaviour — the exact same trap as returning
the address of a local variable with a pointer. Only return a
reference to something that will outlive the function call: a
parameter passed by reference, a member of an object, or a global.

### Why this matters — operator chaining

Returning `std::ostream&` from `operator<<` is exactly what makes
chained output work:

```cpp
std::cout << "a" << "b" << "c";
// each << returns the SAME std::cout by reference,
// so the next << can be called on the result immediately
```

---

## 8. References in range-`for`

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> marks{60, 70, 80};

    for (int& m : marks) {        // reference — modifies the real elements
        m += 5;
    }
    // marks is now {65, 75, 85}

    for (const int& m : marks) {  // const reference — read-only, no copy
        std::cout << m << " ";
    }

    return 0;
}
```

| Form | Behaviour |
|---|---|
| `for (int m : marks)` | copies each element — changes to `m` do nothing |
| `for (int& m : marks)` | real alias — changes to `m` change the vector |
| `for (const int& m : marks)` | read-only alias — no copy, cannot modify |

For small types like `int`, the copy in the first form barely matters.
For large types (`std::string`, custom structs), always prefer
`const auto&` unless you specifically intend to modify each element.

---

## 9. Dangling references

A reference becomes dangling when the object it refers to is
destroyed while the reference is still around — using it afterward is
undefined behaviour.

```cpp
int& makeDangling() {
    int temp = 42;
    return temp;          // temp dies here, reference is now dangling
}

int main() {
    int& ref = makeDangling();
    std::cout << ref;      // undefined behaviour — reading destroyed memory
    return 0;
}
```

This is the same underlying problem as a dangling pointer (see the
Pointers notes), just without the ability to check it against
`nullptr` first — a dangling reference gives you no warning sign at
all. This is one reason references are considered slightly more
dangerous to return than to receive.

---

## 10. What references cannot do

**No reference to a reference, directly:**
```cpp
int x = 5;
int& r = x;
int& & rr = r;    // ERROR: no such thing as a reference to a reference
```
(Template code can produce this situation internally — "reference
collapsing" — but that is an advanced topic, not something you write
by hand.)

**No arrays of references:**
```cpp
int a = 1, b = 2, c = 3;
int& arr[3] = {a, b, c};   // ERROR: arrays of references are not allowed
```
An array needs each slot to be independently assignable and default-
constructible; references can be neither. Use an array/vector of
pointers instead if you need this kind of collection.

**No null references:**
```cpp
int& r = *static_cast<int*>(nullptr);   // technically compiles, but is
                                          // undefined behaviour the moment
                                          // r is used — do not do this
```
There is no legitimate "empty" reference. If "might not have a value"
is a real possibility, that is a signal to use a pointer, or
`std::optional`, instead of a reference.

---

## 11. rvalue references (brief preview)

Everything above is an **lvalue reference** (`int&`) — it binds to a
named, addressable object. C++11 also introduced **rvalue references**
(`int&&`), which bind specifically to temporaries and enable move
semantics — letting an object "steal" a temporary's resources instead
of copying them.

```cpp
void handle(int& x)  { std::cout << "lvalue overload\n"; }
void handle(int&& x) { std::cout << "rvalue overload\n"; }

int main() {
    int a = 5;
    handle(a);        // lvalue overload — a is a named variable
    handle(10);        // rvalue overload — 10 is a temporary
    return 0;
}
```

This is the foundation of `std::move` and move constructors, which
belong to their own dedicated chapter — mentioned here only so `int&&`
does not look unfamiliar when it first appears.

---

## 12. Common pitfalls

**Thinking assignment through a reference rebinds it**
```cpp
int a = 1, b = 2;
int& r = a;
r = b;             // assigns b's VALUE into a — does NOT make r refer to b
```

**Returning a reference to a local variable or temporary**
Covered in Sections 7 and 9 — the most common serious reference bug.

**Passing large objects by value out of habit**
```cpp
void process(std::string text) { ... }         // copies the whole string
void process(const std::string& text) { ... }  // no copy, same behaviour if read-only
```

**Expecting a reference parameter to accept `nullptr` or "nothing"**
References cannot be null — if a function sometimes has "no value" to
work with, use a pointer or `std::optional<T>`, not a reference.

---

## 13. Quick reference

| Syntax | Meaning |
|---|---|
| `int& r = x;` | r is a reference (alias) to x |
| `const int& r = x;` | read-only alias to x, can also bind to temporaries |
| `void f(int& x)` | pass by reference — caller's variable can be modified |
| `void f(const int& x)` | pass by reference, read-only, avoids a copy |
| `int& f()` | function returns an alias to something that must outlive the call |
| `int&& r = 5;` | rvalue reference — binds to a temporary (preview, Section 11) |
| — | references cannot be null, rebound, or left uninitialized |

---

## 14. Practice (try these yourself)

- Declare `int a = 1, b = 2;` and `int& r = a;`. Predict what
  `r = b;` does to `a`, `b`, and `r` before running it — then check.
- Write `void increment(int& x)` and call it on a local variable;
  confirm the caller's variable actually changed.
- Write the same function taking `int` by value instead, and show the
  caller's variable is unaffected.
- Write a function `const std::string& firstNonEmpty(const std::string& a, const std::string& b)`
  that returns whichever argument is non-empty, and explain why
  returning a reference here is safe (both come from the caller).
- Deliberately write a function that returns a reference to a local
  variable, compile it, and read any warning the compiler gives you.
- Rewrite a `for (int x : marks)` loop that was supposed to double
  every element but silently does nothing — fix it by adding `&`.
- Overload a function with `void f(int&)` and `void f(int&&)`, call it
  with both a named variable and a literal, and confirm which
  overload runs for each.