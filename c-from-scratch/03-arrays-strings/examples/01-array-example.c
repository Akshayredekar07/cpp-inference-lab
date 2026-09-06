// Format specifiers used in this program:
// %d  - for printing int variables (decimal integer)
// %zu - for printing size_t variables (unsigned decimal, commonly returned by sizeof)

#include <stdio.h>

int main(){

    int numbers[5] = {10, 20, 30, 40, 50};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    // sizeof(numbers) = 20 bytes (5 * 4)
    // sizeof(numbers[0]) = 4 bytes
    // size = 20 / 4 = 5
    // printf("Size of array: %d\n", size);
    // printf("Elements of array: ");
    // for(int i = 0; i < size; i++){
    //     printf("%d ", numbers[i]);
    // }
    // printf("\n");

    // Multi dimensional arrays
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    int size2 = sizeof(matrix) / sizeof(matrix[0]);
    // sizeof(matrix) = 48 bytes (3 * 4 * 4)
    // sizeof(matrix[0]) = 16 bytes (4 * 4)
    // size2 = 48 / 16 = 3
    printf("Size of matrix (bytes): %zu\n", sizeof(matrix));
    printf("Size of matrix[0] (bytes): %zu\n", sizeof(matrix[0]));
    printf("Size of matrix[0][0] (bytes): %zu\n", sizeof(matrix[0][0]));
    printf("Number of rows: %d\n", size2);
    printf("Number of columns: %zu\n", sizeof(matrix[0]) / sizeof(matrix[0][0]));
    printf("Elements of matrix:\n");
    for(int i = 0; i < size2; i++){
        for(int j = 0; j < sizeof(matrix[0]) / sizeof(matrix[0][0]); j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("\n\n*******************\n\n");

    int matrix2[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };

    int value = matrix2[1][2];
    printf("Value of matrix2[1][2]: %d\n", value);

    matrix2[1][2] = 100;
    printf("Value of matrix2[1][2] after modification: %d\n", matrix2[1][2]);

    //Traversing the matrix2 using nested loops
    printf("Elements of matrix2:\n");
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 3; j++){
            printf("%d ", matrix2[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // three dimensional array - only declare and initialize ONCE!
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

    //Accessing the elements of the arr using nested loops
    printf("Elements of arr:\n");
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 3; j++){
            for(int k = 0; k < 4; k++){
                printf("%d ", arr[i][j][k]);
            }
        }
    }
    printf("\n");
    
    int value2 = arr[1][2][3];
    printf("Value of arr[1][2][3]: %d\n", value2);
    arr[1][2][3] = 100;
    printf("Value of arr[1][2][3] after modification: %d\n", arr[1][2][3]);
    //Traversing the arr using nested loops



    return 0;
}