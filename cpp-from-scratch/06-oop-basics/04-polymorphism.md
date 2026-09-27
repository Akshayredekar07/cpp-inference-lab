# **Pillar 4 — Polymorphism**

Polymorphism — literally "many shapes" — is the ability of one piece
of code to operate on values of **different types**, with the right
behaviour picked per call. In C++ the practical form of this is:

* writing code that takes a pointer or reference to a **base type**,
* and letting the **derived type's** implementation run at runtime.

That is what the question in the introduction asks: *how do I let one
piece of code work on many kinds of thing?*

There are two flavours worth knowing in C++:

| Kind | When the choice is made | C++ mechanism |
|---|---|---|
| **Compile-time (static)** polymorphism | At compile time, by picking the right overload/template | Function overloading, templates, `constexpr if` |
| **Runtime (dynamic)** polymorphism   | At runtime, by looking at the actual object's type | `virtual` functions, vtable, base-class pointers/references |

This chapter focuses on the runtime flavour, which is what most
people mean by "OOP polymorphism". The compile-time flavour appears
all over modern C++ as templates and overload sets.

---

## 1. Without polymorphism

If functions and inheritance are not combined, you get this:

```cpp
#include <iostream>
#include <string>

class Dog {
public:
    std::string name;
    void speak() const { std::cout << name << ": Woof!\n"; }
};

class Cat {
public:
    std::string name;
    void speak() const { std::cout << name << ": Meow!\n"; }
};

void makeDogSpeak(const Dog& d) { d.speak(); }
void makeCatSpeak(const Cat& c) { c.speak(); }
```

The caller has to pick the right function for the right type. Every
new animal means a new function and a new branch at the call site.
Adding `Bird` later means editing every function in the program that
mentions animals.

---

## 2. With polymorphism

Pull the common interface into a base class and call through it:

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Animal {
public:
    explicit Animal(std::string name) : name(std::move(name)) {}
    virtual void speak() const = 0;                 // pure virtual
    virtual ~Animal() = default;

    const std::string& getName() const { return name; }

protected:
    std::string name;
};

class Dog : public Animal {
public:
    explicit Dog(std::string n) : Animal(std::move(n)) {}
    void speak() const override {
        std::cout << getName() << ": Woof!\n";
    }
};

class Cat : public Animal {
public:
    explicit Cat(std::string n) : Animal(std::move(n)) {}
    void speak() const override {
        std::cout << getName() << ": Meow!\n";
    }
};

void announce(const Animal& a) {                    // one function
    a.speak();                                      // right version called
}

int main() {
    Dog d("Rex");
    Cat c("Whisk");

    announce(d);                                    // "Rex: Woof!"
    announce(c);                                    // "Whisk: Meow!"

    // containers of base pointers: classic polymorphic use
    std::vector<std::unique_ptr<Animal>> zoo;
    zoo.push_back(std::make_unique<Dog>("Buddy"));
    zoo.push_back(std::make_unique<Cat>("Mittens"));

    for (const auto& a : zoo) {
        a->speak();                                 // each animal answers for itself
    }
}
```

One function, `announce`, handles every kind of animal — including
the ones you will add next month. Adding `Bird` does not require
touching `announce`. That is the practical value of polymorphism.

---

## 3. How it works — the vtable in one minute

When a class declares a `virtual` function, the compiler:

1. Adds a hidden pointer (the **vptr**) to each object of that class.
2. Creates a table of function pointers (**vtable**) shared by all
   objects of the class.
3. Sets the vptr to point at the vtable at construction time.

Calling `a.speak()` therefore becomes "follow the vptr, jump to the
function pointer for `speak`". The jump target is the *derived*
class's version when the object is actually a derived type.

That indirection costs one pointer per object and one indirect call
per virtual invocation. It is the price of being able to write one
function that works on every kind.

---

## 4. Virtual destructors

If a derived object is going to be deleted through a base pointer,
the base destructor must be `virtual` — otherwise only the base part
is destroyed and the derived members leak.

```cpp
class Animal {
public:
    virtual ~Animal() = default;        // <-- needed for polymorphic delete
};

