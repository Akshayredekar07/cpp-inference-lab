#include <stdio.h>

// int main(){

//     int a = 5;
//     printf("Value of a is %d", a);
//     return 0;
// }

// int main() {
//     int a, b, sum;
    
//     printf("Enter two numbers: ");
//     scanf("%d %d", &a, &b);

//     sum = a + b;

//     printf("Sum = %d", sum);
//     return 0;
// }


int main(){
    int a, b, temp;
    printf("Enter two numbers: ");
    /* scanf expects pointers to variables */
    scanf("%d %d", &a, &b);

    // temp = a;
    // a = b;
    // b = temp;

    a = a + b;
    b = a - b;
    a = a - b;


    /* printf expects values, not addresses */
    printf("After swap: a = %d, b = %d\n", a, b);
    return 0;
}


