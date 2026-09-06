# File Handling in C

## Table of Contents
1. Introduction to File Handling
2. File Pointers
3. File Modes
4. Opening and Closing Files
5. Reading from Files
6. Writing to Files
7. File Positioning Functions
8. Error Handling with Files
9. Practice Problems with Solutions

---

## 1. Introduction to File Handling

### What is File Handling?

File handling in C allows programs to store data permanently on the disk. Unlike variables that lose their data when the program terminates, files preserve information for future use. This is essential for applications that need to maintain data across multiple program executions.

### Why Do We Need File Handling?

- **Permanent Storage**: Data persists even after program termination
- **Large Data Management**: Handle data too large to fit in memory
- **Data Sharing**: Multiple programs can access the same data
- **Backup and Recovery**: Create backups of important information
- **Logging**: Track program execution and errors

### Types of Files

1. **Text Files**: Store data in human-readable ASCII/Unicode format
   - Example: .txt, .c, .csv files
   - Can be opened and read with any text editor
   
2. **Binary Files**: Store data in binary format (0s and 1s)
   - Example: .exe, .bin, .dat files
   - More efficient in terms of storage and speed
   - Not human-readable

---

## 2. File Pointers

### What is a File Pointer?

A file pointer is a special pointer that points to a structure containing information about a file. It's defined in the `stdio.h` header file and is of type `FILE*`.

### Syntax:
```c
FILE *file_pointer;
```

### What Does a File Pointer Store?

The FILE structure contains:
- Current position in the file
- Buffer information
- Mode of file access
- Error indicators
- End-of-file indicator

### Example:
```c
#include <stdio.h>

int main() {
    FILE *fp;  // Declaration of file pointer
    
    // fp will point to a file after fopen() is called
    fp = fopen("example.txt", "r");
    
    if(fp == NULL) {
        printf("File could not be opened\n");
        return 1;
    }
    
    printf("File opened successfully\n");
    fclose(fp);
    
    return 0;
}
```

**Explanation**: 
- `FILE *fp` declares a file pointer named `fp`
- This pointer will be used to perform all file operations
- Without a file pointer, we cannot access files in C

---

## 3. File Modes

File modes specify how a file should be opened and what operations can be performed on it.

### Text File Modes

| Mode | Description | File Exists | File Doesn't Exist |
|------|-------------|-------------|-------------------|
| `"r"` | Read only | Opens file | Returns NULL |
| `"w"` | Write only | Truncates to zero length | Creates new file |
| `"a"` | Append | Writes at end | Creates new file |
| `"r+"` | Read and Write | Opens file | Returns NULL |
| `"w+"` | Read and Write | Truncates to zero length | Creates new file |
| `"a+"` | Read and Append | Writes at end, reads anywhere | Creates new file |

### Binary File Modes

| Mode | Description |
|------|-------------|
| `"rb"` | Read binary |
| `"wb"` | Write binary |
| `"ab"` | Append binary |
| `"rb+"` or `"r+b"` | Read and write binary |
| `"wb+"` or `"w+b"` | Write and read binary |
| `"ab+"` or `"a+b"` | Append and read binary |

### Detailed Explanation with Examples:

#### Mode: "r" (Read)
```c
#include <stdio.h>

int main() {
    FILE *fp = fopen("existing.txt", "r");
    
    if(fp == NULL) {
        printf("Error: File doesn't exist or cannot be opened\n");
        return 1;
    }
    
    // Read operations can be performed
    char ch;
    while((ch = fgetc(fp)) != EOF) {
        printf("%c", ch);
    }
    
    fclose(fp);
    return 0;
}
```
**Use Case**: Reading configuration files, input data files

#### Mode: "w" (Write)
```c
#include <stdio.h>

int main() {
    FILE *fp = fopen("output.txt", "w");
    
    if(fp == NULL) {
        printf("Error: Cannot create file\n");
        return 1;
    }
    
    // Warning: This erases all previous content!
    fprintf(fp, "This is new content\n");
    fprintf(fp, "Previous data is lost\n");
    
    fclose(fp);
    return 0;
}
```
**Use Case**: Creating new files, overwriting old data
**Warning**: This mode destroys existing file content!

#### Mode: "a" (Append)
```c
#include <stdio.h>

int main() {
    FILE *fp = fopen("log.txt", "a");
    
    if(fp == NULL) {
        printf("Error: Cannot open file\n");
        return 1;
    }
    
    // Data is added at the end, preserving existing content
    fprintf(fp, "New log entry\n");
    fprintf(fp, "Another entry\n");
    
    fclose(fp);
    return 0;
}
```
**Use Case**: Log files, adding records to existing data

#### Mode: "r+" (Read and Write)
```c
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
```
**Use Case**: Updating existing files

---

## 4. Opening and Closing Files

### fopen() Function

Opens a file and returns a file pointer.

**Syntax**:
```c
FILE *fopen(const char *filename, const char *mode);
```

**Parameters**:
- `filename`: Path to the file (absolute or relative)
- `mode`: File opening mode

**Returns**:
- File pointer on success
- NULL on failure

