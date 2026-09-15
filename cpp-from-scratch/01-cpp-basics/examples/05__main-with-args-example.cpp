#include <stdio.h>
#include <iostream>

int main(int argc, char* argv[]) {
    printf("Program name: %s\n", argv[0]);
    printf("Number of arguments (argc): %d\n", argc);

    for (int i = 1; i < argc; i++) {
        printf("Argument %d: %s\n", i, argv[i]);
    }

    return 0;
}


// PS D:\c&cpps\cpp-from-scratch\01-cpp-basics\examples> .\05__main-with-args-example.exe 123 akshay rohit new
// Program name: D:\c&cpps\cpp-from-scratch\01-cpp-basics\examples\05__main-with-args-example.exe
// Number of arguments (argc): 5
// Argument 1: 123
// Argument 2: akshay
// Argument 3: rohit
// Argument 4: new
