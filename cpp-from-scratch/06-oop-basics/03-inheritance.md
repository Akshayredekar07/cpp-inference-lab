# **Pillar 3 — Inheritance**

Inheritance is the mechanism for saying **"this new type is a kind of
that existing type"**. The new type (the *derived* or *child* class)
inherits the members of the existing one (the *base* or *parent*
class), then adds its own or overrides what it needs to.

The four pillars again, framed as questions:

| Pillar | Question it answers |
|---|---|
| Encapsulation | How do I keep the inside of an object safe? |
| Abstraction   | How do I expose only what is needed? |
| **Inheritance** | **How do I say "this new thing is a kind of that thing"?** |
| Polymorphism  | How do I let one piece of code work on many kinds of thing? |

---

## 1. A motivating example

A `Dog` and a `Cat` are both animals. They share some things (a name,
an age, a way to be fed) and differ in others (the sound they make).
Without inheritance you either copy the shared code, or live with two
unrelated classes that callers have to know about separately.

```cpp
#include <iostream>
#include <string>

class Animal {
public:
    Animal(std::string name, int age) : name(std::move(name)), age(age) {}

    const std::string& getName() const { return name; }
    int                getAge()  const { return age;  }

    void feed() const {
        std::cout << name << " has been fed.\n";
    }

    // default sound — meant to be overridden
    virtual void speak() const {
        std::cout << name << " makes a generic sound.\n";
    }

    virtual ~Animal() = default;

protected:                  // visible to subclasses, hidden from outside
    std::string name;
    int         age;
};

class Dog : public Animal {
public:
    Dog(std::string name, int age, std::string breed)
      : Animal(std::move(name), age), breed(std::move(breed)) {}

    void speak() const override {
        std::cout << getName() << " says: Woof!\n";
    }

    const std::string& getBreed() const { return breed; }

private:
    std::string breed;
};

class Cat : public Animal {
public:
    Cat(std::string name, int age, bool indoor)
      : Animal(std::move(name)), indoor(indoor) {}

    void speak() const override {
        std::cout << getName() << " says: Meow!\n";
    }

    bool isIndoor() const { return indoor; }

private:
    bool indoor;
};

int main() {
    Dog  d("Rex",   4, "Labrador");
    Cat  c("Whisk", 7, true);

    d.feed();        d.speak();    // inherited + overridden
    c.feed();        c.speak();

    std::cout << d.getName() << " is a "   << d.getBreed()  << "\n";
    std::cout << c.getName() << (c.isIndoor() ? " is" : " is not") << " indoor\n";
}
```

A `Dog` *is a* `Animal`. That "is-a" relationship is the inheritance
contract — anywhere an `Animal` is expected, a `Dog` can be used.

---

## 2. Syntax and access in inheritance

```cpp
class Derived : public Base { ... };
        //  ^      ^
        //  |      └── the access used when promoting Base members
        //  └──────── the new class
```

The access specifier in the inheritance line (`public`, `protected`,
`private`) controls how the base's members are *promoted* into the
derived class:

| Inheritance kind | `Base`'s `public` becomes | `Base`'s `protected` becomes |
|---|---|---|
| `public`    | `public` in `Derived`    | `protected` in `Derived` |
| `protected` | `protected` in `Derived` | `protected` in `Derived` |
| `private`   | `private` in `Derived`   | `private` in `Derived` |

`public` inheritance is by far the most common — it preserves the
"is-a" relationship. `private` inheritance is occasionally used to
reuse implementation but hide the interface (an "is-implemented-in-
terms-of" relationship).

---

## 3. Construction and destruction order

When a derived object is built, the base part is constructed first;
when it is destroyed, the derived part is destroyed first.

```cpp
#include <iostream>

class A { public: A()  { std::cout << "A ctor\n"; } ~A() { std::cout << "A dtor\n"; } };
class B : public A { public: B()  { std::cout << "B ctor\n"; } ~B() { std::cout << "B dtor\n"; } };

int main() {
    B b;
}
// A ctor
// B ctor
// B dtor
// A dtor
```

Practical consequences:

* The base class **must** be constructible from whatever you pass it,
  typically through a member initialiser list (the `: Base(...)`
  part).
* The base destructor should be `virtual` if you intend to delete a
  derived object through a base pointer — otherwise only the base
  part is destroyed.

---

## 4. Overriding member functions

A derived class can **override** a base member function by declaring
a function with the same signature and using the `override` keyword:

```cpp
class Animal {
public:
    virtual void speak() const { std::cout << "...\n"; }   // virtual enables overriding
    virtual ~Animal() = default;
};

class Dog : public Animal {
public:
    void speak() const override { std::cout << "Woof!\n"; }   // override confirms intent
};
```

Notes:

* Without `virtual` in the base, the call binds at compile time to
  the static type (no override happens at runtime).
* Without `override` in the derived, a typo (wrong signature, missing
  `const`) silently creates a new function instead of overriding —
  the bug then hides at runtime.
* Use both: `virtual` on the base side, `override` on the derived
  side.

---

## 5. Calling the base version explicitly

Sometimes an override wants to extend the base behaviour, not replace
it. Use the qualified name `Base::member(...)`:

```cpp
class Logged {
public:
    virtual void save() {
        std::cout << "[base] saving\n";
    }
};

class AuditedSave : public Logged {
public:
    void save() override {
        Logged::save();                  // first do the base work
        std::cout << "[audit] saved\n";  // then add audit logging
    }
};
```

This is the cleanest way to chain behaviour up the inheritance tree
without duplicating it.

---

## 6. What is *not* inherited

Some things do not transfer from base to derived:

| Not inherited | Why |
|---|---|
| Constructors and the destructor | Each class constructs itself; the base ctor runs via the initialiser list |
| Assignment operator overloads   | Each class assigns its own members |
| Friends                          | Friendship is not transitive — being a friend of `Base` does not make you a friend of `Derived` |
| Static members, but only as one shared entity | All derived classes share *one* copy of the static |

---

## 7. A common pitfall — slicing

When you copy a derived object into a base variable, only the base
part survives. The extra members and the overridden virtual
behaviour are cut away. This is called **object slicing**.

```cpp
Dog d("Rex", 4, "Labrador");
Animal a = d;             // slices — only the Animal part is copied
a.speak();                // "Rex makes a generic sound.", not "Woof!"
```

To preserve the derived behaviour, store a **pointer** or **reference**
to the base — that is the bridge to the next pillar, polymorphism.

---

## 8. Quick checklist

* [ ] Use `public` inheritance for genuine "is-a" relationships.
* [ ] Always pair a polymorphic base with a `virtual` destructor.
* [ ] Always use `override` on derived functions that should override.
* [ ] Initialise the base in the derived's member initialiser list.
* [ ] Watch out for slicing — pass derived objects as pointers or
      references to base.
* [ ] Prefer composition ("has-a") over inheritance when the
      relationship is not really "is-a".

---

## 9. Coming up

Inheritance gave us the family tree: derived classes are kinds of
their base. The next pillar, **polymorphism**, uses that family tree
to write code that talks to the base and lets the right derived
answer at runtime — without knowing in advance which one.