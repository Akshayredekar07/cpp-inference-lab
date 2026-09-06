#include <stdio.h>
#include <string.h>

struct Student {
    int rollNo;
    char name[50];
    float marks;
};

// Function to write student records
void writeStudents() {
    FILE *fp;
    struct Student s;
    int n, i;
    
    fp = fopen("students.txt", "w");
    if(fp == NULL) {
        printf("Error opening file for writing\n");
        return;
    }
    
    printf("Enter number of students: ");
    scanf("%d", &n);
    
    for(i = 0; i < n; i++) {
        printf("\nStudent %d:\n", i+1);
        printf("Roll Number: ");
        scanf("%d", &s.rollNo);
        getchar(); // consume the newline left by scanf
        printf("Name: ");
        fgets(s.name, sizeof(s.name), stdin);
        s.name[strcspn(s.name, "\n")] = 0; // remove trailing newline
        printf("Marks: ");
        scanf("%f", &s.marks);
         
        fprintf(fp, "%d|%s|%.2f\n", s.rollNo, s.name, s.marks);
    }
    
    fclose(fp);
    printf("\nRecords saved successfully!\n");
}

// Function to read and display student records
void readStudents() {
    FILE *fp;
    struct Student s;
    
    fp = fopen("students.txt", "r");
    if(fp == NULL) {
        printf("Error opening file for reading\n");
        return;
    }
    
    printf("\n%-10s %-20s %-10s\n", "Roll No", "Name", "Marks");
    printf("==========================================\n");
    
    while(fscanf(fp, "%d|%49[^|]|%f", &s.rollNo, s.name, &s.marks) != EOF) {
        printf("%-10d %-20s %-10.2f\n", s.rollNo, s.name, s.marks);
    }
    
    fclose(fp);
}

int main() {
    int choice;
    
    while(1) {
        printf("\n=== Student Record System ===\n");
        printf("1. Write Student Records\n");
        printf("2. Read Student Records\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                writeStudents();
                break;
            case 2:
                readStudents();
                break;
            case 3:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
    
    return 0;
}