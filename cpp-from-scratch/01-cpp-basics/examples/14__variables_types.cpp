// ════════════════════════════════════════════════════════════
// Variables, Types & Constants
// ════════════════════════════════════════════════════════════
// Build:
//   g++ -std=c++20 -Wall -Wextra -Wpedantic -Wshadow variables_types.cpp -o app
//   ./app
//
// C++20 is required for constinit / consteval / char8_t.
// Everything else works at C++17.
// ════════════════════════════════════════════════════════════

#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <cstdint>
#include <climits>
#include <limits>
#include <type_traits>
#include <iomanip>
#include <cstring>


// ════════════════════════════════════════════════════════════
// Section 8 — constexpr / consteval at namespace scope
// ════════════════════════════════════════════════════════════

// constexpr function: MAY run at compile time, may run at runtime.
constexpr int square(int n) {
    return n * n;
}

// consteval function (C++20): MUST run at compile time. Calling it
// with a runtime value is a hard error.
consteval int cubeAtCompileTime(int n) {
    return n * n * n;
}

// constinit (C++20): guarantees constant initialization, killing the
// static initialization order fiasco. Unlike constexpr, the object is
// still mutable afterwards.
constinit int globalCounter = 100;

// constexpr variable — immutable AND usable in constant expressions.
constexpr int MAX_STUDENTS = 60;

// const at namespace scope has INTERNAL linkage by default in C++
// (unlike C). Each .cpp gets its own copy unless marked extern.
const double PASS_MARK = 33.0;


// ════════════════════════════════════════════════════════════
// Section 11 — storage classes
// ════════════════════════════════════════════════════════════

// static at file scope -> internal linkage (invisible to other TUs)
static int fileLocalSeats = 0;

// extern-linkage global (default for non-const at namespace scope)
int totalEnrollments = 0;

// thread_local: one instance per thread
thread_local int threadRequestCount = 0;

int nextSeat() {
    // static local: initialized ONCE, on first call, survives the call
    static int seat = 0;
    ++fileLocalSeats;
    return ++seat;
}

int countCalls() {
    static int calls = 0;   // separate object from nextSeat's `seat`
    return ++calls;
}


// ════════════════════════════════════════════════════════════
// Section 12 — enums
// ════════════════════════════════════════════════════════════

// Unscoped enum: names leak into the enclosing scope, implicitly
// converts to int. Convenient, collision-prone.
enum Grade { GRADE_A, GRADE_B, GRADE_C, GRADE_D };

// Explicit values; unspecified ones continue from the previous.
enum HttpStatus { OK_200 = 200, MOVED_301 = 301, NOTFOUND_404 = 404 };

// Scoped enum (enum class): names are scoped, NO implicit int
// conversion, underlying type controllable. Prefer this.
enum class Department { CSE, ENTC, MECH, CIVIL };

// Fixed underlying type -> known size, forward-declarable.
enum class Level : std::uint8_t { Junior = 1, Mid = 2, Senior = 3 };

const char* toText(Department d) {
    switch (d) {
        case Department::CSE:   return "CSE";
        case Department::ENTC:  return "ENTC";
        case Department::MECH:  return "MECH";
        case Department::CIVIL: return "CIVIL";
    }
    return "UNKNOWN";
}


// ════════════════════════════════════════════════════════════
// Section 13 — struct
// ════════════════════════════════════════════════════════════

// Aggregate: public members, no user-declared constructors.
// Supports aggregate initialization and designated initializers (C++20).
struct Student {
    std::string name;
    int rollNumber = 0;      // default member initializer
    double cgpa = 0.0;
    Department dept = Department::CSE;
};

// Struct with member functions — still a struct, `struct` just means
// "class with default public access".
struct Rectangle {
    double width  = 0.0;
    double height = 0.0;

    double area() const { return width * height; }
    double perimeter() const { return 2 * (width + height); }
};

// Layout demonstration — padding and alignment.
struct PaddedLayout {
    char  a;      // 1 byte + 3 padding
    int   b;      // 4
    char  c;      // 1 + 7 padding
    double d;     // 8
};

