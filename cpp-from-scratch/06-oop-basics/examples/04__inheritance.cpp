// ════════════════════════════════════════════════════════════
// Pillar 3 — Inheritance: basic → medium → advanced
//
// Covers, in order:
//   1.  is-a + virtual override         (basic)
//   2.  ctor / dtor order tracing       (basic)
//   3.  protected access in inheritance (medium)
//   4.  slicing pitfall                 (basic)
//   5.  final, override, deleted ctor   (medium)
//   6.  multiple inheritance + mixins   (advanced)
//   7.  virtual inheritance — diamond    (advanced)
//   8.  NVI — non-virtual interface     (advanced)
//
// Each numbered banner prints before the corresponding demo in main().
// Companion notes live in: 06-oop-basics/03-inheritance.md
// ════════════════════════════════════════════════════════════


#include <cstddef>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>


// ──── 1. is-a + virtual override ────
// A Dog IS-A Animal. The base declares a virtual speak(); each derived
// class supplies its own version with `override`.
class Animal {
public:
    Animal(std::string name, int age) : name(std::move(name)), age(age) {}
    virtual ~Animal() {}

    const std::string& getName() const { return name; }
    int                getAge()  const { return age;  }

    void feed() const {
        std::cout << "  " << name << " has been fed.\n";
    }

    virtual void speak() const {
        std::cout << "  " << name << " makes a generic sound.\n";
    }

protected:
    std::string name;
    int         age;
};

class Dog : public Animal {
public:
    Dog(std::string name, int age, std::string breed)
      : Animal(std::move(name), age), breed(std::move(breed)) {}

    void speak() const override {
        std::cout << "  " << name << " says: Woof!\n";
    }

    const std::string& getBreed() const { return breed; }

private:
    std::string breed;
};

class Cat : public Animal {
public:
    Cat(std::string name, int age, bool indoor)
      : Animal(std::move(name), age), indoor(indoor) {}

    void speak() const override {
        std::cout << "  " << name << " says: Meow!\n";
    }

    bool isIndoor() const { return indoor; }

private:
    bool indoor;
};

void runIsAAndOverriding() {
    std::cout << "──── 1. is-a & overriding ────\n";

    Dog d("Rex", 4, "Labrador");
    Cat c("Whisk", 7, true);

    d.feed();   d.speak();
    c.feed();   c.speak();

    std::cout << "  " << d.getName() << " is a " << d.getBreed()
              << " (" << d.getAge() << "y)\n";
    std::cout << "  " << c.getName() << (c.isIndoor() ? " is" : " is not") << " indoor\n";
}


// ──── 2. ctor / dtor order ────
// Base part is built first, torn down last. Extra print lines make the
// order visible.
class TraceAnimal {
public:
    explicit TraceAnimal(std::string n) : name(std::move(n)) {
        std::cout << "    [TraceAnimal ctor] " << name << "\n";
    }
    virtual ~TraceAnimal() {
        std::cout << "    [TraceAnimal dtor] " << name << "\n";
    }
    std::string name;
};

class TraceDog : public TraceAnimal {
public:
    explicit TraceDog(std::string n) : TraceAnimal(std::move(n)) {
        std::cout << "    [TraceDog ctor]\n";
    }
    ~TraceDog() override {
        std::cout << "    [TraceDog dtor]\n";
    }
};

void runCtorDtorOrder() {
    std::cout << "──── 2. ctor / dtor order ────\n";

    {
        TraceDog d("Buddy");
        std::cout << "    ...inside scope...\n";
    }
    std::cout << "    ...after scope...\n";
}


// ──── 3. protected access in inheritance ────
// `protected` members are visible to derived classes but hidden from
// outside. A subclass can expose them through its own accessors.
class Account {
protected:                                // derived classes can read
    double balance = 0.0;

public:
    void deposit(double amount) {
        if (amount > 0) balance += amount;
    }
};

class SavingsAccount : public Account {
public:
    double currentBalance() const {        // exposes the protected field
        return balance;
    }

    void applyInterest(double rate) {      // derived can touch it directly
        balance += balance * rate;
    }
};

void runProtectedAccess() {
    std::cout << "──── 3. protected access ────\n";

    SavingsAccount s;
    s.deposit(1000.0);
    s.applyInterest(0.05);
    std::cout << "  balance = " << s.currentBalance() << "\n";
    // s.balance;                          // ERROR: still hidden from outside
}


// ──── 4. slicing pitfall ────
// Assigning a derived object to a base value cuts away the derived
// bits. Pass by reference or pointer to avoid it.
void runSlicing() {
    std::cout << "──── 4. slicing ────\n";

    Dog  d("Buddy", 2, "Beagle");
    Animal sliced = d;                    // only the Animal part survives
    sliced.speak();                       // generic sound, not Woof!

    Animal& ref = d;                      // reference preserves the derived part
    ref.speak();                          // Woof!

    std::cout << "  (notice: only ref.speak() printed Woof!)\n";
}


// ──── 5. final, override, deleted ctor ────
// `final` on a class prevents further derivation. `final` on a method
// prevents further overriding. `= delete` removes a function entirely.
class Base {
public:
    virtual void speak() const { std::cout << "  Base speak\n"; }
    virtual ~Base() = default;
};

