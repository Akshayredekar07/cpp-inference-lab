/**
 * FILE POINTER EXPLANATION
 * ========================
 * 
 * A file pointer is an internal position indicator that tracks the current location
 * within a file where read/write operations will occur.
 * 
 * WHAT IS A FILE POINTER?
 * -----------------------
 * The file pointer (also called file offset or file position indicator) is a special
 * marker maintained by the operating system that keeps track of:
 * - WHERE you are currently reading from or writing to in the file
 * - HOW MANY BYTES have been processed since the file was opened
 * 
 * HOW IT WORKS IN THIS CODE:
 * --------------------------
 * 1. fopen("data.txt", "r+") → File pointer starts at position 0 (beginning of file)
 * 
 * 2. fgets(buffer, 100, fp) → 
 *    - Reads up to 100 characters FROM the current file pointer position
 *    - AUTOMATICALLY moves the file pointer to the end of what was read
 *    - Example: If "Hello\n" is 6 bytes, pointer moves from 0 → 6
 * 
 * 3. fprintf(fp, "Modified") → 
 *    - Writes "Modified" STARTING FROM the current file pointer position (position 6)
 *    - Overwrites existing content from that position onward
 *    - File pointer moves to position 6 + 8 (length of "Modified")
 * 
 * 4. fclose(fp) → Closes file and discards the file pointer
 * 
 * VISUAL EXAMPLE:
 * ---------------
 * Original file: "Hello World\n More text here"
 *                 ^^^^^^^ (6 bytes, pointer was here)
 * 
 * After fgets(): Pointer at position 6
 * After fprintf(): "Hello ModifiedMore text here"
 *                   ^^^^^^^^^^ (overwrites from position 6)
 * 
 * KEY POINTS:
 * - File pointer automatically advances after read/write operations
 * - You can manually control it using fseek() function
 * - Different for each open file handle
 * - Exists only while file is open (reset when reopened)
 */
/**
 * File Operations Example - Read and Modify File Content
 * 
 * This program demonstrates how to open an existing file in read-update mode ("r+"),
 * read its content, and then modify it by writing new data at the current file position.
 * 
 * BUFFER EXPLANATION:
 * -------------------
 * buffer: A character array of size 100 bytes used to store data read from the file.
 * 
 * HOW BUFFER WORKS:
 * - It acts as temporary storage (memory location) to hold string data
 * - Size [100]: Can hold up to 99 characters + 1 null terminator ('\0')
 * - fgets() reads from the file and stores the read data into this buffer
 * 
 * HOW BUFFER IS USED IN THIS CODE:
 * - fgets(buffer, 100, fp): Reads up to 99 characters from file into buffer
 *   and includes the newline character if present
 * - The buffer stores the string temporarily in RAM
 * - printf("Read: %s", buffer): Displays the contents stored in buffer
 * - After reading, the file pointer moves to the end of the read data
 * - fprintf() then writes "Modified" from this current position, overwriting
 *   whatever content comes after the original line
 * 
 * WORKFLOW:
 * 1. Open file in "r+" mode (read and update existing file)
 * 2. Read first line into buffer (max 100 chars)
 * 3. Display buffer contents to console
 * 
 * 4. Write new content starting from current file position
 * 5. Close file
 * 
 * NOTE: File must exist beforehand. Use fopen() return value check to handle errors.
 */
#include <stdio.h>

int main() {
    FILE *fp = fopen("data.txt", "r+");
    
    if(fp == NULL) {
        printf("Error: File must exist\n");
        return 1;
    }
    
    // Read existing content
    char buffer[100];
    fgets(buffer, 100, fp);
    printf("Read: %s", buffer);
    
    // Write new content (overwrites from current position)
    fprintf(fp, "Modified");
    
    fclose(fp);
    return 0;
}