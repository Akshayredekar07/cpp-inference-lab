# **Pillar 1 — Encapsulation**

Encapsulation is the discipline of bundling data and the functions that
work on that data inside one unit, and then **putting a controlled
boundary around it** so outside code can only touch what you allow it to
touch.

In C++ that boundary is drawn with access specifiers (`public`,
`private`, `protected`), and the controlled openings are member
functions. The goal is not "make things private for the sake of it" —
the goal is to make the inside of an object **safe to change** without
breaking anything that uses it.

---

## 1. The problem encapsulation solves

Suppose you write a `BankAccount` with the balance left `public`:

```cpp
struct BankAccount {
    double balance;          // public — anyone can write to it
};

int main() {
    BankAccount a;
    a.balance = -1000;       // perfectly legal, semantically nonsense
}
```

Nothing stops a negative balance, nothing logs the change, nothing
checks for overdraft. The next person to use the struct has no idea
what guarantees it offers, because there are no guarantees.

Wrap the same data in a class with a single public function:

```cpp
class BankAccount {
private:
    double balance = 0.0;    // hidden

public:
    void deposit(double amount) {
        if (amount <= 0) return;        // invariant: only positive deposits
        balance += amount;
    }

    double currentBalance() const { return balance; }
};

int main() {
    BankAccount a;
    a.deposit(500);
    // a.balance = -1000;    // ERROR — balance is private
    std::cout << a.currentBalance();     // 500
}
```

Now the *only* way to add money is through `deposit`, and that function
is a single place where you can add validation, logging, persistence,
or thread-safety later — without changing how callers use the class.

---

## 2. The two halves of encapsulation

| Half | What it means |
|---|---|
| **Bundling** | Data members and the functions that operate on them live together in one class. |
| **Hiding**   | The data is made `private` so outside code cannot reach in and bypass the functions. |

C++ does bundling for you as soon as you write a class. Hiding is
where you have to be deliberate — it requires the `private:` keyword
(or a `friend` declaration, used sparingly).

---

## 3. Getters and setters — the controlled openings

The standard way to expose a private field is through **accessor
functions**:

* a *getter* reads the field (often `const`-qualified),
* a *setter* writes it, usually after validation.

```cpp
#include <iostream>
#include <string>

class Student {
private:
    std::string name;
    int         rollNumber = 0;

public:
    // setter — validates before storing
    void setName(const std::string& newName) {
        if (!newName.empty()) name = newName;
    }

    void setRollNumber(int r) {
        if (r > 0) rollNumber = r;
    }

    // getters — read-only access
    const std::string& getName()      const { return name;      }
    int                getRollNumber() const { return rollNumber; }
};

int main() {
    Student s;
    s.setName("Karan");                  // validated
    s.setName("");                       // rejected, name unchanged
    s.setRollNumber(-7);                 // rejected, rollNumber unchanged

    std::cout << s.getName() << " (" << s.getRollNumber() << ")\n";
}
```

Things worth noticing:

* The setter takes its argument **by const reference** for strings, so
  no copy is made and the caller cannot secretly mutate it.
* The getters return `const std::string&` rather than a copy.
* Both getters are marked `const` because reading should not change
  the object.

---

## 4. A common pattern — invariants behind a wall

A well-encapsulated class exposes a small public surface and keeps a
larger private surface that holds the *invariant* (a rule that must
always be true for the object to be valid).

```cpp
class PositiveNumber {
private:
    int value;                     // invariant: value > 0

public:
    explicit PositiveNumber(int v) : value(v) {
        if (v <= 0) throw std::invalid_argument("must be > 0");
    }

    PositiveNumber& add(int delta) {
        if (value + delta <= 0) throw std::overflow_error("would break invariant");
        value += delta;
        return *this;
    }

    int  read() const { return value; }
};

PositiveNumber p(5);
p.add(3);                          // OK, now 8
// p.add(-100);                    // throws — invariant protected
```

The public API is three operations. The private state holds an
invariant that the constructors and mutators defend together. As long
as no outside code can touch `value` directly, the invariant cannot
be broken.

---

## 5. Encapsulation is not the same as "make everything private"

A field marked `private` and exposed through a getter/setter that does
no extra work is **not really encapsulated** — it is just a verbose
`public` field. Real encapsulation means the public surface enforces
something the raw field would not:

* validation in setters,
* `const`-correctness on getters,
* lazy computation,
* logging, notifications, thread-safety,
* or simply the freedom to change the storage later (e.g. switch from
  a raw `int` to a `std::atomic<int>` or a value computed on the fly).

If your getter just `return x;` and your setter just `x = v;`, ask
yourself whether the field should be `public` after all — or whether
the class should *have* that field at all.

---

## 6. Encapsulation across files

In real projects the class lives in a header (`.h`/`.hpp`) and the
member bodies live in a `.cpp`. The header lists the public surface,
the .cpp keeps the private helpers and implementation details out of
sight:

```
// account.h
class Account {
public:
    void   deposit(double);
    double balance() const;
private:
    double cents;                 // implementation detail
    void   log(const char*);      // helper, not in the header
};
```

Callers `#include "account.h"` and see only the public section. The
private members — and any future refactoring of them — are not part of
their contract.

---

## 7. Quick checklist

* [ ] Data members are `private` (or `protected` if subclasses need them).
* [ ] Every read of a private field goes through a `const` getter.
* [ ] Every write goes through a setter that validates.
* [ ] Constructors establish the invariant before the object is usable.
* [ ] Public member functions are the *only* way to mutate the object.
* [ ] The public surface is small enough to read in one screen.

---

## 8. Coming up

Encapsulation protects the **inside** of a single object. The next
pillar, **abstraction**, is about deciding which parts of a class
should be visible at all — even to other classes — and which should
be hidden behind a simpler, higher-level interface.