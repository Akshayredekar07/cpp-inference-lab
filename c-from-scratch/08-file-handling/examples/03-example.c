/**
 * File Appending Program
 * 
 * This program demonstrates basic file I/O operations in C.
 * It opens a file named "output.txt" in append mode and writes content to it.
 * NOTE: Opening a file in append mode ("a") preserves all previous content!
 * 
 * Return Values:
 *   - Returns 0 on successful execution (file opened and written successfully)
 *   - Returns 1 on error (file cannot be created or opened)
 */
#include <stdio.h>

int main() {
    
    FILE *fp = fopen("output.txt", "a");  // Changed "w" to "a" for append mode
    
    if(fp == NULL) {
        printf("Error: Cannot open file\n");
        return 1;
    }
    
    // fprintf writes formatted text to the file
    // In append mode, this adds content to the end of existing data
    fprintf(fp, "This is appended content\n");
    fprintf(fp, "Previous data is preserved\n");
    
    // fclose closes the file and frees the file pointer
    fclose(fp);
    
    return 0;
}
