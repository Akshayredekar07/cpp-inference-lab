// ════════════════════════════════════════════════════════════
// Operators & Control Flow
// ════════════════════════════════════════════════════════════
// Build:
//   g++ -std=c++17 operators_control_flow.cpp -o app
//   ./app
//
// Pure C++17 — no C++20 features used (see the note in section 13).
// ════════════════════════════════════════════════════════════

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <array>
#include <typeinfo>
#include <iomanip>


template <typename T>
void show(const std::string& label, const T& value) {
    std::cout << "  " << std::left << std::setw(32) << label
              << " = " << value << "\n";
}


// ════════════════════════════════════════════════════════════
// Section 4 helper — logical short-circuit tracing
// ════════════════════════════════════════════════════════════

bool sideEffect(const std::string& name, bool value) {
    std::cout << "    evaluated " << name << " -> " << std::boolalpha << value << "\n";
    return value;
}


// ════════════════════════════════════════════════════════════
// Section 11 — scope resolution ::
// ════════════════════════════════════════════════════════════

int seatCount = 100;   // global

namespace Campus {
    int seatCount = 40;
    namespace Hostel {
        int seatCount = 12;
    }
}

class Classroom {
public:
    static int seatCount;              // declaration
    enum class Wing { East, West };
};
int Classroom::seatCount = 30;         // definition, out-of-line


// ════════════════════════════════════════════════════════════
// Section 12 — cast operators (preview; full chapter later)
// ════════════════════════════════════════════════════════════

struct Animal {
    virtual ~Animal() = default;
    virtual std::string sound() const { return "..."; }
};

struct Dog : Animal {
    std::string sound() const override { return "Woof"; }
    void fetch() const { std::cout << "    fetching the ball\n"; }
};


// ════════════════════════════════════════════════════════════
// Section 13 — operator overloading (preview; full chapter later)
// ════════════════════════════════════════════════════════════

struct Vector2 {
    double x = 0.0;
    double y = 0.0;

    Vector2 operator+(const Vector2& other) const {
        return Vector2{x + other.x, y + other.y};
    }
    bool operator==(const Vector2& other) const {
        return x == other.x && y == other.y;
    }
};

std::ostream& operator<<(std::ostream& out, const Vector2& v) {
    return out << "(" << v.x << ", " << v.y << ")";
}

// Pre-C++20: every comparison is a separate hand-written function.
// (C++20's operator<=> collapses all six into one line — covered later,
// with the rest of C++20, once the core language is done.)
struct Marks {
    int value;
};

bool operator==(const Marks& a, const Marks& b) { return a.value == b.value; }
bool operator!=(const Marks& a, const Marks& b) { return !(a == b); }
bool operator<(const Marks& a, const Marks& b)  { return a.value < b.value; }
bool operator>(const Marks& a, const Marks& b)  { return b < a; }
bool operator<=(const Marks& a, const Marks& b) { return !(b < a); }
bool operator>=(const Marks& a, const Marks& b) { return !(a < b); }


// ════════════════════════════════════════════════════════════
// Section 10 — noexcept specifier examples
// ════════════════════════════════════════════════════════════

void safeOp() noexcept {
    // promises never to throw; violating this calls std::terminate
}

void riskyOp() {
    // may throw
}


