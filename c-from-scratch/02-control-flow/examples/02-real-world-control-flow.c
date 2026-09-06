#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// -----------------------------
// 1. IF-ELSE IF-ELSE (Real use: User login attempts limiter)
int main() {
    int failed_attempts = 3;

    if (failed_attempts >= 5) {
        printf("Account locked due to too many failed attempts!\n");
    } else if (failed_attempts >= 3) {
        printf("Warning: High number of failed login attempts (%d). Account will lock soon.\n", failed_attempts);
    } else if (failed_attempts > 0) {
        printf("Invalid credentials. %d attempt(s) remaining.\n", 5 - failed_attempts);
    } else {
        printf("Login successful! Welcome.\n");
    }

    // -----------------------------
    // 2. SWITCH (Real use: Menu-driven ATM / Embedded device menu)
    printf("\n--- ATM Menu ---\n");
    int choice = 2;  // suppose user pressed 2

    switch (choice) {
        case 1: printf("Balance Enquiry selected\n"); break;
        case 2: printf("Cash Withdrawal selected\n"); break;
        case 3: printf("PIN Change selected\n"); break;
        case 4: printf("Mini Statement selected\n"); break;
        case 5: printf("Exiting... Thank you!\n"); return 0;
        default: printf("Invalid option! Please try again.\n");
    }

    // -----------------------------
    // 3. FOR LOOP (Real use: Processing sensor data array / batch jobs)
    printf("\nTemperature readings (last 10 hours):\n");
    float temps[10] = {22.5, 23.1, 24.0, 26.3, 28.7, 29.2, 27.8, 25.4, 23.9, 22.8};

    float sum = 0;
    for (int i = 0; i < 10; i++) {
        printf("Hour %d: %.1f°C\n", i + 1, temps[i]);
        sum += temps[i];
    }
    printf("Average temperature: %.2f°C\n", sum / 10);

    // -----------------------------
    // 4. WHILE LOOP (Real use: Reading serial/UART data until delimiter)
    printf("\nReading incoming serial data until '\\n':\n");
    char buffer[128] = "SensorData:123.45\nMoreData"; // simulated incoming stream
    int idx = 0;

    while (buffer[idx] != '\0' && buffer[idx] != '\n') {
        printf("%c", buffer[idx]);
        idx++;
    }
    printf("\nMessage received and processed.\n");

    // -----------------------------
    // 5. DO-WHILE (Real use: Ask user for valid input — runs at least once)
    int pin;
    do {
        printf("\nEnter 4-digit PIN: ");
        scanf("%d", &pin);
        if (pin < 1000 || pin > 9999) {
            printf("Invalid PIN! Must be 4 digits.\n");
        }
    } while (pin < 1000 || pin > 9999);
    printf("PIN accepted: %d\n", pin);

    // -----------------------------
    // 6. BREAK & CONTINUE (Real use: Parsing CSV line, skipping comments & empty fields)
    printf("\nParsing CSV line (skip empty fields and stop at comment):\n");
    char csv[] = "100,John,,25000,#comment,ignore rest";
    char *token = strtok(csv, ",");

    while (token != NULL) {
        if (token[0] == '#') {
            printf("Comment found, stopping parse.\n");
            break;                     // stop processing line on comment
        }
        if (strlen(token) == 0) {
            token = strtok(NULL, ",");
            continue;                  // skip empty fields
        }
        printf("Field: %s\n", token);
        token = strtok(NULL, ",");
    }

    // -----------------------------
    // 7. NESTED LOOPS (Real use: Generating multiplication table or 2D game board)
    printf("\nMultiplication Table (1-5):\n");
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 10; j++) {
            printf("%4d", i * j);
        }
        printf("\n");
    }

    // -----------------------------
    // 8. GOTO (Real use: Error cleanup in old C code or resource deallocation)
    // Common in embedded systems when you have multiple failure points
    FILE *logfile = NULL;
    char *buffer_ptr = NULL;

    logfile = fopen("app.log", "a");
    if (!logfile) {
        printf("Failed to open log file!\n");
        goto cleanup;
    }

    buffer_ptr = malloc(1024);
    if (!buffer_ptr) {
        printf("Memory allocation failed!\n");
        goto cleanup;
    }

    fprintf(logfile, "Application started successfully.\n");
    printf("Everything initialized correctly.\n");

cleanup:
    if (buffer_ptr) free(buffer_ptr);
    if (logfile)    fclose(logfile);

    return 0;
}