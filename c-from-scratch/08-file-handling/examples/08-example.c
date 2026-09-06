#include <stdio.h>

int main() {
    FILE *fp;
    char ch;
    int count = 0;
    
    fp = fopen("sample.txt", "r");
    if(fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    
    printf("File contents:\n");
    
    // Read until end of file
    while((ch = fgetc(fp)) != EOF) {
        printf("%c", ch);
        count++;
    }
    
    printf("Total characters: %d\n", count);
    
    fclose(fp);
    return 0;
}