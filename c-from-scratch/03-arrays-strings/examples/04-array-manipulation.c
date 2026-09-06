#include <stdio.h>


//Merge two arrays
void mergeArrays(int arr1[], int size1, int arr2[], int size2, int merged[]){
    for(int i = 0; i < size1; i++){
        merged[i] = arr1[i];
    }
    for(int i = 0; i < size2; i++){
        merged[size1 + i] = arr2[i];
    }
}

/*
Dry Run of mergeArrays()

Input:
    arr1 = {1, 2, 3}
    size1 = 3
    arr2 = {4, 5, 6}
    size2 = 3
    merged = {0, 0, 0, 0, 0, 0}

Step-by-step merging:
i = 0:
    merged[0] = arr1[0] = 1
    merged now: {1, 0, 0, 0, 0, 0}
i = 1:
    merged[1] = arr1[1] = 2
    merged now: {1, 2, 0, 0, 0, 0}
i = 2:
    merged[2] = arr1[2] = 3
    merged now: {1, 2, 3, 0, 0, 0}
i = 3:
    merged[3] = arr2[0] = 4
    merged now: {1, 2, 3, 4, 0, 0}
i = 4:
    merged[4] = arr2[1] = 5
    merged now: {1, 2, 3, 4, 5, 0}
i = 5:
    merged[5] = arr2[2] = 6
    merged now: {1, 2, 3, 4, 5, 6}

Exit loop (i == size2).

FINAL MERGED ARRAY after merge: {1, 2, 3, 4, 5, 6}
*/

// Find the index of an element in an array
int findIndex(int arr[], int size, int element){
    for(int i = 0; i < size; i++){
        if(arr[i] == element){
            return i;
        }
    }
    return -1;
}


//finding frequency of an element in an array
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

/*
Dry Run of findFrequency()

Input:
    arr = {4, 3, 4, 2, 3, 1, 4}
    size = 7

Step-by-step:

visited = {0, 0, 0, 0, 0, 0, 0}

i = 0:
    visited[0] == 0, process arr[0] = 4
    count = 1
    j = 1: arr[1]=3 != 4 -> skip
    j = 2: arr[2]=4 == 4 -> count=2, visited[2]=1
    j = 3: arr[3]=2 != 4 -> skip
    j = 4: arr[4]=3 != 4 -> skip
    j = 5: arr[5]=1 != 4 -> skip
    j = 6: arr[6]=4 == 4 -> count=3, visited[6]=1
    Print: 4 occurs 3 times

i = 1:
    visited[1] == 0, process arr[1] = 3
    count = 1
    j = 2: arr[2]=4 != 3 -> skip
    j = 3: arr[3]=2 != 3 -> skip
    j = 4: arr[4]=3 == 3 -> count=2, visited[4]=1
    j = 5: arr[5]=1 != 3 -> skip
    j = 6: arr[6]=4 != 3 -> skip
    Print: 3 occurs 2 times

i = 2:
    visited[2] == 1, continue

i = 3:
    visited[3] == 0, process arr[3] = 2
    count = 1
    j = 4: arr[4]=3 != 2 -> skip
    j = 5: arr[5]=1 != 2 -> skip
    j = 6: arr[6]=4 != 2 -> skip
    Print: 2 occurs 1 times

i = 4:
    visited[4] == 1, continue

i = 5:
    visited[5] == 0, process arr[5] = 1
    count = 1
    j = 6: arr[6]=4 != 1 -> skip
    Print: 1 occurs 1 times

i = 6:
    visited[6] == 1, continue

Printed output:
4 occurs 3 times
3 occurs 2 times
2 occurs 1 times
1 occurs 1 times
*/


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

/*
Dry Run of removeDuplicates()

Input:
    arr = {4, 3, 4, 2, 3, 1, 4}
    size = 7

Step-by-step execution:

Initial array: {4, 3, 4, 2, 3, 1, 4}
newSize = 0

i = 0:
    isDuplicate = 0
    (no elements in [0, newSize), so skip inner loop)
    Not duplicate, arr[0] = 4 to arr[0]
    newSize = 1
    arr: {4, ...}

i = 1:
    isDuplicate = 0
    j=0: arr[1]=3 != arr[0]=4
    Not duplicate, arr[1] = 3 to arr[1]
    newSize = 2
    arr: {4, 3, ...}

i = 2:
    isDuplicate = 0
    j=0: arr[2]=4 == arr[0]=4 -> isDuplicate=1
    Duplicate found, skip

i = 3:
    isDuplicate = 0
    j=0: arr[3]=2 != arr[0]=4
    j=1: arr[3]=2 != arr[1]=3
    Not duplicate, arr[2] = 2
    newSize = 3
    arr: {4, 3, 2, ...}

i = 4:
    isDuplicate = 0
    j=0: arr[4]=3 == arr[0]=4? No
    j=1: arr[4]=3 == arr[1]=3? Yes -> isDuplicate=1
    Duplicate found, skip

i = 5:
    isDuplicate = 0
    j=0: arr[5]=1 != arr[0]=4
    j=1: arr[5]=1 != arr[1]=3
    j=2: arr[5]=1 != arr[2]=2
    Not duplicate, arr[3] = 1
    newSize = 4
    arr: {4, 3, 2, 1, ...}

i = 6:
    isDuplicate = 0
    j=0: arr[6]=4 == arr[0]=4 -> isDuplicate=1
    Duplicate found, skip

Final array up to newSize:
{4, 3, 2, 1}
Return value: 4

Output:
Array with duplicates removed: {4, 3, 2, 1}
New size: 4
*/


//linear search
int linearSearch(int arr[], int size, int key){
    for(int i = 0; i < size; i++){
        if(arr[i] == key){
            return i;
        }
    }
    return -1;
}

// binary search
int binarySearch(int arr[], int size, int key){
    int left = 0;
    int right = size - 1;
    while(left <= right){
        int mid = (left + right) / 2;
        if(arr[mid] == key){
            return mid;
        }
        else if(arr[mid] < key){
            left = mid + 1;
        }
        else{
            right = mid - 1;
        }
    }
    return -1;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(arr) / sizeof(arr[0]);

    // Merge arrays
    int merged[size + size];
    mergeArrays(arr, size, arr, size, merged);
    printf("Merged array: ");
    for(int i = 0; i < size + size; i++){
        printf("%d ", merged[i]);
    }
    printf("\n");

    // Find Frequency
    printf("Frequency of elements:\n");
    findFrequency(arr, size);
    printf("\n");

    // Remove Duplicates
    int newSize = removeDuplicates(arr, size);
    printf("Array with duplicates removed: ");
    for(int i = 0; i < newSize; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("New size: %d\n", newSize);

    // Find Index
    int index = findIndex(arr, size, 5);
    printf("Index of 5: %d\n", index);
    index = findIndex(arr, size, 11);
    printf("Index of 11: %d\n", index);

    // Binary Search
    printf("Index of 5 in binary search: %d\n", binarySearch(arr, size, 5));
    printf("Index of 11 in binary search: %d\n", binarySearch(arr, size, 11));

    // Linear Search
    printf("Linear search for 5: index = %d\n", linearSearch(arr, size, 5));
    printf("Linear search for 11: index = %d\n", linearSearch(arr, size, 11));

    return 0;
}