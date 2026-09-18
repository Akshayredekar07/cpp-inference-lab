#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>

// ════════════════════════════════════════════════════════════
// Functions in C++ — complete demo
//
// Covers, in order:
//   1.  Function anatomy, declaration vs definition
//   2.  void functions, calling a function
//   3.  Pass by value
//   4.  Pass by reference / const reference
//   5.  Pass by pointer
//   6.  Default arguments
//   7.  Function overloading
//   8.  Recursion (factorial, power)
//   9.  inline and constexpr functions
//  10.  static local variables (persistent state)
//  11.  Function pointers and std::function
//  12.  Lambdas (capture, parameters, return type)
//  13.  Scope and lifetime
//
// Each numbered banner prints before the corresponding demo in main().
// ════════════════════════════════════════════════════════════


// ──── 1. function anatomy: return type, name, parameters ────
int add(int a, int b) {
    return a + b;            // sends a value back to the caller
}


// ──── 1b. function declaration (prototype) ────
// Declared here, defined below — main() can call multiply even
// though its body appears after main().
double multiply(double a, double b);


// ──── 2. void function — no return value ────
void greet(const std::string& name) {
    std::cout << "Hello, " << name << "!\n";
    // no return statement needed
}


// ──── 3. pass by value ────
// The function receives a COPY. The caller's variable is untouched.
void tryToChangeByValue(int x) {
    x = 100;                 // only the local copy is modified
    std::cout << "  inside function: x=" << x << " (local copy)\n";
}


// ──── 4. pass by reference ────
// The function receives an alias to the caller's variable.
// Changes inside are visible outside.
void changeByReference(int& x) {
    x = 100;
}


// ──── 4b. pass by const reference ────
// No copy, but the caller is guaranteed the value won't change.
void printLength(const std::string& s) {
    std::cout << "length=" << s.size() << "\n";
}


// ──── 5. pass by pointer ────
// The function receives the ADDRESS of the caller's variable.
void changeByPointer(int* p) {
    if (p) {                 // always check before dereferencing
        *p = 100;
    }
}


// ──── 5b. pointer overload: handle null safely ────
void changeByPointerSafe(int* p, int newValue) {
    if (p == nullptr) {
        return;              // do nothing if the pointer is null
    }
    *p = newValue;
}


// ──── 6. default arguments ────
// Defaults are filled from the right. Once a parameter has a
// default, every parameter to its right must also have one.
void greetWithStyle(const std::string& name,
                    const std::string& greeting = "Hello",
                    char punct = '!') {
    std::cout << greeting << ", " << name << punct << "\n";
}


// ──── 7. function overloading ────
// Same name, different parameter list. Compiler picks the right one.
int    area(int side)                        { return side * side; }
int    area(int w, int h)                    { return w * h; }
double area(double radius)                   { return 3.14159 * radius * radius; }


// ──── 8. recursion ────
// Two rules: a base case, and each call moves toward it.
int factorial(int n) {
    if (n <= 1) return 1;                     // base case
    return n * factorial(n - 1);              // recursive call
}


// ──── 8b. recursion: power ────
int power(int base, int exp) {
    if (exp == 0) return 1;                   // base case
    return base * power(base, exp - 1);
}


// ──── 9. inline — a hint, mostly used for ODR relaxation ────
inline int square(int x) {
    return x * x;
}


// ──── 9b. constexpr — may be evaluated at compile time ────
constexpr int cube(int x) {
    return x * x * x;
}


// ──── 10. static local — keeps state between calls ────
int nextId() {
    static int counter = 0;                   // initialized ONCE
    return ++counter;
}


// ──── 11. function pointer ────
// A variable that holds the address of a function.
int apply(int (*op)(int, int), int x, int y) {
    return op(x, y);                          // call through the pointer
}


// ──── 11b. std::function — the modern, type-erased wrapper ────
// Can hold any callable: function, lambda, functor, bound member.
int applyModern(const std::function<int(int, int)>& op, int x, int y) {
    return op(x, y);
}


// ──── 12. lambdas ────
// Syntax:  [captures](params) -> returnType { body }
//
//   [ ]         capture nothing
//   [x]         capture x by value (copy)
//   [&x]        capture x by reference
//   [=]         capture everything used, by value
//   [&]         capture everything used, by reference
//   [this]      capture the enclosing class's this pointer

