#include <stdio.h>
#include <string.h>

/**
 * typedef with Structures
 * 
 * The typedef keyword creates an alias for a data type, making code 
 * more readable and reducing verbosity.
 * 
 * Instead of writing: struct Student s1;
 * You can write:      Student s1;
 */

// ============================================
// Method 1: Without typedef (traditional way)
// ============================================
struct Student {
    int roll_no;
    char name[50];
    float marks;
};

// Must use "struct" keyword when declaring variables
struct Student student1, student2;


// ============================================
// Method 2: typedef with anonymous struct
// ============================================
typedef struct {
    int roll_no;
    char name[50];
    float marks;
} Student;

// No "struct" keyword needed - cleaner syntax
Student s1, s2;


// ============================================
// Method 3: typedef with named struct
// ============================================
struct Employee {
    int id;
    char name[50];
    float salary;
};

// Create typedef alias for existing struct
typedef struct Employee Employee;

// Now both forms work:
struct Employee emp1;  // Using struct keyword
Employee emp2;         // Using typedef alias


// ============================================
// Method 4: typedef with named struct (combined)
// ============================================
typedef struct Teacher {
    int id;
    char name[50];
    char subject[30];
} Teacher;

// Can use either form:
struct Teacher t1;  // Using struct keyword
Teacher t2;         // Using typedef alias


// ============================================
// Method 5: Nested structures with typedef
// ============================================
typedef struct {
    float x;
    float y;
} Point;

typedef struct {
    Point center;    // Nested structure
    float radius;
} Circle;

typedef struct {
    Point top_left;
    Point bottom_right;
} Rectangle;


// ============================================
// Method 6: Self-referential structures (linked lists, trees)
// ============================================
typedef struct Node {
    int data;
    struct Node* next;  // Must use "struct Node" here (forward reference)
} Node;


int main(void) {
    printf("=== Method 1: Without typedef ===\n");
    student1.roll_no = 101;
    strcpy(student1.name, "John Doe");
    student1.marks = 85.5f;
    printf("Roll No: %d, Name: %s, Marks: %.2f\n\n", 
           student1.roll_no, student1.name, student1.marks);
    
    
    printf("=== Method 2: typedef with anonymous struct ===\n");
    s1.roll_no = 201;
    strcpy(s1.name, "Jane Smith");
    s1.marks = 92.3f;
    printf("Roll No: %d, Name: %s, Marks: %.2f\n\n", 
           s1.roll_no, s1.name, s1.marks);
    
    
    printf("=== Method 3: typedef with named struct ===\n");
    emp1.id = 301;
    strcpy(emp1.name, "Bob Johnson");
    emp1.salary = 50000.0f;
    printf("ID: %d, Name: %s, Salary: %.2f\n\n", 
           emp1.id, emp1.name, emp1.salary);
    
    emp2.id = 302;
    strcpy(emp2.name, "Alice Brown");
    emp2.salary = 55000.0f;
    printf("ID: %d, Name: %s, Salary: %.2f\n\n", 
           emp2.id, emp2.name, emp2.salary);
    
    
    printf("=== Method 4: Combined typedef declaration ===\n");
    t1.id = 401;
    strcpy(t1.name, "Dr. Williams");
    strcpy(t1.subject, "Mathematics");
    printf("ID: %d, Name: %s, Subject: %s\n\n", 
           t1.id, t1.name, t1.subject);
    
    t2.id = 402;
    strcpy(t2.name, "Prof. Davis");
    strcpy(t2.subject, "Physics");
    printf("ID: %d, Name: %s, Subject: %s\n\n", 
           t2.id, t2.name, t2.subject);
    
    
    printf("=== Method 5: Nested structures ===\n");
    // Initialize Circle with nested Point
    Circle c1 = {{0.0f, 0.0f}, 5.0f};
    printf("Circle center: (%.1f, %.1f)\n", c1.center.x, c1.center.y);
    printf("Circle radius: %.1f\n\n", c1.radius);
    
    // Initialize Circle using designated initializers
    Circle c2 = {
        .center = {10.0f, 20.0f},
        .radius = 7.5f
    };
    printf("Circle center: (%.1f, %.1f)\n", c2.center.x, c2.center.y);
    printf("Circle radius: %.1f\n\n", c2.radius);
    
    // Rectangle with nested Points
    Rectangle rect = {
        .top_left = {1.0f, 5.0f},
        .bottom_right = {10.0f, 1.0f}
    };
    printf("Rectangle top-left: (%.1f, %.1f)\n", 
           rect.top_left.x, rect.top_left.y);
    printf("Rectangle bottom-right: (%.1f, %.1f)\n\n", 
           rect.bottom_right.x, rect.bottom_right.y);
    
    
    printf("=== Method 6: Self-referential structures ===\n");
    Node node1, node2, node3;
    
    node1.data = 10;
    node1.next = &node2;
    
    node2.data = 20;
    node2.next = &node3;
    
    node3.data = 30;
    node3.next = NULL;
    
    // Traverse the linked list
    Node* current = &node1;
    printf("Linked List: ");
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("\n");
    
    return 0;
}
