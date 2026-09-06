/**
 * File Reading Program
 * 
 * This program demonstrates basic file I/O operations in C.
 * It opens a file named "existing.txt" in read mode and displays its contents
 * character by character to the console.
 * 
 * Return Values:
 *   - Returns 0 on successful execution (file opened and read successfully)
 *   - Returns 1 on error (file doesn't exist or cannot be opened)
 * 
 * Exit Codes Explanation:
 *   - return 0: Indicates SUCCESS - the program completed without errors
 *   - return 1: Indicates FAILURE/ERROR - the program encountered an error condition
 * 
 * By convention in C and most programming languages:
 *   - Return code 0 = success
 *   - Return code non-zero (1, 2, 3, etc.) = various error conditions
 * 
 * This allows the calling process or shell script to detect whether the program
 * executed successfully or encountered an error.
 */
#include <stdio.h>

int main(){

    // FILE pointer to hold file handle
    // fopen opens file "existing.txt" in read mode ("r")
    /**
     * FILE - Standard I/O stream type
     * 
     * FILE is a structure defined in <stdio.h> that represents a stream object.
     * It contains information necessary to control the stream, including:
     * - The file position indicator
     * - A buffer for data transfer
     * - EOF and error flags
     * - File descriptor
     * 
     * *fp - Pointer to FILE structure
     * 
     * fp is a pointer variable that holds the memory address of a FILE structure.
     * This pointer is used to:
     * - Identify and reference the opened file in subsequent I/O operations
     * - Pass the file reference to functions like fread(), fwrite(), fgets(), fclose()
     * - Manage the file stream throughout the program
     * 
     * Memory Layout:
     * 
     *    Stack              Heap
     *    ┌─────────┐        ┌──────────────────────┐
     *    │ fp      │───────→│ FILE structure       │
     *    │ (ptr)   │        ├──────────────────────┤
     *    └─────────┘        │ file descriptor      │
     *                       │ buffer               │
     *                       │ position indicator   │
     *                       │ EOF/error flags      │
     *                       └──────────────────────┘
     *                              ↓
     *                       existing.txt file
     * 
     * In this case:
     * - fopen("existing.txt", "r") opens the file "existing.txt" in read mode ("r")
     * - Returns a FILE* pointer if successful, or NULL if the file cannot be opened
     * - The pointer fp is used to perform read operations on the file
     * - Must be passed to fclose(fp) to properly close the file when done
     */
    FILE *fp = fopen("existing.txt", "r");

    // if condition checks if fopen failed (returns NULL on error)
    if (fp == NULL){
        // printf outputs error message to console
        printf("Error: File doesn't exist or cannot be opened\n");
        // return exits program with error code 1
        return 1;
    }

    // char variable to store each character from file
    char ch;
    
    // while loop continues until EOF (End Of File) is reached
    // fgetc reads one character at a time from file
    while ((ch = fgetc(fp)) != EOF){
        // printf outputs each character to console
        printf("%c", ch);
    }
    
    // fclose closes the file and frees the file pointer
    fclose(fp);

    // return exits program with success code 0
    return 0;
}