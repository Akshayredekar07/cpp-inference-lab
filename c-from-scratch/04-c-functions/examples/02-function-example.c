#include <stdio.h>

// Example 1: Factorial (Recursion)
int factorial(int n) {
    if (n == 0) return 1;
    return n * factorial(n-1);
}

// Example 2: Fibonacci (Recursion)
int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n-1) + fibonacci(n-2);
}

// Example 3: GCD (Greatest Common Divisor) - Euclidean Algorithm
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// Example 4: LCM (Least Common Multiple)
int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

// Example 5: Power Function (Exponentiation)
int power(int base, int exp) {
    int result = 1;
    for(int i = 0; i < exp; i++)
        result *= base;
    return result;
}

// Example 6: Check if a number is prime
int isPrime(int n) {
    if (n < 2) return 0;
    for(int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

// Example 7: Calculate sum of digits
int sumOfDigits(int n) {
    if (n == 0) return 0;
    return (n % 10) + sumOfDigits(n / 10);
}

// Example 8: Reverse a number
int reverseNumber(int n) {
    int reversed = 0;
    while (n != 0) {
        reversed = reversed * 10 + n % 10;
        n /= 10;
    }
    return reversed;
}

// Example 9: Check if number is palindrome
int isPalindrome(int n) {
    return n == reverseNumber(n);
}

// Example 10: Print binary representation (recursive)
void printBinary(int n) {
    if (n > 1) printBinary(n/2);
    printf("%d", n%2);
}

int main() {
    int a = 12, b = 18;

    printf("LCM of %d and %d is %d\n", a, b, lcm(a, b));
    printf("Power: %d^%d = %d\n", a, 2, power(a, 2));
    printf("Is %d prime? %s\n", a, isPrime(a) ? "Yes" : "No");
    printf("Sum of digits of %d = %d\n", b, sumOfDigits(b));
    printf("Reverse of %d = %d\n", a, reverseNumber(a));
    printf("Is %d a palindrome? %s\n", 121, isPalindrome(121) ? "Yes" : "No");
    printf("Binary of %d: ", a);
    printBinary(a);
    printf("\n");
    return 0;
}
