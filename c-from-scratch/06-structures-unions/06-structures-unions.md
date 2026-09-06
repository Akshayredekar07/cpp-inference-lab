# **6️⃣ Structures & Unions in C Programming**

In real-world programming, we often need to represent **complex entities** such as a *Student, Book, Employee, Car,* etc.
Each entity has **multiple attributes of different data types**.

* Arrays ❌ → store only **same data type**
* Structures / Unions ✅ → store **heterogeneous data**

These are called **User-Defined Data Types** in C.

---

## **1. Structures (`struct`)**

### **Definition**

A **structure** is a user-defined data type that groups **variables of different data types** under a single name.

It acts as a **blueprint** for creating records.

---

### **Syntax**

```c
struct structure_name {
    data_type member1;
    data_type member2;
    ...
};
```

---

### **Example**

```c
struct Student {
    int id;           // 4 bytes
    char name[20];    // 20 bytes
    float percentage; // 4 bytes
};
```

* This **does NOT allocate memory**
* It only defines a new data type

---

## **2. Declaring Structure Variables**

Memory is allocated **only when variables are declared**.

```c
struct Student s1;
struct Student s2, s3;
```

---

## **3. Initialization of Structures**

### **At Declaration Time**

```c
struct Student s1 = {101, "Alice", 92.5};
```

### **Member-wise Initialization**

```c
s1.id = 102;
strcpy(s1.name, "Rohit");
s1.percentage = 88.5;
```

---

## **4. Accessing Structure Members**

### **Dot Operator (`.`)**

Used when working with a **structure variable**.

```c
printf("%d", s1.id);
printf("%s", s1.name);
```

---

### **Complete Example**

```c
#include <stdio.h>
#include <string.h>

struct Book {
    char title[50];
    int pages;
    float price;
};

int main() {
    struct Book b1;

    b1.pages = 300;
    b1.price = 25.50;
    strcpy(b1.title, "The C Programming Language");

    printf("Title: %s\n", b1.title);
    printf("Pages: %d\n", b1.pages);

    return 0;
}
```

---

## **5. `typedef` for Cleaner Code**

Writing `struct Student` repeatedly is verbose.
`typedef` creates a **type alias**.

---

### **Without `typedef`**

```c
struct Point {
    int x;
    int y;
};

struct Point p1;
```

---

### **With `typedef`**

```c
typedef struct {
    int x;
    int y;
} Point;

Point p1;
```

Benefits:

* Cleaner syntax
* Readable function parameters
* Common in production C code

---

## **6. Array of Structures**

Used to store **multiple records** of the same structure type.

---

### **Example**

```c
typedef struct {
    int id;
    char name[20];
} Employee;

Employee team[3];
```

---

### **Accessing Elements**

```c
team[0].id = 1;
strcpy(team[0].name, "Tanvi");
```

---

### **Loop Example**

```c
for (int i = 0; i < 3; i++) {
    printf("%d %s\n", team[i].id, team[i].name);
}
```

Common use cases:

* Student databases
* Employee records
* Tables and logs

---

## **7. Nested Structures**

A structure can contain **another structure as a member**.

---

### **Example**

```c
struct Date {
    int day;
    int month;
    int year;
};

struct Student {
    int id;
    char name[20];
    struct Date dob;
};
```

---

### **Accessing Nested Members**

```c
s1.dob.day = 15;
s1.dob.month = 8;
s1.dob.year = 2000;
```

Used for:

* Address inside Employee
* Date inside Record
* Coordinates inside Shape

---

## **8. Structure Pointers and Arrow Operator (`->`)**

A **pointer to a structure** stores the address of a structure variable.

---

### **Why Use Structure Pointers**

* Avoid copying large structures
* Pass structures efficiently to functions
* Required for dynamic memory allocation

---

### **Example**

```c
struct Rect {
    int length;
    int width;
};

int main() {
    struct Rect r1 = {10, 20};
    struct Rect *ptr = &r1;

    printf("%d\n", ptr->length);
    ptr->width = 30;
}
```

---