int main() {

    // ════════════════════════════════════════════════════════
    // 1. Operators overview and precedence
    // ════════════════════════════════════════════════════════
    std::cout << "──── 1. precedence overview ────\n";

    // Roughly high -> low precedence (partial, the parts used below):
    //   ::                                    scope resolution
    //   () [] -> . ++ -- (postfix)            postfix
    //   ++ -- + - ! ~ * & sizeof (unary)      unary, right-to-left
    //   * / %                                 multiplicative
    //   + -                                   additive
    //   << >>                                 bitwise shift
    //   < <= > >=                             relational
    //   == !=                                 equality
    //   &                                     bitwise AND
    //   ^                                     bitwise XOR
    //   |                                     bitwise OR
    //   &&                                    logical AND
    //   ||                                    logical OR
    //   ?:                                    ternary, right-to-left
    //   = += -= ...                           assignment, right-to-left
    //   ,                                     comma, LOWEST

    int result = 2 + 3 * 4;          // * before +
    int forced = (2 + 3) * 4;        // parens override precedence

    show("2 + 3 * 4", result);
    show("(2 + 3) * 4", forced);

    // Most operators are left-to-right; assignment and unary are
    // right-to-left. That is why chained assignment works:
    int p, q, r;
    p = q = r = 5;    // evaluated right-to-left: r=5, then q=r, then p=q
    std::cout << "  p=q=r=5  ->  p=" << p << " q=" << q << " r=" << r << "\n";

    std::cout << "  when in doubt, use parentheses — precedence bugs are silent\n";


    // ════════════════════════════════════════════════════════
    // 2. Arithmetic operators
    // ════════════════════════════════════════════════════════
    std::cout << "\n──── 2. arithmetic ────\n";

    int a = 17, b = 5;

    std::cout << "\n\t\ta=" << a << " b=" << b << "\n";

    show("a + b", a + b);
    show("a - b", a - b);
    show("a * b", a * b);
    show("a / b (int / int)", a / b);          // truncates toward zero
    show("a % b", a % b);
    show("-a / b", -a / b);                    // C++11+: truncates toward zero
    show("-a % b", -a % b);                    // sign follows the DIVIDEND

    double da = 17.0, db = 5.0;
    show("17.0 / 5.0", da / db);

    show("unary -a", -a);
    show("unary +a (no-op, promotes)", +a);

    int divByZeroGuardDen = 0;
    if (divByZeroGuardDen != 0) {
        std::cout << (a / divByZeroGuardDen) << "\n";
    } else {
        std::cout << "  a / 0 for ints is UNDEFINED BEHAVIOUR (usually crashes)\n";
    }
    std::cout << "  a / 0.0 for doubles gives inf, not UB: "
              << (17.0 / 0.0) << "\n";


    // ════════════════════════════════════════════════════════
    // 3. Relational and equality operators
    // ════════════════════════════════════════════════════════
    std::cout << "\n──── 3. relational & equality ────\n";

    int x = 10, y = 20;
    std::cout << "\n\tx=" << x << " y=" << y << "\n";
    
    show("x < y", x < y);
    show("x > y", x > y);
    show("x <= 10", x <= 10);
    show("x >= 11", x >= 11);
    show("x == 10", x == 10);
    show("x != y", x != y);

    // Classic trap: a < b < c does NOT do mathematical chaining.
    int lo = 5, mid = 1, hi = 10;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wparentheses"
    bool chained = lo < mid < hi;          // (lo < mid) < hi -> (false=0) < 10 -> true
#pragma GCC diagnostic pop
    std::cout << "  lo < mid < hi = " << chained
              << "   <- (lo<mid) is bool 0/1, THEN compared to hi. Almost never intended.\n";
    std::cout << "  correct form: (lo < mid) && (mid < hi) = "
              << ((lo < mid) && (mid < hi)) << "\n";

    // Comparing floats with == is fragile.
    double f1 = 0.1 + 0.2, f2 = 0.3;
    show("0.1+0.2 == 0.3", (f1 == f2));
    show("|diff| < 1e-9", (std::abs(f1 - f2) < 1e-9));


    // ════════════════════════════════════════════════════════
    // 4. Logical operators
    // ════════════════════════════════════════════════════════
    std::cout << "\n──── 4. logical (short-circuit) ────\n";

    show("!true", !true);
    show("true && false", (true && false));
    show("true || false", (true || false));

    std::cout << "  && stops at the first false:\n";
    if (sideEffect("left(false)", false) && sideEffect("right", true)) {
        std::cout << "    (unreachable)\n";
    }

    std::cout << "  || stops at the first true:\n";
    if (sideEffect("left(true)", true) || sideEffect("right", true)) {
        std::cout << "    entered the if\n";
    }

    std::cout << "  this is why `ptr != nullptr && ptr->value` is SAFE —\n";
    std::cout << "  the right side never runs if ptr is null\n";


    // ════════════════════════════════════════════════════════
    // 5. Bitwise operators
    // ════════════════════════════════════════════════════════
    std::cout << "\n──── 5. bitwise ────\n";

    unsigned int flags = 0b0000;
    const unsigned int READ = 0b0001, WRITE = 0b0010, EXEC = 0b0100;

    show("READ|WRITE", READ | WRITE);
    show("READ & WRITE", READ & WRITE);
    show("READ ^ WRITE", READ ^ WRITE);
    show("~READ (32-bit)", ~READ);
    show("1 << 3", 1 << 3);
    show("16 >> 2", 16 >> 2);

    flags |= READ;                    // set the READ bit
    flags |= WRITE;                   // set the WRITE bit
    show("after set READ,WRITE", flags);

    flags &= ~WRITE;                  // clear the WRITE bit
    show("after clear WRITE", flags);

    flags ^= EXEC;                    // toggle EXEC on
    show("after toggle EXEC", flags);

    bool hasRead = (flags & READ) != 0;
    show("hasRead?", hasRead);

    std::cout << "  masks like this back real permission systems (chmod, GL flags)\n";


    // ════════════════════════════════════════════════════════
    // 6. Assignment and compound assignment
    // ════════════════════════════════════════════════════════
    std::cout << "\n──── 6. assignment ────\n";

    int counter = 10;

    counter += 5;  show("counter += 5", counter);
    counter -= 3;  show("counter -= 3", counter);
    counter *= 2;  show("counter *= 2", counter);
    counter /= 4;  show("counter /= 4", counter);
    counter %= 4;  show("counter %= 4", counter);

    unsigned int bits = 0b1010;
    bits <<= 2;    show("bits <<= 2", bits);
    bits >>= 1;    show("bits >>= 1", bits);
    bits |= 0b1;   show("bits |= 1", bits);
    bits &= 0b0111;show("bits &= 0b0111", bits);
    bits ^= 0b1111;show("bits ^= 0b1111", bits);

    std::cout << "  a += b  is shorthand for a = a + b, evaluated once, not twice\n";
    std::cout << "  matters when the LHS is expensive: arr[compute()] += 1\n";


    // ════════════════════════════════════════════════════════
    // 7. Increment and decrement
    // ════════════════════════════════════════════════════════
    std::cout << "\n──── 7. increment / decrement ────\n";

    int pre = 5;
    int postResult = pre++;           // returns OLD value, then increments
    show("post: pre++ returned", postResult);
    show("pre after post-inc", pre);

    int again = 5;
    int preResult = ++again;          // increments, then returns NEW value
    show("pre: ++again returned", preResult);
    show("again after pre-inc", again);

    // Pointer increment moves by sizeof(element), not by 1 byte.
    int arr[4] = {10, 20, 30, 40};
    int* it = arr;
    show("*it", *it);
    ++it;
    show("*(++it)", *it);
    it++;
    show("*(it++) then read", *it);

    std::cout << "  prefer ++i over i++ for non-trivial iterators: post-inc must\n";
    std::cout << "  copy the old state before mutating; pre-inc does not\n";


    // ════════════════════════════════════════════════════════
    // 8. Member access and pointer operators
    // ════════════════════════════════════════════════════════
    std::cout << "\n──── 8. member access & pointer operators ────\n";

    Vector2 point{3.0, 4.0};
    Vector2* pPoint = &point;

    show("point.x (dot, object)", point.x);
    show("pPoint->y (arrow, pointer)", pPoint->y);
    show("(*pPoint).x (deref then dot)", (*pPoint).x);

    int value = 42;
    int* addr = &value;               // address-of
    int  back = *addr;                // dereference
    show("&value then *addr", back);

    // Pointer-to-member operators .* and ->* — rare, shown for completeness.
    double Vector2::* memberPtr = &Vector2::x;
    Vector2 origin{7.0, 8.0};
    show("origin.*memberPtr", origin.*memberPtr);

    Vector2* pOrigin = &origin;
    show("pOrigin->*memberPtr", pOrigin->*memberPtr);

    std::cout << "  .* / ->* let you store WHICH member to access as a variable\n";


    // ════════════════════════════════════════════════════════
    // 9. Conditional (ternary) and comma
    // ════════════════════════════════════════════════════════
    std::cout << "\n──── 9. ternary & comma ────\n";

    int marksValue = 72;
    std::string grade = (marksValue >= 90) ? "A"
                       : (marksValue >= 75) ? "B"
                       : (marksValue >= 60) ? "C"
                       : "D";
    show("chained ternary grade", grade);

    // Ternary yields an lvalue when both branches match type+valueness.
    int leftScore = 10, rightScore = 20;
    bool pickLeft = false;
    (pickLeft ? leftScore : rightScore) = 99;
    show("leftScore", leftScore);
    show("rightScore (written via ternary)", rightScore);

    // Comma operator: evaluates left, discards it, yields right.
    int commaResult = (std::cout << "    (comma side-effect) ", 5 + 5);
    show("comma expression result", commaResult);

    for (int i = 0, j = 10; i < j; ++i, --j) {
        if (i == 2) {
            std::cout << "    for-comma: i=" << i << " j=" << j << "\n";
        }
    }
    std::cout << "  comma in a for-header is the ONE common legitimate use\n";


    // ════════════════════════════════════════════════════════
    // 10. sizeof, alignof, typeid, noexcept
    // ════════════════════════════════════════════════════════
    std::cout << "\n──── 10. sizeof / alignof / typeid / noexcept ────\n";

    show("sizeof(Vector2)", sizeof(Vector2));
    show("alignof(Vector2)", alignof(Vector2));

    Animal* animalPtr = new Dog();
    std::cout << "  typeid(*animalPtr).name() = " << typeid(*animalPtr).name()
              << "   (RTTI: resolved at RUNTIME via the vtable)\n";
    std::cout << "  typeid(Dog).name()        = " << typeid(Dog).name()
              << "   (resolved at COMPILE time, no object needed)\n";
    delete animalPtr;

    show("noexcept(safeOp())", noexcept(safeOp()));
    show("noexcept(riskyOp())", noexcept(riskyOp()));
    std::cout << "  noexcept(expr) is a COMPILE-TIME query, it does not call expr\n";
    std::cout << "  throwing out of a noexcept function calls std::terminate\n";


    // ════════════════════════════════════════════════════════
    // 11. Scope resolution ::
    // ════════════════════════════════════════════════════════
    std::cout << "\n──── 11. scope resolution :: ────\n";

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
    int seatCount = 5;      // shadows the global
#pragma GCC diagnostic pop

    show("local seatCount", seatCount);
    show("::seatCount (global)", ::seatCount);
    show("Campus::seatCount", Campus::seatCount);
    show("Campus::Hostel::seatCount", Campus::Hostel::seatCount);
    show("Classroom::seatCount (static)", Classroom::seatCount);

    Classroom::Wing wing = Classroom::Wing::East;
    show("Classroom::Wing::East", static_cast<int>(wing));

    std::cout << "  :: with nothing before it means \"global namespace\"\n";
    std::cout << "  break/continue/return (sections 18, 14) are C++'s structured\n";
    std::cout << "  alternative to goto for leaving a scope early\n";


    // ════════════════════════════════════════════════════════
    // 12. Cast operators (preview)
    // ════════════════════════════════════════════════════════
    std::cout << "\n──── 12. casts (preview) ────\n";

    double piValue = 3.99;
    int truncatedPi = static_cast<int>(piValue);          // checked, compile-time
    show("static_cast<int>(3.99)", truncatedPi);

    Animal* base = new Dog();
    Dog* derived = dynamic_cast<Dog*>(base);               // runtime-checked
    if (derived) {
        derived->fetch();
    }
    Animal plainAnimal;
    Animal* plainAsBase = &plainAnimal;   // hide the static type from the compiler
    Dog* failedCast = dynamic_cast<Dog*>(plainAsBase);
    show("dynamic_cast to unrelated type", (failedCast == nullptr));
    delete base;

    const int lockedValue = 100;
    int* unlocked = const_cast<int*>(&lockedValue);        // strips const — dangerous
    std::cout << "  const_cast can compile but writing through it when the\n";
    std::cout << "  ORIGINAL object is truly const is undefined behaviour\n";
    (void)unlocked;

    float bitsAsFloat = 1.5f;
    int* reinterpreted = reinterpret_cast<int*>(&bitsAsFloat);  // raw bit reinterpretation
    std::cout << "  reinterpret_cast raw bits of 1.5f as int = " << *reinterpreted << "\n";

    std::cout << "  rule of thumb: static_cast normally, dynamic_cast for polymorphic\n";
    std::cout << "  downcasts, const_cast only to call legacy APIs, reinterpret_cast\n";
    std::cout << "  as a last resort — a dedicated cast chapter covers this in depth\n";


    // ════════════════════════════════════════════════════════
    // 13. Operator overloading (preview)
    // ════════════════════════════════════════════════════════
    std::cout << "\n──── 13. operator overloading (preview) ────\n";

    Vector2 v1{1.0, 2.0};
    Vector2 v2{3.0, 4.0};
    Vector2 v3 = v1 + v2;              // calls operator+

    std::cout << "  " << v1 << " + " << v2 << " = " << v3 << "\n";
    show("v1 == v1", (v1 == v1));
    show("v1 == v2", (v1 == v2));

    Marks m1{75}, m2{90};
    show("m1 < m2", (m1 < m2));
    show("m1 == m1", (m1 == m1));
    show("m1 >= m2", (m1 >= m2));
    std::cout << "  six operators, six hand-written functions — that boilerplate is\n";
    std::cout << "  exactly what C++20's operator<=> exists to remove (covered later)\n";


    // ════════════════════════════════════════════════════════
    // 14. if / else
    // ════════════════════════════════════════════════════════
    std::cout << "\n──── 14. if / else ────\n";

    int attendance = 82;

    if (attendance >= 75) {
        std::cout << "  eligible for exam\n";
    } else if (attendance >= 60) {
        std::cout << "  needs condonation\n";
    } else {
        std::cout << "  detained\n";
    }

    // C++17: if with an init-statement — scopes the variable to the if/else.
    std::map<std::string, int> roster{{"Karan", 21}, {"Tanvi", 22}};

    if (auto found = roster.find("Karan"); found != roster.end()) {
        std::cout << "  init-if found: " << found->first << " -> " << found->second << "\n";
    } else {
        std::cout << "  not found\n";
    }
    // `found` does not exist here — it was scoped to the if/else above.


    // ════════════════════════════════════════════════════════
    // 15. switch / case / default
    // ════════════════════════════════════════════════════════
    std::cout << "\n──── 15. switch ────\n";

    int day = 3;

    switch (day) {
        case 1:
        case 7:
            std::cout << "  weekend\n";
            break;
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            std::cout << "  weekday\n";
            break;
        default:
            std::cout << "  invalid day\n";
            break;
    }

    // Intentional fallthrough, marked so -Wimplicit-fallthrough stays quiet.
    int level = 2;
    switch (level) {
        case 3:
            std::cout << "  grants admin\n";
            [[fallthrough]];
        case 2:
            std::cout << "  grants write\n";
            [[fallthrough]];
        case 1:
            std::cout << "  grants read\n";
            break;
        default:
            std::cout << "  no access\n";
    }

    // C++17: switch with an init-statement.
    switch (int code = 404; code) {
        case 200:
            std::cout << "  OK\n";
            break;
        case 404:
            std::cout << "  init-switch: Not Found\n";
            break;
        default:
            std::cout << "  Unhandled\n";
    }

    std::cout << "  forgetting `break` falls through SILENTLY — the #1 switch bug\n";


    // ════════════════════════════════════════════════════════
    // 16. while and do-while
    // ════════════════════════════════════════════════════════
    std::cout << "\n──── 16. while / do-while ────\n";

    int n = 5, factorial = 1;
    while (n > 1) {
        factorial *= n;
        --n;
    }
    show("5! via while", factorial);

    // do-while runs the body at least ONCE, condition checked after.
    int menuChoice = 99;
    int attempts = 0;
    do {
        ++attempts;
        menuChoice = (attempts == 1) ? 99 : 1;   // simulate: bad input, then good
    } while (menuChoice != 1 && attempts < 5);
    show("do-while attempts before valid input", attempts);

    std::cout << "  while checks BEFORE the body; do-while checks AFTER\n";
    std::cout << "  do-while guarantees at least one execution — good for menus\n";


    // ════════════════════════════════════════════════════════
    // 17. for and range-for
    // ════════════════════════════════════════════════════════
    std::cout << "\n──── 17. for / range-for ────\n";

    for (int i = 0; i < 3; ++i) {
        std::cout << "  classic for i=" << i << "\n";
    }

    std::vector<std::string> names{"Karan", "Tanvi", "Rohit"};

    for (const auto& name : names) {           // range-for, read-only
        std::cout << "  range-for name=" << name << "\n";
    }

    for (auto& name : names) {                 // range-for, mutable
        name += "!";
    }
    std::cout << "  after mutation: " << names[0] << ", " << names[1] << ", " << names[2] << "\n";

    // range-for with an index, using structured bindings over a zipped index.
    for (std::size_t i = 0; i < names.size(); ++i) {
        std::cout << "  indexed: [" << i << "] = " << names[i] << "\n";
    }

    std::cout << "  range-for calls begin()/end() once; never .push_back() into\n";
    std::cout << "  the SAME container you are range-for'ing — iterators may invalidate\n";


    // ════════════════════════════════════════════════════════
    // 18. break, continue
    // ════════════════════════════════════════════════════════
    std::cout << "\n──── 18. break / continue ────\n";

    for (int i = 1; i <= 10; ++i) {
        if (i % 2 == 0) continue;      // skip evens
        if (i > 7) break;              // stop early
        std::cout << "  odd, <=7: " << i << "\n";
    }

    // C++ has NO labeled break — this is the standard workaround.
    bool stopOuter = false;
    for (int i = 0; i < 3 && !stopOuter; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (i == 1 && j == 1) {
                stopOuter = true;
                break;                  // only breaks the INNER loop
            }
            std::cout << "  nested i=" << i << " j=" << j << "\n";
        }
    }
    std::cout << "  a bare `break` only exits the INNERMOST loop or switch\n";


    // ════════════════════════════════════════════════════════
    // 19. goto and labels
    // ════════════════════════════════════════════════════════
    std::cout << "\n──── 19. goto ────\n";

    int retries = 0;

