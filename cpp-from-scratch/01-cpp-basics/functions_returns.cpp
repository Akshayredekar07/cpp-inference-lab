#include <iostream>
#include <string>

// ──── no parameters, no return ────
// void means the function does not return a value.

void greet() {
    std::cout << "Hello from greet()\n";
}


// ──── one parameter ────
// name is a local variable initialized from the caller's argument.

void greetUser(const std::string& name) {
    std::cout << "Hello, " << name << "\n";
}


// ──── one parameter, return value ────

int square(int x) {
    return x * x;
}


// ──── multiple parameters ────

int add(int a, int b) {
    return a + b;
}


// ──── different parameter types ────

double calculatePrice(double price, int quantity) {
    return price * quantity;
}


// ──── bool return value ────

bool isEven(int number) {
    return number % 2 == 0;
}


// ──── early return ────
// return can terminate a function before reaching the end.

void logMessage(const char* message) {
    if (!message) {
        return;
    }

    std::cerr << "log: " << message << "\n";
}


// ──── multiple return paths ────

int maxValue(int a, int b) {
    if (a > b) {
        return a;
    }

    return b;
}


// ──── pass by value ────
// The parameter receives a copy of the argument.

void changeValue(int x) {
    x = 100;
}


// ──── pass by reference ────
// The parameter refers to the caller's original variable.

void changeValue(int& x) {
    x = 100;
}


// ──── const reference ────
// Reads the caller's object without copying or modifying it.

void printName(const std::string& name) {
    std::cout << "Name: " << name << "\n";
}


// ──── default parameter ────

int power(int base, int exponent = 2) {
    int result = 1;

    for (int i = 0; i < exponent; ++i) {
        result *= base;
    }

    return result;
}


// ──── return different calculations ────

int calculateTotal(int price, int quantity, int discount) {
    int subtotal = price * quantity;
    return subtotal - discount;
}


int main() {

    // ──── no parameters, no return ────

    std::cout << "──── void function ────\n";

    greet();


    // ──── one parameter ────

    std::cout << "\n──── one parameter ────\n";

    greetUser("Akshay");


    // ──── one parameter, return value ────

    std::cout << "\n──── return value ────\n";

    int result = square(5);

    std::cout << "square(5)=" << result << "\n";


    // ──── multiple parameters ────

    std::cout << "\n──── multiple parameters ────\n";

    int sum = add(10, 20);

    std::cout << "add(10, 20)=" << sum << "\n";


    // ──── different parameter types ────

    std::cout << "\n──── different parameter types ────\n";

    double totalPrice = calculatePrice(99.50, 3);

    std::cout << "99.50 x 3=" << totalPrice << "\n";


    // ──── bool return ────

    std::cout << "\n──── bool return ────\n";

    std::cout << "isEven(10)=" << isEven(10) << "\n";
    std::cout << "isEven(7)=" << isEven(7) << "\n";


    // ──── early return ────

    std::cout << "\n──── early return ────\n";

    logMessage("server started");
    logMessage(nullptr);


    // ──── multiple return paths ────

    std::cout << "\n──── multiple return paths ────\n";

    std::cout << "maxValue(10, 20)="
              << maxValue(10, 20)
              << "\n";

    std::cout << "maxValue(50, 30)="
              << maxValue(50, 30)
              << "\n";


    // ──── pass by value ────

    std::cout << "\n──── pass by value ────\n";

    int value1 = 10;

    changeValue(value1);

    // value1 is unchanged because the function received a copy.
    std::cout << "value1=" << value1 << "\n";


    // ──── pass by reference ────

    std::cout << "\n──── pass by reference ────\n";

    int value2 = 10;

    changeValue(value2);

    // value2 is changed because the function received a reference.
    std::cout << "value2=" << value2 << "\n";


    // ──── const reference ────

    std::cout << "\n──── const reference ────\n";

    std::string name = "Akshay";

    printName(name);


    // ──── default parameter ────

    std::cout << "\n──── default parameter ────\n";

    std::cout << "power(5)="
              << power(5)
              << "\n";

    std::cout << "power(5, 3)="
              << power(5, 3)
              << "\n";


    // ──── returned value used in expression ────

    std::cout << "\n──── return value in expression ────\n";

    int answer = add(square(3), square(4));

    std::cout << "square(3) + square(4)="
              << answer
              << "\n";


    // ──── returned value stored ────

    std::cout << "\n──── returned value stored ────\n";

    int price = 500;
    int quantity = 3;
    int discount = 100;

    int finalPrice =
        calculateTotal(price, quantity, discount);

    std::cout << "finalPrice=" << finalPrice << "\n";


    // ──── main return ────

    std::cout << "\n──── main return ────\n";

    return 0;
}