class Derived final : public Base {        // nobody may derive from Derived
public:
    void speak() const override final {    // nobody may override speak()
        std::cout << "  Derived speak\n";
    }
};

class NonCopyable {
public:
    NonCopyable() = default;
    NonCopyable(const NonCopyable&)            = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
    NonCopyable(NonCopyable&&) noexcept            = default;
    NonCopyable& operator=(NonCopyable&&) noexcept = default;
};

void runFinalAndDelete() {
    std::cout << "──── 5. final / override / = delete ────\n";

    Derived d;
    d.speak();

    NonCopyable a;
    NonCopyable b = std::move(a);         // OK — move is allowed
    // NonCopyable c = b;                 // ERROR — copy is deleted
    static_cast<void>(b);
    std::cout << "  (NonCopyable: copy deleted, move allowed)\n";
}


// ──── 6. multiple inheritance + mixins ────
// Combine several small interfaces. Diamond-shaped hierarchies with
// state are usually a bad idea; interfaces without state are fine.
class IDrawable {
public:
    virtual ~IDrawable() = default;
    virtual void draw() const = 0;
};

class ISerializable {
public:
    virtual ~ISerializable() = default;
    virtual std::string serialize() const = 0;
};

class Sprite : public IDrawable, public ISerializable {
private:
    std::string name;
public:
    explicit Sprite(std::string n) : name(std::move(n)) {}

    void draw() const override {
        std::cout << "  drawing sprite " << name << "\n";
    }

    std::string serialize() const override {
        return "<sprite name=\"" + name + "\"/>";
    }
};

void runMultipleInheritance() {
    std::cout << "──── 6. multiple inheritance + mixins ────\n";

    Sprite s("hero");
    s.draw();
    std::cout << "  xml = " << s.serialize() << "\n";
}


// ──── 7. virtual inheritance — diamond problem ────
// Without `virtual`, two paths to the same base would create two copies
// of that base. `virtual` on the inheritance edges collapses them.
class PoweredDevice {
public:
    std::string power = "AC";
    PoweredDevice() { std::cout << "    [PoweredDevice ctor]\n"; }
    virtual ~PoweredDevice() { std::cout << "    [PoweredDevice dtor]\n"; }
};

class Scanner : virtual public PoweredDevice {
public:
    Scanner() { std::cout << "    [Scanner ctor]\n"; }
    ~Scanner() override { std::cout << "    [Scanner dtor]\n"; }
};

class Printer : virtual public PoweredDevice {
public:
    Printer() { std::cout << "    [Printer ctor]\n"; }
    ~Printer() override { std::cout << "    [Printer dtor]\n"; }
};

class Copier : public Scanner, public Printer {
public:
    Copier() { std::cout << "    [Copier ctor]\n"; }
    ~Copier() override { std::cout << "    [Copier dtor]\n"; }
};

void runVirtualInheritance() {
    std::cout << "──── 7. virtual inheritance (diamond) ────\n";

    Copier c;
    std::cout << "    power = " << c.power << " (single copy, not two)\n";
}


// ──── 8. NVI — non-virtual interface ────
// The public function is non-virtual; it sets invariants and forwards
// to a private virtual hook. Subclasses cannot change the contract,
// only the implementation details.
class NetworkRequest {
public:
    std::string execute() {                // non-virtual public interface
        std::cout << "  [NVI] open\n";
        std::string body = doSend();       // virtual hook
        std::cout << "  [NVI] close\n";
        return body;
    }

    virtual ~NetworkRequest() = default;

protected:
    virtual std::string doSend() = 0;
};

class HttpRequest : public NetworkRequest {
protected:
    std::string doSend() override {
        return "HTTP/1.1 200 OK ...";
    }
};

void runNvi() {
    std::cout << "──── 8. NVI (non-virtual interface) ────\n";

    HttpRequest r;
    std::cout << "  body = " << r.execute() << "\n";
}


int main() {

    // ──── 1. is-a & overriding ────
    std::cout << "════ 1. is-a & overriding ════\n";
    runIsAAndOverriding();


    // ──── 2. ctor / dtor order ────
    std::cout << "\n════ 2. ctor / dtor order ════\n";
    runCtorDtorOrder();


    // ──── 3. protected access ────
    std::cout << "\n════ 3. protected access ════\n";
    runProtectedAccess();


    // ──── 4. slicing ────
    std::cout << "\n════ 4. slicing ════\n";
    runSlicing();


    // ──── 5. final / override / = delete ────
    std::cout << "\n════ 5. final / override / = delete ════\n";
    runFinalAndDelete();


    // ──── 6. multiple inheritance ────
    std::cout << "\n════ 6. multiple inheritance + mixins ════\n";
    runMultipleInheritance();


    // ──── 7. virtual inheritance ────
    std::cout << "\n════ 7. virtual inheritance (diamond) ════\n";
    runVirtualInheritance();


    // ──── 8. NVI ────
    std::cout << "\n════ 8. NVI (non-virtual interface) ════\n";
    runNvi();


    std::cout << "\n════ done ════\n";

    return 0;
}


// ════════════════════════════════════════════════════════════
// End of inheritance.
// Companion note: 06-oop-basics/03-inheritance.md
// ════════════════════════════════════════════════════════════