#include <stdio.h>
#include <string.h>

/**
 * Array of Structures and Nested Structures
 * 
 * This file demonstrates:
 * 1. Array of structures - declaring, initializing, and accessing
 * 2. Nested structures - structures within structures
 */

// ============================================
// PART 1: Array of Structures
// ============================================

// Structure definition
struct Student {
    int roll_no;
    char name[50];
    float marks;
};

// Example 1: Array declaration and initialization
void example1_array_initialization(void) {
    printf("=== Example 1: Array Initialization ===\n");
    
    // Array declaration with initialization
    struct Student class[3] = {
        {101, "Alice", 85.5f},
        {102, "Bob", 78.2f},
        {103, "Charlie", 92.0f}
    };
    
    // Access first student
    printf("First student - Name: %s\n", class[0].name);
    printf("First student - Roll No: %d, Marks: %.2f\n\n", 
           class[0].roll_no, class[0].marks);
    
    // Access third student's marks
    printf("Third student - Name: %s, Marks: %.2f\n\n", 
           class[2].name, class[2].marks);
    
    // Display all students
    printf("All Students:\n");
    for (int i = 0; i < 3; i++) {
        printf("  [%d] Roll No: %d, Name: %s, Marks: %.2f\n",
               i, class[i].roll_no, class[i].name, class[i].marks);
    }
    printf("\n");
}


// Example 2: Array with user input
void example2_array_user_input(void) {
    printf("=== Example 2: Array with User Input ===\n");
    
    typedef struct {
        int roll_no;
        char name[50];
        float marks;
    } Student;
    
    Student class[100];
    int n;
    
    printf("Enter number of students (max 100): ");
    scanf("%d", &n);
    
    if (n > 100 || n <= 0) {
        printf("Invalid number of students!\n\n");
        return;
    }
    
    // Input student data
    for (int i = 0; i < n; i++) {
        printf("\nStudent %d:\n", i + 1);
        printf("  Roll No: ");
        scanf("%d", &class[i].roll_no);
        printf("  Name: ");
        scanf("%s", class[i].name);
        printf("  Marks: ");
        scanf("%f", &class[i].marks);
    }
    
    // Display all students
    printf("\n--- Student Records ---\n");
    for (int i = 0; i < n; i++) {
        printf("\nStudent %d:\n", i + 1);
        printf("  Roll No: %d\n", class[i].roll_no);
        printf("  Name   : %s\n", class[i].name);
        printf("  Marks  : %.2f\n", class[i].marks);
    }
    
    // Find highest marks
    if (n > 0) {
        float max = class[0].marks;
        int top_index = 0;
        for (int i = 1; i < n; i++) {
            if (class[i].marks > max) {
                max = class[i].marks;
                top_index = i;
            }
        }
        
        printf("\n--- Topper ---\n");
        printf("Name: %s\n", class[top_index].name);
        printf("Roll No: %d\n", class[top_index].roll_no);
        printf("Marks: %.2f\n\n", class[top_index].marks);
    }
}


// Example 3: Array operations
void example3_array_operations(void) {
    printf("=== Example 3: Array Operations ===\n");
    
    typedef struct {
        int roll_no;
        char name[50];
        float marks;
    } Student;
    
    Student students[5] = {
        {101, "Alice", 85.5f},
        {102, "Bob", 78.2f},
        {103, "Charlie", 92.0f},
        {104, "Diana", 88.0f},
        {105, "Eve", 95.5f}
    };
    
    int n = 5;
    
    // Calculate average marks
    float sum = 0.0f;
    for (int i = 0; i < n; i++) {
        sum += students[i].marks;
    }
    float average = sum / n;
    printf("Average marks: %.2f\n", average);
    
    // Count students above average
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (students[i].marks > average) {
            count++;
        }
    }
    printf("Students above average: %d\n\n", count);
}


// ============================================
// PART 2: Nested Structures
// ============================================

