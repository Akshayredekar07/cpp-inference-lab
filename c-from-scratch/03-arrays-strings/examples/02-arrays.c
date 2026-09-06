
#include <stdio.h>

int main(void) {
    /* Example declarations */
    int numbers[5];
    float prices[10];
    char name[20];

    /* Initialize at declaration */
    int arr_init[5] = {10, 20, 30, 40, 50};

    /* Partial initialization (remaining elements set to 0) */
    int arr_partial[5] = {10, 20}; // becomes {10,20,0,0,0}

    /* Automatic size calculation */
    int arr_auto[] = {10, 20, 30, 40}; // size = 4

    /* Initialize all to zero */
    int arr_zero[5] = {0}; // {0,0,0,0,0}

    /* Initialize after declaration */
    int arr_after[5];
    arr_after[0] = 10;
    arr_after[1] = 20;
    arr_after[2] = 30;
    arr_after[3] = 40;
    arr_after[4] = 50;

    /* Another initializer form */
    int arr_simple[5] = {10, 20, 30, 40, 50};

    /* Reading values */
    int first = arr_simple[0];
    int third = arr_simple[2];

    /* Modifying values */
    arr_simple[1] = 25; // now {10,25,30,40,50}

    /* Print arr_simple using for-loop */
    printf("arr_simple: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr_simple[i]);
    }
    printf("\n");

    /* Print arr_init using while-loop */
    printf("arr_init: ");
    int j = 0;
    while (j < 5) {
        printf("%d ", arr_init[j]);
        j++;
    }
    printf("\n");

    /* Print examples showing partial and zero initialization */
    printf("arr_partial: ");
    for (int k = 0; k < 5; k++) printf("%d ", arr_partial[k]);
    printf("\n");

    printf("arr_zero: ");
    for (int k = 0; k < 5; k++) printf("%d ", arr_zero[k]);
    printf("\n");

    (void)first; /* keep compiler quiet if unused */
    (void)third;

    

    return 0;
}