**Example with Error Checking**:
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    
    // Attempt to open file
    fp = fopen("myfile.txt", "w");
    
    // Always check if file opened successfully
    if(fp == NULL) {
        printf("Error opening file!\n");
        perror("Error");  // Prints system error message
        exit(1);
    }
    
    printf("File opened successfully\n");
    
    // Perform file operations here
    fprintf(fp, "Hello, File!\n");
    
    fclose(fp);
    return 0;
}
```

### fclose() Function

Closes an open file and flushes any buffered data.

**Syntax**:
```c
int fclose(FILE *file_pointer);
```

**Returns**:
- 0 on success
- EOF on failure

**Why is fclose() Important?**

1. **Flushes Buffer**: Ensures all data is written to disk
2. **Releases Resources**: Frees memory associated with the file
3. **Prevents Data Loss**: Uncommitted data might be lost without closing
4. **System Limits**: Systems have a limit on open files

**Example**:
```c
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
```

### Complete File Operation Example:
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char filename[100];
    
    printf("Enter filename: ");
    scanf("%s", filename);
    
    // Open file in write mode
    fp = fopen(filename, "w");
    
    if(fp == NULL) {
        fprintf(stderr, "Cannot open file '%s'\n", filename);
        exit(EXIT_FAILURE);
    }
    
    // Write data
    fprintf(fp, "Line 1: File handling in C\n");
    fprintf(fp, "Line 2: fopen and fclose functions\n");
    fprintf(fp, "Line 3: Example completed\n");
    
    // Close file
    if(fclose(fp) != 0) {
        fprintf(stderr, "Error closing file\n");
        exit(EXIT_FAILURE);
    }
    
    printf("Data written and file closed successfully\n");
    
    return 0;
}
```

---

## 5. Reading from Files

### 5.1 fgetc() - Read Single Character

Reads a single character from the file.

**Syntax**:
```c
int fgetc(FILE *file_pointer);
```

**Returns**:
- Character read (as int)
- EOF on end of file or error

**Example 1: Reading Character by Character**
```c
#include <stdio.h>

int main() {
    FILE *fp;
    char ch;
    
    fp = fopen("sample.txt", "r");
    if(fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    
    printf("File contents:\n");
    
    // Read until end of file
    while((ch = fgetc(fp)) != EOF) {
        printf("%c", ch);
    }
    
    fclose(fp);
    return 0;
}
```

**Example 2: Counting Characters**
```c
#include <stdio.h>

int main() {
    FILE *fp;
    char ch;
    int count = 0;
    
    fp = fopen("document.txt", "r");
    if(fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    
    while((ch = fgetc(fp)) != EOF) {
        count++;
    }
    
    printf("Total characters: %d\n", count);
    
    fclose(fp);
    return 0;
}
```

### 5.2 fgets() - Read String/Line

Reads a line or specified number of characters from the file.

**Syntax**:
```c
char *fgets(char *str, int n, FILE *file_pointer);
```

**Parameters**:
- `str`: Buffer to store the string
- `n`: Maximum number of characters to read (including null terminator)
- `file_pointer`: File to read from

**Returns**:
- Pointer to string on success
- NULL on end of file or error

**Example 1: Reading Line by Line**
```c
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
    
    // Read and print each line
    while(fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);  // Note: fgets includes newline
    }
    
    fclose(fp);
    return 0;
}
```

**Example 2: Reading First N Lines**
```c
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
    
    fclose(fp);
    return 0;
}
```

### 5.3 fscanf() - Formatted Input

Reads formatted data from a file, similar to scanf().

**Syntax**:
```c
int fscanf(FILE *file_pointer, const char *format, ...);
```

**Returns**:
- Number of items successfully read
- EOF on end of file or error

**Example 1: Reading Structured Data**
```c
#include <stdio.h>

int main() {
    FILE *fp;
    int rollNo;
    char name[50];
    float marks;
    
    fp = fopen("students.txt", "r");
    if(fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    
    printf("Student Records:\n");
    printf("================\n");
    
    // Read formatted data
    while(fscanf(fp, "%d %s %f", &rollNo, name, &marks) != EOF) {
        printf("Roll: %d, Name: %s, Marks: %.2f\n", rollNo, name, marks);
    }
    
    fclose(fp);
    return 0;
}
```

**Example 2: Reading CSV-like Data**
```c
#include <stdio.h>

int main() {
    FILE *fp;
    char name[50];
    int age;
    float salary;
    
    fp = fopen("employees.txt", "r");
    if(fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    
    printf("Employee Data:\n");
    printf("%-20s %-10s %-10s\n", "Name", "Age", "Salary");
    printf("========================================\n");
    
    while(fscanf(fp, "%s %d %f", name, &age, &salary) == 3) {
        printf("%-20s %-10d $%.2f\n", name, age, salary);
    }
    
    fclose(fp);
    return 0;
}
```

### 5.4 fread() - Binary Read

Reads binary data from a file.

**Syntax**:
```c
size_t fread(void *ptr, size_t size, size_t count, FILE *file_pointer);
```

**Parameters**:
- `ptr`: Pointer to memory where data will be stored
- `size`: Size of each element in bytes
- `count`: Number of elements to read
- `file_pointer`: File to read from

**Returns**:
- Number of elements successfully read

**Example 1: Reading Structure**
```c
#include <stdio.h>
#include <string.h>

struct Student {
    int id;
    char name[50];
    float marks;
};

int main() {
    FILE *fp;
    struct Student s;
    
    fp = fopen("student.dat", "rb");
    if(fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    
    // Read one student record
    if(fread(&s, sizeof(struct Student), 1, fp) == 1) {
        printf("Student Details:\n");
        printf("ID: %d\n", s.id);
        printf("Name: %s\n", s.name);
        printf("Marks: %.2f\n", s.marks);
    }
    
    fclose(fp);
    return 0;
}
```

**Example 2: Reading Multiple Records**
```c
#include <stdio.h>

struct Product {
    int code;
    char name[30];
    float price;
};

int main() {
    FILE *fp;
    struct Product p;
    
    fp = fopen("products.dat", "rb");
    if(fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    
    printf("Product Inventory:\n");
    printf("================\n");
    
    // Read all products
    while(fread(&p, sizeof(struct Product), 1, fp) == 1) {
        printf("Code: %d, Name: %s, Price: $%.2f\n", 
               p.code, p.name, p.price);
    }
    
    fclose(fp);
    return 0;
}
```

---

## 6. Writing to Files

### 6.1 fputc() - Write Single Character

Writes a single character to the file.

**Syntax**:
```c
int fputc(int character, FILE *file_pointer);
```

**Returns**:
- Character written on success
- EOF on error

