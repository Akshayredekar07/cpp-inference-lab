# Arrays in C - Detailed Notes

## Table of Contents
1. Introduction to Arrays
2. One-Dimensional Arrays
3. Multi-Dimensional Arrays
4. Array Operations
5. Searching Algorithms
6. Sorting Algorithms
7. Common Pitfalls and Best Practices

---

## 1. Introduction to Arrays

### What is an Array?
An array is a collection of elements of the same data type stored in contiguous memory locations. It allows you to store multiple values under a single variable name.

### Why Use Arrays?
- Store multiple values of the same type efficiently
- Easy to access elements using index
- Simplifies code when dealing with large amounts of data
- Foundation for more complex data structures

### Key Characteristics:
- **Fixed Size**: Size is determined at declaration and cannot be changed
- **Same Data Type**: All elements must be of the same type
- **Contiguous Memory**: Elements are stored in consecutive memory locations
- **Zero-Based Indexing**: First element is at index 0

---

## 2. One-Dimensional Arrays

### Declaration Syntax
```c
data_type array_name[size];
```

### Examples of Declaration
```c
int numbers[5];           // Array of 5 integers
float prices[10];         // Array of 10 floating-point numbers
char name[20];            // Array of 20 characters (string)
```

### Initialization

#### Method 1: Initialize at Declaration
```c
int numbers[5] = {10, 20, 30, 40, 50};
```

#### Method 2: Partial Initialization
```c
int numbers[5] = {10, 20};  // Remaining elements are 0
// Result: {10, 20, 0, 0, 0}
```

#### Method 3: Automatic Size Calculation
```c
int numbers[] = {10, 20, 30, 40, 50};  // Size automatically becomes 5
```

#### Method 4: Initialize All to Zero
```c
int numbers[5] = {0};  // All elements are 0
```

#### Method 5: Initialize After Declaration
```c
int numbers[5];
numbers[0] = 10;
numbers[1] = 20;
numbers[2] = 30;
numbers[3] = 40;
numbers[4] = 50;
```

### Accessing Array Elements

```c
int numbers[5] = {10, 20, 30, 40, 50};

// Reading values
int first = numbers[0];   // first = 10
int third = numbers[2];   // third = 30

// Modifying values
numbers[1] = 25;          // Array becomes {10, 25, 30, 40, 50}
```

### Array Traversal

#### Using for Loop
```c
int numbers[5] = {10, 20, 30, 40, 50};

// Print all elements
for(int i = 0; i < 5; i++) {
    printf("%d ", numbers[i]);
}
```

#### Using while Loop
```c
int i = 0;
while(i < 5) {
    printf("%d ", numbers[i]);
    i++;
}
```

### Input and Output

#### Taking Input from User
```c
int numbers[5];
printf("Enter 5 numbers:\n");
for(int i = 0; i < 5; i++) {
    scanf("%d", &numbers[i]);
}
```

#### Displaying Array
```c
printf("Array elements are:\n");
for(int i = 0; i < 5; i++) {
    printf("numbers[%d] = %d\n", i, numbers[i]);
}
```

### Memory Representation

```
Array: int arr[5] = {10, 20, 30, 40, 50};

Memory Layout:
┌────┬────┬────┬────┬────┐
│ 10 │ 20 │ 30 │ 40 │ 50 │
└────┴────┴────┴────┴────┘
 [0]  [1]  [2]  [3]  [4]   ← Indices

If base address is 1000 (and int is 4 bytes):
Address: 1000, 1004, 1008, 1012, 1016
```

### Finding Array Size

```c
int numbers[5] = {10, 20, 30, 40, 50};
int size = sizeof(numbers) / sizeof(numbers[0]);
// sizeof(numbers) = 20 bytes (5 * 4)
// sizeof(numbers[0]) = 4 bytes
// size = 20 / 4 = 5
```

---

## 3. Multi-Dimensional Arrays

### Two-Dimensional Arrays

#### Declaration and Initialization
```c
// Declaration
int matrix[3][4];  // 3 rows, 4 columns

// Initialization Method 1
int matrix[3][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12}
};

// Initialization Method 2 (linear)
int matrix[3][4] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

// Partial Initialization
int matrix[3][4] = {
    {1, 2},
    {5},
    {9, 10}
};
// Result:
// 1  2  0  0
// 5  0  0  0
// 9  10 0  0
```

