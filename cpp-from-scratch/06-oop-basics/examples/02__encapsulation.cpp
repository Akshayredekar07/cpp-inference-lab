// ════════════════════════════════════════════════════════════
// Pillar 1 — Encapsulation: basic → medium → advanced
//
// Covers, in order:
//   1.  public vs private field                 (basic)
//   2.  getters / setters with validation       (basic)
//   3.  default member initialisers             (basic)
//   4.  invariant defence in ctor + mutator     (medium)
//   5.  const correctness on getters            (medium)
//   6.  static factory enforcing validity       (medium)
//   7.  friend function for tight coupling      (medium)
//   8.  Pimpl idiom — fully hidden impl         (advanced)
//   9.  Rule of five — copy / move / RAII       (advanced)
//
// Each numbered banner prints before the corresponding demo in main().
// Companion notes live in: 06-oop-basics/01-encapsulation.md
// ════════════════════════════════════════════════════════════


#include <cstddef>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>


// ──── 1. public vs private field ────
// Same shape, different boundary. The private version forces every
// change to go through a member function — which is exactly where
// invariants, logging, or thread-safety will eventually live.
struct PublicCounter { int n = 0; };

class PrivateCounter {
private:
    int n = 0;

public:
    void inc() { ++n; }
    int  read() const { return n; }
};

void runPublicVsPrivate() {
    std::cout << "──── 1. public vs private field ────\n";

    PublicCounter  pub;
    PrivateCounter priv;

    pub.n  = 42;                          // direct write — no checks
    pub.n  = -1;                          // still legal, semantically junk

    priv.inc();
    priv.inc();
    // priv.n = -1;                       // ERROR: n is private

    std::cout << "  pub.n  = " << pub.n      << "\n";
    std::cout << "  priv  = " << priv.read() << "\n";
}


// ──── 2. getters / setters with validation ────
// Rejecting invalid input in the setter keeps the object consistent.
class Student {
private:
    std::string name;
    int         rollNumber = 0;

public:
    void setName(const std::string& newName) {
        if (!newName.empty()) name = newName;
    }

    void setRollNumber(int r) {
        if (r > 0) rollNumber = r;
    }

    const std::string& getName()      const { return name;      }
    int                getRollNumber() const { return rollNumber; }
};

void runGettersAndSetters() {
    std::cout << "──── 2. getters / setters ────\n";

    Student s;
    s.setName("Karan");
    s.setName("");                        // rejected
    s.setRollNumber(-7);                  // rejected
    std::cout << "  " << s.getName() << " (" << s.getRollNumber() << ")\n";
}


// ──── 3. default member initialisers ────
// C++11 lets the class itself provide defaults for its data members.
// Every constructor picks them up automatically.
class Config {
private:
    int    retries   = 3;
    double timeoutS = 1.5;
    bool   verbose   = false;

public:
    // No constructor — defaults above are used for every instance.
    int    getRetries()   const { return retries;   }
    double getTimeoutS()  const { return timeoutS;  }
    bool   isVerbose()    const { return verbose;   }
};

void runDefaultInitialisers() {
    std::cout << "──── 3. default member initialisers ────\n";

    Config c;                             // all defaults applied
    std::cout << "  retries=" << c.getRetries()
              << " timeout=" << c.getTimeoutS()
              << " verbose=" << std::boolalpha << c.isVerbose() << "\n";
}


// ──── 4. invariant defence in ctor + mutator ────
// The constructor establishes the invariant; the mutator defends it on
// every change. Outside code cannot break it without bypassing the API.
class PositiveNumber {
private:
    int value;                            // invariant: value > 0

public:
    explicit PositiveNumber(int v) : value(v) {
        if (v <= 0) throw std::invalid_argument("PositiveNumber: must be > 0");
    }

    PositiveNumber& add(int delta) {
        if (value + delta <= 0) throw std::overflow_error("would break invariant");
        value += delta;
        return *this;
    }

    int read() const { return value; }
};

