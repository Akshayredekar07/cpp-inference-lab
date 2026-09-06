#include <stdio.h>      // Standard Input/Output library
#include <stdlib.h>     // Standard library for exit()

int main() {
    FILE *fp;           // Pointer to FILE structure
    char filename[100]; // Array to store filename
    
    printf("Enter filename: ");
    scanf("%s", filename);  // Read filename from user
    
    // Open file in write mode
    fp = fopen(filename, "w");  // fopen: opens file, "w": write mode
    
    if(fp == NULL) {    // Check if file opening failed
        fprintf(stderr, "Cannot open file '%s'\n", filename);  // Print error to stderr
        exit(EXIT_FAILURE);  // Exit program with failure code
    }
    
    // Write data to file using fprintf
    fprintf(fp, "Line 1: File handling in C\n");
    fprintf(fp, "Line 2: fopen and fclose functions\n");
    fprintf(fp, "Line 3: Example completed\n");
    
    // Close file - fclose flushes buffer and closes file stream
    if(fclose(fp) != 0) {  // Check if closing failed
        fprintf(stderr, "Error closing file\n");
        exit(EXIT_FAILURE);
    }
    
    printf("Data written and file closed successfully\n");
    
    return 0;  // Return 0 to indicate successful execution
}