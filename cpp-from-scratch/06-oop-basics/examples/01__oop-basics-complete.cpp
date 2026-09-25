// ════════════════════════════════════════════════════════════
// Object-Oriented Programming in C++ — complete demo
//
// Covers, in order:
//   1.  Classes and objects — definition, two instances, struct vs class
//   2.  Access specifiers — public, private, protected
//   3.  Encapsulation — getters and setters with validation
//   4.  Member functions and the `this` pointer — chaining
//   5.  Constructors — default, parameterised, initializer list
//   6.  Copy constructor — when it fires
//   7.  Destructor — RAII / automatic cleanup
//   8.  `static` members — shared data, object counter
//   9.  `const` member functions — read-only access
//  10.  Composition — Car HAS-A Engine
//  11.  Inheritance + virtual functions — a first look at polymorphism
//  12.  Rule of Three vs Rule of Zero — raw pointer vs std::unique_ptr
//
// Each numbered banner prints before the corresponding demo in main().
// Companion notes live in: 06-oop-basics/06-oop-basics.md
// ════════════════════════════════════════════════════════════


#include <cstddef>
#include <iostream>
#include <string>
#include <utility>
#include <vector>


// ──── 1. classes and objects ────
// A class is a blueprint; an object is what gets built from one.
// Each instance has its own copy of the data members.
class Student {
public:                                // public for now — encapsulation comes in §3
    std::string name;
    int         rollNumber = 0;        // in-class default initialiser (C++11)

    void introduce() const {           // const — does not modify the object
        std::cout << "  Hi, I'm " << name
                  << ", roll " << rollNumber << "\n";
    }
};

void demo_classesAndObjects() {
    std::cout << "──── 1. classes and objects ────\n";

    Student alice;                     // default-constructed
    alice.name        = "Alice";
    alice.rollNumber  = 21;

    Student bob{"Bob", 22};            // aggregate-ish init (public members)

    alice.introduce();
    bob.introduce();

    // class vs struct — the ONLY difference is default access.
    struct Point {                     // members are public by default
        int x;
        int y;
    };
    Point p{3, 4};
    std::cout << "  struct Point = (" << p.x << ", " << p.y << ")\n";
}


// ──── 2. access specifiers ────
// public:    visible to anyone
// protected: visible to this class and anything derived from it
// private:   visible only to this class (and friends)
class Account {
private:                               // default for `class`
    double balance;

protected:
    std::string accountNumber;         // accessible to derived classes too

public:
    std::string owner;

    Account(const std::string& ownerName, const std::string& number, double initial)
        : balance(initial), accountNumber(number) {
        owner = ownerName;
    }

    void deposit(double amount) {
        if (amount > 0) balance += amount;   // OK — Account can touch its own private parts
    }

    double getBalance() const {
        return balance;
    }
};

void demo_accessSpecifiers() {
    std::cout << "──── 2. access specifiers ────\n";

    Account a("Karan", "AC-001", 100.0);
    a.deposit(50.0);
    a.owner = "Karan S.";              // OK  — public

    // a.balance       = 0;            // ERROR — private
    // a.accountNumber = "AC-002";     // ERROR — protected (and not accessible from here)

    std::cout << "  balance after one deposit = "
              << a.getBalance() << "\n";
}


// ──── 3. encapsulation (getters and setters with validation) ────
// The whole point: keep state private, only expose controlled access.
class StudentEncapsulated {
private:
    std::string name;
    int         rollNumber = 0;        // in-class default

public:
    void setName(const std::string& n) {
        if (!n.empty()) name = n;      // validation lives here, once
    }
    const std::string& getName() const { return name; }

    void setRoll(int r) {
        if (r > 0) rollNumber = r;
    }
    int getRoll() const { return rollNumber; }
};

void demo_encapsulation() {
    std::cout << "──── 3. encapsulation ────\n";

    StudentEncapsulated s;
    s.setName("Karan");
    s.setRoll(21);

    std::cout << "  " << s.getName() << " (" << s.getRoll() << ")\n";

    s.setName("");                     // rejected by setter
    s.setRoll(-7);                     // rejected by setter
    std::cout << "  after invalid setName/setRoll, still: "
              << s.getName() << " (" << s.getRoll() << ")\n";
}


// ──── 4. member functions and the `this` pointer ────
// `this` is a hidden pointer to the object the call was made on.
// Returning *this enables chaining.
class Counter {
private:
    int n = 0;

public:
    Counter& increment() {            // returns a reference to *this
        ++this->n;                     // `this->` is usually implicit
        return *this;
    }
    Counter& add(int v) {
        n += v;
        return *this;
    }
    int current() const { return n; }
};

void demo_thisPointer() {
    std::cout << "──── 4. this pointer & chaining ────\n";

    Counter c;
    c.increment().increment().add(5).increment();
    std::cout << "  chained result = " << c.current() << "\n";
}


