#include <stdio.h>

int main() {
    int n, i, j;

    // =========================================================
// 1. Solid Square Pattern
printf("1. Solid Square (n=5):\n");
n = 5;
for(i = 1; i <= n; i++) {        // i = row
        for(j = 1; j <= n; j++) {    // j = column
            printf("* ");
        }
        printf("\n");
    }
    /* DRY RUN (Structured):
       i=1 → j runs 1 to 5 → * * * * *
       i=2 → j runs 1 to 5 → * * * * *
       i=3 → j runs 1 to 5 → * * * * *
       i=4 → j runs 1 to 5 → * * * * *
       i=5 → j runs 1 to 5 → * * * * *
       Output: 5×5 solid square
    */
    printf("\n");

    // =========================================================
    // 2. Hollow Square
    printf("2. Hollow Square (n=6):\n");
    n = 6;
    for(i = 1; i <= n; i++) {
        for(j = 1; j <= n; j++) {
            if(i == 1 || i == n || j == 1 || j == n)
                printf("* ");
            else
                printf("  ");
        }
        printf("\n");
    }
    /* DRY RUN:
       Row 1 (i=1) → border row → all * → * * * * * *
       Row 2 to 5 → only j=1 and j=6 are border → *     *
       Row 6 (i=6) → border row → all * → * * * * * *
       Result → Only outer boundary has *, inside empty
    */
    printf("\n");

    // =========================================================
    // 3. Right Triangle (Left Aligned)
    printf("3. Left-Aligned Right Triangle (n=5):\n");
    n = 5;
    for(i = 1; i <= n; i++) {
        for(j = 1; j <= i; j++) {
            printf("* ");
        }
        printf("\n");
    }
    /* DRY RUN:
       i=1 → j=1 to 1 → *
       i=2 → j=1 to 2 → * *
       i=3 → j=1 to 3 → * * *
       i=4 → j=1 to 4 → * * * *
       i=5 → j=1 to 5 → * * * * *
    */
    printf("\n");

    // =========================================================
    // 4. Right-Aligned Triangle
    printf("4. Right-Aligned Triangle (n=5):\n");
    n = 5;
    for(i = 1; i <= n; i++) {
        for(j = 1; j <= n-i; j++) printf("  ");   // spaces
        for(j = 1; j <= i; j++)    printf("* ");  // stars
        printf("\n");
    }
    /* DRY RUN:
       i=1 → spaces:4 → stars:1 →     *
       i=2 → spaces:3 → stars:2 →    * *
       i=3 → spaces:2 → stars:3 →   * * *
       i=4 → spaces:1 → stars:4 →  * * * *
       i=5 → spaces:0 → stars:5 → * * * * *
    */
    printf("\n");

    // =========================================================
    // 5. Inverted Right Triangle
    printf("5. Inverted Triangle (n=5):\n");
    n = 5;
    for(i = n; i >= 1; i--) {
        for(j = 1; j <= i; j++) {
            printf("* ");
        }
        printf("\n");
    }
    /* DRY RUN:
       i=5 → * * * * *
       i=4 → * * * *
       i=3 → * * *
       i=2 → * *
       i=1 → *
    */
    printf("\n");

    // =========================================================
    // 6. Pyramid Pattern
    printf("6. Pyramid (n=5):\n");
    n = 5;
    for(i = 1; i <= n; i++) {
        for(j = 1; j <= n-i; j++) printf("  ");
        for(j = 1; j <= 2*i-1; j++) printf("* ");
        printf("\n");
    }
    /* DRY RUN (spaces | stars):
       i=1 → sp:4 → stars:1  →     *
       i=2 → sp:3 → stars:3  →    * * *
       i=3 → sp:2 → stars:5  →   * * * * *
       i=4 → sp:1 → stars:7  →  * * * * * * *
       i=5 → sp:0 → stars:9  → * * * * * * * * *
    */
    printf("\n");

    // =========================================================
    // 7. Full Diamond
    printf("7. Diamond (n=5):\n");
    n = 5;
    // Upper half
    for(i = 1; i <= n; i++) {
        for(j = 1; j <= n-i; j++) printf("  ");
        for(j = 1; j <= 2*i-1; j++) printf("* ");
        printf("\n");
    }
    // Lower half
    for(i = n-1; i >= 1; i--) {
        for(j = 1; j <= n-i; j++) printf("  ");
        for(j = 1; j <= 2*i-1; j++) printf("* ");
        printf("\n");
    }
    /* DRY RUN: Upper same as pyramid
       Lower half reverses from i=4 down to i=1 → symmetric diamond
    */
    printf("\n");

    // =========================================================
    // 8. Number Triangle (1 12 123...)
    printf("8. Number Increasing Triangle:\n");
    n = 5;
    for(i = 1; i <= n; i++) {
        for(j = 1; j <= i; j++) {
            printf("%d ", j);
        }
        printf("\n");
    }
    /* DRY RUN:
       i=1 → 1
       i=2 → 1 2
       i=3 → 1 2 3
       i=4 → 1 2 3 4
       i=5 → 1 2 3 4 5
    */
    printf("\n");

    // =========================================================
    // 9. Floyd's Triangle
    printf("9. Floyd's Triangle:\n");
    n = 5;
    int num = 1;
    for(i = 1; i <= n; i++) {
        for(j = 1; j <= i; j++) {
            printf("%d ", num++);
        }
        printf("\n");
    }
    /* DRY RUN:
       Row1 → 1
       Row2 → 2 3
       Row3 → 4 5 6
       Row4 → 7 8 9 10
       Row5 → 11 12 13 14 15
    */
    printf("\n");

    // =========================================================
    // 10. Pascal's Triangle
    printf("10. Pascal's Triangle (n=6 rows):\n");
    n = 6;
    for(i = 0; i < n; i++) {
        int val = 1;
        for(j = 1; j <= n-i; j++) printf("  ");
        for(j = 0; j <= i; j++) {
            printf("%4d", val);
            val = val * (i - j) / (j + 1);
        }
        printf("\n");
    }
    /* DRY RUN (Row = C = binomial coefficient):
       Row0 →          1
       Row1 →        1   1
       Row2 →      1   2   1
       Row3 →    1   3   3   1
       Row4 →  1   4   6   4   1
       Row5 → 1   5  10  10   5   1
    */
    printf("\n");

    // =========================================================
    // 11. Butterfly Pattern
    printf("11. Butterfly Pattern:\n");
    n = 5;
    // Upper
    for(i = 1; i <= n; i++) {
        for(j = 1; j <= i; j++) printf("* ");
        for(j = 1; j <= 2*(n-i); j++) printf("  ");
        for(j = 1; j <= i; j++) printf("* ");
        printf("\n");
    }
    // Lower
    for(i = n; i >= 1; i--) {
        for(j = 1; j <= i; j++) printf("* ");
        for(j = 1; j <= 2*(n-i); j++) printf("  ");
        for(j = 1; j <= i; j++) printf("* ");
        printf("\n");
    }
    /* DRY RUN (left stars | gap | right stars):
       i=1 → *         * 
       i=2 → * *     * *
       i=3 → * * * * * * *
       i=4 → * * * * * * * *
       i=5 → * * * * * * * * *
       Then mirror reverse → looks like butterfly wings
    */
    printf("\n");

    // =========================================================
    // 12. Hollow Diamond
    printf("12. Hollow Diamond:\n");
    n = 5;
    // Upper half
    for(i = 1; i <= n; i++) {
        for(j = 1; j <= n-i; j++) printf("  ");
        printf("* ");
        if(i > 1) {
            for(j = 1; j <= 2*i-3; j++) printf("  ");
            printf("* ");
        }
        printf("\n");
    }
    // Lower half
    for(i = n-1; i >= 1; i--) {
        for(j = 1; j <= n-i; j++) printf("  ");
        printf("* ");
        if(i > 1) {
            for(j = 1; j <= 2*i-3; j++) printf("  ");
            printf("* ");
        }
        printf("\n");
    }
    /* DRY RUN:
       Only prints * at two ends of each row, middle is space
       Upper: gradually increases distance between two *
       Lower: gradually decreases → hollow diamond shape
    */

    return 0;
}