// ════════════════════════════════════════════════════════════
// Pillar 4 — Polymorphism: basic → medium → advanced
//
// Covers, in order:
//   1.  runtime: one fn, many kinds         (basic)
//   2.  polymorphic container               (basic)
//   3.  virtual destructor at work          (basic)
//   4.  static polymorphism with templates  (medium)
//   5.  pure virtual with default impl      (medium)
//   6.  downcasting with dynamic_cast       (medium)
//   7.  vtable caveat in ctor / dtor        (medium)
//   8.  std::function-based polymorphism    (advanced)
//   9.  std::variant + std::visit           (advanced)
//  10.  CRTP static polymorphism            (advanced)
//
// Each numbered banner prints before the corresponding demo in main().
// Companion notes live in: 06-oop-basics/04-polymorphism.md
// ════════════════════════════════════════════════════════════


#include <cmath>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <typeinfo>
#include <utility>
#include <variant>
#include <vector>


// ──── polymorphic base ────
// Pure virtual speak() makes Animal abstract; virtual destructor is
// mandatory because we delete derived objects through base pointers.
class Animal {
public:
    explicit Animal(std::string name) : name(std::move(name)) {}
    virtual ~Animal() = default;

    virtual void speak() const = 0;

    const std::string& getName() const { return name; }

protected:
    std::string name;
};

class Dog : public Animal {
public:
    explicit Dog(std::string n) : Animal(std::move(n)) {}
    void speak() const override { std::cout << "  " << getName() << ": Woof!\n"; }
};

class Cat : public Animal {
public:
    explicit Cat(std::string n) : Animal(std::move(n)) {}
    void speak() const override { std::cout << "  " << getName() << ": Meow!\n"; }
};

class Bird : public Animal {
public:
    explicit Bird(std::string n) : Animal(std::move(n)) {}
    void speak() const override { std::cout << "  " << getName() << ": Tweet!\n"; }
};


// ──── 1. runtime: one fn, many kinds ────
// Same signature — different runtime answers via the vtable.
void announce(const Animal& a) {
    a.speak();
}

void runOneFnManyKinds() {
    std::cout << "──── 1. one function, many kinds ────\n";

    Dog  d("Rex");
    Cat  c("Whisk");
    Bird b("Tweety");

    announce(d);
    announce(c);
    announce(b);
}


// ──── 2. polymorphic container ────
// std::vector<Animal> would slice. unique_ptr<Animal> preserves the
// derived type for each element.
void runPolymorphicContainer() {
    std::cout << "──── 2. polymorphic container ────\n";

    std::vector<std::unique_ptr<Animal>> zoo;
    zoo.push_back(std::make_unique<Dog>("Buddy"));
    zoo.push_back(std::make_unique<Cat>("Mittens"));
    zoo.push_back(std::make_unique<Bird>("Polly"));

    for (const auto& a : zoo) {
        a->speak();
    }
}


// ──── 3. virtual destructor at work ────
// A non-virtual base destructor would leak the derived part. Tracing
// the destructor calls makes the dispatch visible.
class TraceAnimal {
public:
    explicit TraceAnimal(std::string n) : name(std::move(n)) {}
    virtual ~TraceAnimal() { std::cout << "    [TraceAnimal dtor] " << name << "\n"; }
    std::string name;
};

class TraceDog : public TraceAnimal {
public:
    explicit TraceDog(std::string n) : TraceAnimal(std::move(n)) {}
    ~TraceDog() override { std::cout << "    [TraceDog dtor] " << name << "\n"; }
};

void runVirtualDestructor() {
    std::cout << "──── 3. virtual destructor ────\n";

    std::unique_ptr<TraceAnimal> p = std::make_unique<TraceDog>("Rex");
    static_cast<void>(p);
    std::cout << "    (about to leave scope, derived dtor runs via base ptr)\n";
}