void lambdaDemo() {
    std::vector<int> nums{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int threshold = 4;

    auto isAbove = [threshold](int n) {       // capture threshold by value
        return n > threshold;
    };

    int count = std::count_if(nums.begin(), nums.end(), isAbove);
    std::cout << "count above " << threshold << " = " << count << "\n";

    // Sum using a lambda with mutable state captured by reference.
    int running = 0;
    auto accumulate = [&running](int n) {
        running += n;
    };

    std::for_each(nums.begin(), nums.end(), accumulate);
    std::cout << "sum = " << running << "\n";

    // Generic lambda (C++14+): auto parameter works for any type.
    auto twice = [](auto x) { return x + x; };
    std::cout << "twice(5) = "   << twice(5)   << "\n";
    std::cout << "twice(2.5) = " << twice(2.5) << "\n";
}


// ──── 13. scope and lifetime ────
int globalCounter = 0;                        // global — lifetime = whole program

void scopeDemo() {
    int local = 10;                           // local — dies at end of function
    {
        int inner = 20;                       // block-local — dies at }
        std::cout << "inside block: local=" << local
                  << ", inner=" << inner << "\n";
    }
    // std::cout << inner;                    // ERROR: inner is out of scope
    std::cout << "after block: local=" << local << "\n";

    ++globalCounter;                          // can read/write globals
}


// ──── helper used to show global vs local ────
void bumpGlobal() {
    ++globalCounter;
}


int main() {

    // ──── 1. anatomy + declaration + definition ────
    std::cout << "════ 1. function anatomy ════\n";

    int sum = add(3, 4);
    std::cout << "add(3, 4) = " << sum << "\n";

    // multiply was only DECLARED above; this call works because
    // the compiler saw the prototype.
    std::cout << "multiply(5.5, 2) = " << multiply(5.5, 2) << "\n";


    // ──── 2. void function ────
    std::cout << "\n════ 2. void function ════\n";

    greet("Karan");
    greet("Tanvi");


    // ──── 3. pass by value ────
    std::cout << "\n════ 3. pass by value ════\n";

    int a = 10;
    tryToChangeByValue(a);
    std::cout << "after tryToChangeByValue: a=" << a
              << " (unchanged)\n";


    // ──── 4. pass by reference ────
    std::cout << "\n════ 4. pass by reference ════\n";

    int b = 10;
    changeByReference(b);
    std::cout << "after changeByReference: b=" << b
              << " (changed)\n";


    // ──── 4b. const reference ────
    std::cout << "\n════ 4b. const reference ════\n";

    std::string name = "Akshay";
    printLength(name);                        // no copy, read-only access


    // ──── 5. pass by pointer ────
    std::cout << "\n════ 5. pass by pointer ════\n";

    int c = 10;
    changeByPointer(&c);
    std::cout << "after changeByPointer: c=" << c
              << " (changed)\n";

    int* nothing = nullptr;
    changeByPointerSafe(nothing, 999);        // safe — does nothing
    std::cout << "nullptr stayed safe\n";


    // ──── 6. default arguments ────
    std::cout << "\n════ 6. default arguments ════\n";

    greetWithStyle("Karan");                  // "Hello, Karan!"
    greetWithStyle("Tanvi", "Hi");            // "Hi, Tanvi!"
    greetWithStyle("Rohit", "Hey", '.');      // "Hey, Rohit."


    // ──── 7. overloading ────
    std::cout << "\n════ 7. overloading ════\n";

    std::cout << "area(5)        = " << area(5)        << "\n";
    std::cout << "area(4, 6)     = " << area(4, 6)     << "\n";
    std::cout << "area(2.0)      = " << area(2.0)      << "\n";


    // ──── 8. recursion ────
    std::cout << "\n════ 8. recursion ════\n";

    std::cout << "factorial(5)   = " << factorial(5)   << "\n";
    std::cout << "factorial(0)   = " << factorial(0)   << "\n";
    std::cout << "power(2, 10)   = " << power(2, 10)   << "\n";


    // ──── 9. inline and constexpr ────
    std::cout << "\n════ 9. inline and constexpr ════\n";

    std::cout << "square(7)      = " << square(7)      << "\n";

    constexpr int c9 = cube(3);               // computed at compile time
    int arr9[c9] = {};                        // OK — c9 is a constant expression
    (void)arr9;                               // silence unused warning
    std::cout << "cube(3)        = " << c9
              << ", array of size " << c9 << "\n";


    // ──── 10. static local ────
    std::cout << "\n════ 10. static local ════\n";

    std::cout << "nextId() = " << nextId() << "\n";
    std::cout << "nextId() = " << nextId() << "\n";
    std::cout << "nextId() = " << nextId() << "\n";
    // counter survives across calls — initialized only once.


    // ──── 11. function pointer ────
    std::cout << "\n════ 11. function pointer ════\n";

    int (*op)(int, int) = &add;
    std::cout << "apply(add, 3, 4) = " << apply(op, 3, 4) << "\n";

    // square takes one int, so it does not match the binary
    // function-pointer signature. Stick with add for the demo:
    int (*binOp)(int, int) = &add;
    std::cout << "binOp(10, 20)    = " << binOp(10, 20) << "\n";

    // ──── 11b. std::function ────
    std::cout << "\n════ 11b. std::function ════\n";

    std::function<int(int, int)> binFunc = [](int a, int b) {
        return a * b;
    };
    std::cout << "applyModern(lambda, 5, 6) = "
              << applyModern(binFunc, 5, 6) << "\n";

    binFunc = add;                             // also holds plain functions
    std::cout << "applyModern(add, 5, 6)    = "
              << applyModern(binFunc, 5, 6) << "\n";


    // ──── 12. lambdas ────
    std::cout << "\n════ 12. lambdas ════\n";

    lambdaDemo();


    // ──── 13. scope and lifetime ────
    std::cout << "\n════ 13. scope and lifetime ════\n";

    bumpGlobal();
    bumpGlobal();
    scopeDemo();
    std::cout << "globalCounter = " << globalCounter << "\n";


    std::cout << "\n════ done ════\n";

    return 0;
}


// ════════════════════════════════════════════════════════════
// Definition of multiply — placed AFTER main() on purpose.
// The forward declaration at the top is what makes this legal.
// ════════════════════════════════════════════════════════════
double multiply(double a, double b) {
    return a * b;
}