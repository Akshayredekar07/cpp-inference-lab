# **C++ Language Learning**

## **0. Setup**

Install a C++ compiler:

- **Windows:** VS Code + MinGW-w64 / Visual Studio
- **Mac:** Xcode Command Line Tools
- **Linux:** g++ (usually pre-installed)

Learn basic compilation:

```
g++ program.cpp -o program
./program
```


## **1. C++ Basics**

**Core Concepts**

- What is C++ and its relationship with C
- Structure of a C++ program
- `iostream` library: `cin`, `cout`, `cerr`
- Namespaces (`std::`, `using namespace std`)
- Variables & Data Types (including `bool`, `wchar_t`)
- Operators (all types from C + scope resolution `::`)
- Comments (`//` and `/* */`)
- Constants (`const`, `constexpr`)
- Enums, structs, and unions
- Preprocessor directives (`#include`, `#define`, macros, header guards)
- Header/source file separation (`.h` / `.cpp`), compilation and linking basics

**Practice Problems**

- Add two numbers
- Swap using reference variables
- Simple calculator
- Check odd/even
- Find largest of 3 numbers
- Temperature converter
- Area and perimeter of shapes

## **2. Control Flow**

**Topics**

- Conditional statements: `if`, `else if`, `else`
- Ternary operator
- `switch case`
- Loops: `for`, `while`, `do-while`
- Range-based for loop (C++11)
- Loop control: `break`, `continue`
- Nested loops

**Practice**

- Factorial (iterative and recursive)
- Fibonacci sequence
- Prime number checker
- Number reversal
- Pattern printing (pyramids, stars, numbers)
- Armstrong numbers
- Perfect numbers
- Menu-driven programs


## **3. Functions**

**Topics**

- Function declaration and definition
- Function overloading
- Default arguments
- Inline functions
- Pass by value, reference, and pointer
- Return by reference
- Recursion
- Function templates (basic introduction)
- Lambda expressions (C++11)

**Practice**

- Overload functions for different data types
- GCD and LCM calculator
- Tower of Hanoi
- Number system converters
- Implement mathematical functions
- Use lambda for simple operations


## **4. Arrays & Strings**

**Topics**

- Arrays (1D, 2D, multi-dimensional)
- Array initialization and traversal
- C-style strings vs `std::string`
- String class methods (length, substr, find, append, etc.)
- String streams (`stringstream`)
- `std::array` (C++11)
- Character functions (`isalpha`, `isdigit`, `toupper`, etc.)

**Practice**

- Array manipulation (search, sort, reverse)
- Matrix operations
- String palindrome checker
- Anagram checker
- Word count in sentence
- String tokenization
- Remove duplicates from array
- Implement basic string algorithms


## **5. Pointers & References**

**Topics**

- Pointer basics (same as C)
- References (`&`) — declaration and usage
- Pointer vs reference differences
- Pointer arithmetic
- Pointers to objects
- `this` pointer
- Function pointers
- Smart pointers introduction (`unique_ptr`, `shared_ptr`, `weak_ptr`)
- `nullptr` (C++11)

**Practice**

- Swap using pointers and references
- Dynamic array manipulation
- Pointer-based data structure operations
- Implement reference-based functions
- Practice smart pointer usage

---

## **6. Object-Oriented Programming (OOP)**

**Classes and Objects**

- Class definition and object creation
- Access specifiers (`public`, `private`, `protected`)
- Member functions and data members
- `this` pointer

**Constructors and Destructors**

- Default, parameterized, copy constructors
- Constructor overloading
- Destructor and its role
- Constructor initialization list

**Encapsulation**

- Data hiding
- Getters and setters

**Inheritance**

- Single, multiple, multilevel, hierarchical, hybrid
- `public`, `protected`, `private` inheritance
- Constructor and destructor in inheritance
- Order of execution

**Polymorphism**

- Compile-time (function/operator overloading)
- Runtime (virtual functions, pure virtual functions)
- Abstract classes and interfaces
- Virtual destructors

**Abstraction**

- Abstract classes
- Interfaces

**Practice**

- Design a `BankAccount` class
- Create `Student` and `Teacher` classes with inheritance
- Implement shape hierarchy (Shape → Circle, Rectangle)
- Virtual function demonstrations
- Operator overloading (for complex numbers, matrices)
- Build a simple library management system


## **7. Operator Overloading**

**Topics**

- Overloadable vs non-overloadable operators
- Unary operator overloading (`++`, `--`, `-`, `!`)
- Binary operator overloading (`+`, `-`, `*`, `/`, `==`, etc.)
- Stream operators (`<<`, `>>`)
- Subscript operator (`[]`)
- Function call operator (`()`)
- Friend functions for operator overloading

**Practice**

- Overload operators for `Complex` class
- Matrix class with arithmetic operators
- String class implementation
- Distance/Time class operations
- Fraction class with full arithmetic


## **8. Dynamic Memory Management**

**Topics**

- `new` and `delete` operators
- `new[]` and `delete[]` for arrays
- Memory leaks and their prevention
- RAII (Resource Acquisition Is Initialization)
- Smart pointers (C++11): `std::unique_ptr`, `std::shared_ptr`, `std::weak_ptr`
- `make_unique` and `make_shared` (C++14)

**Practice**

- Create dynamic arrays and matrices
- Implement custom dynamic string class
- Practice with smart pointers
- Build memory-safe data structures
- Detect and fix memory leaks