**Example 1: Writing Characters**
```c
#include <stdio.h>

int main() {
    FILE *fp;
    char ch;
    
    fp = fopen("output.txt", "w");
    if(fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    
    // Write alphabet
    for(ch = 'A'; ch <= 'Z'; ch++) {
        fputc(ch, fp);
    }
    
    fputc('\n', fp);  // Add newline
    
    fclose(fp);
    printf("Characters written successfully\n");
    
    return 0;
}
```

**Example 2: Copy File Character by Character**
```c
#include <stdio.h>

int main() {
    FILE *source, *dest;
    char ch;
    
    source = fopen("original.txt", "r");
    dest = fopen("copy.txt", "w");
    
    if(source == NULL || dest == NULL) {
        printf("Error opening files\n");
        return 1;
    }
    
    // Copy character by character
    while((ch = fgetc(source)) != EOF) {
        fputc(ch, dest);
    }
    
    printf("File copied successfully\n");
    
    fclose(source);
    fclose(dest);
    
    return 0;
}
```

### 6.2 fputs() - Write String

Writes a string to the file.

**Syntax**:
```c
int fputs(const char *str, FILE *file_pointer);
```

**Returns**:
- Non-negative value on success
- EOF on error

**Example 1: Writing Multiple Lines**
```c
#include <stdio.h>

int main() {
    FILE *fp;
    
    fp = fopen("notes.txt", "w");
    if(fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    
    // Write lines
    fputs("File Handling in C\n", fp);
    fputs("==================\n", fp);
    fputs("1. fopen() - Opens a file\n", fp);
    fputs("2. fclose() - Closes a file\n", fp);
    fputs("3. fputs() - Writes a string\n", fp);
    
    fclose(fp);
    printf("Notes written successfully\n");
    
    return 0;
}
```

**Example 2: Writing User Input**
```c
#include <stdio.h>

int main() {
    FILE *fp;
    char line[200];
    
    fp = fopen("diary.txt", "a");  // Append mode
    if(fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    
    printf("Enter your diary entry (type 'END' to finish):\n");
    
    while(1) {
        fgets(line, sizeof(line), stdin);
        
        if(strncmp(line, "END", 3) == 0) {
            break;
        }
        
        fputs(line, fp);
    }
    
    fclose(fp);
    printf("Entry saved successfully\n");
    
    return 0;
}
```

### 6.3 fprintf() - Formatted Output

Writes formatted data to a file, similar to printf().

**Syntax**:
```c
int fprintf(FILE *file_pointer, const char *format, ...);
```

**Returns**:
- Number of characters written on success
- Negative value on error

**Example 1: Writing Student Records**
```c
#include <stdio.h>

int main() {
    FILE *fp;
    int n, i;
    int rollNo;
    char name[50];
    float marks;
    
    fp = fopen("students.txt", "w");
    if(fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    
    printf("Enter number of students: ");
    scanf("%d", &n);
    
    fprintf(fp, "Student Records\n");
    fprintf(fp, "===============\n\n");
    
    for(i = 0; i < n; i++) {
        printf("\nStudent %d:\n", i+1);
        printf("Roll Number: ");
        scanf("%d", &rollNo);
        printf("Name: ");
        scanf("%s", name);
        printf("Marks: ");
        scanf("%f", &marks);
        
        fprintf(fp, "%d %s %.2f\n", rollNo, name, marks);
    }
    
    fclose(fp);
    printf("\nRecords saved successfully\n");
    
    return 0;
}
```

**Example 2: Creating Report**
```c
#include <stdio.h>
#include <time.h>

int main() {
    FILE *fp;
    time_t now;
    
    fp = fopen("report.txt", "w");
    if(fp == NULL) {
        printf("Error creating report\n");
        return 1;
    }
    
    // Get current time
    time(&now);
    
    // Write report header
    fprintf(fp, "SALES REPORT\n");
    fprintf(fp, "============\n");
    fprintf(fp, "Generated on: %s\n", ctime(&now));
    fprintf(fp, "\n");
    
    // Write data
    fprintf(fp, "%-15s %-10s %-10s\n", "Product", "Quantity", "Amount");
    fprintf(fp, "%-15s %-10s %-10s\n", "-------", "--------", "------");
    fprintf(fp, "%-15s %-10d $%-9.2f\n", "Laptop", 5, 5000.00);
    fprintf(fp, "%-15s %-10d $%-9.2f\n", "Mouse", 20, 500.00);
    fprintf(fp, "%-15s %-10d $%-9.2f\n", "Keyboard", 15, 1200.00);
    fprintf(fp, "\n");
    fprintf(fp, "Total Amount: $%.2f\n", 6700.00);
    
    fclose(fp);
    printf("Report generated successfully\n");
    
    return 0;
}
```

### 6.4 fwrite() - Binary Write

Writes binary data to a file.

**Syntax**:
```c
size_t fwrite(const void *ptr, size_t size, size_t count, FILE *file_pointer);
```

**Parameters**:
- `ptr`: Pointer to data to be written
- `size`: Size of each element in bytes
- `count`: Number of elements to write
- `file_pointer`: File to write to

**Returns**:
- Number of elements successfully written

**Example 1: Writing Structure**
```c
#include <stdio.h>
#include <string.h>

struct Employee {
    int id;
    char name[50];
    float salary;
};

int main() {
    FILE *fp;
    struct Employee emp;
    
    fp = fopen("employee.dat", "wb");
    if(fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    
    // Fill structure
    emp.id = 101;
    strcpy(emp.name, "John Doe");
    emp.salary = 50000.00;
    
    // Write to file
    if(fwrite(&emp, sizeof(struct Employee), 1, fp) == 1) {
        printf("Employee record saved successfully\n");
    } else {
        printf("Error writing to file\n");
    }
    
    fclose(fp);
    return 0;
}
```