// Example 4: Basic nested structure
void example4_basic_nested(void) {
    printf("=== Example 4: Basic Nested Structure ===\n");
    
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
    
    // Declare and initialize
    struct Employee emp1;
    emp1.emp_id = 1001;
    strcpy(emp1.name, "John Smith");
    emp1.salary = 50000.0f;
    emp1.join_date.day = 15;
    emp1.join_date.month = 8;
    emp1.join_date.year = 2020;
    
    // Accessing values
    printf("Employee ID: %d\n", emp1.emp_id);
    printf("Name: %s\n", emp1.name);
    printf("Salary: %.2f\n", emp1.salary);
    printf("Joining Date: %d/%d/%d\n\n",
           emp1.join_date.day,
           emp1.join_date.month,
           emp1.join_date.year);
    
    // Initialize during declaration
    struct Employee emp2 = {
        1002,
        "Jane Doe",
        55000.0f,
        {20, 3, 2021}  // Nested structure initialization
    };
    
    printf("Employee ID: %d\n", emp2.emp_id);
    printf("Name: %s\n", emp2.name);
    printf("Joining Date: %d/%d/%d\n\n",
           emp2.join_date.day,
           emp2.join_date.month,
           emp2.join_date.year);
}


// Example 5: Multiple nested structures with typedef
void example5_multiple_nested(void) {
    printf("=== Example 5: Multiple Nested Structures ===\n");
    
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
    
    // Initialize using positional initializers
    Person p1 = {
        "John Doe",
        30,
        {123, "Main St", "New York", 10001},  // home address
        {456, "Park Ave", "New York", 10002}  // office address
    };
    
    printf("Name: %s\n", p1.name);
    printf("Age: %d\n", p1.age);
    printf("Home Address: %d %s, %s - %d\n",
           p1.home.house_no, p1.home.street,
           p1.home.city, p1.home.pincode);
    printf("Office Address: %d %s, %s - %d\n\n",
           p1.office.house_no, p1.office.street,
           p1.office.city, p1.office.pincode);
    
    // Initialize using designated initializers
    Person p2 = {
        .name = "Alice Johnson",
        .age = 28,
        .home = {
            .house_no = 789,
            .street = "Broadway",
            .city = "Boston",
            .pincode = 02101
        },
        .office = {
            .house_no = 321,
            .street = "State St",
            .city = "Boston",
            .pincode = 02102
        }
    };
    
    printf("Name: %s\n", p2.name);
    printf("Home: %d %s, %s - %d\n",
           p2.home.house_no, p2.home.street,
           p2.home.city, p2.home.pincode);
    printf("Office: %d %s, %s - %d\n\n",
           p2.office.house_no, p2.office.street,
           p2.office.city, p2.office.pincode);
}


// Example 6: Array of nested structures
void example6_array_nested(void) {
    printf("=== Example 6: Array of Nested Structures ===\n");
    
    typedef struct {
        int day;
        int month;
        int year;
    } Date;
    
    typedef struct {
        int emp_id;
        char name[50];
        float salary;
        Date join_date;
    } Employee;
    
    // Array of employees with nested dates
    Employee employees[3] = {
        {1001, "Alice", 50000.0f, {15, 1, 2020}},
        {1002, "Bob", 55000.0f, {20, 3, 2021}},
        {1003, "Charlie", 60000.0f, {10, 6, 2022}}
    };
    
    printf("Employee Records:\n");
    for (int i = 0; i < 3; i++) {
        printf("\nEmployee %d:\n", i + 1);
        printf("  ID: %d\n", employees[i].emp_id);
        printf("  Name: %s\n", employees[i].name);
        printf("  Salary: %.2f\n", employees[i].salary);
        printf("  Join Date: %d/%d/%d\n",
               employees[i].join_date.day,
               employees[i].join_date.month,
               employees[i].join_date.year);
    }
    printf("\n");
}


// ============================================
// Main Function
// ============================================
int main(void) {
    // Array of Structures examples
    example1_array_initialization();
    
    // Uncomment to test user input (requires input)
    // example2_array_user_input();
    
    example3_array_operations();
    
    // Nested Structures examples
    example4_basic_nested();
    example5_multiple_nested();
    example6_array_nested();
    
    return 0;
}
