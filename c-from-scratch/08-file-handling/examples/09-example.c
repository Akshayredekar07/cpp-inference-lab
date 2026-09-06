#include <stdio.h>

int main() {
    FILE *fp;
    char line[256];
    
    fp = fopen("poem.txt", "r");
    if(fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    
    printf("File contents:\n");
    printf("================\n");
    
    // DRY RUN:
    // 1. fp points to poem.txt file in read mode
    // 2. Check if file opened successfully (fp != NULL)
    // 3. Print header "File contents:\n" and separator "================\n"
    // 4. Loop through file line by line:
    //    - fgets reads max 255 chars (or until newline) into 'line'
    //    - Continue while fgets doesn't return NULL (EOF or error)
    //    - printf prints current line (newline already in 'line' from fgets)
    // 5. When fgets returns NULL, exit loop
    // 6. Close file with fclose(fp)
    // 7. Return 0 (success)
    
    while(fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
    }
    
    fclose(fp);
    return 0;
}
