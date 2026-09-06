#include <stdio.h>

int main() {
    int n = 7;  // height of letters (odd number recommended for symmetry)
    int i, j;

    // =====================================================
    // 1. Letter A
    printf("1. Letter A:\n");
    for(i = 1; i <= n; i++) {
        for(j = 1; j <= n; j++) {
            if(j == 1 || j == n)               // left & right vertical
                printf("*");
            else if(i == 1 || i == (n/2 + 1))   // top & middle horizontal
                printf("*");
            else
                printf(" ");
        }
        printf("\n");
    }
    /* Output:
       *****  
       *   *  
       *   *  
       *****  
       *   *  
       *   *  
       *   *  
    */

    printf("\n");

    // =====================================================
    // 2. Letter B
    printf("2. Letter B:\n");
    for(i = 1; i <= n; i++) {
        for(j = 1; j <= n; j++) {
            if(j == 1 || j == n)                     // vertical lines
                printf("*");
            else if(i == 1 || i == n || i == n/2 + 1) // three horizontals
                printf("*");
            else
                printf(" ");
        }
        printf("\n");
    }

    printf("\n");

    // =====================================================
    // 3. Letter C
    printf("3. Letter C:\n");
    for(i = 1; i <= n; i++) {
        for(j = 1; j <= n; j++) {
            if(i == 1 || i == n || j == 1)
                printf("*");
            else
                printf(" ");
        }
        printf("\n");
    }

    printf("\n");

    // =====================================================
    // 4. Letter E
    printf("4. Letter E:\n");
    for(i = 1; i <= n; i++) {
        for(j = 1; j <= n; j++) {
            if(j == 1 || i == 1 || i == n || i == n/2 + 1)
                printf("*");
            else
                printf(" ");
        }
        printf("\n");
    }

    printf("\n");

    // =====================================================
    // 5. Letter H
    printf("5. Letter H:\n");
    for(i = 1; i <= n; i++) {
        for(j = 1; j <= n; j++) {
            if(j == 1 || j == n || i == n/2 + 1)
                printf("*");
            else
                printf(" ");
        }
        printf("\n");
    }

    printf("\n");

    // =====================================================
    // 6. Letter O (Hollow)
    printf("6. Letter O (Hollow):\n");
    for(i = 1; i <= n; i++) {
        for(j = 1; j <= n; j++) {
            if(i == 1 || i == n || j == 1 || j == n)
                printf("*");
            else
                printf(" ");
        }
        printf("\n");
    }

    printf("\n");

    // =====================================================
    // 7. Letter X
    printf("7. Letter X:\n");
    for(i = 1; i <= n; i++) {
        for(j = 1; j <= n; j++) {
            if(i == j || i + j == n + 1)
                printf("*");
            else
                printf(" ");
        }
        printf("\n");
    }

    printf("\n");

    // =====================================================
    // 8. Letter K
    printf("8. Letter K:\n");
    int mid = n / 2 + 1;
    for(i = 1; i <= n; i++) {
        for(j = 1; j <= mid; j++) {
            if(j == 1 || (i + j == mid + 1) || (i - j == mid - 1))
                printf("*");
            else
                printf(" ");
        }
        printf("\n");
    }

    printf("\n");

    return 0;
}