### **Dot vs Arrow**

| Case                 | Operator |
| -------------------- | -------- |
| Structure variable   | `.`      |
| Pointer to structure | `->`     |

`ptr->member` ≡ `(*ptr).member`

---

## **9. Union (`union`)**

A **union** is similar to a structure but **shares memory** among all members.

---

### **Key Rule**

Only **one member** can hold a valid value at a time.

---

### **Syntax**

```c
union Data {
    int i;
    float f;
    char str[20];
};
```

* Memory size = **largest member**
* Here → 20 bytes

---

### **Example**

```c
union Data d;
d.i = 10;
d.f = 3.14;   // overwrites previous value
```

---

### **Structure vs Union**

| Feature        | Structure          | Union                     |
| -------------- | ------------------ | ------------------------- |
| Memory         | Sum of all members | Largest member only       |
| Active members | All at once        | One at a time             |
| Data overlap   | No                 | Yes                       |
| Use case       | Records            | Memory-efficient variants |

Used in:

* Embedded systems
* Protocol parsing
* Variant data storage

---

## **10. Enumerations (`enum`)**

`enum` defines **named integer constants**.

---

### **Syntax**

```c
enum Level {
    LOW,
    MEDIUM,
    HIGH
};
```

Default values:

```
LOW = 0, MEDIUM = 1, HIGH = 2
```

---

### **Custom Values**

```c
enum Status {
    FAILED = -1,
    SUCCESS = 1,
    PENDING = 2
};
```

---

### **With `typedef`**

```c
typedef enum {
    RED, GREEN, BLUE
} Color;

Color c = GREEN;
```

Used for:

* States
* Modes
* Error codes
* Flags

---

## **11. Bit Fields**

Bit fields allow **bit-level storage** inside structures.

---

### **Syntax**

```c
struct Flags {
    unsigned int isVisible : 1;
    unsigned int isActive  : 1;
    unsigned int type      : 4;
};
```

* `isVisible` → 1 bit
* `type` → 4 bits (0–15)

---

### **Example**

```c
struct Flags f = {1, 0, 5};
f.isActive = 1;
```

---

### **Important Notes**

* Cannot take address using `&`
* Layout is implementation-dependent
* Best for low-level and embedded programming

---

## **12. Combined Mini Example**

```c
#include <stdio.h>
#include <string.h>

typedef enum { DEV, TEST, PROD } Env;

typedef struct {
    unsigned int debug : 1;
    unsigned int verbose : 1;
    unsigned int level : 2;
} LogFlags;

typedef struct {
    char name[20];
    Env env;
    LogFlags flags;
} Config;

int main() {
    Config cfg = {"ServiceA", PROD, {1, 0, 2}};
    Config *p = &cfg;

    printf("%s %d %u %u %u\n",
           p->name, p->env,
           p->flags.debug, p->flags.verbose, p->flags.level);
}
```

---
# Complete Notes: C Programming - Structures & Unions

