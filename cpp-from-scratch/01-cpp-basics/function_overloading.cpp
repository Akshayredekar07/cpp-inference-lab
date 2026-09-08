#include <iostream>
#include <string>
#include <vector>

// ──── basic overloading ────
// Same function name, different parameter list.
// The compiler selects the matching overload.

void print(int x) {
    std::cout << "int: " << x << "\n";
}

void print(double x) {
    std::cout << "double: " << x << "\n";
}

void print(const std::string& x) {
    std::cout << "string: " << x << "\n";
}


// ──── different number of parameters ────
// Overloads can differ by parameter count.

int add(int a, int b) {
    return a + b;
}

int add(int a, int b, int c) {
    return a + b + c;
}


// ──── different parameter types ────

double calculate(double a, double b) {
    return a + b;
}

int calculate(int a, int b) {
    return a * b;
}


// ──── const and non-const reference ────
// These can form different overloads in some contexts.

void process(int& value) {
    std::cout << "non-const reference: " << value << "\n";
}

void process(const int& value) {
    std::cout << "const reference: " << value << "\n";
}


// ──── string literal overload ────
// "hello" is const char[], which normally decays to const char*.

void show(const char* text) {
    std::cout << "C-string: " << text << "\n";
}

void show(const std::string& text) {
    std::cout << "std::string: " << text << "\n";
}


// ──── pointer overload ────

void inspect(int* value) {
    if (value) {
        std::cout << "pointer: " << *value << "\n";
    } else {
        std::cout << "pointer: null\n";
    }
}

void inspect(int value) {
    std::cout << "integer: " << value << "\n";
}


// ──── overload with default parameter ────
// Be careful: default arguments can create ambiguity.

void configure(int width) {
    std::cout << "width=" << width << "\n";
}

void configure(int width, int height = 100) {
    std::cout << "width=" << width
              << ", height=" << height << "\n";
}


// ──── overload resolution ────
// Exact matches are generally preferred over conversions.

void convert(int value) {
    std::cout << "convert(int): " << value << "\n";
}

void convert(double value) {
    std::cout << "convert(double): " << value << "\n";
}


// ──── overloaded functions with different return values ────
// Return type alone CANNOT create an overload.
//
// This would NOT compile:
//
// int result(int x);
// double result(int x);
//
// The parameter list is identical.


// ──── advanced: function templates vs overloads ────
// A template can provide a generic implementation.

template <typename T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}


// ──── advanced: explicit overload + template ────
// A normal overload can coexist with a function template.
// Exact non-template overloads are preferred when applicable.

template <typename T>
void display(T value) {
    std::cout << "template: " << value << "\n";
}

void display(int value) {
    std::cout << "int overload: " << value << "\n";
}


int main() {

    // ──── basic overloading ────
    std::cout << "──── basic overloading ────\n";

    print(7);
    print(3.14);
    print(std::string("Ada"));


    // ──── number of parameters ────
    std::cout << "\n──── parameter count ────\n";

    std::cout << "add(2, 3)="
              << add(2, 3)
              << "\n";

    std::cout << "add(2, 3, 4)="
              << add(2, 3, 4)
              << "\n";


    // ──── parameter types ────
    std::cout << "\n──── parameter types ────\n";

    std::cout << "calculate(5, 3)="
              << calculate(5, 3)
              << "\n";

    std::cout << "calculate(5.0, 3.0)="
              << calculate(5.0, 3.0)
              << "\n";


    // ──── const reference overload ────
    std::cout << "\n──── reference overload ────\n";

    int value = 10;

    process(value);

    const int constant = 20;

    process(constant);


    // ──── string literal vs std::string ────
    std::cout << "\n──── string overload ────\n";

    show("Hello");

    std::string name = "Akshay";

    show(name);


    // ──── pointer overload ────
    std::cout << "\n──── pointer overload ────\n";

    int number = 50;

    inspect(number);
    inspect(&number);
    inspect(nullptr);


    // ──── overload resolution ────
    std::cout << "\n──── overload resolution ────\n";

    convert(10);
    convert(10.5);


    // ──── implicit conversion ────
    std::cout << "\n──── implicit conversion ────\n";

    double decimal = 10.5;

    // Exact double overload is selected.
    convert(decimal);

    // Integer overload is selected.
    convert(10);


    // ──── template overload ────
    std::cout << "\n──── function template ────\n";

    std::cout << "maximum(10, 20)="
              << maximum(10, 20)
              << "\n";

    std::cout << "maximum(3.5, 2.5)="
              << maximum(3.5, 2.5)
              << "\n";


    // ──── template and normal overload ────
    std::cout << "\n──── template + overload ────\n";

    display(10);       // normal int overload
    display(3.14);     // template


    // ──── explicit type selection ────
    std::cout << "\n──── explicit type selection ────\n";

    display<int>(10);
    display<double>(3.14);


    // ──── overload is compile-time ────
    std::cout << "\n──── compile-time selection ────\n";

    int x = 10;
    double y = 20.5;

    print(x);
    print(y);


    // ──── invalid overload idea ────
    std::cout << "\n──── return type rule ────\n";

    std::cout << "Return type alone cannot overload a function.\n";
    std::cout << "Parameter list must be different.\n";


    std::cout << "\n──── done ────\n";

    return 0;
}