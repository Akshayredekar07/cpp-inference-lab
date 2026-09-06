#include <stdio.h>

// Find maximum value in an array
int findMax(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// Find minimum value in an array
int findMin(int arr[], int size) {
    int min = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

// Calculate the sum of all array elements
int sumArray(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

// Calculate the average of all array elements
double averageArray(int arr[], int size) {
    if (size == 0) return 0.0;
    int sum = sumArray(arr, size);
    return (double)sum / size;
}

// Reverse the array in place
void reverseArray(int arr[], int size) {
    int temp;
    for (int i = 0; i < size / 2; i++) {
        temp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = temp;
    }
}

/*
Dry Run of reverseArray()

Input:
    arr = {7, 2, 10, 4, 1, 8}
    size = 6

Step-by-step swaps:
i = 0:
    temp = arr[0] = 7
    arr[0] = arr[5] = 8
    arr[5] = temp = 7
    arr now: {8, 2, 10, 4, 1, 7}

i = 1:
    temp = arr[1] = 2
    arr[1] = arr[4] = 1
    arr[4] = temp = 2
    arr now: {8, 1, 10, 4, 2, 7}

i = 2:
    temp = arr[2] = 10
    arr[2] = arr[3] = 4
    arr[3] = temp = 10
    arr now: {8, 1, 4, 10, 2, 7}

Exit loop (i == size/2).

FINAL ARRAY after reverse: {8, 1, 4, 10, 2, 7}
*/

// Print array elements
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Copy array elements to another array
void copyArray(int source[], int dest[], int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = source[i];
    }
}
/*
Dry Run of copyArray()

Input:
    source = {7, 2, 10, 4, 1, 8}
    dest   = {0, 0, 0, 0, 0, 0}
    size   = 6

Step-by-step copying:
i = 0:
    dest[0] = source[0] = 7
    dest now: {7, 0, 0, 0, 0, 0}

i = 1:
    dest[1] = source[1] = 2
    dest now: {7, 2, 0, 0, 0, 0}

i = 2:
    dest[2] = source[2] = 10
    dest now: {7, 2, 10, 0, 0, 0}

i = 3:
    dest[3] = source[3] = 4
    dest now: {7, 2, 10, 4, 0, 0}

i = 4:
    dest[4] = source[4] = 1
    dest now: {7, 2, 10, 4, 1, 0}

i = 5:
    dest[5] = source[5] = 8
    dest now: {7, 2, 10, 4, 1, 8}

Exit loop (i == size).

FINAL DEST ARRAY after copy: {7, 2, 10, 4, 1, 8}
*/

// Insert an element into the array
void insertElement(int arr[], int *size, int pos, int value) {
    for (int i = *size; i > pos; i--) {
        arr[i] = arr[i-1];
    }
    arr[pos] = value;
    (*size)++;
}

/*
Dry Run of insertElement()

Input:
    arr   = {7, 2, 10, 4, 1, 8}
    size  = 6
    pos   = 2
    value = 99

Goal: Insert 99 at position 2

Step-by-step insertion:
Initial array: {7, 2, 10, 4, 1, 8}
Initial size: 6

for (int i = size; i > pos; i--):

i = 6:
    arr[6] = arr[5] = 8
    arr now: {7, 2, 10, 4, 1, 8, 8}
i = 5:
    arr[5] = arr[4] = 1
    arr now: {7, 2, 10, 4, 1, 1, 8}
i = 4:
    arr[4] = arr[3] = 4
    arr now: {7, 2, 10, 4, 4, 1, 8}
i = 3:
    arr[3] = arr[2] = 10
    arr now: {7, 2, 10, 10, 4, 1, 8}

After loop, insert value at pos:
    arr[2] = 99
    arr now: {7, 2, 99, 10, 4, 1, 8}

size is incremented to 7.

Final array: {7, 2, 99, 10, 4, 1, 8}
Final size: 7
*/

void deleteElement(int arr[], int *size, int pos){
    // Shift elements to left
    for(int i=pos; i<*size-1; i++){
        arr[i]=arr[i+1];
    }
    (*size)--;
}

/*
Dry Run of deleteElement()

Input:
    arr  = {7, 2, 10, 4, 1, 8}
    size = 6
    pos  = 3

Goal: Delete element at position 3 (i.e., value 4)

Step-by-step deletion:
Initial array: {7, 2, 10, 4, 1, 8}
Initial size: 6

for (int i = pos; i < size-1; i++):
i = 3:
    arr[3] = arr[4] = 1
    arr now: {7, 2, 10, 1, 1, 8}
i = 4:
    arr[4] = arr[5] = 8
    arr now: {7, 2, 10, 1, 8, 8}

After loop, decrement size:
    size = 5

Array after deletion: {7, 2, 10, 1, 8}
Final size: 5
*/





int main() {
    int arr[6] = {7, 2, 10, 4, 1, 8};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Array elements: ");
    printArray(arr, size);

    int max = findMax(arr, size);
    int min = findMin(arr, size);
    int sum = sumArray(arr, size);
    double avg = averageArray(arr, size);

    printf("Maximum value: %d\n", max);
    printf("Minimum value: %d\n", min);
    printf("Sum: %d\n", sum);
    printf("Average: %.2f\n", avg);

    printf("Reversing the array...\n");
    reverseArray(arr, size);

    printf("Array after reverse: ");
    printArray(arr, size);

    printf("Copying the array...\n");
    int copy[size];
    copyArray(arr, copy, size);
    printf("Copied array: ");
    printArray(copy, size);
    printf("Inserting an element into the array...\n");
    insertElement(arr, &size, 2, 99);
    printf("Array after insertion: ");
    printArray(arr, size);
    printf("Deleting an element from the array...\n");
    deleteElement(arr, &size, 3);
    printf("Array after deletion: ");
    printArray(arr, size);
    
    return 0;
}
