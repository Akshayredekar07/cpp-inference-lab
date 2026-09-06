/**
 * Structure Pointers, Dynamic Allocation and Self-Referential Structures
 *
 * This file demonstrates:
 * 1. Using pointers with structures
 * 2. Dynamically allocating memory for an array of structures
 * 3. Self-referential structures (simple linked list)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================
// PART 1: Pointers to Structures
// ============================================

// Structure definition
typedef struct {
    int id;
    char name[50];
    float salary;
} Employee;

// Display employee details using a pointer
void example1_display_employee(const Employee *emp) {
    printf("ID    : %d\n", emp->id);
    printf("Name  : %s\n", emp->name);
    printf("Salary: %.2f\n", emp->salary);
}

// Give a percentage raise to an employee using a pointer
void example1_give_raise(Employee *emp, float percentage) {
    emp->salary += emp->salary * (percentage / 100.0f);
}

// Example 1: Basic pointer-to-structure usage
void example1_pointer_to_structure(void) {
    printf("=== Example 1: Pointer to Structure ===\n");

    Employee emp1 = {1001, "John Smith", 50000.0f};
    Employee *ptr = &emp1;  // pointer to structure

    printf("Before raise:\n");
    example1_display_employee(ptr);

    example1_give_raise(ptr, 10.0f);  // 10%% raise

    printf("\nAfter 10%% raise:\n");
    example1_display_employee(ptr);
    printf("\n");
}


// ============================================
// PART 2: Dynamic Memory Allocation for Structures
// ============================================

typedef struct {
    int roll_no;
    char name[50];
    float marks;
} Student;

// Example 2: Dynamically allocated array of structures
void example2_dynamic_students(void) {
    printf("=== Example 2: Dynamic Array of Students ===\n");

    Student *ptr = NULL;
    int n;

    printf("Enter number of students: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of students.\n\n");
        return;
    }

    // Allocate memory for n students
    ptr = (Student *)malloc((size_t)n * sizeof(Student));
    if (ptr == NULL) {
        printf("Memory allocation failed!\n\n");
        return;
    }

    // Input data
    for (int i = 0; i < n; i++) {
        printf("\nStudent %d:\n", i + 1);
        printf("  Roll No: ");
        scanf("%d", &(ptr + i)->roll_no);

        printf("  Name   : ");
        scanf("%49s", (ptr + i)->name);  // limit to avoid overflow

        printf("  Marks  : ");
        scanf("%f", &(ptr + i)->marks);
    }

    // Display data
    printf("\n--- Student Records ---\n");
    for (int i = 0; i < n; i++) {
        printf("\nStudent %d:\n", i + 1);
        printf("  Roll No: %d\n", (ptr + i)->roll_no);
        printf("  Name   : %s\n", (ptr + i)->name);
        printf("  Marks  : %.2f\n", (ptr + i)->marks);
    }
    printf("\n");

    // Free allocated memory
    free(ptr);
}


// ============================================
// PART 3: Self-Referential Structures (Linked List)
// ============================================

typedef struct Node {
    int data;
    struct Node *next;  // Pointer to next node
} Node;

// Example 3: Simple linked list with three nodes
void example3_linked_list(void) {
    printf("=== Example 3: Self-Referential Structure (Linked List) ===\n");

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
    printf("NULL\n\n");
}


int main(void) {
    // Pointer to Structure example
    example1_pointer_to_structure();

    // Dynamic allocation for array of Students
    example2_dynamic_students();

    // Self-referential structure example (linked list)
    example3_linked_list();

    return 0;
}

