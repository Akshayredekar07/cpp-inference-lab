# **Pillar 2 — Abstraction**

Abstraction is the act of showing **only essential features** of an
object and hiding the **implementation details**. Encapsulation is a
mechanism — the private/public boundary inside one class. Abstraction
is a design choice — what you choose to put on the other side of that
boundary, and what you leave out.

The two ideas overlap, and many tutorials use them interchangeably.
A clean way to keep them straight:

* **Encapsulation** = *how* you hide things (private members,
  accessors).
* **Abstraction**   = *what* you choose to expose (a small, intention-
  revealing public surface that doesn't leak how the work is done).

---

## 1. An analogy

When you drive a car you interact with the *steering wheel, pedals,
gear lever*. You do not interact with the steering rack, the brake
calipers, or the gear synchros.

| What you see | What is hidden |
|---|---|
| `accelerate()`   | fuel injection, throttle mapping, traction control |
| `brake()`        | hydraulic pressure, ABS sensors, pad wear |
| `shiftGear(int)` | clutch plate, synchro rings, gearbox ratios |

The accelerator pedal is the **abstraction**. The engine underneath
is the **implementation**. You can swap the engine (petrol → hybrid
→ electric) without retraining drivers, because they only ever saw
the abstraction.

That is the goal: write code whose users can ignore how it works.

---

## 2. Abstraction in C++ — what it looks like

A class exposes only the operations the caller needs, and hides the
data and helper functions that exist purely to make those operations
work.

```cpp
#include <iostream>
#include <vector>
#include <numeric>

class Average {
private:
    std::vector<double> samples;       // implementation detail

    // helper — only used inside the class
    double total() const {
        return std::accumulate(samples.begin(), samples.end(), 0.0);
    }

public:
    void   add(double x)  { samples.push_back(x); }   // abstraction
    double value() const  { return total() / samples.size(); }
    size_t count() const  { return samples.size(); }
};

int main() {
    Average a;
    a.add(10.0);
    a.add(20.0);
    a.add(30.0);
    std::cout << a.value() << "\n";   // 20 — caller doesn't know it's a vector
}
```

The caller knows: "I can add samples, I can ask for the value, I can
ask for the count." They do **not** know that samples are stored in a
`std::vector`, that running totals are computed each call, or that the
implementation might later switch to a streaming windowed average.

---

## 3. Abstract base classes — interfaces with zero implementation

C++ has a special use of `virtual` functions to define **pure
abstractions**: a class whose public surface is *only* the operations
a caller needs, with no state and no default behaviour. Subclasses
fill in the details.

```cpp
#include <iostream>
#include <cmath>

// an abstract type — only the "what", never the "how"
class Shape {
public:
    virtual double area()  const = 0;     // pure virtual
    virtual double perimeter() const = 0; // pure virtual
    virtual ~Shape() {}                  // virtual destructor (always)
};

class Circle : public Shape {
private:
    double radius;

public:
    explicit Circle(double r) : radius(r) {}
    double area() const override        { return M_PI * radius * radius; }
    double perimeter() const override   { return 2 * M_PI * radius; }
};

class Rectangle : public Shape {
private:
    double w, h;

public:
    Rectangle(double width, double height) : w(width), h(height) {}
    double area() const override        { return w * h; }
    double perimeter() const override   { return 2 * (w + h); }
};

int main() {
    Shape* s = new Circle(2.0);
    std::cout << s->area() << "\n";        // 12.566...
    delete s;
}
```

Two things happened:

* `Shape` is **abstract** — you cannot create a `Shape` directly,
  because the `= 0` says "this method has no implementation here".
* `Circle` and `Rectangle` are **concrete** — they supply the missing
  implementations.

The shape of the abstraction is the pair of pure virtual functions.
The concrete classes decide *how* to answer them.

---

## 4. Abstract classes vs concrete classes

| Aspect | Abstract class | Concrete class |
|---|---|---|
| Can be instantiated? | No (if it has any pure virtuals) | Yes |
| Purpose | Define an interface / a contract | Provide a usable type |
| Memory layout | Usually has a vtable pointer; no guarantee on member layout | Fully defined |
| Example            | `Shape`, `Drawable`, `Comparable` | `Circle`, `FileReader` |
| Use when           | Multiple types must answer the same questions the same way | You need a working object of that exact type |

A useful test: if the noun makes sense as a real thing on its own,
it is probably concrete. If the noun only makes sense as a category of
other nouns, it is probably abstract.

---

## 5. Hiding complexity with header-only abstractions

Sometimes the abstraction is just a free function or a class with
static methods that wraps a longer procedure:

```cpp
class Temperature {
public:
    static double celsiusToFahrenheit(double c) {
        return c * 9.0 / 5.0 + 32.0;
    }

    static double fahrenheitToCelsius(double f) {
        return (f - 32.0) * 5.0 / 9.0;
    }
};

// usage
double boilingF = Temperature::celsiusToFahrenheit(100.0); // 212
```

The caller does not need to remember the formula. The class is just a
namespace with a nicer name. This is still abstraction: the *what* is
"convert a temperature", the *how* is buried in the function body.

---

## 6. Encapsulation vs abstraction at a glance

| Question | Encapsulation | Abstraction |
|---|---|---|
| "What is it?" | A protection mechanism for the inside of an object | A design choice about which features to expose |
| "Where does it live?" | Mostly inside one class (private members) | Across the class boundary (public interface) |
| "What does it hide?" | State and helpers | Anything not needed to use the object |
| "How is it expressed in C++?" | `private:`, `protected:`, `friend` | `virtual ... = 0`, small public surfaces, header-only utility classes |
| "What does it buy you?" | Invariants, safe refactoring | Replaceable implementations, smaller mental load on callers |

You usually need both. Encapsulation without abstraction gives you a
class with too many `public` knobs. Abstraction without encapsulation
gives you an interface that anyone can reach past and break.

---

## 7. Quick checklist

* [ ] Each class exposes a small number of intention-revealing
      operations.
* [ ] Callers do not need to know which data structure, algorithm, or
      library is used internally.
* [ ] Abstract base classes are used for "category" nouns that have
      multiple concrete shapes.
* [ ] Concrete subclasses supply the missing implementations.
* [ ] Pure virtual functions are paired with a `virtual` destructor in
      the base class.
* [ ] Implementation details (helpers, cached values) are `private` and
      can change without touching callers.

---

## 8. Coming up

Abstraction answers "what should this look like to the outside?".
Encapsulation answers "how do I keep the inside safe?". The next
pillar, **inheritance**, answers a different question entirely: how do
I say *this new thing is a kind of that thing*?