// ──── 4. static polymorphism with templates ────
// The compiler instantiates one announce_t per type — no vtable, no
// runtime cost. The trade-off is code size.
template <typename AnimalLike>
void announce_t(const AnimalLike& a) {
    a.speak();
}

void runStaticPolymorphism() {
    std::cout << "──── 4. static polymorphism ────\n";

    announce_t(Dog("Rex"));
    announce_t(Cat("Whisk"));
    announce_t(Bird("Tweety"));
}


// ──── 5. pure virtual with default impl ────
// A pure virtual can still ship with a body. Derived classes may
// ignore it or call it explicitly as `Base::method()`.
class Greeting {
public:
    virtual std::string greet() const = 0;
    virtual ~Greeting() = default;
};

// default body — defined out of line because pure virtuals are usually
// declared in the header and defined in a .cpp in real projects.
std::string Greeting::greet() const { return "hello"; }

class FancyGreeting : public Greeting {
public:
    std::string greet() const override { return "salutations"; }
};

class EchoGreeting : public Greeting {
public:
    std::string greet() const override { return Greeting::greet(); }  // uses base body
};

void runPureVirtualDefault() {
    std::cout << "──── 5. pure virtual with default impl ────\n";

    FancyGreeting f;
    EchoGreeting  e;
    std::cout << "  fancy = " << f.greet()
              << "  echo  = " << e.greet() << "\n";
}


// ──── 6. downcasting with dynamic_cast ────
// When you only have a base pointer, dynamic_cast asks the runtime
// whether it actually points at a derived. Returns nullptr on mismatch.
class BirdCastable : public Animal {
public:
    explicit BirdCastable(std::string n) : Animal(std::move(n)) {}
    void speak() const override { std::cout << "  " << getName() << ": Tweet!\n"; }

    void fly() const { std::cout << "  " << getName() << " is flying\n"; }
};

void runDynamicCast() {
    std::cout << "──── 6. downcasting with dynamic_cast ────\n";

    std::unique_ptr<Animal> a = std::make_unique<BirdCastable>("Tweety");
    std::unique_ptr<Animal> b = std::make_unique<Dog>("Rex");

    if (auto bird = dynamic_cast<BirdCastable*>(a.get())) {
        bird->fly();                      // success — a really is a BirdCastable
    }

    if (auto bird = dynamic_cast<BirdCastable*>(b.get())) {
        bird->fly();
    } else {
        std::cout << "  b is not a BirdCastable (dynamic_cast returned nullptr)\n";
    }

    // typeid gives the actual runtime type
    std::cout << "  typeid(*a) = " << typeid(*a).name() << "\n";
    std::cout << "  typeid(*b) = " << typeid(*b).name() << "\n";
}


// ──── 7. vtable caveat in ctor / dtor ────
// Inside a constructor or destructor, the dynamic type IS the type
// being constructed/destroyed — virtual calls dispatch to that level,
// not to any further-derived override.
class BaseCTOR {
public:
    BaseCTOR() { call(); }                // virtual call inside ctor
    virtual ~BaseCTOR() { call(); }       // virtual call inside dtor
    virtual void call() const { std::cout << "  BaseCTOR::call\n"; }
};

class DerivedCTOR : public BaseCTOR {
public:
    DerivedCTOR() { }                     // base ctor already ran, sees BaseCTOR::call
    void call() const override { std::cout << "  DerivedCTOR::call\n"; }
};

void runCtorDtorCaveat() {
    std::cout << "──── 7. vtable caveat in ctor / dtor ────\n";

    DerivedCTOR d;
    d.call();                             // now sees DerivedCTOR::call
}


// ──── 8. std::function-based polymorphism ────
// Type erasure: a class can hold arbitrary callables behind a uniform
// interface. No inheritance required at the call site.
class Clickable {
public:
    void onClick(std::function<void()> h) { handlers.push_back(std::move(h)); }
    void click() {
        for (auto& h : handlers) h();
    }

private:
    std::vector<std::function<void()>> handlers;
};