void runInvariants() {
    std::cout << "──── 4. invariants ────\n";

    PositiveNumber p(5);
    p.add(3);                             // now 8
    std::cout << "  value = " << p.read() << "\n";

    try {
        p.add(-100);                      // throws
    } catch (const std::exception& e) {
        std::cout << "  caught: " << e.what() << "\n";
    }
}


// ──── 5. const correctness on getters ────
// `const` on a getter says "this read will not change the object".
// Returning const& for strings avoids a copy.
class BufferView {
private:
    std::vector<int> data;

public:
    explicit BufferView(std::vector<int> d) : data(std::move(d)) {}

    const int& at(std::size_t i) const { return data.at(i); }   // const getter
    std::size_t size() const { return data.size(); }

    // non-const — only mutable API
    void push(int x) { data.push_back(x); }
};

void runConstCorrectness() {
    std::cout << "──── 5. const correctness ────\n";

    BufferView b({10, 20, 30});
    const BufferView& cref = b;

    std::cout << "  b[1] = " << cref.at(1) << "\n";   // const ref, calls const getter
    b.push(40);
    // cref.push(40);                                // ERROR — cref is const
    std::cout << "  size = " << cref.size() << "\n";
}


// ──── 6. static factory enforcing validity ────
// The constructor is private — the only way in is a named factory that
// either returns a valid object or reports failure via std::optional.
#include <optional>

class Email {
private:
    std::string address;

    explicit Email(std::string a) : address(std::move(a)) {}

public:
    static std::optional<Email> make(const std::string& candidate) {
        auto at = candidate.find('@');
        if (at == std::string::npos || at == 0 || at + 1 == candidate.size()) {
            return std::nullopt;
        }
        return Email(candidate);
    }

    const std::string& emailAddress() const { return address; }
};

void runStaticFactory() {
    std::cout << "──── 6. static factory ────\n";

    auto good = Email::make("karan@example.com");
    auto bad  = Email::make("not-an-email");

    if (good) std::cout << "  valid: " << good->emailAddress() << "\n";
    else      std::cout << "  rejected (no factory entry)\n";

    if (bad)  std::cout << "  valid: " << bad->emailAddress()  << "\n";
    else      std::cout << "  rejected (no '@' in candidate)\n";
}


// ──── 7. friend function for tight coupling ────
// friend lets a specific free function (or class) reach into the
// private members. Use sparingly — only when the coupling is real.
class Counter {
private:
    int n = 0;
    friend void reset(Counter&);          // free function gets access

public:
    void inc() { ++n; }
    int  read() const { return n; }
};

void reset(Counter& c) { c.n = 0; }       // definition of the friend

void runFriend() {
    std::cout << "──── 7. friend function ────\n";

    Counter c;
    c.inc(); c.inc(); c.inc();
    std::cout << "  before reset = " << c.read() << "\n";
    reset(c);
    std::cout << "  after  reset = " << c.read() << "\n";
}


// ──── 8. Pimpl idiom — fully hidden implementation ────
// The header only mentions a forward-declared Impl. The .cpp would hold
// the real definition; here we keep both in one file for self-contained
// compilation. Callers recompile only when the public API changes.
class Widget {
private:
    struct Impl;                          // forward declaration only
    std::unique_ptr<Impl> p;              // opaque pointer

public:
    Widget();
    ~Widget();                            // out-of-line because Impl is incomplete here

    Widget(Widget&&) noexcept;            // move-only by design
    Widget& operator=(Widget&&) noexcept;

    // Disable copy — Pimpl + copy is a footgun unless you write it
    Widget(const Widget&)            = delete;
    Widget& operator=(const Widget&) = delete;

    void   setName(const std::string&);
    std::string name() const;
    int    size() const;
};

// ──── definitions (in a real project these would live in widget.cpp) ────
struct Widget::Impl {
    std::string name;
    std::vector<int> payload;
};

