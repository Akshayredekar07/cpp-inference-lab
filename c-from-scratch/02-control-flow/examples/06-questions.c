#include <stdio.h>
#include <math.h>

// ============================================================
// 1. Factorial of a Number
int factorial(int n) {
    int fact = 1;
    for(int i = 1; i <= n; i++) {
        fact = fact * i;
    }
    return fact;
}

int main() {
    printf("1. Factorial of 5:\n");
    int num = 5;
    printf("Factorial of %d = %d\n", num, factorial(num));

    /* DRY RUN (n=5):
       i=1 → fact = 1 × 1 = 1
       i=2 → fact = 1 × 2 = 2
       i=3 → fact = 2 × 3 = 6
       i=4 → fact = 6 × 4 = 24
       i=5 → fact = 24 × 5 = 120
       Output: 120
    */
    printf("\n");

    // ============================================================
    // 2. Fibonacci Sequence (First n terms)
    printf("2. Fibonacci Sequence (first 8 terms):\n");
    int n = 8, t1 = 0, t2 = 1, next;
    printf("%d %d ", t1, t2);

    for(int i = 3; i <= n; i++) {
        next = t1 + t2;
        printf("%d ", next);
        t1 = t2;
        t2 = next;
    }

    /* DRY RUN:
       Start: 0 1
       i=3 → next=0+1=1 → print 1 → t1=1, t2=1
       i=4 → next=1+1=2 → print 2 → t1=1, t2=2
       i=5 → next=1+2=3 → print 3 → t1=2, t2=3
       i=6 → next=2+3=5 → print 5 → t1=3, t2=5
       i=7 → next=3+5=8 → print 8 → t1=5, t2=8
       i=8 → next=5+8=13 → print 13
       Output: 0 1 1 2 3 5 8 13
    */
    printf("\n\n");

    // ============================================================
    // 3. Check if a Number is Prime
    printf("3. Check Prime (Number = 17):\n");
    int num2 = 17, flag = 0;

    for(int i = 2; i <= num2/2; i++) {
        if(num2 % i == 0) {
            flag = 1;
            break;
        }
    }
    if(flag == 0 && num2 > 1)
        printf("%d is Prime\n", num2);
    else
        printf("%d is Not Prime\n", num2);

    /* DRY RUN (num=17):
       i=2 → 17%2=1 ≠0 → continue
       i=3 → 17%3=2 ≠0 → continue
       i=4 → 17%4=1 ≠0 → continue
       i=5 → 17%5=2 ≠0 → continue
       i=6 → 17%6=5 ≠0 → continue
       i=7 → 17%7=3 ≠0 → continue
       i=8 → 17%8=1 ≠0 → continue
       Loop ends → flag still 0 → Prime!
    */
    printf("\n");

    // ============================================================
    // 4. Reverse a Number
    printf("4. Reverse a Number (12345):\n");
    int number = 12345, reversed = 0, rem;

    int temp = number;
    while(temp != 0) {
        rem = temp % 10;
        reversed = reversed * 10 + rem;
        temp = temp / 10;
    }
    printf("Reversed = %d\n", reversed);

    /* DRY RUN (number=12345):
       Step1: temp=12345 → rem=5 → rev=0×10+5=5 → temp=1234
       Step2: temp=1234  → rem=4 → rev=5×10+4=54 → temp=123
       Step3: temp=123   → rem=3 → rev=54×10+3=543 → temp=12
       Step4: temp=12    → rem=2 → rev=543×10+2=5432 → temp=1
       Step5: temp=1     → rem=1 → rev=5432×10+1=54321 → temp=0
       Loop ends → Reversed = 54321
    */
    printf("\n");

    // ============================================================
    // 5. Sum of Digits
    printf("5. Sum of Digits (6859):\n");
    int num3 = 6859, sum = 0;

    while(num3 > 0) {
        sum = sum + (num3 % 10);
        num3 = num3 / 10;
    }
    printf("Sum of digits = %d\n", sum);

    /* DRY RUN:
       num=6859 → digit=9 → sum=0+9=9 → num=685
       num=685  → digit=5 → sum=9+5=14 → num=68
       num=68   → digit=8 → sum=14+8=22 → num=6
       num=6    → digit=6 → sum=22+6=28 → num=0
       Loop ends → Sum = 28
    */
    printf("\n");

    // ============================================================
    // 6. Check Armstrong Number (153 = 1³ + 5³ + 3³)
    printf("6. Check Armstrong Number (153):\n");
    int num4 = 153, original = num4, digits = 0, temp2 = num4;

    // Count digits
    while(temp2 > 0) {
        digits++;
        temp2 /= 10;
    }

    int result = 0;
    temp2 = num4;
    while(temp2 > 0) {
        int digit = temp2 % 10;
        result += pow(digit, digits);
        temp2 /= 10;
    }

    if(result == original)
        printf("%d is Armstrong Number\n", original);
    else
        printf("%d is Not Armstrong\n", original);

    /* DRY RUN (153):
       Step1: Count digits → 153→15→1 → digits=3
       Step2: Calculate sum of cubes
         digit=3 → result=0 + 3³=27
         digit=5 → result=27 + 5³=27+125=152
         digit=1 → result=152 + 1³=152+1=153
       result(153) == original(153) → Yes, Armstrong!
       Other examples: 370, 371, 407, 1634
    */

    return 0;
}