void runStdFunctionPoly() {
    std::cout << "──── 8. std::function-based polymorphism ────\n";

    Clickable c;
    int n = 0;
    c.onClick([&n] { std::cout << "  click #" << ++n << "\n"; });
    c.onClick([]   { std::cout << "  beep!\n"; });

    c.click();
    c.click();
}


// ──── 9. std::variant + std::visit ────
// Closed set of alternatives, no inheritance, exhaustive dispatch by
// the compiler (missing overload = compile error).
struct CircleAlt    { double r; explicit CircleAlt(double r_) : r(r_) {} };
struct RectangleAlt { double w, h; RectangleAlt(double w_, double h_) : w(w_), h(h_) {} };
using GeoShape = std::variant<CircleAlt, RectangleAlt>;

struct NameVisitor {
    std::string operator()(const CircleAlt&    ) const { return "circle";   }
    std::string operator()(const RectangleAlt& ) const { return "rectangle"; }
};

void runVariantPoly() {
    std::cout << "──── 9. std::variant + std::visit ────\n";

    std::vector<GeoShape> shapes = { CircleAlt(1.0), RectangleAlt(2.0, 3.0) };

    for (const auto& s : shapes) {
        std::cout << "  kind = " << std::visit(NameVisitor{}, s) << "\n";
    }
}


// ──── 10. CRTP static polymorphism ────
// Derived passes itself as the template parameter; "virtual" calls
// resolve at compile time with zero overhead.
template <typename Derived>
class AnimalLike {
public:
    void speak() const {
        static_cast<const Derived*>(this)->speakImpl();
    }
};

class DogCRTP : public AnimalLike<DogCRTP> {
public:
    void speakImpl() const { std::cout << "  Woof (CRTP)\n"; }
};

class CatCRTP : public AnimalLike<CatCRTP> {
public:
    void speakImpl() const { std::cout << "  Meow (CRTP)\n"; }
};

void runCrtp() {
    std::cout << "──── 10. CRTP static polymorphism ────\n";

    DogCRTP d;
    CatCRTP c;

    AnimalLike<DogCRTP>& ad = d;
    AnimalLike<CatCRTP>& ac = c;

    ad.speak();
    ac.speak();
}


int main() {

    // ──── 1. one function, many kinds ────
    std::cout << "════ 1. one function, many kinds ════\n";
    runOneFnManyKinds();


    // ──── 2. polymorphic container ────
    std::cout << "\n════ 2. polymorphic container ════\n";
    runPolymorphicContainer();


    // ──── 3. virtual destructor ────
    std::cout << "\n════ 3. virtual destructor ════\n";
    runVirtualDestructor();


    // ──── 4. static polymorphism ────
    std::cout << "\n════ 4. static polymorphism ════\n";
    runStaticPolymorphism();


    // ──── 5. pure virtual with default impl ────
    std::cout << "\n════ 5. pure virtual with default impl ════\n";
    runPureVirtualDefault();


    // ──── 6. dynamic_cast ────
    std::cout << "\n════ 6. downcasting with dynamic_cast ════\n";
    runDynamicCast();


    // ──── 7. vtable caveat in ctor / dtor ────
    std::cout << "\n════ 7. vtable caveat in ctor / dtor ════\n";
    runCtorDtorCaveat();


    // ──── 8. std::function polymorphism ────
    std::cout << "\n════ 8. std::function-based polymorphism ════\n";
    runStdFunctionPoly();


    // ──── 9. std::variant + std::visit ────
    std::cout << "\n════ 9. std::variant + std::visit ════\n";
    runVariantPoly();


    // ──── 10. CRTP ────
    std::cout << "\n════ 10. CRTP static polymorphism ════\n";
    runCrtp();


    std::cout << "\n════ done ════\n";

    return 0;
}


// ════════════════════════════════════════════════════════════
// End of polymorphism demo.
// Companion note: 06-oop-basics/04-polymorphism.md
// ════════════════════════════════════════════════════════════