// ──── 5. constructors ────
// Constructs run automatically. The initializer list (`: a(v)`) is the
// only way to set const members / members that lack a default ctor.
class Box {
private:
    const std::size_t id;             // const — MUST be initialised, not assigned
    std::string       label;
    int               weight = 0;     // in-class default

public:
    Box() : id(0), label("untitled") {}                  // default ctor
    Box(std::size_t i, const std::string& l, int w)
        : id(i), label(l), weight(w) {}                   // parameterised ctor

    void print() const {
        std::cout << "  Box#" << id << " " << label
                  << " weight=" << weight << "\n";
    }
};

void demo_constructors() {
    std::cout << "──── 5. constructors ────\n";

    Box a;                             // default
    Box b(1, "first", 10);             // parameterised

    a.print();
    b.print();
}


// ──── 6. copy constructor ────
// Fired by `T copy = original;`, passing by value, returning by value.
// Takes `const T&` — by-value would recurse forever.
class Student6 {
private:
    std::string name;
public:
    Student6(const std::string& n = "anon") : name(n) {}

    // user-defined copy constructor — prints every time it fires
    Student6(const Student6& other) : name(other.name) {
        std::cout << "  [copy ctor fired for " << name << "]\n";
    }

    const std::string& getName() const { return name; }
};

// helper — receives by VALUE, so a copy is made on the way in
void printStudent(Student6 s) {
    std::cout << "  inside printStudent: " << s.getName() << "\n";
}

void demo_copyConstructor() {
    std::cout << "──── 6. copy constructor ────\n";

    Student6 alice("Alice");
    Student6 copy = alice;             // copy ctor fires here
    Student6 another(alice);           // also a copy

    printStudent(alice);               // and here (passed by value)
}


// ──── 7. destructor ────
// Runs automatically, in reverse order of construction, even on
// exceptions — this is what makes RAII possible.
class File {
private:
    std::string path;
    bool        open = false;

public:
    File(const std::string& p) : path(p) {
        std::cout << "  [open  " << path << "]\n";
        open = true;
    }
    ~File() {
        if (open) std::cout << "  [close " << path << "]\n";
    }
};

void demo_destructor() {
    std::cout << "──── 7. destructor / RAII ────\n";

    File a("a.txt");
    {
        File b("b.txt");
        std::cout << "  inside inner scope\n";
    }                                   // b.~File() runs HERE
    std::cout << "  back in outer scope\n";
}                                       // a.~File() runs HERE


// ──── 8. `static` members ────
// Shared by every object. Declared in the class, defined exactly once
// outside it. A `static` function has no `this` and can be called
// without any object.
class Widget {
private:
    std::string name;
    static int  alive;                 // declaration

public:
    Widget(const std::string& n) : name(n) { ++alive; }
    ~Widget() { --alive; }

    static int count() {              // no `this`
        return alive;
    }
    const std::string& getName() const { return name; }
};
int Widget::alive = 0;                 // definition — exactly once

void demo_staticMembers() {
    std::cout << "──── 8. static members ────\n";

    std::cout << "  initial count  = " << Widget::count() << "\n";
    Widget a("a"), b("b");
    std::cout << "  after 2 made   = " << Widget::count() << "\n";
    {
        Widget c("c");
        std::cout << "  after 3 made   = " << Widget::count() << "\n";
    }
    std::cout << "  after c dies   = " << Widget::count() << "\n";

    // static function callable without any object
    std::cout << "  Widget::count() = " << Widget::count() << "\n";
}


// ──── 9. `const` member functions ────
// Promises not to modify *this. Required to call on const objects;
// marks intent; compiler enforces the promise.
class Thermostat {
private:
    int temperature = 20;

public:
    void setTemp(int t)        { temperature = t; }   // mutating
    int  getTemp() const       { return temperature; } // non-mutating
    int  bumpUp() const {                                // const CAN still mutate mutable state
        // ++temperature;                              // ERROR inside const fn
        return temperature + 1;                         // reading is fine
    }
};

void demo_constMemberFunctions() {
    std::cout << "──── 9. const member functions ────\n";

    Thermostat t;
    t.setTemp(24);
    std::cout << "  getTemp() = " << t.getTemp() << "\n";

    const Thermostat frozen;           // default-constructed → temperature = 20
    std::cout << "  frozen.getTemp() = " << frozen.getTemp() << "\n";
    // frozen.setTemp(30);                                // ERROR — not const
    std::cout << "  frozen.bumpUp() = " << frozen.bumpUp() << "\n";
}


// ──── 10. composition (HAS-A) ────
// Building complex types by including simpler ones. By value is the
// simplest, safest default.
class Engine {
private:
    int horsepower = 100;
public:
    int hp() const { return horsepower; }
};