**Example 2: Writing Array of Structures**
```c
#include <stdio.h>
#include <string.h>

struct Book {
    int isbn;
    char title[100];
    char author[50];
    float price;
};

int main() {
    FILE *fp;
    struct Book books[3];
    int i;
    
    // Initialize books
    books[0].isbn = 1001;
    strcpy(books[0].title, "C Programming");
    strcpy(books[0].author, "Dennis Ritchie");
    books[0].price = 450.00;
    
    books[1].isbn = 1002;
    strcpy(books[1].title, "Data Structures");
    strcpy(books[1].author, "Tanenbaum");
    books[1].price = 550.00;
    
    books[2].isbn = 1003;
    strcpy(books[2].title, "Algorithms");
    strcpy(books[2].author, "Cormen");
    books[2].price = 650.00;
    
    fp = fopen("library.dat", "wb");
    if(fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    
    // Write all books
    if(fwrite(books, sizeof(struct Book), 3, fp) == 3) {
        printf("All book records saved successfully\n");
    } else {
        printf("Error writing to file\n");
    }
    
    fclose(fp);
    return 0;
}
```

---

## 7. File Positioning Functions

### 7.1 fseek() - Move File Pointer

Moves the file pointer to a specific location in the file.

**Syntax**:
```c
int fseek(FILE *file_pointer, long offset, int origin);
```

**Parameters**:
- `file_pointer`: File pointer
- `offset`: Number of bytes to move (can be negative)
- `origin`: Reference position
  - `SEEK_SET` (0): Beginning of file
  - `SEEK_CUR` (1): Current position
  - `SEEK_END` (2): End of file

**Returns**:
- 0 on success
- Non-zero on error

**Example 1: Reading from Specific Position**
```c
#include <stdio.h>

int main() {
    FILE *fp;
    char ch;
    
    fp = fopen("sample.txt", "r");
    if(fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    
    // Move to 10th byte from beginning
    fseek(fp, 10, SEEK_SET);
    
    // Read from that position
    printf("Character at position 10: ");
    ch = fgetc(fp);
    printf("%c\n", ch);
    
    // Move back 5 bytes from current position
    fseek(fp, -5, SEEK_CUR);
    ch = fgetc(fp);
    printf("Character 5 bytes back: %c\n", ch);
    
    // Move to 5 bytes before end
    fseek(fp, -5, SEEK_END);
    ch = fgetc(fp);
    printf("Character 5 bytes from end: %c\n", ch);
    
    fclose(fp);
    return 0;
}
```

**Example 2: Random Access of Records**
```c
#include <stdio.h>
#include <string.h>

struct Student {
    int rollNo;
    char name[50];
    float marks;
};

int main() {
    FILE *fp;
    struct Student s;
    int recordNum;
    
    fp = fopen("students.dat", "rb");
    if(fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    
    printf("Enter record number to read (1-based): ");
    scanf("%d", &recordNum);
    
    // Move to specific record
    fseek(fp, (recordNum - 1) * sizeof(struct Student), SEEK_SET);
    
    // Read the record
    if(fread(&s, sizeof(struct Student), 1, fp) == 1) {
        printf("\nStudent Record:\n");
        printf("Roll No: %d\n", s.rollNo);
        printf("Name: %s\n", s.name);
        printf("Marks: %.2f\n", s.marks);
    } else {
        printf("Record not found\n");
    }
    
    fclose(fp);
    return 0;
}
```

### 7.2 ftell() - Get Current Position

Returns the current position of the file pointer.

**Syntax**:
```c
long ftell(FILE *file_pointer);
```

**Returns**:
- Current file position on success
- -1L on error

**Example 1: Getting File Size**
```c
#include <stdio.h>

int main() {
    FILE *fp;
    long size;
    
    fp = fopen("document.txt", "r");
    if(fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    
    // Move to end of file
    fseek(fp, 0, SEEK_END);
    
    // Get position (which is the file size)
    size = ftell(fp);
    
    printf("File size: %ld bytes\n", size);
    
    fclose(fp);
    return 0;
}
```

**Example 2: Tracking Read Progress**
```c
#include <stdio.h>

int main() {
    FILE *fp;
    char line[200];
    long position;
    
    fp = fopen("large_file.txt", "r");
    if(fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    
    // Get file size
    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);  // Go back to beginning
    
    printf("Reading file...\n");
    
    while(fgets(line, sizeof(line), fp) != NULL) {
        position = ftell(fp);
        printf("Progress: %.2f%% (%ld/%ld bytes)\n", 
               (position * 100.0) / fileSize, position, fileSize);
    }
    
    fclose(fp);
    return 0;
}
```

### 7.3 rewind() - Reset to Beginning

Moves the file pointer to the beginning of the file.

**Syntax**:
```c
void rewind(FILE *file_pointer);
```

**Note**: `rewind(fp)` is equivalent to `fseek(fp, 0, SEEK_SET)`

**Example 1: Reading File Twice**
```c
#include <stdio.h>

int main() {
    FILE *fp;
    char ch;
    
    fp = fopen("data.txt", "r");
    if(fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    
    printf("First read:\n");
    while((ch = fgetc(fp)) != EOF) {
        printf("%c", ch);
    }
    
    // Reset to beginning
    rewind(fp);
    
    printf("\n\nSecond read:\n");
    while((ch= fgetc(fp)) != EOF) {
        printf("%c", ch);
    }
    
    fclose(fp);
    return 0;
}
```

**Example 2: Counting and Displaying**
```c
#include <stdio.h>

int main() {
    FILE *fp;
    char line[200];
    int lineCount = 0;
    
    fp = fopen("report.txt", "r");
    if(fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    
    // Count lines
    while(fgets(line, sizeof(line), fp) != NULL) {
        lineCount++;
    }
    
    printf("Total lines: %d\n\n", lineCount);
    
    // Reset and display content
    rewind(fp);
    
    printf("File content:\n");
    printf("=============\n");
    while(fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
    }
    
    fclose(fp);
    return 0;
}
```

---

## 8. Error Handling with Files

