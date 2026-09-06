/**
 * File Writing Program
 * 
 * This program demonstrates basic file I/O operations in C.
 * It opens a file named "output.txt" in write mode and writes content to it.
 * WARNING: Opening a file in write mode ("w") erases all previous content!
 * 
 * Return Values:
 *   - Returns 0 on successful execution (file opened and written successfully)
 *   - Returns 1 on error (file cannot be created or opened)
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

int main() {
    
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
     * - Pass the file reference to functions like fprintf(), fwrite(), fclose()
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
     *                       output.txt file
     * 
     * In this case:
     * - fopen("output.txt", "w") opens the file "output.txt" in write mode ("w")
     * - Returns a FILE* pointer if successful, or NULL if the file cannot be created
     * - The pointer fp is used to perform write operations on the file
     * - Must be passed to fclose(fp) to properly close the file when done
     */
    FILE *fp = fopen("output.txt", "w");
    
    // if condition checks if fopen failed (returns NULL on error)
    // NOTE: Logic error detected! Condition should be (fp == NULL), not (fp != NULL)
    /*
     * Check if file pointer is NULL, indicating that fopen() failed to create/open the file.
     * This condition evaluates to true when fp == NULL, meaning the file operation was unsuccessful.
     * Possible reasons for failure include:
     * - Invalid file path or filename
     * - Insufficient permissions to create/write to the file
     * - Disk is full or read-only
     * - File descriptor limit reached
     * If the condition is true, an error message is printed and the function returns 1 (error code).
     */
    if(fp == NULL) {
        printf("Error: Cannot create file\n");
        return 1;
    }
    
    // fprintf writes formatted text to the file
    // WARNING: This erases all previous content in "output.txt"!
    fprintf(fp, "This is new content\n");
    fprintf(fp, "Previous data is lost\n");
    
    // fclose closes the file and frees the file pointer
    fclose(fp);
    
    // return exits program with success code 0
    return 0;
}