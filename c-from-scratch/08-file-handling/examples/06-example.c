#include <stdio.h>

int main() {
    FILE *fp = fopen("test.txt", "w");
    
    if(fp == NULL) {
        return 1;
    }
    
    fprintf(fp, "Important data");
    
    // Close the file
    if(fclose(fp) == EOF) {
        printf("Error closing file\n");
        return 1;
    }
    
    printf("File closed successfully\n");
    return 0;
}