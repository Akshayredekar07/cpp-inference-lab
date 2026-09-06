#include <stdio.h>
#include <stdlib.h>

int main() {
    
    FILE *fp;
    
    // Open "myfile.txt" in write mode ("w")
    // If file doesn't exist, it creates a new one
    // If file exists, it truncates (clears) the content
    fp = fopen("myfile.txt", "w");

    if(fp == NULL){
        printf("Error opening file\n");
        perror("Error");  // Prints system error message
        exit(1);  // Exit program with error code 1
    }

    printf("File opened successful!");

    // fprintf - Write formatted text to file
    // Similar to printf(), but writes to file instead of console
    // "Hello file\n" is the string written to the file
    fprintf(fp, "Hello file\n");

    // Close the file to free resources and ensure data is saved
    fclose(fp);
    
    return 0; 
}
