
// #include <stdio.h>


// int main(){

//     int age = 18;
//     if (age >= 18){
//         printf("You are eligible to vote");
//     }
//     return 0;
// }


// #include <stdio.h>

// int main(){


//     int number = 10;
//     if (number % 2 == 0){
//         printf("%d is even\n", number);
//     }else{
//         printf("%d is odd\n", number);
//     }

//     return 0;
// }

// #include <stdio.h>

// int main(){


//     int marks = 85;

//     if(marks >= 90){
//         printf("Grade: A+\n");
//     }else if(marks >= 80){
//         printf("Grade: A\n");
//     }else if (marks >= 70){
//         printf("Grade: B\n");
//     }else if (marks >= 60){
//         printf("Grade: C\n");
//     }else{
//         printf("Grade: F\n");
//     }
    
    
//     return 0;
// }


// #include <stdio.h>

// int main(){
    
//     int age = 25;
//     int hasLicense = 1;

//     if(age >= 18){
//         if(hasLicense){
//             printf("You can drive\n");
//         }else{
//             printf("You need to license to drive\n");
//         }
//     }else{
//         printf("You are too young to drive\n");
//     }

//     return 0;
// }



// #include <stdio.h>

// int main(){
    
//     int a = 10, b = 20;
//     int max = (a > b)? a: b;
//     printf("Maximum: %d\n", max);  // Output: 20

//     return 0;
// }



// #include <stdio.h>

// int main(){
    
//     int month = 4;

//     switch(month){
//         case 12:
//         case 1:
//         case 2:
//             printf("Winter\n");
//             break;
//         case 3:
//         case 4:
//         case 5:
//             printf("Spring\n");
//             break;
//         case 6:
//         case 7:
//         case 8:
//             printf("Summer\n");
//             break;
//         case 9:
//         case 10:
//         case 11:
//             printf("Autumn\n");
//             break;
//         default:
//             printf("Invalid month\n");

//     }

//     return 0;
// }


// #include <stdio.h>

// int main(){
    
//     int month = 4;

//     switch(month){
//         case 12:
//         case 1:
//         case 2:
//             printf("Winter\n");
//             break;
//         case 3:
//         case 4:
//         case 5:
//             printf("Spring\n");
//             break;
//         case 6:
//         case 7:
//         case 8:
//             printf("Summer\n");
//             break;
//         case 9:
//         case 10:
//         case 11:
//             printf("Autumn\n");
//             break;
//         default:
//             printf("Invalid month\n");

//     }

//     return 0;
// }


// #include <stdio.h>

// int main(){
    
//     for(int i=1; i<=10; i++){
//         printf("%d ", i);
//     }
//     printf("\n");

//     return 0;
// }


// #include <stdio.h>

// int main(){
    
//     for (int i=0, j=10; i<j; i++, j--){
//         printf("i = %d, j = %d\n", i, j);
//     }

//     return 0;
// }

// #include <stdio.h>

// int main(){

//     int i = 1;
//     while (i <= 5){
//         printf("%d", i);
//         i++;
//     }
//     return 0;
// }


// #include <stdio.h>

// int main(){

//     // Print a square pattern
//     for (int i = 1; i <= 5; i++) {
//         for (int j = 1; j <= 5; j++) {
//             printf("* ");
//         }
//         printf("\n");
//     }

//     for (int i = 1; i <= 10; i++) {
//         for (int j = 1; j <= 10; j++) {
//             printf("%4d", i * j);
//         }
//         printf("\n");
//     }

//     // Pyramid pattern: For row i, spaces = rows - i, stars = 2*i - 1
//     int rows = 5;

//     /*
//     Dry run summary:
//     rows = 5

//     i = 1:
//       spaces = 5 - 1 = 4  -> "    "
//       stars  = 2*1 - 1 = 1 -> "*"
//       line: "    *"
//     i = 2:
//       spaces = 3
//       stars  = 3
//       line: "   ***"
//     i = 3:
//       spaces = 2
//       stars  = 5
//       line: "  *****"
//     i = 4:
//       spaces = 1
//       stars  = 7
//       line: " *******"
//     i = 5:
//       spaces = 0
//       stars  = 9
//       line: "*********"
//     */

//     for (int i = 1; i <= rows; i++) {

//         // Print (rows - i) spaces
//         for (int j = 1; j <= rows - i; j++) {
//             printf(" ");
//         }

//         // Print (2*i - 1) stars
//         for (int k = 1; k <= 2 * i - 1; k++) {
//             printf("*");
//         }

//         // End of current row
//         printf("\n");
//     }

//     return 0;
// }




// #include <stdio.h>

// int main(){

//     for(int i = 1; i <= 100; i++){
//         if (i%7 == 0){
//              printf("First number divisible by 7: %d\n", i);
//              break;
//         }
//     }

//     return 0;
// }


// #include <stdio.h>

// int main(){

//     for(int i = 1; i <= 3; i++){
//         for( int j = 1; j<=3; j++){
//             if(j == 2){
//                 break;
//             }
//             printf("i=%d, j=%d\n", i, j);
//         }
//     }

//     int choice = 1;
//     switch (choice) {
//     case 1:
//         printf("Option 1\n");
//         break;  // prevents fall-through
//     case 2:
//         printf("Option 2\n");
//         break;
//     }

//     return 0;
// }


#include <stdio.h>

int main(){

    // Print odd numbers from 1 to 10
    // for (int i = 1; i <= 10; i++) {
    //     if (i % 2 == 0) {
    //         continue;  // skip even numbers
    //     }
    //     printf("%d ", i);
    // }


    // Skip negative numbers
    int numbers[] = {5, -3, 8, -1, 10, -7, 4};
    int sum = 0;

    for (int i = 0; i < 7; i++) {
        if (numbers[i] < 0) {
            continue;  // skip negative numbers
        }
        sum += numbers[i];
    }
    printf("Sum of positive numbers: %d\n", sum);

}