#### Memory Representation
```
2D Array: int arr[3][4]

Logical View:
     Col0 Col1 Col2 Col3
Row0 [ 1   2   3   4  ]
Row1 [ 5   6   7   8  ]
Row2 [ 9   10  11  12 ]

Physical Memory (Row-Major Order):
[1][2][3][4][5][6][7][8][9][10][11][12]
```

#### Accessing 2D Array Elements
```c
int matrix[3][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12}
};

// Access element at row 1, column 2
int value = matrix[1][2];  // value = 7

// Modify element
matrix[2][3] = 100;  // Changes 12 to 100
```

#### Traversing 2D Arrays
```c
// Using nested loops
for(int i = 0; i < 3; i++) {           // rows
    for(int j = 0; j < 4; j++) {       // columns
        printf("%d ", matrix[i][j]);
    }
    printf("\n");
}
```

#### Input for 2D Arrays
```c
int matrix[3][4];
printf("Enter elements of 3x4 matrix:\n");
for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 4; j++) {
        printf("Element [%d][%d]: ", i, j);
        scanf("%d", &matrix[i][j]);
    }
}
```

### Three-Dimensional Arrays

```c
// Declaration
int arr[2][3][4];  // 2 blocks, 3 rows, 4 columns each

// Initialization
int arr[2][3][4] = {
    {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    },
    {
        {13, 14, 15, 16},
        {17, 18, 19, 20},
        {21, 22, 23, 24}
    }
};

// Accessing elements
int value = arr[1][2][3];  // value = 24

// Traversing 3D array
for(int i = 0; i < 2; i++) {
    for(int j = 0; j < 3; j++) {
        for(int k = 0; k < 4; k++) {
            printf("%d ", arr[i][j][k]);
        }
        printf("\n");
    }
    printf("\n");
}
```

---

## 4. Array Operations

### 4.1 Finding Maximum and Minimum

```c
int findMax(int arr[], int size) {
    int max = arr[0];
    for(int i = 1; i < size; i++) {
        if(arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int findMin(int arr[], int size) {
    int min = arr[0];
    for(int i = 1; i < size; i++) {
        if(arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}
```

### 4.2 Sum and Average

```c
int sumArray(int arr[], int size) {
    int sum = 0;
    for(int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

float averageArray(int arr[], int size) {
    int sum = sumArray(arr, size);
    return (float)sum / size;
}
```

### 4.3 Reversing an Array

```c
void reverseArray(int arr[], int size) {
    int start = 0;
    int end = size - 1;
    
    while(start < end) {
        // Swap elements
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        
        start++;
        end--;
    }
}
```

### 4.4 Copying an Array

```c
void copyArray(int source[], int dest[], int size) {
    for(int i = 0; i < size; i++) {
        dest[i] = source[i];
    }
}
```

### 4.5 Inserting an Element

```c
void insertElement(int arr[], int *size, int pos, int value) {
    // Shift elements to right
    for(int i = *size; i > pos; i--) {
        arr[i] = arr[i-1];
    }
    
    // Insert new element
    arr[pos] = value;
    (*size)++;
}

// Example usage:
// int arr[10] = {1, 2, 3, 4, 5};
// int size = 5;
// insertElement(arr, &size, 2, 99);
// Result: {1, 2, 99, 3, 4, 5}
```

### 4.6 Deleting an Element

```c
void deleteElement(int arr[], int *size, int pos) {
    // Shift elements to left
    for(int i = pos; i < *size - 1; i++) {
        arr[i] = arr[i+1];
    }
    
    (*size)--;
}
```

### 4.7 Merging Two Arrays

```c
void mergeArrays(int arr1[], int size1, int arr2[], int size2, int result[]) {
    int i;
    
    // Copy first array
    for(i = 0; i < size1; i++) {
        result[i] = arr1[i];
    }
    
    // Copy second array
    for(i = 0; i < size2; i++) {
        result[size1 + i] = arr2[i];
    }
}
```

### 4.8 Finding Frequency of Elements

```c
void findFrequency(int arr[], int size) {
    int visited[size];
    
    // Initialize visited array
    for(int i = 0; i < size; i++) {
        visited[i] = 0;
    }
    
    for(int i = 0; i < size; i++) {
        if(visited[i] == 1)
            continue;
            
        int count = 1;
        for(int j = i + 1; j < size; j++) {
            if(arr[i] == arr[j]) {
                count++;
                visited[j] = 1;
            }
        }
        
        printf("%d occurs %d times\n", arr[i], count);
    }
}
```

### 4.9 Removing Duplicates

