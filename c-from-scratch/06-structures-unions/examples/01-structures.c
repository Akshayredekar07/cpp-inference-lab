#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/// Basic structure definition with all members
struct Student {
    int roll_no;
    char name[50];
    float marks;
    char grade;
};

/// Example of an anonymous struct type with variables declared immediately
/// (You CANNOT declare more variables of this type later, because it has no name)
struct {
    int x;
    int y;
} point1, point2;

/// Global variables of type struct Student, initialized in different ways

// Method 1: Positional initialization during declaration
struct Student g_s1 = {101, "John Doe", 85.5f, 'A'};

// Method 2: Designated initializers (C99 and later)
struct Student g_s2 = {
    .roll_no = 102,
    .name    = "Jane Smith",
    .marks   = 92.3f,
    .grade   = 'A'
};

// Method 3: Partial initialization (remaining members set to 0 / '\0')
struct Student g_s3 = {103};  // roll_no = 103, name[0] = '\0', marks = 0.0f, grade = '\0'


int main(void) {
    /// Local variables of type struct Student

    // Method 1: Positional initialization in main
    struct Student s1 = {1, "John", 90.0f, 'A'};
    printf("Student 1:\n");
    printf("  Roll No: %d\n", s1.roll_no);
    printf("  Name   : %s\n", s1.name);
    printf("  Marks  : %.2f\n", s1.marks);
    printf("  Grade  : %c\n\n", s1.grade);

    // Method 2: Designated initialization in main
    struct Student s2 = {
        .roll_no = 2,
        .name    = "Jane",
        .marks   = 85.0f,
        .grade   = 'B'
    };
    printf("Student 2:\n");
    printf("  Roll No: %d\n", s2.roll_no);
    printf("  Name   : %s\n", s2.name);
    printf("  Marks  : %.2f\n", s2.marks);
    printf("  Grade  : %c\n\n", s2.grade);

    // Method 3: Declare first, then assign members one by one
    struct Student s3;
    s3.roll_no = 3;
    strcpy(s3.name, "Alice");
    s3.marks = 78.5f;
    s3.grade = 'C';

    printf("Student 3:\n");
    printf("  Roll No: %d\n", s3.roll_no);
    printf("  Name   : %s\n", s3.name);
    printf("  Marks  : %.2f\n", s3.marks);
    printf("  Grade  : %c\n\n", s3.grade);

    // Using the anonymous struct variables
    point1.x = 10;
    point1.y = 20;
    point2.x = 30;
    point2.y = 40;

    printf("Point1: (%d, %d)\n", point1.x, point1.y);
    printf("Point2: (%d, %d)\n", point2.x, point2.y);

    return 0;
}