struct PackedLayout {
    double d;     // 8
    int    b;     // 4
    char   a;     // 1
    char   c;     // 1 + 2 padding
};


// ════════════════════════════════════════════════════════════
// Section 14 — union
// ════════════════════════════════════════════════════════════

// All members share the SAME storage. Only one member is "active".
// Reading an inactive member is undefined behaviour in C++.
union Value {
    int         asInt;
    float       asFloat;
    char        asBytes[4];
};

// Tagged union — the safe pattern: carry a discriminator yourself.
enum class ValueKind { Int, Double, Text };

struct TaggedValue {
    ValueKind kind;
    union {
        int    i;
        double d;
    };
    std::string text;   // kept outside the union: non-trivial type
};


// ════════════════════════════════════════════════════════════
// Section 7 — reference / pointer helpers
// ════════════════════════════════════════════════════════════

void byValue(int x)        { x = 999; (void)x; }
void byReference(int& x)   { x = 999; }
void byConstRef(const int& x) { std::cout << "  read-only: " << x << "\n"; }
void byPointer(int* x)     { if (x) *x = 999; }


// ════════════════════════════════════════════════════════════
// Section 9 — decltype / decltype(auto) helpers
// ════════════════════════════════════════════════════════════

std::vector<int> marksPool{90, 75, 60, 45};

// auto DROPS references and const -> returns a COPY
auto getCopy(int index) { return marksPool[index]; }

// decltype(auto) PRESERVES the exact type -> returns int&
decltype(auto) getRef(int index) { return marksPool[index]; }


// ════════════════════════════════════════════════════════════
// Section 10 — type aliases
// ════════════════════════════════════════════════════════════

// Old C style
typedef unsigned long long Timestamp;

// Modern: reads left-to-right, and supports templates
using RollNumber = int;
using StudentList = std::vector<Student>;
using Callback = void(*)(int);            // function pointer alias

// typedef CANNOT do this; `using` can — alias templates.
template <typename T>
using Pair = std::pair<T, T>;

void onSeatAssigned(int seat) {
    std::cout << "  callback fired for seat " << seat << "\n";
}


// ════════════════════════════════════════════════════════════
// small printing helper
// ════════════════════════════════════════════════════════════

template <typename T>
void show(const std::string& label, const T& value) {
    std::cout << "  " << std::left << std::setw(26) << label
              << " = " << value << "\n";
}


