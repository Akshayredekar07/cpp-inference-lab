#include <stdio.h>
#include <string.h>

/**
 * Accessing Structure Members
 * 
 * Structure members are accessed using the dot operator (.)
 * Syntax: structure_variable.member_name
 */

struct Student {
    int roll_no;
    char name[50];
    float marks;
};

int main(void) {
    // ============================================
    // Method 1: Declare first, then assign members individually
    // ============================================
    struct Student s1;
    
    // Assigning values using dot operator
    s1.roll_no = 101;
    strcpy(s1.name, "Alice Johnson");
    s1.marks = 88.5f;
    
    // Accessing and displaying values
    printf("=== Method 1: Individual Assignment ===\n");
    printf("Roll No: %d\n", s1.roll_no);
    printf("Name   : %s\n", s1.name);
    printf("Marks  : %.2f\n\n", s1.marks);
    
    
    // ============================================
    // Method 2: Initialize during declaration (positional)
    // ============================================
    struct Student s2 = {102, "Bob Smith", 92.5f};
    
    printf("=== Method 2: Positional Initialization ===\n");
    printf("Roll No: %d\n", s2.roll_no);
    printf("Name   : %s\n", s2.name);
    printf("Marks  : %.2f\n\n", s2.marks);
    
    
    // ============================================
    // Method 3: Initialize using designated initializers (C99)
    // ============================================
    struct Student s3 = {
        .roll_no = 103,
        .name = "Charlie Brown",
        .marks = 87.0f
    };
    
    printf("=== Method 3: Designated Initializers ===\n");
    printf("Roll No: %d\n", s3.roll_no);
    printf("Name   : %s\n", s3.name);
    printf("Marks  : %.2f\n\n", s3.marks);
    
    
    // ============================================
    // Method 4: Modify members after initialization
    // ============================================
    struct Student s4 = {104, "Diana Prince", 95.0f};
    
    printf("=== Method 4: Modifying Members ===\n");
    printf("Before modification:\n");
    printf("Roll No: %d, Marks: %.2f\n", s4.roll_no, s4.marks);
    
    // Modify individual members
    s4.marks = 98.5f;  // Update marks
    s4.roll_no = 105;  // Update roll number
    
    printf("After modification:\n");
    printf("Roll No: %d, Marks: %.2f\n\n", s4.roll_no, s4.marks);
    
    
    // ============================================
    // Method 5: Copy structure using assignment
    // ============================================
    struct Student s5;
    s5 = s1;  // Copy all members from s1 to s5
    
    printf("=== Method 5: Structure Copy ===\n");
    printf("s5 (copied from s1):\n");
    printf("Roll No: %d\n", s5.roll_no);
    printf("Name   : %s\n", s5.name);
    printf("Marks  : %.2f\n\n", s5.marks);
    
    
    // ============================================
    // Method 6: Using members in expressions
    // ============================================
    printf("=== Method 6: Using Members in Expressions ===\n");
    float average = (s1.marks + s2.marks + s3.marks) / 3.0f;
    printf("Average marks of s1, s2, s3: %.2f\n", average);
    
    // Conditional access
    if (s1.marks > 90.0f) {
        printf("%s has excellent marks!\n", s1.name);
    }
    
    return 0;
}