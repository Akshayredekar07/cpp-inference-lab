#include <iostream>

// ──── statements ─────────────────────────────────────────────
// A statement performs an action and usually ends with ;
// Examples:
//     int x = 10;        declaration statement
//     x = x + 1;         expression statement
//     return 0;          return statement

// ──── expressions ────────────────────────────────────────────
// An expression produces a value.
// Examples:
//     10
//     x
//     x + 1
//     square(5)
//     x * y

// ──── blocks ─────────────────────────────────────────────────
// A block is a sequence of statements inside { }.
// Blocks introduce scope.

int main() {

    // ──── statements ─────────────────────────────────────────
    std::cout << "──── statements ────\n";

    int x = 10;            // declaration statement
    x = x + 1;             // expression statement
    std::cout << x << "\n";

    // ──── expressions ────────────────────────────────────────
    std::cout << "\n──── expressions ────\n";

    int a = 5;
    int b = 3;

    std::cout << a << "\n";          // variable expression
    std::cout << (a + b) << "\n";     // operator expression
    std::cout << 100 << "\n";         // literal expression

    // ──── blocks ─────────────────────────────────────────────
    std::cout << "\n──── blocks ────\n";

    {
        // nested block — own scope
        int y = 20;

        std::cout << "x=" << x << "\n";
        std::cout << "y=" << y << "\n";
    }

    // y is not visible here because it belongs
    // to the nested block.
    //
    // std::cout << y;
    // error: 'y' was not declared in this scope

    // ──── block scope ────────────────────────────────────────
    std::cout << "\n──── block scope ────\n";

    int value = 100;

    {
        int value = 200;       // different variable
        std::cout << value << "\n";
    }

    std::cout << value << "\n";

    // ──── combined example ───────────────────────────────────
    std::cout << "\n──── combined ────\n";

    int number = 10;           // declaration statement
    number = number * 2;       // expression statement

    {
        int result = number + 5;   // declaration statement
        std::cout << result << "\n";
    }

    // result no longer exists here.

    std::cout << "\n──── done ────\n";
    return 0;
}