int main() {

    // ════════════════════════════════════════════════════════
    // 1. Variables
    // ════════════════════════════════════════════════════════
    std::cout << "──── 1. variables ────\n";

    int rollNumber = 21;               // declaration + initialization
    double cgpa = 8.15;
    char section = 'A';
    bool isEnrolled = true;

    std::cout << "rollNumber = " << rollNumber << "\n";
    std::cout << "cgpa       = " << cgpa << "\n";
    std::cout << "section    = " << section << "\n";
    std::cout << "isEnrolled = " << std::boolalpha << isEnrolled << "\n";

    // A local left uninitialized holds GARBAGE — reading it is UB.
    // int garbage;            // never do this
    // std::cout << garbage;   // undefined behaviour

    // Globals/statics ARE zero-initialized. Locals are NOT.
    std::cout << "totalEnrollments (global, zero-init) = " << totalEnrollments << "\n";

    // Multiple declarations on one line — the * binds to the NAME.
    int a = 1, b = 2, c = 3;
    std::cout << "a,b,c = " << a << "," << b << "," << c << "\n";

    int  valueOne = 5;
    int* ptrOne = &valueOne;
    int* ptrTwo = nullptr;   // NOT `int* p1, p2;` — p2 would be a plain int
    std::cout << "ptrOne targets " << *ptrOne
              << ", ptrTwo is null = " << (ptrTwo == nullptr) << "\n";


    // ════════════════════════════════════════════════════════
    // 2. Initialization forms and narrowing
    // ════════════════════════════════════════════════════════
    std::cout << "\n──── 2. initialization forms ────\n";

    int copyInit    = 10;      // copy initialization
    int directInit(20);        // direct initialization
    int braceInit{30};         // direct-list-init  <- PREFER THIS
    int copyBrace = {40};      // copy-list-init
    int valueInit{};           // value-init -> zero
    int defaultInit;           // default-init -> INDETERMINATE for locals
    defaultInit = 50;          // assign before reading

    show("copy  int x = 10", copyInit);
    show("direct int x(20)", directInit);
    show("brace int x{30}", braceInit);
    show("copy-brace x = {40}", copyBrace);
    show("value int x{}", valueInit);
    show("default (assigned after)", defaultInit);

    // Narrowing: braces REJECT lossy conversions at compile time.
    double precise = 3.99;
    int truncated = precise;          // silent: 3
    // int safe{precise};             // ERROR: narrowing conversion

    show("int x = 3.99 (silent)", truncated);
    std::cout << "  int x{3.99} would be a COMPILE ERROR — that is the point\n";

    // Most vexing parse: `Rectangle r();` declares a FUNCTION.
    // Rectangle mvp();     // function returning Rectangle, taking nothing
    Rectangle fixed{};      // braces make it unambiguously an object
    show("Rectangle r{} area", fixed.area());

    // Brace init with a vector behaves differently from parens.
    std::vector<int> byParens(5, 1);   // 5 elements, each 1
    std::vector<int> byBraces{5, 1};   // 2 elements: 5 and 1

    std::cout << "  vector(5,1) size = " << byParens.size() << "\n";
    std::cout << "  vector{5,1} size = " << byBraces.size()
              << "  <- initializer_list wins\n";


    // ════════════════════════════════════════════════════════
    // 3. Fundamental data types
    // ════════════════════════════════════════════════════════
    std::cout << "\n──── 3. fundamental types ────\n";

    bool flag = true;
    char letter = 'K';
    short smallNum = 32000;
    int number = 2000000;
    long longNum = 9000000000L;
    long long hugeNum = 9000000000000000000LL;
    float ratio = 3.14159f;
    double precision = 3.141592653589793;
    long double extended = 3.14159265358979323846L;

    std::cout << std::setprecision(17);
    show("bool", flag);
    show("char", letter);
    show("short", smallNum);
    show("int", number);
    show("long", longNum);
    show("long long", hugeNum);
    show("float", ratio);
    show("double", precision);
    show("long double (cast to double)", static_cast<double>(extended));
    std::cout << std::setprecision(6);

    // void: no value. Only valid as a return type or void*.
    void* anyPointer = &number;
    std::cout << "  void* can point at anything, cannot be dereferenced directly\n";
    std::cout << "  recovered via cast = " << *static_cast<int*>(anyPointer) << "\n";

    // Floating point is NOT exact.
    double sum = 0.1 + 0.2;
    std::cout << std::setprecision(17);
    std::cout << "  0.1 + 0.2 = " << sum << "  (== 0.3 is " << (sum == 0.3) << ")\n";
    std::cout << std::setprecision(6);
    std::cout << "  compare floats with an epsilon, never with ==\n";


    // ════════════════════════════════════════════════════════
    // 4. Type modifiers and fixed-width integers
    // ════════════════════════════════════════════════════════
    std::cout << "\n──── 4. modifiers & fixed-width ────\n";

    signed int   positiveOrNegative = -100;
    unsigned int nonNegativeOnly = 100u;

    show("signed int", positiveOrNegative);
    show("unsigned int", nonNegativeOnly);

    // Signed/unsigned mixing: the signed operand converts to unsigned.
    int signedValue = -1;
    unsigned int unsignedValue = 1u;
    std::cout << "  (-1 < 1u) evaluates to "
              << (signedValue < static_cast<int>(unsignedValue))
              << " when cast correctly\n";
    std::cout << "  but -1 as unsigned wraps to " << static_cast<unsigned int>(-1) << "\n";

    // Unsigned wraparound is DEFINED (modulo 2^N).
    unsigned char wrapping = 255;
    wrapping = static_cast<unsigned char>(wrapping + 1);
    show("255u8 + 1 wraps to", static_cast<int>(wrapping));

    // Signed overflow is UNDEFINED BEHAVIOUR — not a wrap, a bug.
    std::cout << "  signed overflow is UB; the optimizer may assume it never happens\n";

    // Fixed-width types: guaranteed size, portable across ABIs.
    std::int8_t   i8  = -128;
    std::uint8_t  u8  = 255;
    std::int16_t  i16 = -32768;
    std::uint32_t u32 = 4294967295u;
    std::int64_t  i64 = -9223372036854775807LL;
    std::size_t   sz  = 42;
    std::ptrdiff_t diff = -5;

    show("int8_t  (printed as int)", static_cast<int>(i8));
    show("uint8_t (printed as int)", static_cast<int>(u8));
    show("int16_t", i16);
    show("uint32_t", u32);
    show("int64_t", i64);
    show("size_t", sz);
    show("ptrdiff_t", diff);
    std::cout << "  int8_t is a typedef for char -> streams print it as a CHARACTER\n";


    // ════════════════════════════════════════════════════════
    // 5. Character types and encodings
    // ════════════════════════════════════════════════════════
    std::cout << "\n──── 5. character types ────\n";

    char narrow = 'A';
    signed char   explicitSigned = -1;
    unsigned char explicitUnsigned = 255;
    wchar_t wide = L'A';
    char16_t utf16 = u'A';
    char32_t utf32 = U'A';
    char8_t  utf8  = u8'A';     // C++20, distinct type

    show("char 'A' as int", static_cast<int>(narrow));
    show("signed char", static_cast<int>(explicitSigned));
    show("unsigned char", static_cast<int>(explicitUnsigned));
    show("wchar_t size", sizeof(wide));
    show("char16_t size", sizeof(utf16));
    show("char32_t size", sizeof(utf32));
    show("char8_t size", sizeof(utf8));

    std::cout << "  plain char is a THIRD type: not signed char, not unsigned char\n";
    std::cout << "  its signedness is implementation-defined (signed on x86 Linux)\n";

    // Escape sequences
    std::cout << "  escapes: tab[\t] newline shown, quote[\"] backslash[\\] bell suppressed\n";
    std::cout << "  hex \\x41 = " << '\x41' << ", octal \\101 = " << '\101' << "\n";

    // Raw string literal — no escaping needed.
    std::string windowsPath = R"(C:\Users\Akshay\notes.txt)";
    std::cout << "  raw literal: " << windowsPath << "\n";

    // UTF-8 literal: bytes, not characters.
    const char* devanagari = "\u0928\u092e\u0938\u094d\u0924\u0947";
    std::cout << "  utf-8 text: " << devanagari
              << "  bytes = " << std::strlen(devanagari) << "\n";
    std::cout << "  strlen counts BYTES, not visible characters\n";


    // ════════════════════════════════════════════════════════
    // 6. std::string basics
    // ════════════════════════════════════════════════════════
    std::cout << "\n──── 6. std::string ────\n";

    std::string empty;
    std::string fromLiteral = "Karan";
    std::string repeated(5, 'x');
    std::string copied = fromLiteral;
    std::string sub = fromLiteral.substr(0, 3);

    show("empty.size()", empty.size());
    show("fromLiteral", fromLiteral);
    show("string(5,'x')", repeated);
    show("substr(0,3)", sub);

    std::string full = fromLiteral + " Redekar";
    full += "!";
    show("concatenated", full);
    show("length()", full.length());
    show("front()", full.front());
    show("back()", full.back());
    show("find(\"Red\")", full.find("Red"));

    // at() is bounds-checked and throws; operator[] is not.
    show("full.at(0)", full.at(0));
    std::cout << "  at() throws std::out_of_range; [] out of range is UB\n";

    // c_str() for C APIs
    std::cout << "  c_str() -> " << std::strlen(full.c_str()) << " bytes\n";

    // string_view: non-owning, no allocation, no copy.
    std::string_view view = full;
    std::string_view prefix = view.substr(0, 5);
    show("string_view prefix", std::string(prefix));
    std::cout << "  string_view does NOT own the data — outliving it is UB\n";

    // Small String Optimization: short strings avoid heap allocation.
    show("sizeof(std::string)", sizeof(std::string));
    std::cout << "  short strings live inside that object (SSO), no malloc\n";


    // ════════════════════════════════════════════════════════
    // 7. References and pointers
    // ════════════════════════════════════════════════════════
    std::cout << "\n──── 7. references & pointers ────\n";

    int original = 10;
    int& alias = original;       // reference: another NAME for original
    int* pointer = &original;    // pointer: an OBJECT holding an address

    alias = 20;
    show("after alias = 20, original", original);

    *pointer = 30;
    show("after *pointer = 30", original);

    show("&original == pointer", (&original == pointer));
    show("&alias == &original", (&alias == &original));

    // References: must be initialized, can never be reseated.
    int other = 99;
    alias = other;               // ASSIGNS 99 into original, does NOT rebind
    show("alias = other; original", original);
    show("other", other);

    // Pointers: can be null, can be reseated, need dereferencing.
    pointer = &other;
    show("reseated pointer target", *pointer);

    int* nothing = nullptr;
    show("nullptr is null", (nothing == nullptr));
    std::cout << "  dereferencing a null pointer is UB — always guard it\n";

    // const placement — read right to left.
    int mutableValue = 1;
    const int* ptrToConst = &mutableValue;          // data const, pointer free
    int* const constPtr = &mutableValue;            // pointer const, data free
    const int* const bothConst = &mutableValue;     // both const

    *constPtr = 2;
    show("int* const -> data writable", mutableValue);
    std::cout << "  const int* p    : cannot write *p, can reseat p\n";
    std::cout << "  int* const p    : can write *p, cannot reseat p\n";
    std::cout << "  const int* const: neither\n";
    std::cout << "  (unused reads: " << *ptrToConst << ", " << *bothConst << ")\n";

    // Parameter passing
    int passed = 1;
    byValue(passed);
    show("after byValue", passed);
    byReference(passed);
    show("after byReference", passed);
    passed = 1;
    byPointer(&passed);
    show("after byPointer", passed);
    byConstRef(passed);

    // const ref binds to a temporary and extends its lifetime.
    const int& boundTemp = 5 + 5;
    show("const int& bound to temp", boundTemp);


    // ════════════════════════════════════════════════════════
    // 8. Constants
    // ════════════════════════════════════════════════════════
    std::cout << "\n──── 8. const / constexpr / constinit / consteval ────\n";

    const int fixedSeats = 60;
    // fixedSeats = 61;             // ERROR: assignment to read-only

    constexpr int compileTimeSeats = 60;
    constexpr int derived = square(8);     // evaluated at COMPILE time

    show("const int", fixedSeats);
    show("constexpr int", compileTimeSeats);
    show("constexpr square(8)", derived);

    // constexpr function called with a RUNTIME value -> runs at runtime.
    int runtimeInput = 7;
    int runtimeResult = square(runtimeInput);
    show("square(runtime 7)", runtimeResult);

    // consteval MUST be compile time.
    constexpr int cube = cubeAtCompileTime(4);
    show("consteval cube(4)", cube);
    std::cout << "  cubeAtCompileTime(runtimeInput) would NOT compile\n";

    // constinit: constant-initialized, still mutable.
    globalCounter += 5;
    show("constinit globalCounter", globalCounter);

    // constexpr array size — const alone is not always enough.
    int fixedArray[compileTimeSeats] = {};
    show("array sized by constexpr", sizeof(fixedArray) / sizeof(fixedArray[0]));

    show("namespace constexpr MAX_STUDENTS", MAX_STUDENTS);
    show("namespace const PASS_MARK", PASS_MARK);

    std::cout << "  const     : cannot modify (may still be runtime-initialized)\n";
    std::cout << "  constexpr : usable in constant expressions, implies const\n";
    std::cout << "  constinit : constant-INITIALIZED but mutable (C++20)\n";
    std::cout << "  consteval : function must run at compile time (C++20)\n";


    // ════════════════════════════════════════════════════════
    // 9. Type inference
    // ════════════════════════════════════════════════════════
    std::cout << "\n──── 9. auto / decltype ────\n";

    auto inferredInt = 42;            // int
    auto inferredDouble = 3.14;       // double
    auto inferredString = std::string("Drishya");
    auto inferredChar = 'D';          // char, NOT std::string

    show("auto 42", inferredInt);
    show("auto 3.14", inferredDouble);
    show("auto string", inferredString);
    show("auto 'D'", inferredChar);

    // auto with a literal "..." gives const char*, not std::string
    auto literalPtr = "Tanvi";
    std::cout << "  is_same<decltype(auto x = \"Tanvi\"), const char*> = "
              << std::is_same_v<decltype(literalPtr), const char*> << "\n";
    std::cout << "  is_same<..., std::string> = "
              << std::is_same_v<decltype(literalPtr), std::string> << "\n";
    std::cout << "  use auto x = \"Tanvi\"s or std::string{...} for a real string\n";

    // auto DROPS const and references.
    const int constSource = 10;
    auto droppedConst = constSource;          // int, not const int
    droppedConst = 11;
    show("auto dropped const, now", droppedConst);

    // Restore them explicitly.
    const auto& keptRef = constSource;
    show("const auto& kept", keptRef);

    // auto& vs auto in loops
    std::vector<int> scores{10, 20, 30};

    for (auto scoreCopy : scores) {
        scoreCopy *= 2;                        // modifies a copy
    }
    std::cout << "  after `for (auto v : scores) v *= 2` -> "
              << scores[0] << "," << scores[1] << "," << scores[2] << "\n";

    for (auto& scoreRef : scores) {
        scoreRef *= 2;                         // modifies the element
    }
    std::cout << "  after `for (auto& v : scores) v *= 2` -> "
              << scores[0] << "," << scores[1] << "," << scores[2] << "\n";

    // decltype: the declared type of an expression, references intact.
    int base = 5;
    int& baseRef = base;
    decltype(base)    plainCopy = 1;           // int
    decltype(baseRef) refCopy = base;          // int&
    decltype((base))  parenRef = base;         // int& — the parens matter

    refCopy = 7;
    show("decltype(baseRef) is int&, base", base);
    parenRef = 9;
    show("decltype((base)) is int&, base", base);
    show("decltype(base) is int", plainCopy);

    // auto vs decltype(auto) on a returning function
    auto copyOut = getCopy(0);
    decltype(auto) refOut = getRef(0);
    refOut = 111;

    show("getCopy returned a copy", copyOut);
    show("getRef wrote through, pool[0]", marksPool[0]);

    std::cout << "  is_same<decltype(getRef(0)), int&> = "
              << std::is_same_v<decltype(getRef(0)), int&> << "\n";


    // ════════════════════════════════════════════════════════
    // 10. Type aliases
    // ════════════════════════════════════════════════════════
    std::cout << "\n──── 10. type aliases ────\n";

    Timestamp created = 1726480000ULL;
    RollNumber roll = 22;
    Pair<int> rangePair{1, 100};
    Callback handler = &onSeatAssigned;

    show("typedef Timestamp", created);
    show("using RollNumber", roll);
    show("alias template Pair<int>", rangePair.first);
    handler(7);

    StudentList batch{
        {"Karan",   21, 8.15, Department::CSE},
        {"Drishya", 22, 9.02, Department::ENTC}
    };
    show("StudentList size", batch.size());

    std::cout << "  typedef reads right-to-left, `using` reads left-to-right\n";
    std::cout << "  only `using` supports alias TEMPLATES\n";
    std::cout << "  aliases create no new type: is_same<RollNumber,int> = "
              << std::is_same_v<RollNumber, int> << "\n";
    std::cout << "  so they give you readability, NOT type safety\n";


    // ════════════════════════════════════════════════════════
    // 11. Storage classes
    // ════════════════════════════════════════════════════════
    std::cout << "\n──── 11. storage classes ────\n";

    {
        int blockScoped = 1;      // automatic storage, dies at }
        show("automatic (block-scoped)", blockScoped);
    }
    // blockScoped is gone here

    std::cout << "  static local persists across calls:\n";
    std::cout << "    nextSeat() -> " << nextSeat() << "\n";
    std::cout << "    nextSeat() -> " << nextSeat() << "\n";
    std::cout << "    nextSeat() -> " << nextSeat() << "\n";
    show("fileLocalSeats (static file)", fileLocalSeats);
    show("countCalls() (own static)", countCalls());

    threadRequestCount += 3;
    show("thread_local counter", threadRequestCount);

    std::cout << "  auto     : the C meaning is dead; auto now means type inference\n";
    std::cout << "  register : deprecated in C++11, removed in C++17\n";
    std::cout << "  mutable  : lets a member change inside a const member function\n";
    std::cout << "  extern   : declares a symbol defined in another TU\n";


    // ════════════════════════════════════════════════════════
    // 12. Enums
    // ════════════════════════════════════════════════════════
    std::cout << "\n──── 12. enums ────\n";

    Grade g = GRADE_B;
    HttpStatus status = NOTFOUND_404;

    show("unscoped GRADE_B", static_cast<int>(g));
    show("unscoped NOTFOUND_404", static_cast<int>(status));
    std::cout << "  unscoped enums convert to int IMPLICITLY: GRADE_B + 1 = "
              << (GRADE_B + 1) << "\n";
    std::cout << "  and their names leak into the enclosing scope\n";

    Department dept = Department::ENTC;
    Level level = Level::Senior;

    std::cout << "  scoped Department::ENTC = " << toText(dept) << "\n";
    show("scoped, explicit cast", static_cast<int>(dept));
    show("Level::Senior", static_cast<int>(level));
    show("sizeof(Department)", sizeof(Department));
    show("sizeof(Level : uint8_t)", sizeof(Level));

    std::cout << "  `int n = Department::CSE;` is a COMPILE ERROR — that is the win\n";
    std::cout << "  two enum classes can both have a member named CSE with no clash\n";

    // Switch over a scoped enum: the compiler warns on missing cases
    // under -Wswitch, which is why toText handles all four.
    std::cout << "  -Wall warns if a switch misses an enumerator\n";


    // ════════════════════════════════════════════════════════
    // 13. struct
    // ════════════════════════════════════════════════════════
    std::cout << "\n──── 13. struct ────\n";

    // Aggregate initialization, in declaration order.
    Student arjun{"Arjun", 23, 7.80, Department::MECH};

    // Designated initializers (C++20) — must follow declaration order.
    Student rohit{.name = "Rohit", .rollNumber = 24, .cgpa = 8.90};

    // Default member initializers fill the rest.
    Student blank{};

    std::cout << "  " << arjun.name << " roll=" << arjun.rollNumber
              << " cgpa=" << arjun.cgpa << " dept=" << toText(arjun.dept) << "\n";
    std::cout << "  " << rohit.name << " roll=" << rohit.rollNumber
              << " cgpa=" << rohit.cgpa << " dept=" << toText(rohit.dept)
              << "  <- dept came from the default member initializer\n";
    std::cout << "  blank name=[" << blank.name << "] roll=" << blank.rollNumber << "\n";

    Rectangle room{12.5, 10.0};
    show("Rectangle.area()", room.area());
    show("Rectangle.perimeter()", room.perimeter());

    // Structured bindings (C++17) decompose an aggregate.
    auto [bindName, bindRoll, bindCgpa, bindDept] = arjun;
    std::cout << "  structured binding -> " << bindName << " / " << bindRoll
              << " / " << bindCgpa << " / " << toText(bindDept) << "\n";

    // Padding and alignment
    show("sizeof(PaddedLayout)", sizeof(PaddedLayout));
    show("alignof(PaddedLayout)", alignof(PaddedLayout));
    show("sizeof(PackedLayout)", sizeof(PackedLayout));
    show("alignof(PackedLayout)", alignof(PackedLayout));
    std::cout << "  same four members, different size — member ORDER controls padding\n";
    std::cout << "  order members largest-to-smallest to shrink the struct\n";

    std::cout << "  struct vs class: ONLY the default access (public vs private)\n";


    // ════════════════════════════════════════════════════════
    // 14. union
    // ════════════════════════════════════════════════════════
    std::cout << "\n──── 14. union ────\n";

    Value v;
    v.asInt = 1094795585;          // 0x41414141

    show("sizeof(Value)", sizeof(Value));
    show("v.asInt", v.asInt);
    std::cout << "  same bytes as chars: ";
    for (int i = 0; i < 4; ++i) {
        std::cout << v.asBytes[i];
    }
    std::cout << "\n";

    std::cout << "  union size = size of its LARGEST member, all members overlap\n";
    std::cout << "  reading a member you did not write is UB in C++ (type punning)\n";
    std::cout << "  the legal tool for punning is std::bit_cast (C++20) or memcpy\n";

    // Tagged union — the safe pattern.
    TaggedValue tagged;
    tagged.kind = ValueKind::Double;
    tagged.d = 9.25;

    std::cout << "  tagged union: kind=Double, d=" << tagged.d << "\n";

    tagged.kind = ValueKind::Int;
    tagged.i = 42;
    std::cout << "  tagged union: kind=Int,    i=" << tagged.i << "\n";

    std::cout << "  in modern C++ prefer std::variant — it tracks the tag for you\n";


    // ════════════════════════════════════════════════════════
    // 15. sizeof / alignof / numeric_limits / is_same_v
    // ════════════════════════════════════════════════════════
    std::cout << "\n──── 15. sizeof / alignof / limits / traits ────\n";

    std::cout << "sizes (bytes):\n";
    show("bool", sizeof(bool));
    show("char", sizeof(char));
    show("wchar_t", sizeof(wchar_t));
    show("int", sizeof(int));
    show("long", sizeof(long));
    show("long long", sizeof(long long));
    show("float", sizeof(float));
    show("double", sizeof(double));
    show("long double", sizeof(long double));
    show("std::string", sizeof(std::string));
    show("void*", sizeof(void*));
    show("Student", sizeof(Student));

    std::cout << "  only sizeof(char) == 1 is guaranteed by the standard\n";
    std::cout << "  sizeof returns std::size_t, and is evaluated at COMPILE time\n";

    std::cout << "alignments:\n";
    show("alignof(char)", alignof(char));
    show("alignof(int)", alignof(int));
    show("alignof(double)", alignof(double));
    show("alignof(Student)", alignof(Student));
    show("alignof(std::max_align_t)", alignof(std::max_align_t));

    std::cout << "numeric_limits:\n";
    show("int min", std::numeric_limits<int>::min());
    show("int max", std::numeric_limits<int>::max());
    show("unsigned int max", std::numeric_limits<unsigned int>::max());
    show("long long max", std::numeric_limits<long long>::max());
    show("double min (smallest +)", std::numeric_limits<double>::min());
    show("double max", std::numeric_limits<double>::max());
    show("double lowest (most -)", std::numeric_limits<double>::lowest());
    show("double epsilon", std::numeric_limits<double>::epsilon());
    show("double digits10", std::numeric_limits<double>::digits10);
    show("int is_signed", std::numeric_limits<int>::is_signed);
    show("char is_signed", std::numeric_limits<char>::is_signed);
    show("double has_infinity", std::numeric_limits<double>::has_infinity);

    std::cout << "  min() for FLOATS is the smallest POSITIVE value, not the most\n";
    std::cout << "  negative — use lowest() for that. Classic bug.\n";
    std::cout << "  CHAR_BIT = " << CHAR_BIT << " (bits per byte, not always 8)\n";

    std::cout << "is_same_v checks (compile-time):\n";
    show("int vs signed int", (std::is_same_v<int, signed int>));
    show("char vs signed char", (std::is_same_v<char, signed char>));
    show("char vs unsigned char", (std::is_same_v<char, unsigned char>));
    show("int32_t vs int", (std::is_same_v<std::int32_t, int>));
    show("size_t vs unsigned long", (std::is_same_v<std::size_t, unsigned long>));
    show("RollNumber vs int", (std::is_same_v<RollNumber, int>));
    show("decltype(1+1) vs int", (std::is_same_v<decltype(1 + 1), int>));
    show("decltype('a') vs char", (std::is_same_v<decltype('a'), char>));
    show("decltype(\"s\") vs const char(&)[2]", (std::is_same_v<decltype("s"), const char(&)[2]>));

    std::cout << "  char is a distinct type from BOTH signed and unsigned char\n";
    std::cout << "  a string literal's type is const char[N], not const char*\n";


    std::cout << "\n──── done ────\n";

    return 0;
}