### 8.1 feof() - Check End of File

Tests whether end-of-file has been reached.

**Syntax**:
```c
int feof(FILE *file_pointer);
```

**Returns**:
- Non-zero if EOF reached
- 0 otherwise

**Example**:
```c
#include <stdio.h>

int main() {
    FILE *fp;
    char ch;
    
    fp = fopen("test.txt", "r");
    if(fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    
    while(1) {
        ch = fgetc(fp);
        
        if(feof(fp)) {
            printf("\nEnd of file reached\n");
            break;
        }
        
        printf("%c", ch);
    }
    
    fclose(fp);
    return 0;
}
```

### 8.2 ferror() - Check for Errors

Tests whether an error occurred during file operations.

**Syntax**:
```c
int ferror(FILE *file_pointer);
```

**Returns**:
- Non-zero if error occurred
- 0 otherwise

**Example**:
```c
#include <stdio.h>

int main() {
    FILE *fp;
    int num;
    
    fp = fopen("numbers.txt", "r");
    if(fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    
    while(fscanf(fp, "%d", &num) == 1) {
        printf("%d ", num);
        
        if(ferror(fp)) {
            printf("\nError reading file\n");
            clearerr(fp);  // Clear error flag
            break;
        }
    }
    
    fclose(fp);
    return 0;
}
```

### 8.3 clearerr() - Clear Error Flags

Clears the end-of-file and error indicators.

**Syntax**:
```c
void clearerr(FILE *file_pointer);
```

**Example**:
```c
#include <stdio.h>

int main() {
    FILE *fp;
    char ch;
    
    fp = fopen("data.txt", "r");
    if(fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    
    // Read until EOF
    while((ch = fgetc(fp)) != EOF) {
        printf("%c", ch);
    }
    
    printf("\nEOF reached: %d\n", feof(fp));
    
    // Clear EOF flag
    clearerr(fp);
    
    printf("After clearerr, EOF: %d\n", feof(fp));
    
    // Can now use the file again
    rewind(fp);
    ch = fgetc(fp);
    printf("First character: %c\n", ch);
    
    fclose(fp);
    return 0;
}
```

### 8.4 perror() - Print Error Message

Prints a descriptive error message to stderr.

**Syntax**:
```c
void perror(const char *str);
```

**Example**:
```c
#include <stdio.h>

int main() {
    FILE *fp;
    
    fp = fopen("nonexistent.txt", "r");
    if(fp == NULL) {
        perror("Error");
        // Prints: Error: No such file or directory
        return 1;
    }
    
    fclose(fp);
    return 0;
}
```

### Complete Error Handling Example:
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char filename[100];
    char buffer[256];
    
    printf("Enter filename to read: ");
    scanf("%s", filename);
    
    fp = fopen(filename, "r");
    
    // Check if file opened successfully
    if(fp == NULL) {
        fprintf(stderr, "Error: Cannot open file '%s'\n", filename);
        perror("Reason");
        exit(EXIT_FAILURE);
    }
    
    printf("\nReading file...\n");
    printf("================\n");
    
    // Read file with error checking
    while(fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
        
        // Check for read error
        if(ferror(fp)) {
            fprintf(stderr, "\nError reading file\n");
            clearerr(fp);
            break;
        }
    }
    
    // Check why loop ended
    if(feof(fp)) {
        printf("\n\nFile read successfully\n");
    }
    
    // Close file and check for errors
    if(fclose(fp) != 0) {
        fprintf(stderr, "Error closing file\n");
        exit(EXIT_FAILURE);
    }
    
    return 0;
}
```

---

## 9. Practice Problems with Complete Solutions

### Problem 1: Write and Read Student Records

```c
#include <stdio.h>
#include <string.h>

struct Student {
    int rollNo;
    char name[50];
    float marks;
};

// Function to write student records
void writeStudents() {
    FILE *fp;
    struct Student s;
    int n, i;
    
    fp = fopen("students.txt", "w");
    if(fp == NULL) {
        printf("Error opening file for writing\n");
        return;
    }
    
    printf("Enter number of students: ");
    scanf("%d", &n);
    
    for(i = 0; i < n; i++) {
        printf("\nStudent %d:\n", i+1);
        printf("Roll Number: ");
        scanf("%d", &s.rollNo);
        printf("Name: ");
        scanf("%s", s.name);
        printf("Marks: ");
        scanf("%f", &s.marks);
        
        fprintf(fp, "%d %s %.2f\n", s.rollNo, s.name, s.marks);
    }
    
    fclose(fp);
    printf("\nRecords saved successfully!\n");
}

// Function to read and display student records
void readStudents() {
    FILE *fp;
    struct Student s;
    
    fp = fopen("students.txt", "r");
    if(fp == NULL) {
        printf("Error opening file for reading\n");
        return;
    }
    
    printf("\n%-10s %-20s %-10s\n", "Roll No", "Name", "Marks");
    printf("==========================================\n");
    
    while(fscanf(fp, "%d %s %f", &s.rollNo, s.name, &s.marks) != EOF) {
        printf("%-10d %-20s %-10.2f\n", s.rollNo, s.name, s.marks);
    }
    
    fclose(fp);
}

