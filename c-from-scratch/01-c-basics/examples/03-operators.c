#include <stdio.h>

int main() {
    int a = 10, b = 3;          // a → 10,   b → 3

    // 1. Arithmetic Operators
    printf("Arithmetic:\n");
    // Output:
    // Arithmetic:
    printf("a + b = %d\n", a + b);          // a + b = 13
    printf("a - b = %d\n", a - b);          // a - b = 7
    printf("a * b = %d\n", a * b);          // a * b = 30
    printf("a / b = %d\n", a / b);          // a / b = 3      (integer division, 10/3 = 3, truncates toward zero)
    printf("a %% b = %d\n", a % b);         // a % b = 1      (remainder of 10 ÷ 3)

    // 2. Unary Operators
    int x = 5;                              // x → 5
    printf("\nUnary:\n");
    // Output:
    // Unary:
    printf("x = %d\n", x);                  // x = 5
    printf("++x = %d\n", ++x);              // ++x = 6    (pre-increment: x becomes 6, then returns 6) → x now 6
    printf("x++ = %d (after = %d)\n", x++, x);
                                            // x++ = 6 (post-increment: returns current 6, THEN x becomes 7)
                                            // (after = 7) → x now 7
    printf("--x = %d\n", --x);              // --x = 6    (pre-decrement: x becomes 6, returns 6) → x now 6
    printf("x-- = %d (after = %d)\n", x--, x);
                                            // x-- = 6 (post-decrement: returns current 6, THEN x becomes 5)
                                            // (after = 5) → x now 5
    printf("-x = %d\n", -x);                // -x = -5    (unary minus, x remains 5)
    printf("+x = %d\n", +x);                // +x = 5     (unary plus, x remains 5)

    // 3. Relational Operators
    printf("\nRelational:\n");
    // Output:
    // Relational:
    printf("a == b = %d\n", a == b);        // a == b = 0    (false)
    printf("a != b = %d\n", a != b);        // a != b = 1    (true)
    printf("a > b = %d\n", a > b);          // a > b = 1     (true)
    printf("a < b = %d\n", a < b);          // a < b = 0     (false)
    printf("a >= b = %d\n", a >= b);        // a >= b = 1    (true)
    printf("a <= b = %d\n", a <= b);        // a <= b = 0    (false)

    // 4. Logical Operators
    printf("\nLogical:\n");
    // Output:
    // Logical:
    printf("(a > b) && (b > 0) = %d\n", (a > b) && (b > 0));
                                            // (10>3) && (3>0) → 1 && 1 = 1
    printf("(a > b) || (b < 0) = %d\n", (a > b) || (b < 0));
                                            // (10>3) || (3<0) → 1 || 0 = 1
    printf("!(a > b) = %d\n", !(a > b));    // !(10>3) → !1 = 0

    // 5. Bitwise Operators (a=10 → 1010b, b=3 → 0011b)
    printf("\nBitwise:\n");
    // Output:
    // Bitwise:
    printf("a & b = %d\n", a & b);          // 1010 & 0011 = 0010 → 2
    printf("a | b = %d\n", a | b);          // 1010 | 0011 = 1011 → 11
    printf("a ^ b = %d\n", a ^ b);          // 1010 ^ 0011 = 1001 → 9
    printf("~a = %d\n", ~a);                // ~00001010 (32-bit) = 11110101 → -11 (two's complement)
    printf("a << 1 = %d\n", a << 1);        // 1010 << 1 = 10100 → 20
    printf("a >> 1 = %d\n", a >> 1);        // 1010 >> 1 = 0101 → 5

    // 6. Assignment Operators
    printf("\nAssignment:\n");
    int y = 10;                             // y → 10
    printf("y = %d\n", y);                  // y = 10
    y += 5; printf("y += 5 → %d\n", y);     // y = 15
    y -= 3; printf("y -= 3 → %d\n", y);     // y = 12
    y *= 2; printf("y *= 2 → %d\n", y);     // y = 24
    y /= 4; printf("y /= 4 → %d\n", y);     // y = 6   (24/4=6)
    y %= 3; printf("y %%= 3 → %d\n", y);    // y = 0   (6 % 3 = 0)
    y &= 1; printf("y &= 1 → %d\n", y);     // y = 0   (0 & 1 = 0)
    y |= 2; printf("y |= 2 → %d\n", y);     // y = 2   (0 | 2 = 2)
    y ^= 3; printf("y ^= 3 → %d\n", y);     // y = 1   (2 ^ 3 = 1)

    // 7. Conditional (Ternary) Operator
    printf("\nTernary:\n");
    int max = (a > b) ? a : b;              // (10 > 3) is true → max = 10
    printf("max = %d\n", max);              // max = 10

    // 8. Comma Operator
    printf("\nComma Operator:\n");
    int z;
    z = (a = 5, b = 8, a + b);              // comma evaluates left-to-right, result is the last one
                                            // a becomes 5, b becomes 8, then a+b=13 → z=13
    printf("z = (a=5, b=8, a+b) = %d\n", z);// z = 13
                                            // Note: a is now 5, b is now 8 permanently

    return 0;
}