```c
int removeDuplicates(int arr[], int size) {
    int newSize = 0;
    
    for(int i = 0; i < size; i++) {
        int isDuplicate = 0;
        
        // Check if element already exists in result
        for(int j = 0; j < newSize; j++) {
            if(arr[i] == arr[j]) {
                isDuplicate = 1;
                break;
            }
        }
        
        // If not duplicate, add to result
        if(!isDuplicate) {
            arr[newSize] = arr[i];
            newSize++;
        }
    }
    
    return newSize;
}
```

---

## 5. Searching Algorithms

### 5.1 Linear Search

**Concept**: Check each element sequentially until target is found

**Time Complexity**: O(n)

**Space Complexity**: O(1)

```c
int linearSearch(int arr[], int size, int key) {
    for(int i = 0; i < size; i++) {
        if(arr[i] == key) {
            return i;  // Return index where found
        }
    }
    return -1;  // Not found
}

// Example usage:
// int arr[] = {64, 34, 25, 12, 22, 11, 90};
// int index = linearSearch(arr, 7, 25);
// if(index != -1)
//     printf("Found at index %d", index);
```

### 5.2 Binary Search

**Concept**: Divide and conquer approach on sorted arrays

**Prerequisite**: Array must be sorted

**Time Complexity**: O(log n)

**Space Complexity**: O(1)

#### Iterative Approach
```c
int binarySearch(int arr[], int size, int key) {
    int left = 0;
    int right = size - 1;
    
    while(left <= right) {
        int mid = left + (right - left) / 2;  // Prevents overflow
        
        if(arr[mid] == key) {
            return mid;  // Found
        }
        else if(arr[mid] < key) {
            left = mid + 1;  // Search right half
        }
        else {
            right = mid - 1;  // Search left half
        }
    }
    
    return -1;  // Not found
}
```

#### Recursive Approach
```c
int binarySearchRecursive(int arr[], int left, int right, int key) {
    if(left > right) {
        return -1;  // Base case: not found
    }
    
    int mid = left + (right - left) / 2;
    
    if(arr[mid] == key) {
        return mid;
    }
    else if(arr[mid] < key) {
        return binarySearchRecursive(arr, mid + 1, right, key);
    }
    else {
        return binarySearchRecursive(arr, left, mid - 1, key);
    }
}

// Usage: binarySearchRecursive(arr, 0, size-1, key);
```

**Visual Example**:
```
Array: [11, 12, 22, 25, 34, 64, 90]
Search for: 25

Step 1: left=0, right=6, mid=3
        arr[3]=25 → Found!
```

---

## 6. Sorting Algorithms

### 6.1 Bubble Sort

**Concept**: Repeatedly swap adjacent elements if they're in wrong order

**Time Complexity**: O(n²)

**Space Complexity**: O(1)

**Stable**: Yes

```c
void bubbleSort(int arr[], int size) {
    for(int i = 0; i < size - 1; i++) {
        int swapped = 0;
        
        for(int j = 0; j < size - i - 1; j++) {
            if(arr[j] > arr[j + 1]) {
                // Swap
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        
        // Optimization: If no swap, array is sorted
        if(swapped == 0) {
            break;
        }
    }
}
```

**Visual Example**:
```
Initial: [64, 34, 25, 12, 22]

Pass 1: [34, 25, 12, 22, 64]  (64 bubbles to end)
Pass 2: [25, 12, 22, 34, 64]  (34 bubbles to position)
Pass 3: [12, 22, 25, 34, 64]  (25 bubbles to position)
Pass 4: [12, 22, 25, 34, 64]  (Already sorted)
```

### 6.2 Selection Sort

**Concept**: Find minimum element and place it at the beginning

**Time Complexity**: O(n²)

**Space Complexity**: O(1)

**Stable**: No

```c
void selectionSort(int arr[], int size) {
    for(int i = 0; i < size - 1; i++) {
        int minIndex = i;
        
        // Find minimum element in unsorted part
        for(int j = i + 1; j < size; j++) {
            if(arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        
        // Swap minimum with first unsorted element
        if(minIndex != i) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}
```

**Visual Example**:
```
Initial: [64, 25, 12, 22, 11]

Pass 1: [11, 25, 12, 22, 64]  (11 is minimum)
Pass 2: [11, 12, 25, 22, 64]  (12 is minimum)
Pass 3: [11, 12, 22, 25, 64]  (22 is minimum)
Pass 4: [11, 12, 22, 25, 64]  (25 is minimum)
```