## **9. Standard Template Library (STL)**

**Containers**

- Sequence: `vector`, `deque`, `list`, `forward_list`, `array`
- Associative: `set` / `multiset`, `map` / `multimap`
- Unordered (C++11): `unordered_set` / `unordered_multiset`, `unordered_map` / `unordered_multimap`
- Container Adapters: `stack`, `queue`, `priority_queue`

**Iterators**

- Iterator types (input, output, forward, bidirectional, random access)
- `begin()`, `end()`, `rbegin()`, `rend()`
- Iterator operations

**Algorithms**

- Sorting: `sort()`, `stable_sort()`, `partial_sort()`
- Searching: `find()`, `binary_search()`, `lower_bound()`, `upper_bound()`
- Modifying: `copy()`, `move()`, `transform()`, `replace()`
- Numeric: `accumulate()`, `inner_product()`
- Set operations: `set_union()`, `set_intersection()`
- Other: `reverse()`, `rotate()`, `unique()`, `shuffle()`

**Functors and Function Objects**

- Creating custom functors
- Predefined functors (`less`, `greater`, etc.)

**Practice**

- Solve problems using each container
- Implement common algorithms using STL
- Practice iterator usage
- Build programs combining multiple containers
- Performance comparison between containers


## **10. Exception Handling**

**Topics**

- `try`, `catch`, `throw`
- Exception specifications
- Standard exception classes
- Custom exception classes
- Stack unwinding
- `noexcept` specifier (C++11)
- RAII and exception safety

**Practice**

- Handle division by zero
- File operation error handling
- Input validation with exceptions
- Create custom exception hierarchy
- Implement exception-safe classes

---

## **11. File Handling**

**Topics**

- File streams: `ifstream`, `ofstream`, `fstream`
- File modes and flags
- Reading and writing text files
- Binary file operations
- File positioning: `seekg()`, `seekp()`, `tellg()`, `tellp()`
- Checking file states (eof, fail, bad)
- Serialization and deserialization

**Practice**

- Read/write student records
- Copy file contents
- Search and replace in files
- Binary file operations with objects
- CSV file parser
- Create log file system
- File-based database simulation


## **12. Templates**

**Topics**

- Function templates
- Class templates
- Template specialization
- Non-type template parameters
- Default template arguments
- Variadic templates (C++11)
- Template template parameters
- SFINAE basics

**Practice**

- Generic swap function
- Generic array/vector class
- Template-based stack/queue
- Generic sorting functions
- Template-based pair/tuple class
- Calculator with template classes

---

## **13. Modern C++ (C++11/14/17/20)**

**C++11 Features**

- Auto keyword
- Range-based for loops
- Lambda expressions
- Smart pointers
- `nullptr`
- Move semantics and rvalue references
- `std::thread` and basic multithreading
- `constexpr`
- Uniform initialization
- `static_assert`

**C++14 Features**

- Generic lambdas
- `std::make_unique`
- Return type deduction
- Binary literals

**C++17 Features**

- Structured bindings
- `if` with initializer
- `std::optional`, `std::variant`, `std::any`
- `std::filesystem`
- Fold expressions

**C++20 Features**

- Concepts
- Ranges
- Coroutines
- Modules
- Three-way comparison operator (`<=>`)

**Practice**

- Refactor old code using modern features
- Practice lambda expressions extensively
- Use auto appropriately
- Implement move constructors
- Work with filesystem library
- Basic threading programs

## **14. Advanced Topics**

**Multithreading**

- `std::thread`, `std::mutex`, `std::lock_guard`
- Condition variables
- Atomic operations
- Thread pool

**Move Semantics**

- Rvalue references
- Move constructors and assignment
- Perfect forwarding

**Type Traits and Metaprogramming**

- `std::enable_if`
- Template metaprogramming basics
- SFINAE patterns

**Design Patterns**

- Singleton, Factory, Observer
- Strategy, Decorator, etc.

**Memory Model**

- Stack vs Heap
- Memory alignment
- Cache-friendly code

**Practice**

- Implement thread-safe data structures
- Create resource-managing classes with move semantics
- Practice design patterns
- Build performance-critical components

## **15. Data Structures & Algorithms**

Implement these from scratch in C++:

- **Linear:** Linked List, Stack, Queue, Deque
- **Trees:** Binary Tree, BST, AVL, Red-Black, Heap
- **Graphs:** Adjacency List/Matrix, BFS, DFS
- **Hashing:** Hash Table, Hash Map
- **Advanced:** Trie, Segment Tree, Fenwick Tree

Also practice:

- Sorting algorithms (Quick, Merge, Heap, etc.)
- Searching algorithms
- Dynamic programming
- Greedy algorithms
- Graph algorithms (Dijkstra, Kruskal, Prim)

## **16. Build Real Projects**

- Student/Employee Management System (OOP + File Handling)
- Banking System (accounts, transactions, inheritance)
- Library Management System (classes, STL, file operations)
- Chat Application (sockets, multithreading)
- Simple Database Engine (file-based, indexing)
- Game Development (Snake, Tetris, Chess)
- Text Editor (file handling, data structures)
- Task Manager/Scheduler
- Compiler/Interpreter (lexer, parser)
- Web Server (basic HTTP, sockets)
- Cryptocurrency Simulator
- Image Processing Tool