int main() {
    int choice;
    
    while(1) {
        printf("\n=== Student Record System ===\n");
        printf("1. Write Student Records\n");
        printf("2. Read Student Records\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                writeStudents();
                break;
            case 2:
                readStudents();
                break;
            case 3:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
    
    return 0;
}
```

### Problem 2: Append Data to Existing File

```c
#include <stdio.h>
#include <time.h>

void appendLog() {
    FILE *fp;
    char message[200];
    time_t now;
    
    fp = fopen("activity_log.txt", "a");
    if(fp == NULL) {
        printf("Error opening log file\n");
        return;
    }
    
    // Get current time
    time(&now);
    
    printf("Enter log message: ");
    getchar();  // Clear newline
    fgets(message, sizeof(message), stdin);
    
    // Write timestamp and message
    fprintf(fp, "[%s] %s", ctime(&now), message);
    
    fclose(fp);
    printf("Log entry added successfully!\n");
}

void viewLog() {
    FILE *fp;
    char line[256];
    
    fp = fopen("activity_log.txt", "r");
    if(fp == NULL) {
        printf("No log file found\n");
        return;
    }
    
    printf("\n=== Activity Log ===\n");
    while(fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
    }
    
    fclose(fp);
}

int main() {
    int choice;
    
    while(1) {
        printf("\n=== Log System ===\n");
        printf("1. Add Log Entry\n");
        printf("2. View Log\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                appendLog();
                break;
            case 2:
                viewLog();
                break;
            case 3:
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
    
    return 0;
}
```

### Problem 3: Copy Contents from One File to Another

```c
#include <stdio.h>

void copyFile(char *source, char *destination) {
    FILE *src, *dest;
    char ch;
    int count = 0;
    
    // Open source file
    src = fopen(source, "r");
    if(src == NULL) {
        printf("Error: Cannot open source file '%s'\n", source);
        return;
    }
    
    // Open destination file
    dest = fopen(destination, "w");
    if(dest == NULL) {
        printf("Error: Cannot create destination file '%s'\n", destination);
        fclose(src);
        return;
    }
    
    // Copy character by character
    while((ch = fgetc(src)) != EOF) {
        fputc(ch, dest);
        count++;
    }
    
    printf("File copied successfully!\n");
    printf("Total bytes copied: %d\n", count);
    
    fclose(src);
    fclose(dest);
}

int main() {
    char source[100], destination[100];
    
    printf("Enter source filename: ");
    scanf("%s", source);
    
    printf("Enter destination filename: ");
    scanf("%s", destination);
    
    copyFile(source, destination);
    
    return 0;
}
```

### Problem 4: Count Lines, Words, and Characters

```c
#include <stdio.h>
#include <ctype.h>

void analyzeFile(char *filename) {
    FILE *fp;
    char ch;
    int lines = 0, words = 0, characters = 0;
    int inWord = 0;
    
    fp = fopen(filename, "r");
    if(fp == NULL) {
        printf("Error opening file '%s'\n", filename);
        return;
    }
    
    while((ch = fgetc(fp)) != EOF) {
        characters++;
        
        // Count lines
        if(ch == '\n') {
            lines++;
        }
        
        // Count words
        if(isspace(ch)) {
            inWord = 0;
        } else if(inWord == 0) {
            inWord = 1;
            words++;
        }
    }
    
    // If file doesn't end with newline, count last line
    if(characters > 0 && ch != '\n') {
        lines++;
    }
    
    printf("\n=== File Statistics ===\n");
    printf("Lines: %d\n", lines);
    printf("Words: %d\n", words);
    printf("Characters: %d\n", characters);
    
    fclose(fp);
}

int main() {
    char filename[100];
    
    printf("Enter filename to analyze: ");
    scanf("%s", filename);
    
    analyzeFile(filename);
    
    return 0;
}
```

### Problem 5: Simple Log System

```c
#include <stdio.h>
#include <time.h>
#include <string.h>

#define LOG_FILE "system.log"

typedef enum {
    INFO,
    WARNING,
    ERROR
} LogLevel;

void writeLog(LogLevel level, char *message) {
    FILE *fp;
    time_t now;
    char *levelStr;
    
    fp = fopen(LOG_FILE, "a");
    if(fp == NULL) {
        printf("Error opening log file\n");
        return;
    }
    
    // Get current time
    time(&now);
    struct tm *timeinfo = localtime(&now);
    
    // Determine log level string
    switch(level) {
        case INFO:
            levelStr = "INFO";
            break;
        case WARNING:
            levelStr = "WARNING";
            break;
        case ERROR:
            levelStr = "ERROR";
            break;
    }
    
    // Write log entry
    fprintf(fp, "[%04d-%02d-%02d %02d:%02d:%02d] [%s] %s\n",
            timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday,
            timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec,
            levelStr, message);
    
    fclose(fp);
}

void viewLogs() {
    FILE *fp;
    char line[256];
    
    fp = fopen(LOG_FILE, "r");
    if(fp == NULL) {
        printf("No logs found\n");
        return;
    }
    
    printf("\n=== System Logs ===\n");
    while(fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
    }
    
    fclose(fp);
}

void searchLogs(char *keyword) {
    FILE *fp;
    char line[256];
    int found = 0;
    
    fp = fopen(LOG_FILE, "r");
    if(fp == NULL) {
        printf("No logs found\n");
        return;
    }
    
    printf("\n=== Search Results for '%s' ===\n", keyword);
    while(fgets(line, sizeof(line), fp) != NULL) {
        if(strstr(line, keyword) != NULL) {
            printf("%s", line);
            found = 1;
        }
    }
    
    if(!found) {
        printf("No matching logs found\n");
    }
    
    fclose(fp);
}

int main() {
    int choice;
    char message[200];
    char keyword[50];
    int level;
    
    while(1) {
        printf("\n=== Log System ===\n");
        printf("1. Add INFO log\n");
        printf("2. Add WARNING log\n");
        printf("3. Add ERROR log\n");
        printf("4. View all logs\n");
        printf("5. Search logs\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();  // Clear newline
        
        switch(choice) {
            case 1:
            case 2:
            case 3:
                printf("Enter log message: ");
                fgets(message, sizeof(message), stdin);
                message[strcspn(message, "\n")] = 0;  // Remove newline
                
                if(choice == 1) level = INFO;
                else if(choice == 2) level = WARNING;
                else level = ERROR;
                
                writeLog(level, message);
                printf("Log entry added\n");
                break;
                
            case 4:
                viewLogs();
                break;
                
            case 5:
                printf("Enter keyword to search: ");
                fgets(keyword, sizeof(keyword), stdin);
                keyword[strcspn(keyword, "\n")] = 0;
                searchLogs(keyword);
                break;
                
            case 6:
                printf("Exiting...\n");
                return 0;
                
            default:
                printf("Invalid choice!\n");
        }
    }
    
    return 0;
}
```

### Problem 6: Binary File Operations

```c
#include <stdio.h>
#include <string.h>

struct Product {
    int id;
    char name[50];
    float price;
    int quantity;
};

void addProduct() {
    FILE *fp;
    struct Product p;
    
    fp = fopen("inventory.dat", "ab");
    if(fp == NULL) {
        printf("Error opening file\n");
        return;
    }
    
    printf("Enter Product ID: ");
    scanf("%d", &p.id);
    printf("Enter Product Name: ");
    scanf("%s", p.name);
    printf("Enter Price: ");
    scanf("%f", &p.price);
    printf("Enter Quantity: ");
    scanf("%d", &p.quantity);
    
    fwrite(&p, sizeof(struct Product), 1, fp);
    
    fclose(fp);
    printf("Product added successfully!\n");
}

void viewProducts() {
    FILE *fp;
    struct Product p;
    
    fp = fopen("inventory.dat", "rb");
    if(fp == NULL) {
        printf("No inventory file found\n");
        return;
    }
    
    printf("\n%-10s %-30s %-10s %-10s\n", "ID", "Name", "Price", "Quantity");
    printf("============================================================\n");
    
    while(fread(&p, sizeof(struct Product), 1, fp) == 1) {
        printf("%-10d %-30s $%-9.2f %-10d\n", 
               p.id, p.name, p.price, p.quantity);
    }
    
    fclose(fp);
}

void searchProduct() {
    FILE *fp;
    struct Product p;
    int searchId, found = 0;
    
    fp = fopen("inventory.dat", "rb");
    if(fp == NULL) {
        printf("No inventory file found\n");
        return;
    }
    
    printf("Enter Product ID to search: ");
    scanf("%d", &searchId);
    
    while(fread(&p, sizeof(struct Product), 1, fp) == 1) {
        if(p.id == searchId) {
            printf("\nProduct Found:\n");
            printf("ID: %d\n", p.id);
            printf("Name: %s\n", p.name);
            printf("Price: $%.2f\n", p.price);
            printf("Quantity: %d\n", p.quantity);
            found = 1;
            break;
        }
    }
    
    if(!found) {
        printf("Product not found\n");
    }
    
    fclose(fp);
}

void updateProduct() {
    FILE *fp;
    struct Product p;
    int searchId, found = 0;
    long position;
    
    fp = fopen("inventory.dat", "rb+");
    if(fp == NULL) {
        printf("No inventory file found\n");
        return;
    }
    
    printf("Enter Product ID to update: ");
    scanf("%d", &searchId);
    
    while(fread(&p, sizeof(struct Product), 1, fp) == 1) {
        if(p.id == searchId) {
            found = 1;
            printf("\nCurrent Details:\n");
            printf("Name: %s\n", p.name);
            printf("Price: $%.2f\n", p.price);
            printf("Quantity: %d\n", p.quantity);
            
            printf("\nEnter new details:\n");
            printf("Name: ");
            scanf("%s", p.name);
            printf("Price: ");
            scanf("%f", &p.price);
            printf("Quantity: ");
            scanf("%d", &p.quantity);
            
            // Move back to write position
            fseek(fp, -sizeof(struct Product), SEEK_CUR);
            fwrite(&p, sizeof(struct Product), 1, fp);
            
            printf("Product updated successfully!\n");
            break;
        }
    }
    
    if(!found) {
        printf("Product not found\n");
    }
    
    fclose(fp);
}

int main() {
    int choice;
    
    while(1) {
        printf("\n=== Inventory Management ===\n");
        printf("1. Add Product\n");
        printf("2. View All Products\n");
        printf("3. Search Product\n");
        printf("4. Update Product\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                addProduct();
                break;
            case 2:
                viewProducts();
                break;
            case 3:
                searchProduct();
                break;
            case 4:
                updateProduct();
                break;
            case 5:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
    
    return 0;
}
```

### Problem 7: Mini Project - Contact Manager

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CONTACT_FILE "contacts.dat"

struct Contact {
    int id;
    char name[50];
    char phone[15];
    char email[50];
};

int getNextId() {
    FILE *fp;
    struct Contact c;
    int maxId = 0;
    
    fp = fopen(CONTACT_FILE, "rb");
    if(fp == NULL) {
        return 1;
    }
    
    while(fread(&c, sizeof(struct Contact), 1, fp) == 1) {
        if(c.id > maxId) {
            maxId = c.id;
        }
    }
    
    fclose(fp);
    return maxId + 1;
}

void addContact() {
    FILE *fp;
    struct Contact c;
    
    fp = fopen(CONTACT_FILE, "ab");
    if(fp == NULL) {
        printf("Error opening file\n");
        return;
    }
    
    c.id = getNextId();
    
    printf("Enter Name: ");
    getchar();
    fgets(c.name, sizeof(c.name), stdin);
    c.name[strcspn(c.name, "\n")] = 0;
    
    printf("Enter Phone: ");
    fgets(c.phone, sizeof(c.phone), stdin);
    c.phone[strcspn(c.phone, "\n")] = 0;
    
    printf("Enter Email: ");
    fgets(c.email, sizeof(c.email), stdin);
    c.email[strcspn(c.email, "\n")] = 0;
    
    fwrite(&c, sizeof(struct Contact), 1, fp);
    
    fclose(fp);
    printf("\nContact added successfully! (ID: %d)\n", c.id);
}

void viewContacts() {
    FILE *fp;
    struct Contact c;
    int count = 0;
    
    fp = fopen(CONTACT_FILE, "rb");
    if(fp == NULL) {
        printf("No contacts found\n");
        return;
    }
    
    printf("\n%-5s %-25s %-15s %-30s\n", "ID", "Name", "Phone", "Email");
    printf("=======================================================================\n");
    
    while(fread(&c, sizeof(struct Contact), 1, fp) == 1) {
        printf("%-5d %-25s %-15s %-30s\n", c.id, c.name, c.phone, c.email);
        count++;
    }
    
    printf("\nTotal contacts: %d\n", count);
    
    fclose(fp);
}

void searchContact() {
    FILE *fp;
    struct Contact c;
    char searchName[50];
    int found = 0;
    
    fp = fopen(CONTACT_FILE, "rb");
    if(fp == NULL) {
        printf("No contacts found\n");
        return;
    }
    
    printf("Enter name to search: ");
    getchar();
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = 0;
    
    printf("\nSearch Results:\n");
    printf("%-5s %-25s %-15s %-30s\n", "ID", "Name", "Phone", "Email");
    printf("=======================================================================\n");
    
    while(fread(&c, sizeof(struct Contact), 1, fp) == 1) {
        if(strstr(c.name, searchName) != NULL) {
            printf("%-5d %-25s %-15s %-30s\n", c.id, c.name, c.phone, c.email);
            found = 1;
        }
    }
    
    if(!found) {
        printf("No matching contacts found\n");
    }
    
    fclose(fp);
}

void deleteContact() {
    FILE *fp, *temp;
    struct Contact c;
    int deleteId, found = 0;
    
    fp = fopen(CONTACT_FILE, "rb");
    if(fp == NULL) {
        printf("No contacts found\n");
        return;
    }
    
    temp = fopen("temp.dat", "wb");
    if(temp == NULL) {
        printf("Error creating temporary file\n");
        fclose(fp);
        return;
    }
    
    printf("Enter Contact ID to delete: ");
    scanf("%d", &deleteId);
    
    while(fread(&c, sizeof(struct Contact), 1, fp) == 1) {
        if(c.id == deleteId) {
            found = 1;
            printf("Contact '%s' deleted\n", c.name);
        } else {
            fwrite(&c, sizeof(struct Contact), 1, temp);
        }
    }
    
    fclose(fp);
    fclose(temp);
    
    if(found) {
        remove(CONTACT_FILE);
        rename("temp.dat", CONTACT_FILE);
    } else {
        remove("temp.dat");
        printf("Contact not found\n");
    }
}

void updateContact() {
    FILE *fp;
    struct Contact c;
    int updateId, found = 0;
    
    fp = fopen(CONTACT_FILE, "rb+");
    if(fp == NULL) {
        printf("No contacts found\n");
        return;
    }
    
    printf("Enter Contact ID to update: ");
    scanf("%d", &updateId);
    
    while(fread(&c, sizeof(struct Contact), 1, fp) == 1) {
        if(c.id == updateId) {
            found = 1;
            
            printf("\nCurrent Details:\n");
            printf("Name: %s\n", c.name);
            printf("Phone: %s\n", c.phone);
            printf("Email: %s\n", c.email);
            
            printf("\nEnter new details:\n");
            printf("Name: ");
            getchar();
            fgets(c.name, sizeof(c.name), stdin);
            c.name[strcspn(c.name, "\n")] = 0;
            
            printf("Phone: ");
            fgets(c.phone, sizeof(c.phone), stdin);
            c.phone[strcspn(c.phone, "\n")] = 0;
            
            printf("Email: ");
            fgets(c.email, sizeof(c.email), stdin);
            c.email[strcspn(c.email, "\n")] = 0;
            
            fseek(fp, -sizeof(struct Contact), SEEK_CUR);
            fwrite(&c, sizeof(struct Contact), 1, fp);
            
            printf("\nContact updated successfully!\n");
            break;
        }
    }
    
    if(!found) {
        printf("Contact not found\n");
    }
    
    fclose(fp);
}

void displayMenu() {
    printf("\n╔════════════════════════════════╗\n");
    printf("║   CONTACT MANAGER SYSTEM       ║\n");
    printf("╠════════════════════════════════╣\n");
    printf("║ 1. Add Contact                 ║\n");
    printf("║ 2. View All Contacts           ║\n");
    printf("║ 3. Search Contact              ║\n");
    printf("║ 4. Update Contact              ║\n");
    printf("║ 5. Delete Contact              ║\n");
    printf("║ 6. Exit                        ║\n");
    printf("╚════════════════════════════════╝\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;
    
    printf("\n╔════════════════════════════════╗\n");
    printf("║  Welcome to Contact Manager    ║\n");
    printf("╚════════════════════════════════╝\n");
    
    while(1) {
        displayMenu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                addContact();
                break;
            case 2:
                viewContacts();
                break;
            case 3:
                searchContact();
                break;
            case 4:
                updateContact();
                break;
            case 5:
                deleteContact();
                break;
            case 6:
                printf("\nThank you for using Contact Manager!\n");
                return 0;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
        
        printf("\nPress Enter to continue...");
        getchar();
        getchar();
    }
    
    return 0;
}
```

---

## Summary

### Key Points to Remember:

1. **Always check if file opened successfully** using `if(fp == NULL)`
2. **Always close files** using `fclose()` after operations
3. **Use text mode** for human-readable data (default)
4. **Use binary mode** for structures and efficient storage
5. **Error handling** is crucial for robust programs
6. **File positioning** functions allow random access
7. **Buffer flushing** happens automatically with `fclose()`

### Common Pitfalls:

1. Forgetting to close files
2. Not checkingfor NULL after fopen()
3. Using wrong file mode
4. Not handling end-of-file properly
5. Mixing text and binary modes
6. Buffer overflow in fgets()
7. Not clearing input buffer after scanf()

### Best Practices:

1. Use meaningful file names
2. Check return values of file operations
3. Use appropriate file modes
4. Close files as soon as operations are complete
5. Use binary mode for structures
6. Implement proper error handling
7. Comment your file operations clearly
8. Use constants for file names
