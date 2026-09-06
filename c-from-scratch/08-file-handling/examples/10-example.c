#include <stdio.h>

int main() {
    FILE *fp;
    char line[200];
    int lineNumber = 1;
    int maxLines = 5;
    
    fp = fopen("data.txt", "r");
    if(fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    
    printf("First %d lines:\n", maxLines);
    
    while(fgets(line, sizeof(line), fp) != NULL && lineNumber <= maxLines) {
        printf("%d: %s", lineNumber, line);
        lineNumber++;
    }
    /**
     * Reads and displays lines from a file with line numbers
     * 
     * This loop iterates through a file, reading one line at a time using fgets(),
     * printing each line with its corresponding line number, until either:
     * - EOF (End Of File) is reached, OR
     * - The maximum number of lines (maxLines) is displayed
     * 
     * DRY RUN EXAMPLE:
     * ----------------
     * Assume: maxLines = 3, file contains:
     *   "Hello"
     *   "World"
     *   "Example"
     *   "Extra"
     * 
     * Iteration 1: lineNumber=1, fgets() reads "Hello"
     *              Output: "1: Hello"
     *              lineNumber becomes 2
     * 
     * Iteration 2: lineNumber=2, fgets() reads "World"
     *              Output: "2: World"
     *              lineNumber becomes 3
     * 
     * Iteration 3: lineNumber=3, fgets() reads "Example"
     *              Output: "3: Example"
     *              lineNumber becomes 4
     * 
     * Iteration 4: Loop condition fails (lineNumber 4 > maxLines 3)
     *              Loop terminates, "Extra" is NOT printed
     * 
     * Parameters:
     *   line - Buffer to store each line read from file
     *   sizeof(line) - Maximum bytes to read per line
     *   fp - File pointer to read from
     *   lineNumber - Current line counter (incremented each iteration)
     *   maxLines - Maximum number of lines to display
     */
    
    fclose(fp);
    return 0;
}