## Table of Contents
1. [Introduction to Structures](#introduction-to-structures)
2. [Structure Definition and Usage](#structure-definition-and-usage)
3. [Accessing Structure Members](#accessing-structure-members)
4. [typedef for Cleaner Code](#typedef-for-cleaner-code)
5. [Array of Structures](#array-of-structures)
6. [Nested Structures](#nested-structures)
7. [Structure Pointers](#structure-pointers)
8. [Unions](#unions)
9. [Enumerations (enum)](#enumerations-enum)
10. [Bit Fields](#bit-fields)
11. [Memory Layout and Padding](#memory-layout-and-padding)
12. [Best Practices](#best-practices)

---

## Introduction to Structures

A **structure** is a user-defined data type in C that allows you to group variables of different data types under a single name. Structures are particularly useful for representing real-world entities with multiple attributes.

### Why Use Structures?
- Organize related data together
- Create custom data types
- Represent complex entities (students, employees, coordinates, etc.)
- Pass multiple related values to functions efficiently
- Build data structures (linked lists, trees, etc.)

---

## Structure Definition and Usage

### Basic Syntax

```c
struct structure_name {
    data_type member1;
    data_type member2;
    // ... more members
};
```

### Example: Defining a Structure

```c
struct Student {
    int roll_no;
    char name[50];
    float marks;
    char grade;
};
```

### Declaring Structure Variables

There are three ways to declare structure variables:

#### Method 1: After Structure Definition
```c
struct Student {
    int roll_no;
    char name[50];
    float marks;
};

// Declare variables
struct Student s1, s2, s3;
```

#### Method 2: During Structure Definition
```c
struct Student {
    int roll_no;
    char name[50];
    float marks;
} s1, s2, s3;  // Variables declared here
```

#### Method 3: Anonymous Structure
```c
struct {
    int x;
    int y;
} point1, point2;  // Can't create more variables of this type later
```

### Initializing Structures

```c
// Method 1: During declaration
struct Student s1 = {101, "John Doe", 85.5};

// Method 2: Designated initializers (C99 and later)
struct Student s2 = {
    .roll_no = 102,
    .marks = 92.3,
    .name = "Jane Smith"
};

// Method 3: Partial initialization (remaining members set to 0)
struct Student s3 = {103};  // Only roll_no initialized
```

---

## Accessing Structure Members

Structure members are accessed using the **dot operator (.)**.

### Syntax
```c
structure_variable.member_name
```

### Example: Complete Program

```c
#include <stdio.h>
#include <string.h>

struct Student {
    int roll_no;
    char name[50];
    float marks;
};

int main() {
    struct Student s1;
    
    // Assigning values
    s1.roll_no = 101;
    strcpy(s1.name, "Alice Johnson");
    s1.marks = 88.5;
    
    // Accessing and displaying values
    printf("Roll No: %d\n", s1.roll_no);
    printf("Name: %s\n", s1.name);
    printf("Marks: %.2f\n", s1.marks);
    
    return 0;
}
```

### Reading Input into Structures

```c
struct Student s1;

printf("Enter roll number: ");
scanf("%d", &s1.roll_no);

printf("Enter name: ");
scanf("%s", s1.name);  // No & needed for array

printf("Enter marks: ");
scanf("%f", &s1.marks);
```

---

## typedef for Cleaner Code

The `typedef` keyword creates an alias for a data type, making code more readable and reducing verbosity.

### Without typedef

```c
struct Student {
    int roll_no;
    char name[50];
};

struct Student s1, s2;  // Must use "struct" keyword
```

### With typedef

```c
typedef struct {
    int roll_no;
    char name[50];
} Student;

Student s1, s2;  // No "struct" keyword needed
```

### Alternative typedef Syntax

```c
struct Student {
    int roll_no;
    char name[50];
};

typedef struct Student Student;

// Now both forms work:
struct Student s1;
Student s2;
```

### Practical Example

```c
#include <stdio.h>

typedef struct {
    float x;
    float y;
} Point;

typedef struct {
    Point center;
    float radius;
} Circle;

int main() {
    Circle c1 = {{0.0, 0.0}, 5.0};
    
    printf("Circle center: (%.1f, %.1f)\n", c1.center.x, c1.center.y);
    printf("Circle radius: %.1f\n", c1.radius);
    
    return 0;
}
```

---

## Array of Structures

An array of structures allows you to store multiple records of the same type.

### Declaration and Initialization

```c
struct Student {
    int roll_no;
    char name[50];
    float marks;
};

// Array declaration
struct Student class[50];  // Array of 50 students

// Initialization
struct Student class[3] = {
    {101, "Alice", 85.5},
    {102, "Bob", 78.2},
    {103, "Charlie", 92.0}
};
```

### Accessing Array Elements

```c
// Access first student
printf("Name: %s\n", class[0].name);

// Access third student's marks
printf("Marks: %.2f\n", class[2].marks);
```

### Complete Example: Student Management

```c
#include <stdio.h>
#include <string.h>

typedef struct {
    int roll_no;
    char name[50];
    float marks;
} Student;

int main() {
    Student class[100];
    int n, i;
    
    printf("Enter number of students: ");
    scanf("%d", &n);
    
    // Input student data
    for (i = 0; i < n; i++) {
        printf("\nStudent %d:\n", i + 1);
        printf("Roll No: ");
        scanf("%d", &class[i].roll_no);
        printf("Name: ");
        scanf("%s", class[i].name);
        printf("Marks: ");
        scanf("%f", &class[i].marks);
    }
    
    // Display all students
    printf("\n--- Student Records ---\n");
    for (i = 0; i < n; i++) {
        printf("\nRoll No: %d\n", class[i].roll_no);
        printf("Name: %s\n", class[i].name);
        printf("Marks: %.2f\n", class[i].marks);
    }
    
    // Find highest marks
    float max = class[0].marks;
    int top_index = 0;
    for (i = 1; i < n; i++) {
        if (class[i].marks > max) {
            max = class[i].marks;
            top_index = i;
        }
    }
    
    printf("\nTopper: %s with %.2f marks\n", 
           class[top_index].name, class[top_index].marks);
    
    return 0;
}
```

---

## Nested Structures

A structure can contain another structure as a member.

### Syntax and Example

```c
struct Date {
    int day;
    int month;
    int year;
};

struct Employee {
    int emp_id;
    char name[50];
    float salary;
    struct Date join_date;  // Nested structure
};
```

### Accessing Nested Structure Members

```c
struct Employee emp1;

// Assigning values
emp1.emp_id = 1001;
emp1.join_date.day = 15;
emp1.join_date.month = 8;
emp1.join_date.year = 2020;

// Accessing values
printf("Employee ID: %d\n", emp1.emp_id);
printf("Joining Date: %d/%d/%d\n", 
       emp1.join_date.day, 
       emp1.join_date.month, 
       emp1.join_date.year);
```

### Complex Nested Example

```c
#include <stdio.h>

typedef struct {
    int house_no;
    char street[50];
    char city[50];
    int pincode;
} Address;

typedef struct {
    char name[50];
    int age;
    Address home;      // Nested structure
    Address office;    // Another nested structure
} Person;

int main() {
    Person p1 = {
        "John Doe",
        30,
        {123, "Main St", "New York", 10001},
        {456, "Park Ave", "New York", 10002}
    };
    
    printf("Name: %s\n", p1.name);
    printf("Home: %d %s, %s - %d\n", 
           p1.home.house_no, p1.home.street, 
           p1.home.city, p1.home.pincode);
    printf("Office: %d %s, %s - %d\n", 
           p1.office.house_no, p1.office.street, 
           p1.office.city, p1.office.pincode);
    
    return 0;
}
```

---

## Structure Pointers

Pointers to structures allow dynamic memory allocation and efficient passing of structures to functions.

### Declaration and Initialization

```c
struct Student {
    int roll_no;
    char name[50];
    float marks;
};

struct Student s1 = {101, "Alice", 85.5};
struct Student *ptr;

ptr = &s1;  // Pointer now points to s1
```

### Accessing Members via Pointer

There are two ways to access structure members through a pointer:

#### Method 1: Using (*pointer).member
```c
printf("Roll No: %d\n", (*ptr).roll_no);
(*ptr).marks = 90.0;
```

#### Method 2: Using Arrow Operator (->)
```c
printf("Roll No: %d\n", ptr->roll_no);
ptr->marks = 90.0;
```

The arrow operator `->` is preferred as it's more concise and readable.

### Complete Example with Pointers

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    float salary;
} Employee;

void displayEmployee(Employee *emp) {
    printf("ID: %d\n", emp->id);
    printf("Name: %s\n", emp->name);
    printf("Salary: %.2f\n", emp->salary);
}

void giveRaise(Employee *emp, float percentage) {
    emp->salary += emp->salary * (percentage / 100.0);
}

int main() {
    Employee emp1 = {1001, "John Smith", 50000.0};
    Employee *ptr = &emp1;
    
    printf("Before raise:\n");
    displayEmployee(ptr);
    
    giveRaise(ptr, 10);  // 10% raise
    
    printf("\nAfter 10%% raise:\n");
    displayEmployee(ptr);
    
    return 0;
}
```

### Dynamic Memory Allocation for Structures

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int roll_no;
    char name[50];
    float marks;
} Student;

int main() {
    Student *ptr;
    int n, i;
    
    printf("Enter number of students: ");
    scanf("%d", &n);
    
    // Allocate memory for n students
    ptr = (Student *)malloc(n * sizeof(Student));
    
    if (ptr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    // Input data
    for (i = 0; i < n; i++) {
        printf("\nStudent %d:\n", i + 1);
        printf("Roll No: ");
        scanf("%d", &(ptr + i)->roll_no);
        printf("Name: ");
        scanf("%s", (ptr + i)->name);
        printf("Marks: ");
        scanf("%f", &(ptr + i)->marks);
    }
    
    // Display data
    printf("\n--- Student Records ---\n");
    for (i = 0; i < n; i++) {
        printf("\nRoll No: %d\n", (ptr + i)->roll_no);
        printf("Name: %s\n", (ptr + i)->name);
        printf("Marks: %.2f\n", (ptr + i)->marks);
    }
    
    free(ptr);  // Free allocated memory
    return 0;
}
```

### Self-Referential Structures

Structures that contain a pointer to the same structure type (used in linked lists, trees):

```c
typedef struct Node {
    int data;
    struct Node *next;  // Pointer to next node
} Node;

int main() {
    Node n1, n2, n3;
    
    n1.data = 10;
    n2.data = 20;
    n3.data = 30;
    
    n1.next = &n2;
    n2.next = &n3;
    n3.next = NULL;
    
    // Traversing the linked list
    Node *current = &n1;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
    
    return 0;
}
```

---

## Unions

A **union** is a user-defined data type similar to structures, but with one key difference: all members share the same memory location.

### Key Differences: Structure vs Union

| Feature | Structure | Union |
|---------|-----------|-------|
| Memory | Each member has separate memory | All members share same memory |
| Size | Sum of all member sizes (+ padding) | Size of largest member |
| Access | All members accessible simultaneously | Only one member valid at a time |
| Usage | Store multiple values together | Store different types at different times |

### Union Syntax

```c
union union_name {
    data_type member1;
    data_type member2;
    // ... more members
};
```

### Basic Example

```c
#include <stdio.h>

union Data {
    int i;
    float f;
    char c;
};

int main() {
    union Data d;
    
    printf("Size of union: %lu bytes\n", sizeof(d));
    
    d.i = 10;
    printf("d.i = %d\n", d.i);
    
    d.f = 3.14;
    printf("d.f = %.2f\n", d.f);
    printf("d.i = %d (corrupted!)\n", d.i);  // Overwritten
    
    d.c = 'A';
    printf("d.c = %c\n", d.c);
    printf("d.f = %.2f (corrupted!)\n", d.f);  // Overwritten
    
    return 0;
}
```

**Output:**
```
Size of union: 4 bytes
d.i = 10
d.f = 3.14
d.i = 1078523331 (corrupted!)
d.c = A
d.f = 0.00 (corrupted!)
```

### Practical Use Case: Tagged Union

Unions are often used with an additional tag to track which member is currently valid:

```c
#include <stdio.h>

enum DataType { INT, FLOAT, CHAR };

typedef struct {
    enum DataType type;
    union {
        int i;
        float f;
        char c;
    } value;
} Data;

void printData(Data d) {
    switch (d.type) {
        case INT:
            printf("Integer: %d\n", d.value.i);
            break;
        case FLOAT:
            printf("Float: %.2f\n", d.value.f);
            break;
        case CHAR:
            printf("Character: %c\n", d.value.c);
            break;
    }
}

int main() {
    Data d1, d2, d3;
    
    d1.type = INT;
    d1.value.i = 42;
    
    d2.type = FLOAT;
    d2.value.f = 3.14159;
    
    d3.type = CHAR;
    d3.value.c = 'X';
    
    printData(d1);
    printData(d2);
    printData(d3);
    
    return 0;
}
```

### Memory Comparison

```c
#include <stdio.h>

struct Sample1 {
    int i;
    float f;
    char c;
};

union Sample2 {
    int i;
    float f;
    char c;
};

int main() {
    printf("Size of structure: %lu bytes\n", sizeof(struct Sample1));
    printf("Size of union: %lu bytes\n", sizeof(union Sample2));
    
    return 0;
}
```

**Typical Output:**
```
Size of structure: 12 bytes (4 + 4 + 1 + 3 padding)
Size of union: 4 bytes (size of largest member)
```

---

## Enumerations (enum)

An **enumeration** is a user-defined data type consisting of named integer constants. Enums improve code readability and maintainability.

### Basic Syntax

```c
enum enum_name {
    constant1,
    constant2,
    constant3
};
```

### Default Values

By default, enum constants start at 0 and increment by 1:

```c
enum Weekday {
    SUNDAY,      // 0
    MONDAY,      // 1
    TUESDAY,     // 2
    WEDNESDAY,   // 3
    THURSDAY,    // 4
    FRIDAY,      // 5
    SATURDAY     // 6
};
```

### Custom Values

You can assign specific values to enum constants:

```c
enum Month {
    JAN = 1,
    FEB,        // 2
    MAR,        // 3
    APR = 10,
    MAY,        // 11
    JUN         // 12
};
```

### Using Enums

```c
#include <stdio.h>

enum Status {
    PENDING,
    APPROVED,
    REJECTED
};

typedef enum {
    RED,
    GREEN,
    BLUE,
    YELLOW
} Color;

int main() {
    enum Status order_status = PENDING;
    Color favorite = BLUE;
    
    printf("Order status: %d\n", order_status);
    printf("Favorite color: %d\n", favorite);
    
    if (order_status == PENDING) {
        printf("Order is pending approval.\n");
    }
    
    return 0;
}
```

### Practical Example: State Machine

```c
#include <stdio.h>

typedef enum {
    IDLE,
    RUNNING,
    PAUSED,
    STOPPED
} State;

void printState(State s) {
    switch (s) {
        case IDLE:
            printf("System is idle\n");
            break;
        case RUNNING:
            printf("System is running\n");
            break;
        case PAUSED:
            printf("System is paused\n");
            break;
        case STOPPED:
            printf("System is stopped\n");
            break;
        default:
            printf("Unknown state\n");
    }
}

int main() {
    State current_state = IDLE;
    
    printState(current_state);
    
    current_state = RUNNING;
    printState(current_state);
    
    current_state = PAUSED;
    printState(current_state);
    
    return 0;
}
```

### Enum with Structures

```c
#include <stdio.h>

typedef enum {
    MALE,
    FEMALE,
    OTHER
} Gender;

typedef struct {
    char name[50];
    int age;
    Gender gender;
} Person;

int main() {
    Person p1 = {"Alice", 25, FEMALE};
    Person p2 = {"Bob", 30, MALE};
    
    printf("%s is ", p1.name);
    if (p1.gender == MALE) {
        printf("male\n");
    } else if (p1.gender == FEMALE) {
        printf("female\n");
    } else {
        printf("other\n");
    }
    
    return 0;
}
```

---

## Bit Fields

Bit fields allow you to specify the exact number of bits a structure member should occupy, enabling memory-efficient storage of flags and small integers.

### Syntax

```c
struct structure_name {
    data_type member1 : bit_width;
    data_type member2 : bit_width;
};
```

### Basic Example

```c
#include <stdio.h>

struct Flags {
    unsigned int is_active : 1;    // 1 bit
    unsigned int is_admin : 1;     // 1 bit
    unsigned int level : 3;        // 3 bits (0-7)
    unsigned int reserved : 3;     // 3 bits
};

int main() {
    struct Flags f;
    
    f.is_active = 1;
    f.is_admin = 0;
    f.level = 5;
    
    printf("Size of Flags: %lu byte(s)\n", sizeof(f));
    printf("Active: %u\n", f.is_active);
    printf("Admin: %u\n", f.is_admin);
    printf("Level: %u\n", f.level);
    
    return 0;
}
```

### Practical Use Case: Permissions System

```c
#include <stdio.h>

struct Permissions {
    unsigned int read : 1;
    unsigned int write : 1;
    unsigned int execute : 1;
    unsigned int delete : 1;
};

typedef struct {
    char username[50];
    struct Permissions perms;
} User;

void displayPermissions(User u) {
    printf("User: %s\n", u.username);
    printf("Permissions: ");
    if (u.perms.read) printf("R");
    if (u.perms.write) printf("W");
    if (u.perms.execute) printf("X");
    if (u.perms.delete) printf("D");
    printf("\n");
}

int main() {
    User admin = {"admin", {1, 1, 1, 1}};
    User guest = {"guest", {1, 0, 0, 0}};
    
    displayPermissions(admin);
    displayPermissions(guest);
    
    return 0;
}
```

### Limitations and Considerations

1. **Portability**: Bit field layout is implementation-dependent
2. **Cannot take address**: You cannot use `&` operator on bit fields
3. **Type restriction**: Typically use `unsigned int` or `int`
4. **No arrays**: Cannot create arrays of bit fields

```c
struct Example {
    unsigned int flag : 1;
};

int main() {
    struct Example e;
    // int *ptr = &e.flag;  // ERROR: Cannot take address
    
    return 0;
}
```

### Bit Field Example: Date Packing

```c
#include <stdio.h>

struct Date {
    unsigned int day : 5;      // 1-31 (needs 5 bits)
    unsigned int month : 4;    // 1-12 (needs 4 bits)
    unsigned int year : 12;    // 0-4095 (needs 12 bits)
};

int main() {
    struct Date d = {25, 12, 2024};
    
    printf("Size: %lu byte(s)\n", sizeof(d));  // Usually 4 bytes
    printf("Date: %02u/%02u/%u\n", d.day, d.month, d.year);
    
    // Without bit fields, this would take 12 bytes (4+4+4)
    return 0;
}
```

---

## Memory Layout and Padding

Understanding how structures are stored in memory helps optimize memory usage and performance.

### Structure Padding

The compiler may add padding bytes between structure members to ensure proper alignment for efficient memory access.

```c
#include <stdio.h>

struct Example1 {
    char c;      // 1 byte
    // 3 bytes padding
    int i;       // 4 bytes
    char d;      // 1 byte
    // 3 bytes padding
};

struct Example2 {
    char c;      // 1 byte
    char d;      // 1 byte
    // 2 bytes padding
    int i;       // 4 bytes
};

int main() {
    printf("Size of Example1: %lu bytes\n", sizeof(struct Example1));  // 12
    printf("Size of Example2: %lu bytes\n", sizeof(struct Example2));  // 8
    
    return 0;
}
```

### Visualizing Memory Layout

```c
// Example1 Memory Layout (12 bytes total):
// [c][pad][pad][pad][i][i][i][i][d][pad][pad][pad]
//  0  1   2   3   4 5 6 7  8  9   10  11

// Example2 Memory Layout (8 bytes total):
// [c][d][pad][pad][i][i][i][i]
//  0  1   2   3   4 5 6 7
```

### Using `#pragma pack` to Control Padding

```c
#include <stdio.h>

#pragma pack(1)  // No padding
struct Packed {
    char c;
    int i;
    char d;
};
#pragma pack()  // Restore default

struct Unpacked {
    char c;
    int i;
    char d;
};

int main() {
    printf("Packed size: %lu bytes\n", sizeof(struct Packed));      // 6
    printf("Unpacked size: %lu bytes\n", sizeof(struct Unpacked));  // 12
    
    return 0;
}
```

**Warning**: Packed structures may cause performance issues on some architectures due to unaligned memory access.

### Member Ordering for Optimal Memory Usage

```c
// Poor ordering (16 bytes with padding)
struct Poor {
    char a;      // 1 byte + 3 padding
    int b;       // 4 bytes
    char c;      // 1 byte + 3 padding
    int d;       // 4 bytes
};

// Better ordering (12 bytes with padding)
struct Better {
    int b;       // 4 bytes
    int d;       // 4 bytes
    char a;      // 1 byte
    char c;      // 1 byte
    // 2 bytes padding
};
```

---

## Best Practices

### 1. Use typedef for Cleaner Code

```c
// Good
typedef struct {
    int id;
    char name[50];
} Employee;

Employee emp1, emp2;
```

### 2. Initialize Structures Properly

```c
// Good: All members initialized
Student s1 = {101, "Alice", 85.5};

// Good: Designated initializers
Student s2 = {.roll_no = 102, .name = "Bob"};

// Avoid: Uninitialized structures (contains garbage values)
Student s3;  // Dangerous without initialization
```

### 3. Use const for Read-Only Structures

```c
void displayStudent(const Student *s) {
    printf("Name: %s\n", s->name);
    // s->marks = 100;  // Error: cannot modify const structure
}
```

### 4. Prefer Passing Pointers to Functions

```c
// Efficient: Pass by pointer (4 or 8 bytes)
void updateEmployee(Employee *emp) {
    emp->salary *= 1.1;
}

// Inefficient: Pass by value (copies entire structure)
void displayEmployee(Employee emp) {
    printf("Name: %s\n", emp.name);
}
```

### 5. Use Enums for Related Constants

```c
// Good
typedef enum {
    ERROR_NONE = 0,
    ERROR_FILE_NOT_FOUND = 1,
    ERROR_PERMISSION_DENIED = 2
} ErrorCode;

// Avoid magic numbers
// if (status == 2) { ... }  // What does 2 mean?
if (status == ERROR_PERMISSION_DENIED) { ... }  // Clear!
```

### 6. Document Structure Purpose

```c
/**
 * Represents a 2D point in Cartesian coordinates
 */
typedef struct {
    float x;  ///< X-coordinate
    float y;  ///< Y-coordinate
} Point;
```

### 7. Consider Memory Alignment

```c
// Optimize member ordering for smaller size
typedef struct {
    // Group same-sized members together
    double d;      // 8 bytes
    long l;        // 8 bytes
    int i;         // 4 bytes
    short s;       // 2 bytes
    char c1;       // 1 byte
    char c2;       // 1 byte
} OptimizedStruct;
```

### 8. Use Unions Carefully

```c
// Always track which member is valid
typedef struct {
    enum { INT_TYPE, FLOAT_TYPE } type;
    union {
        int i;
        float f;
    } value;
} TypedValue;
```

### 9. Validate Dynamic Allocation

```c
Student *students = (Student *)malloc(n * sizeof(Student));
if (students == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return 1;
}
// Use students...
free(students);
```

### 10. Use Self-Documenting Names

```c
// Good
typedef struct {
    int employee_id;
    char full_name[100];
    float annual_salary;
} EmployeeRecord;

// Avoid
typedef struct {
    int id;
    char n[100];
    float s;
} ER;
```

---

## Summary

### Structures
- Group related data of different types
- Each member has its own memory location
- Accessed using `.` operator (variable) or `->` operator (pointer)
- Can be nested, organized in arrays, and dynamically allocated

### Unions
- Share memory among all members
- Size equals largest member
- Only one member valid at a time
- Useful for memory-constrained scenarios

### Enumerations
- Named integer constants
- Improve code readability
- Useful for state machines, options, flags

### Bit Fields
- Specify exact bit width for members
- Memory-efficient for flags and small integers
- Implementation-dependent, limited portability

### Key Takeaways
1. Use structures to organize related data
2. Use typedef to simplify declarations
3. Pass structures to functions via pointers for efficiency
4. Understand memory layout and padding for optimization
5. Use unions when you need to store different types at different times
6. Use enums for named constants and better code clarity
7. Use bit fields for memory-critical applications with caution

---

## Practice Exercises

1. Create a structure to represent a book (title, author, price, pages) and write functions to display and update book information.

2. Implement a student database using an array of structures with functions to