class Dog : public Animal {
private:
    std::unique_ptr<int[]> data;
public:
    Dog() : data(std::make_unique<int[]>(1000)) {}
    // unique_ptr will run only if Dog's destructor runs
};

int main() {
    std::unique_ptr<Animal> p = std::make_unique<Dog>();
    // when p goes out of scope, Animal's virtual dtor dispatches to Dog's dtor,
    // which then runs ~unique_ptr, which frees data
}
```

Rule of thumb: any base class intended for polymorphic use has a
`virtual` destructor.

---

## 5. Pure virtual and abstract base classes

A pure virtual function (`= 0`) says "this class has no
implementation; derived classes must supply one". A class with any
pure virtual is **abstract** — you cannot instantiate it directly.

```cpp
class Shape {
public:
    virtual double area()      const = 0;
    virtual double perimeter() const = 0;
    virtual ~Shape() {}
};
```

`Shape` exists only as an interface. `Circle`, `Rectangle`,
`Triangle` etc. inherit from it and fill in the two pure virtuals.
Code that talks to `Shape&` can do its work without caring which
concrete shape it has been given.

---

## 6. `override` and `final`

| Keyword | Where | What it means |
|---|---|---|
| `override` | On a derived member function | Asserts that this function overrides a virtual in the base. If the signature does not match, the compiler complains. |
| `final`    | On a class                       | No class may derive from this one. |
| `final`    | On a virtual function            | No derived class may override this one. |

```cpp
class Sealed : public Shape {            // nobody may derive from Sealed
    double area() const override final { ... }
};
```

These keywords catch mistakes early and document intent clearly.

---

## 7. Static (compile-time) polymorphism

Templates give you polymorphism without `virtual`:

```cpp
#include <iostream>

template <typename Animal>
void announce(const Animal& a) { a.speak(); }

struct Dog { void speak() const { std::cout << "Woof!\n"; } };
struct Cat { void speak() const { std::cout << "Meow!\n"; } };

int main() {
    announce(Dog{});                     // generates announce<Dog>
    announce(Cat{});                     // generates announce<Cat>
}
```

The compiler produces a separate `announce` for each type. No vtable,
no runtime cost. The trade-off is code size (more generated
functions) and that the choice is fixed at compile time.

In practice C++ code mixes both: templates for type-parameterised
algorithms, virtuals when the exact type is not known until the program
runs.

---

## 8. The cost and when to avoid it

Polymorphism is not free, and not always the right tool:

* **Cost**: one vptr per object, one indirect call per virtual
  invocation, slightly worse branch prediction, no inlining across
  the call.
* **Alternative**: if the set of types is closed and small, prefer
  a `std::variant` + `std::visit`, or a simple tagged union.
* **When to use**: the family of types is open-ended or defined across
  translation units (plugins, library extensions), or the cost of an
  indirect call is irrelevant next to the rest of the work.

---

## 9. Quick checklist

* [ ] Base classes intended for polymorphic use have a `virtual`
      destructor.
* [ ] Derived overrides are marked `override`.
* [ ] Pure virtual functions define the contract; derived classes
      supply the implementation.
* [ ] Containers of polymorphic objects hold pointers or smart
      pointers, not the objects themselves (slicing).
* [ ] Use templates when the choice of type is known at compile time;
      use virtuals when it is only known at runtime.

---

## 10. Recap — the four pillars

| Pillar | Question | C++ tools |
|---|---|---|
| Encapsulation | How do I keep the inside safe? | `private`, `protected`, accessors |
| Abstraction   | What do I expose?                | Small public surface, pure virtual interfaces |
| Inheritance   | How do I say "is-a"?             | `: public Base`, `protected` members |
| Polymorphism  | How do I let one call work on many? | `virtual`/`override`, base pointers and references, vtables |

Used together, they let you build types whose **inside** is safe
(encapsulation), whose **outside** is small and intention-revealing
(abstraction), whose **family** is explicit (inheritance), and whose
**behaviour** is chosen at the right moment (polymorphism).