Widget::Widget()  : p(std::make_unique<Impl>()) {}
Widget::~Widget() = default;
Widget::Widget(Widget&&) noexcept            = default;
Widget& Widget::operator=(Widget&&) noexcept = default;

void          Widget::setName(const std::string& n) { p->name = n; }
std::string   Widget::name() const                 { return p->name; }
int           Widget::size()  const                { return static_cast<int>(p->payload.size()); }

void runPimpl() {
    std::cout << "──── 8. Pimpl idiom ────\n";

    Widget w;
    w.setName("hidden-impl");
    std::cout << "  name = " << w.name() << ", size = " << w.size() << "\n";
}


// ──── 9. Rule of five — copy / move / RAII ────
// A class that owns a resource needs to decide what happens on copy,
// move, and destruction. The five are: dtor, copy ctor, copy assign,
// move ctor, move assign.
class OwnedBuffer {
private:
    std::size_t   bytes = 0;
    std::unique_ptr<char[]> data;

public:
    OwnedBuffer() = default;
    explicit OwnedBuffer(std::size_t n) : bytes(n), data(std::make_unique<char[]>(n)) {}

    // copy — allocate a fresh buffer and copy the bytes
    OwnedBuffer(const OwnedBuffer& other)
      : bytes(other.bytes), data(std::make_unique<char[]>(other.bytes)) {
        std::copy(other.data.get(), other.data.get() + bytes, data.get());
    }

    OwnedBuffer& operator=(OwnedBuffer other) {   // copy-and-swap idiom
        swap(*this, other);
        return *this;
    }

    // move — steal the pointer, leave the source empty
    OwnedBuffer(OwnedBuffer&& other) noexcept
      : bytes(other.bytes), data(std::move(other.data)) {
        other.bytes = 0;
    }

    OwnedBuffer& operator=(OwnedBuffer&& other) noexcept {
        bytes = other.bytes;
        data  = std::move(other.data);
        other.bytes = 0;
        return *this;
    }

    ~OwnedBuffer() = default;

    friend void swap(OwnedBuffer& a, OwnedBuffer& b) noexcept {
        std::swap(a.bytes, b.bytes);
        std::swap(a.data,  b.data);
    }

    std::size_t size() const { return bytes; }
};

void runRuleOfFive() {
    std::cout << "──── 9. rule of five ────\n";

    OwnedBuffer a(64);
    OwnedBuffer b = a;                    // copy ctor
    OwnedBuffer c = std::move(a);         // move ctor — a is now empty

    std::cout << "  a.size = " << a.size()
              << "  b.size = " << b.size()
              << "  c.size = " << c.size() << "\n";
}


int main() {

    // ──── 1. public vs private field ────
    std::cout << "════ 1. public vs private field ════\n";
    runPublicVsPrivate();


    // ──── 2. getters / setters ────
    std::cout << "\n════ 2. getters / setters ════\n";
    runGettersAndSetters();


    // ──── 3. default member initialisers ────
    std::cout << "\n════ 3. default member initialisers ════\n";
    runDefaultInitialisers();


    // ──── 4. invariants ────
    std::cout << "\n════ 4. invariants ════\n";
    runInvariants();


    // ──── 5. const correctness ────
    std::cout << "\n════ 5. const correctness ════\n";
    runConstCorrectness();


    // ──── 6. static factory ────
    std::cout << "\n════ 6. static factory ════\n";
    runStaticFactory();


    // ──── 7. friend function ────
    std::cout << "\n════ 7. friend function ════\n";
    runFriend();


    // ──── 8. Pimpl idiom ────
    std::cout << "\n════ 8. Pimpl idiom ════\n";
    runPimpl();


    // ──── 9. rule of five ────
    std::cout << "\n════ 9. rule of five ════\n";
    runRuleOfFive();


    std::cout << "\n════ done ════\n";

    return 0;
}


// ════════════════════════════════════════════════════════════
// End of encapsulation demo.
// Companion note: 06-oop-basics/01-encapsulation.md
// ════════════════════════════════════════════════════════════