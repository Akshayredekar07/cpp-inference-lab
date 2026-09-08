#include <iostream>
#include <string>

// ──── basic function 
// A function is a reusable block of code.
// It can receive inputs (parameters) and return a value.

void greet() {
    std::cout << "Hello, C++\n";
}

// ──── function with parameters 
void greetUser(const std::string& name) {
    std::cout << "Hello, " << name << "\n";
}

// ──── function with return value 
int add(int a, int b) {
    return a + b;
}

// ──── function declaration 
// Declaration tells the compiler that the function exists.
// Definition can appear later.

double multiply(double a, double b);

// ──── default parameters 
void printMessage(const std::string& message, int times = 1) {
    for (int i = 0; i < times; ++i) {
        std::cout << message << "\n";
    }
}

// ──── pass by value 
// A copy of the argument is passed to the function.

void changeValue(int x) {
    x = 100;
}

// ──── pass by reference 
// The function works with the original variable.

void changeValueByReference(int& x) {
    x = 100;
}

// ──── const reference 
// Avoids copying while preventing modification.

void printName(const std::string& name) {
    std::cout << "Name: " << name << "\n";
}

// ──── function overloading 
// Same function name, different parameter lists.

int square(int x) {
    return x * x;
}

double square(double x) {
    return x * x;
}

// ──── recursion 
// A function can call itself.

int factorial(int n) {
    if (n <= 1) {
        return 1;
    }

    return n * factorial(n - 1);
}

// ──── inline function 
inline int cube(int x) {
    return x * x * x;
}


// ──── function definition 
double multiply(double a, double b) {
    return a * b;
}


int main() {

    // ──── calling a function 
    std::cout << "──── basic function ────\n";

    greet();


    // ──── function parameters 
    std::cout << "\n──── parameters ────\n";

    greetUser("Arjun");
    greetUser("Akshay");


    // ──── return value 
    std::cout << "\n──── return value ────\n";

    int result = add(10, 20);

    std::cout << "10 + 20 = " << result << "\n";


    // ──── function declaration 
    std::cout << "\n──── declaration ────\n";

    std::cout << "5.5 * 2 = " << multiply(5.5, 2) << "\n";


    // ──── default parameters 
    std::cout << "\n──── default parameters ────\n";

    printMessage("Hello");
    printMessage("C++", 3);


    // ──── pass by value 
    std::cout << "\n──── pass by value ────\n";

    int value1 = 10;

    changeValue(value1);

    // Original value is unchanged.
    std::cout << "value1=" << value1 << "\n";


    // ──── pass by reference ──────────────────────────────────
    std::cout << "\n──── pass by reference ────\n";

    int value2 = 10;

    changeValueByReference(value2);

    // Original value is changed.
    std::cout << "value2=" << value2 << "\n";


    // ──── const reference ────────────────────────────────────
    std::cout << "\n──── const reference ────\n";

    std::string name = "Akshay";

    printName(name);


    // ──── function overloading ───────────────────────────────
    std::cout << "\n──── function overloading ────\n";

    std::cout << "square(5) = " << square(5) << "\n";
    std::cout << "square(2.5) = " << square(2.5) << "\n";


    // ──── recursion ──────────────────────────────────────────
    std::cout << "\n──── recursion ────\n";

    std::cout << "factorial(5) = " << factorial(5) << "\n";


    // ──── inline function ────────────────────────────────────
    std::cout << "\n──── inline function ────\n";

    std::cout << "cube(3) = " << cube(3) << "\n";


    // ──── function composition ───────────────────────────────
    std::cout << "\n──── function composition ────\n";

    int x = add(5, 5);
    int y = square(x);

    std::cout << "square(add(5, 5)) = " << y << "\n";


    std::cout << "\n──── done ────\n";

    return 0;
}
