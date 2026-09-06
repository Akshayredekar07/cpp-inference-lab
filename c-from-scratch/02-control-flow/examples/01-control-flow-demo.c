#include <stdio.h>

int main() {

    int a = 25;

    // 1. IF - ELSE IF - ELSE
    printf("IF-ELSE Demo:\n");
    if (a > 30) {
        printf("a is greater than 30\n");
    } else if (a == 25) {
        printf("a is exactly 25\n");
    } else {
        printf("a is less than 25\n");
    }

    // 2. SWITCH CASE
    printf("\nSWITCH Demo:\n");
    int day = 3;
    switch (day) {
        case 1: printf("Monday\n"); break;
        case 2: printf("Tuesday\n"); break;
        case 3: printf("Wednesday\n"); break;
        case 4: printf("Thursday\n"); break;
        case 5: printf("Friday\n"); break;
        default: printf("Weekend\n");
    }

    // 3. FOR LOOP
    printf("\nFOR Loop (1 to 5):\n");
    for (int i = 1; i <= 5; i++) {
        printf("%d ", i);
    }

    // 4. WHILE LOOP
    printf("\n\nWHILE Loop (5 to 1):\n");
    int x = 5;
    while (x > 0) {
        printf("%d ", x);
        x--;
    }

    // 5. DO-WHILE LOOP
    printf("\n\nDO-WHILE Loop (runs at least once):\n");
    int y = 0;
    do {
        printf("Value of y: %d\n", y);
        y++;
    } while (y < 3);

    // 6. BREAK & CONTINUE inside loop
    printf("\nBREAK & CONTINUE Demo:\n");
    for (int i = 1; i <= 10; i++) {
        if (i == 3) {
            continue;  // skip 3
        }
        if (i == 8) {
            break;     // stop loop at 8
        }
        printf("%d ", i);
    }

    // 7. NESTED LOOPS
    printf("\n\nNested Loops (3x3 grid):\n");
    for (int r = 1; r <= 3; r++) {
        for (int c = 1; c <= 3; c++) {
            printf("(%d, %d) ", r, c);
        }
        printf("\n");
    }

    // 8. GOTO STATEMENT
    printf("\nGOTO Demo:\n");
    int z = 0;
start_point:
    printf("z = %d\n", z);
    z++;
    if (z < 3)
        goto start_point;
    printf("Exited goto loop.\n");

    return 0;
}
