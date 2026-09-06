#include <stdio.h>

int main() {
    FILE *fp;
    int rollNo;
    char name[50];
    float marks;
    
    fp = fopen("students.txt", "r");
    if(fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    
    printf("Student Records:\n");
    printf("================\n");
    
    // Read formatted data
    while(fscanf(fp, "%d %s %f", &rollNo, name, &marks) != EOF) {
        printf("Roll: %d, Name: %s, Marks: %.2f\n", rollNo, name, marks);
    }
    
    fclose(fp);
    return 0;
}