### 6.3 Insertion Sort

**Concept**: Build sorted array one element at a time

**Time Complexity**: O(n²), O(n) for nearly sorted

**Space Complexity**: O(1)

**Stable**: Yes

```c
void insertionSort(int arr[], int size) {
    for(int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        
        // Move elements greater than key one position ahead
        while(j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        
        arr[j + 1] = key;
    }
}
```

**Visual Example**:
```
Initial: [12, 11, 13, 5, 6]

Step 1: [11, 12, 13, 5, 6]   (Insert 11)
Step 2: [11, 12, 13, 5, 6]   (13 already in place)
Step 3: [5, 11, 12, 13, 6]   (Insert 5)
Step 4: [5, 6, 11, 12, 13]   (Insert 6)
```

### Comparison of Sorting Algorithms

```
Algorithm      | Time (Best) | Time (Avg) | Time (Worst) | Space | Stable
---------------|-------------|------------|--------------|-------|--------
Bubble Sort    | O(n)        | O(n²)      | O(n²)        | O(1)  | Yes
Selection Sort | O(n²)       | O(n²)      | O(n²)        | O(1)  | No
Insertion Sort | O(n)        | O(n²)      | O(n²)        | O(1)  | Yes
```

---

## 7. Common Pitfalls and Best Practices

### Pitfall 1: Array Index Out of Bounds
```c
// WRONG
int arr[5];
arr[5] = 10;  // Index 5 doesn't exist (valid: 0-4)

// CORRECT
int arr[5];
arr[4] = 10;  // Last valid index is size-1
```

### Pitfall 2: Not Initializing Arrays
```c
// WRONG - Contains garbage values
int arr[5];
printf("%d", arr[0]);  // Unpredictable output

// CORRECT
int arr[5] = {0};  // All elements initialized to 0
```

### Pitfall 3: Forgetting Array Size
```c
// WRONG - Size information lost
void printArray(int arr[]) {
    // How many elements to print?
}

// CORRECT - Pass size as parameter
void printArray(int arr[], int size) {
    for(int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
}
```

### Pitfall 4: Comparing Arrays with ==
```c
// WRONG
int arr1[] = {1, 2, 3};
int arr2[] = {1, 2, 3};
if(arr1 == arr2)  // Compares addresses, not contents

// CORRECT
int areEqual(int arr1[], int arr2[], int size) {
    for(int i = 0; i < size; i++) {
        if(arr1[i] != arr2[i])
            return 0;
    }
    return 1;
}
```

### Pitfall 5: Returning Local Arrays
```c
// WRONG - Returns pointer to local variable
int* createArray() {
    int arr[5] = {1, 2, 3, 4, 5};
    return arr;  // Undefined behavior
}

// CORRECT - Use static or dynamic allocation
int* createArray() {
    static int arr[5] = {1, 2, 3, 4, 5};
    return arr;
}
```

### Best Practices

1. **Always Initialize Arrays**
   ```c
   int arr[100] = {0};  // Good practice
   ```

2. **Use Constants for Size**
   ```c
   #define SIZE 10
   int arr[SIZE];
   ```

3. **Check Boundaries**
   ```c
   if(index >= 0 && index < size) {
       arr[index] = value;
   }
   ```

4. **Use sizeof Correctly**
   ```c
   int size = sizeof(arr) / sizeof(arr[0]);
   ```

5. **Pass Size with Arrays**
   ```c
   void func(int arr[], int size) { }
   ```

6. **Clear Naming Convention**
   ```c
   int studentScores[50];  // Clear purpose
   int arr[50];            // Less clear
   ```

---

## Summary

### Key Takeaways:
- Arrays store multiple values of same type in contiguous memory
- Use zero-based indexing (first element at index 0)
- Always pass size when passing arrays to functions
- Multi-dimensional arrays are arrays of arrays
- Common operations: search, sort, insert, delete, reverse
- Linear search works on any array, binary search needs sorted array
- Different sorting algorithms have different trade-offs

### Practice Checklist:
✓ Declare and initialize arrays  
✓ Access and modify array elements  
✓ Traverse arrays using loops  
✓ Implement searching algorithms  
✓ Implement sorting algorithms  
✓ Work with 2D arrays (matrices)  
✓ Handle array operations (insert, delete, merge)  
✓ Avoid common pitfalls  

---

**Next Steps**: Practice the exercises provided in the roadmap and move on to Strings, which are character arrays with special properties!