# **C Language Learning**

## **0. Setup**

Install a C compiler:

- **Windows:** VS Code + MinGW-w64 / TDM-GCC
- **Mac:** Xcode Command Line Tools
- **Linux:** gcc, usually pre-installed

Learn basic compilation:

```bash
gcc program.c -o program
./program
```

## **1. C Basics**

**Core Concepts**

- What is C and why learn it
- Structure of a C program
- Header files and `#include`
- `main()` function and return values
- Output with `printf()`
- Input with `scanf()`
- Variables and data types
- Constants with `const` and `#define`
- Operators: arithmetic, relational, logical, assignment, bitwise
- Comments and code formatting

**Practice Problems**

- Print hello world
- Add two numbers
- Swap two numbers
- Check odd/even
- Find the largest of 3 numbers
- Build a simple calculator
- Convert temperature between Celsius and Fahrenheit

## **2. Control Flow**

**Topics**

- Conditional statements: `if`, `else if`, `else`
- Nested conditions
- Ternary operator
- `switch case`
- Loops: `for`, `while`, `do-while`
- Loop control: `break` and `continue`
- Nested loops
- Pattern printing

**Practice**

- Check voting eligibility
- Grade calculator
- Factorial
- Fibonacci sequence
- Prime number checker
- Reverse a number
- Sum of digits
- Armstrong number checker
- Star and number patterns
- Menu-driven programs

## **3. Arrays & Strings**

**Topics**

- 1D arrays
- Array initialization and traversal
- Array insertion, deletion, search, and update
- 2D arrays and matrices
- Character arrays
- C strings and null terminator
- String functions: `strlen`, `strcpy`, `strcmp`, `strcat`
- Manual string operations without library functions

**Practice**

- Find max and min in an array
- Linear search
- Binary search
- Reverse an array
- Sort an array
- Matrix addition and multiplication
- String palindrome checker
- Count vowels and consonants
- Reverse a string
- Compare strings manually

## **4. Functions**

**Topics**

- Function declaration, definition, and call
- Function prototypes
- Parameters and return values
- Pass by value
- Passing addresses to functions
- Recursion
- Scope of variables
- Header/source organization basics

**Practice**

- Factorial using functions
- Fibonacci using recursion
- GCD and LCM calculator
- Power function
- Number system converter
- Prime checker function
- Array helper functions
- Simple calculator using functions

## **5. Pointers**

**Topics**

- Pointer declaration and initialization
- Address-of operator `&`
- Dereference operator `*`
- Pointer arithmetic
- Pointers and arrays
- Pointers and strings
- Pointers to pointers
- Pointers with functions
- Function pointers
- `void *`
- `NULL` pointers and dangling pointers

**Practice**

- Swap using pointers
- Traverse an array with pointers
- Reverse an array using pointers
- Implement `strlen` using pointers
- Pointer-based string copy
- Use function pointers for simple callbacks

## **6. Structures, Unions & Enums**

**Structures**

- Defining a `struct`
- Accessing structure members
- Structure variables
- Array of structures
- Nested structures
- Structure pointers and `->`
- Passing structures to functions
- `typedef` with structures

**Unions and Enums**

- Defining a `union`
- Difference between `struct` and `union`
- Memory layout basics
- Defining an `enum`
- Named constants with enums
- Bit fields introduction

**Practice**

- Student record system
- Employee database
- Book information program
- Complex number operations
- Date and time structure
- Enum-based menu program

## **7. Dynamic Memory Management**

**Topics**

- Stack vs heap memory
- `malloc()`
- `calloc()`
- `realloc()`
- `free()`
- Dynamic arrays
- Dynamic 2D arrays
- Memory leaks
- Dangling pointers
- Safe allocation checks

**Practice**

- Create a dynamic array
- Resize an array at runtime
- Dynamic matrix allocation
- Dynamic string operations
- Create linked list nodes
- Detect and fix simple memory leaks

## **8. File Handling**

**Topics**

- File pointers
- File modes: `r`, `w`, `a`, `rb`, `wb`, `ab`
- Opening and closing files with `fopen()` and `fclose()`
- Reading with `fscanf()`, `fgets()`, `fgetc()`, `fread()`
- Writing with `fprintf()`, `fputs()`, `fputc()`, `fwrite()`
- File positioning with `fseek()`, `ftell()`, `rewind()`
- Text files vs binary files
- Error handling with files

**Practice**

- Write text to a file
- Read text from a file
- Append data to a file
- Copy one file to another
- Count lines, words, and characters
- Store student records
- Binary file read/write
- Build a file-based contact manager

## **9. Data Structures in C**

**Linear Data Structures**

- Singly linked list
- Doubly linked list
- Circular linked list
- Stack using arrays
- Stack using linked lists
- Queue and circular queue
- Priority queue basics

**Trees, Graphs, and Hashing**

- Binary tree
- Binary search tree
- Heap basics
- Graph representation with adjacency matrix
- Graph representation with adjacency list
- BFS and DFS
- Hash tables

**Practice**

- Implement insert, delete, search, and traversal
- Reverse a linked list
- Balanced parentheses with stack
- Queue simulation
- Tree traversal
- Graph traversal
- Simple hash table

## **10. Advanced C**

**Topics**

- Preprocessor directives
- Macros and macro pitfalls
- Header guards
- Multi-file programs
- Command-line arguments with `argc` and `argv`
- Storage classes: `auto`, `static`, `extern`, `register`
- Type casting
- Bitwise operations
- Modular programming
- Debugging with `gdb`
- Memory checking with tools such as Valgrind
- Basic optimization ideas

**Practice**

- Build a multi-file calculator
- Use headers for reusable functions
- Parse command-line arguments
- Bitwise flag program
- Debug a crashing program
- Refactor examples into modules

## **11. Build Real Projects**

- File-based student management system
- Contact book with search and update
- Console-based snake game
- Task or to-do list manager
- Simple text editor
- Banking system simulation
- Tic-tac-toe
- Calculator with history
- Mini shell
- Basic interpreter
- File compression toy project
- Data structure visualizer in console