retryLabel:
    ++retries;
    if (retries < 3) {
        goto retryLabel;               // backward jump: a manual loop
    }
    show("retries via goto", retries);

    // goto is the ONE real use case still endorsed: breaking out of
    // deeply nested loops in C-style code with no early-return option.
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (i == 1 && j == 1) {
                goto doubleBreak;       // jumps out of BOTH loops at once
            }
        }
    }
doubleBreak:
    std::cout << "  goto jumped out of two nested loops in one step\n";

    // Illegal example (commented): cannot jump INTO the scope of a
    // variable with an initializer.
    //
    //     goto skip;
    //     int guarded = 5;   // error: jump bypasses initialization
    // skip:
    //     std::cout << guarded;

    std::cout << "  outside that one case, prefer break/continue/return/exceptions\n";


    // ════════════════════════════════════════════════════════
    // 20. Structured bindings (C++17)
    // ════════════════════════════════════════════════════════
    std::cout << "\n──── 20. structured bindings ────\n";

    std::pair<std::string, int> student{"Drishya", 22};
    auto [studentName, studentRoll] = student;
    show("pair binding: name", studentName);
    show("pair binding: roll", studentRoll);

    std::tuple<std::string, double, bool> record{"Arjun", 8.15, true};
    auto [tName, tCgpa, tActive] = record;
    std::cout << "  tuple binding: " << tName << ", " << tCgpa
              << ", " << std::boolalpha << tActive << "\n";

    std::map<std::string, int> attendanceMap{{"Karan", 91}, {"Tanvi", 88}};
    for (const auto& [studentKey, percent] : attendanceMap) {
        std::cout << "  map binding: " << studentKey << " -> " << percent << "%\n";
    }

    int fixedArr[3] = {7, 8, 9};
    auto [e0, e1, e2] = fixedArr;
    std::cout << "  array binding: " << e0 << ", " << e1 << ", " << e2 << "\n";

    // Binding to REFERENCES to mutate through the binding.
    auto& [refName, refRoll] = student;
    refRoll = 23;
    show("student.second after ref-binding write", student.second);

    std::cout << "  structured bindings replace std::tie / .first / .second /\n";
    std::cout << "  std::get<N> boilerplate almost everywhere\n";


    // ════════════════════════════════════════════════════════
    // 21. Practice problems
    // ════════════════════════════════════════════════════════
    // [ ] Precedence quiz — predict, then verify: `int r = 10 - 2 * 3 % 4 + 1;`
    // [ ] Integer division trap — write a function averaging an int vector
    //     that returns a silently wrong result via int/int division, then fix it.
    // [ ] Chained comparison bug — reproduce `a < b < c` giving a wrong
    //     answer, then rewrite it with `&&`.
    // [ ] Bit flags — model 4 file permissions (read/write/exec/delete) as
    //     bits in one `unsigned int`; write set/clear/toggle/has functions.
    // [ ] Pre vs post — write a loop where `i++` vs `++i` inside the same
    //     expression (e.g. `arr[i++] = i;`) gives a genuinely different result.
    // [ ] Ternary lvalue — write `(cond ? a : b) = value;` and explain
    //     when the compiler rejects it (differing types/valueness).
    // [ ] noexcept audit — mark a function `noexcept`, then make it throw
    //     under a condition, and observe `std::terminate` firing.
    // [ ] Scope resolution drill — shadow a global with a local of the
    //     same name, then read both in one line using `::`.
    // [ ] switch fallthrough — write a switch with an intentional
    //     fallthrough and an accidental one (missing `break`); compare.
    // [ ] do-while menu — build a "retry until valid" input loop that
    //     MUST run at least once even before any input is read.
    // [ ] Labeled-break workaround — write a 3x3 nested loop that needs
    //     to stop both loops on a condition, without using `goto`.
    // [ ] goto vs flag — rewrite the double-nested-loop `goto` example
    //     above using only a boolean flag, then decide which reads clearer.
    // [ ] Structured bindings refactor — take a function returning
    //     `std::pair<bool,std::string>` (success + message) and consume
    //     it at every call site with a structured binding instead of
    //     `.first` / `.second`.
    // [ ] Range-for invalidation — deliberately `push_back` into a
    //     vector while range-for'ing over it and observe what breaks.
    // [ ] Cast selection — given a `Base*` known to point at a `Derived`,
    //     justify in one sentence why `static_cast` is appropriate there
    //     instead of `dynamic_cast`.
    // [ ] Spaceship operator — give a `struct` two int members and a
    //     defaulted `operator<=>`; sort a `std::vector` of them and
    //     confirm the ordering matches member declaration order.


    std::cout << "\n──── done ────\n";

    return 0;
}