class Car {
private:
    std::string model;
    Engine      engine;                // a Car HAS an Engine (by value)

public:
    Car(const std::string& m) : model(m) {}

    void specs() const {
        std::cout << "  " << model << " — " << engine.hp() << " HP\n";
    }
};

void demo_composition() {
    std::cout << "──── 10. composition ────\n";

    Car c("Swift");
    c.specs();
}


// ──── 11. inheritance + virtual functions (polymorphism preview) ────
// `virtual` lets the *dynamic* type decide which override runs.
// A polymorphic base needs a `virtual` destructor.
class Animal {
public:
    virtual void speak() const { std::cout << "  ...\n"; }
    virtual ~Animal() = default;       // MUST be virtual for polymorphic delete
};

class Dog : public Animal {
public:
    void speak() const override { std::cout << "  Woof!\n"; }
};

class Cat : public Animal {
public:
    void speak() const override { std::cout << "  Meow!\n"; }
};

void demo_polymorphism() {
    std::cout << "──── 11. polymorphism (preview) ────\n";

    Dog d;
    Cat  c;

    // store derived objects in base-class pointers
    std::vector<Animal*> zoo{&d, &c};

    for (Animal* a : zoo) {
        a->speak();                   // dispatches to the *actual* type
    }

    // safe polymorphic delete — virtual dtor chain runs
    Animal* p = new Dog;
    delete p;                         // ~Dog() then ~Animal() both run
}


// ──── 12. rule of three vs rule of zero ────
// Old-style: own resource → write destructor + copy ctor + copy assign.
// Modern : own it via std::unique_ptr → write none of them.
class BufferOld {
private:
    char*          data;
    std::size_t    size;

public:
    BufferOld(std::size_t n) : data(new char[n]), size(n) {}

    ~BufferOld() { delete[] data; }

    BufferOld(const BufferOld& other)
        : data(new char[other.size]), size(other.size) {
        std::copy(other.data, other.data + size, data);
    }

    BufferOld& operator=(const BufferOld& other) {
        if (this != &other) {
            char* fresh = new char[other.size];
            std::copy(other.data, other.data + other.size, fresh);
            delete[] data;
            data = fresh;
            size = other.size;
        }
        return *this;
    }

    std::size_t getSize() const { return size; }
};

class BufferNew {
private:
    // vector handles copy, move, destruction. Rule of Zero.
    std::vector<char> data;

public:
    BufferNew(std::size_t n) : data(n) {}
    std::size_t getSize() const { return data.size(); }
};

void demo_ruleOfZero() {
    std::cout << "──── 12. rule of three vs zero ────\n";

    BufferOld a(64);
    BufferOld b = a;                  // copy ctor fires
    std::cout << "  BufferOld sizes: a=" << a.getSize()
              << " b=" << b.getSize() << "\n";

    BufferNew c(64), d = c;
    std::cout << "  BufferNew sizes: c=" << c.getSize()
              << " d=" << d.getSize() << "\n";
    // no destructor / copy ctor / copy assign written — vector handles them
}


int main() {

    // ──── 1. classes and objects ────
    std::cout << "════ 1. classes and objects ════\n";
    demo_classesAndObjects();


    // ──── 2. access specifiers ────
    std::cout << "\n════ 2. access specifiers ════\n";
    demo_accessSpecifiers();


    // ──── 3. encapsulation ────
    std::cout << "\n════ 3. encapsulation ════\n";
    demo_encapsulation();


    // ──── 4. this pointer ────
    std::cout << "\n════ 4. this pointer & chaining ════\n";
    demo_thisPointer();


    // ──── 5. constructors ────
    std::cout << "\n════ 5. constructors ════\n";
    demo_constructors();


    // ──── 6. copy constructor ────
    std::cout << "\n════ 6. copy constructor ════\n";
    demo_copyConstructor();


    // ──── 7. destructor ────
    std::cout << "\n════ 7. destructor / RAII ════\n";
    demo_destructor();


    // ──── 8. static members ────
    std::cout << "\n════ 8. static members ════\n";
    demo_staticMembers();


    // ──── 9. const member functions ────
    std::cout << "\n════ 9. const member functions ════\n";
    demo_constMemberFunctions();


    // ──── 10. composition ────
    std::cout << "\n════ 10. composition (has-a) ════\n";
    demo_composition();


    // ──── 11. polymorphism (preview) ────
    std::cout << "\n════ 11. polymorphism (preview) ════\n";
    demo_polymorphism();


    // ──── 12. rule of three vs zero ────
    std::cout << "\n════ 12. rule of three vs zero ════\n";
    demo_ruleOfZero();


    std::cout << "\n════ done ════\n";

    return 0;
}


// ════════════════════════════════════════════════════════════
// End of OOP basics demo.
// Companion note: 06-oop-basics/06-oop-basics.md
// ════════════════════════════════════════════════════════════
