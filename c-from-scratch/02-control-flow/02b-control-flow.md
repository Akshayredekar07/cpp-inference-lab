# Control Flow in C Programming

## Table of Contents
1. Introduction to Control Flow
2. Conditional Statements
3. Looping Statements
4. Jump Statements
5. Best Practices

---

## 1. Introduction to Control Flow

**What is Control Flow?**
Control flow determines the order in which statements are executed in a program. By default, C executes statements sequentially (top to bottom), but control flow statements allow us to alter this execution order based on conditions or repetitions.

**Types of Control Flow:**
- **Sequential:** Normal line-by-line execution
- **Conditional:** Decision-making (if, switch)
- **Iterative:** Repetition (loops)
- **Jump:** Unconditional transfer (break, continue, goto)

---

## 2. Conditional Statements

### 2.1 if Statement

**Syntax:**
```c
if (condition) {
    // code to execute if condition is true
}
```

**How it works:**
- Evaluates the condition (must be a boolean expression)
- If condition is true (non-zero), executes the block
- If condition is false (zero), skips the block

**Example:**
```c
int age = 18;
if (age >= 18) {
    printf("You are eligible to vote\n");
}
```

**Important Points:**
- Condition is enclosed in parentheses
- Braces {} are optional for single statement, but recommended
- Any non-zero value is considered true
- Zero is considered false

---

### 2.2 if-else Statement

**Syntax:**
```c
if (condition) {
    // executes if condition is true
} else {
    // executes if condition is false
}
```

**Example:**
```c
int number = 10;
if (number % 2 == 0) {
    printf("%d is even\n", number);
} else {
    printf("%d is odd\n", number);
}
```

---

### 2.3 if-else-if Ladder

**Syntax:**
```c
if (condition1) {
    // executes if condition1 is true
} else if (condition2) {
    // executes if condition2 is true
} else if (condition3) {
    // executes if condition3 is true
} else {
    // executes if all conditions are false
}
```

**Example:**
```c
int marks = 85;

if (marks >= 90) {
    printf("Grade: A+\n");
} else if (marks >= 80) {
    printf("Grade: A\n");
} else if (marks >= 70) {
    printf("Grade: B\n");
} else if (marks >= 60) {
    printf("Grade: C\n");
} else {
    printf("Grade: F\n");
}
```

**Key Points:**
- Conditions are checked from top to bottom
- First true condition's block executes, rest are skipped
- else is optional and executes when all conditions fail

---

### 2.4 Nested if Statements

**Definition:** An if statement inside another if statement

**Syntax:**
```c
if (condition1) {
    if (condition2) {
        // executes if both conditions are true
    }
}
```

**Example:**
```c
int age = 25;
int hasLicense = 1;

if (age >= 18) {
    if (hasLicense) {
        printf("You can drive\n");
    } else {
        printf("You need a license to drive\n");
    }
} else {
    printf("You are too young to drive\n");
}
```

**Best Practice:** Avoid deep nesting (more than 3 levels) for code readability

---

### 2.5 Ternary Operator (Conditional Operator)

**Syntax:**
```c
condition ? expression1 : expression2;
```

**How it works:**
- If condition is true, expression1 is evaluated
- If condition is false, expression2 is evaluated
- Returns the value of the evaluated expression

**Example:**
```c
int a = 10, b = 20;
int max = (a > b) ? a : b;
printf("Maximum: %d\n", max);  // Output: 20
```

**Complex Example:**
```c
int num = 15;
char* result = (num > 0) ? "Positive" : (num < 0) ? "Negative" : "Zero";
printf("%s\n", result);
```

**Use Cases:**
- Simple conditional assignments
- Compact code for simple decisions
- Avoid for complex conditions (reduces readability)

---

### 2.6 switch-case Statement

**Syntax:**
```c
switch (expression) {
    case constant1:
        // code block
        break;
    case constant2:
        // code block
        break;
    case constant3:
        // code block
        break;
    default:
        // code block
}
```

**How it works:**
- Expression is evaluated once
- Value is compared with each case constant
- Matching case's code executes
- break exits the switch
- default executes if no case matches

**Example:**
```c
int day = 3;

switch (day) {
    case 1:
        printf("Monday\n");
        break;
    case 2:
        printf("Tuesday\n");
        break;
    case 3:
        printf("Wednesday\n");
        break;
    case 4:
        printf("Thursday\n");
        break;
    case 5:
        printf("Friday\n");
        break;
    case 6:
        printf("Saturday\n");
        break;
    case 7:
        printf("Sunday\n");
        break;
    default:
        printf("Invalid day\n");
}
```

**Fall-through Behavior:**
```c
int month = 4;

switch (month) {
    case 12:
    case 1:
    case 2:
        printf("Winter\n");
        break;
    case 3:
    case 4:
    case 5:
        printf("Spring\n");
        break;
    case 6:
    case 7:
    case 8:
        printf("Summer\n");
        break;
    case 9:
    case 10:
    case 11:
        printf("Autumn\n");
        break;
    default:
        printf("Invalid month\n");
}
```

**Important Rules:**
- Expression must be integer or character type (int, char, enum)
- Cannot use float or string
- Case values must be constants (not variables)
- break is optional but usually needed
- default is optional
- Cases can be in any order

**switch vs if-else-if:**
- Use switch for checking single variable against multiple constant values
- Use if-else-if for complex conditions or range checking
- switch is often more readable for multiple discrete values

---

## 3. Looping Statements

### 3.1 for Loop

**Syntax:**
```c
for (initialization; condition; update) {
    // loop body
}
```

**Execution Flow:**
1. Initialization executes once
2. Condition is checked
3. If true, loop body executes
4. Update statement executes
5. Steps 2-4 repeat until condition becomes false

**Example:**
```c
// Print numbers 1 to 10
for (int i = 1; i <= 10; i++) {
    printf("%d ", i);
}
printf("\n");
```

**Variations:**

**Multiple initializations and updates:**
```c
for (int i = 0, j = 10; i < j; i++, j--) {
    printf("i = %d, j = %d\n", i, j);
}
```

**Infinite loop:**
```c
for (;;) {
    printf("This runs forever\n");
    // need break to exit
}
```

**Skipping parts:**
```c
int i = 0;
for (; i < 5;) {
    printf("%d ", i);
    i++;
}
```

**Common Use Cases:**
- When you know the number of iterations
- Array traversal
- Counting operations

---

### 3.2 while Loop

**Syntax:**
```c
while (condition) {
    // loop body
}
```

**Execution Flow:**
1. Condition is checked first
2. If true, loop body executes
3. Steps 1-2 repeat until condition becomes false
4. If condition is initially false, loop never executes

**Example:**
```c
int i = 1;
while (i <= 5) {
    printf("%d ", i);
    i++;
}
```

**Input validation example:**
```c
int num;
printf("Enter a positive number: ");
scanf("%d", &num);

while (num <= 0) {
    printf("Invalid! Enter a positive number: ");
    scanf("%d", &num);
}
```

**Common Use Cases:**
- When number of iterations is unknown
- Input validation
- Menu-driven programs
- Reading until end of file

---

### 3.3 do-while Loop

**Syntax:**
```c
do {
    // loop body
} while (condition);
```

**Execution Flow:**
1. Loop body executes first
2. Then condition is checked
3. If true, loop repeats
4. If false, loop exits
5. Guaranteed to execute at least once

**Example:**
```c
int i = 1;
do {
    printf("%d ", i);
    i++;
} while (i <= 5);
```

**Menu example:**
```c
int choice;
do {
    printf("\n--- MENU ---\n");
    printf("1. Add\n");
    printf("2. Subtract\n");
    printf("3. Exit\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    
    switch (choice) {
        case 1:
            printf("Addition selected\n");
            break;
        case 2:
            printf("Subtraction selected\n");
            break;
        case 3:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice\n");
    }
} while (choice != 3);
```

**while vs do-while:**
- Use while when condition should be checked before execution
- Use do-while when loop must execute at least once
- do-while is perfect for menu-driven programs

---

### 3.4 Nested Loops

**Definition:** A loop inside another loop

**Example 1: Pattern Printing**
```c
// Print a square pattern
for (int i = 1; i <= 5; i++) {
    for (int j = 1; j <= 5; j++) {
        printf("* ");
    }
    printf("\n");
}
```

**Example 2: Multiplication Table**
```c
for (int i = 1; i <= 10; i++) {
    for (int j = 1; j <= 10; j++) {
        printf("%4d", i * j);
    }
    printf("\n");
}
```

**Example 3: Pyramid Pattern**
```c
int rows = 5;
for (int i = 1; i <= rows; i++) {
    // Print spaces
    for (int j = 1; j <= rows - i; j++) {
        printf(" ");
    }
    // Print stars
    for (int k = 1; k <= 2 * i - 1; k++) {
        printf("*");
    }
    printf("\n");
}
```
![alt text](image.png)

**Time Complexity Note:**
- Nested loops multiply complexity
- Two nested loops: O(n²)
- Three nested loops: O(n³)

---

## 4. Jump Statements

### 4.1 break Statement

**Purpose:** Exits from the nearest enclosing loop or switch statement

**In Loops:**
```c
// Find first number divisible by 7
for (int i = 1; i <= 100; i++) {
    if (i % 7 == 0) {
        printf("First number divisible by 7: %d\n", i);
        break;  // exits the loop
    }
}
```

**In Nested Loops:**
```c
// break only exits the innermost loop
for (int i = 1; i <= 3; i++) {
    for (int j = 1; j <= 3; j++) {
        if (j == 2) {
            break;  // exits inner loop only
        }
        printf("i=%d, j=%d\n", i, j);
    }
}
```

**In switch:**
```c
switch (choice) {
    case 1:
        printf("Option 1\n");
        break;  // prevents fall-through
    case 2:
        printf("Option 2\n");
        break;
}
```

---

### 4.2 continue Statement

**Purpose:** Skips the rest of the current iteration and moves to the next iteration

**Example:**
```c
// Print odd numbers from 1 to 10
for (int i = 1; i <= 10; i++) {
    if (i % 2 == 0) {
        continue;  // skip even numbers
    }
    printf("%d ", i);
}
```

**Practical Example:**
```c
// Skip negative numbers
int numbers[] = {5, -3, 8, -1, 10, -7, 4};
int sum = 0;

for (int i = 0; i < 7; i++) {
    if (numbers[i] < 0) {
        continue;  // skip negative numbers
    }
    sum += numbers[i];
}
printf("Sum of positive numbers: %d\n", sum);
```

**break vs continue:**
- break: Exits the entire loop
- continue: Skips to next iteration

---

### 4.3 goto Statement

**Purpose:** Unconditional jump to a labeled statement

**Syntax:**
```c
goto label;
// ...
label:
    // code
```

**Example:**
```c
int num, sum = 0;

input:
    printf("Enter a number (0 to stop): ");
    scanf("%d", &num);
    
    if (num == 0) {
        goto end;
    }
    
    sum += num;
    goto input;

end:
    printf("Sum: %d\n", sum);
```

**Breaking out of nested loops:**
```c
for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
        if (i * j > 6) {
            goto exit_loops;
        }
        printf("(%d,%d) ", i, j);
    }
}

exit_loops:
    printf("\nExited both loops\n");
```

**Warning:**
- goto is generally discouraged
- Makes code hard to read and debug
- Can lead to "spaghetti code"
- Use only when absolutely necessary
- Modern alternatives: break, continue, functions with return

---

## 5. Best Practices

### 5.1 Code Readability

**Use meaningful conditions:**
```c
// Bad
if (x)

// Good
if (isValidInput)
```

**Avoid deep nesting:**
```c
// Bad
if (condition1) {
    if (condition2) {
        if (condition3) {
            if (condition4) {
                // code
            }
        }
    }
}

// Good - use early returns
if (!condition1) return;
if (!condition2) return;
if (!condition3) return;
if (!condition4) return;
// code
```

### 5.2 Loop Optimization

**Avoid unnecessary operations inside loops:**
```c
// Bad
for (int i = 0; i < strlen(str); i++) {
    // strlen() called every iteration
}

// Good
int len = strlen(str);
for (int i = 0; i < len; i++) {
    // strlen() called once
}
```

### 5.3 Infinite Loop Prevention

**Always ensure loop termination:**
```c
// Bad - might be infinite
int i = 0;
while (i != 10) {
    i += 2;  // if i is odd, infinite loop
}

// Good
int i = 0;
while (i < 10) {
    i += 2;
}
```

### 5.4 Switch Statement Tips

- Always include break unless fall-through is intentional
- Use default case for error handling
- Order cases logically (most common first for performance)

### 5.5 Common Pitfalls

**Assignment in condition:**
```c
// Bug - assignment instead of comparison
if (x = 5) {  // always true
    // code
}

// Correct
if (x == 5) {
    // code
}
```

**Semicolon after if/for:**
```c
// Bug - empty statement
if (x > 0);
    printf("Positive");  // always executes

// Correct
if (x > 0)
    printf("Positive");
```

---

## Practice Problems

1. Write a program to check if a number is prime
2. Create a calculator using switch-case
3. Print all Armstrong numbers between 1 and 1000
4. Generate Fibonacci series using different loops
5. Create a menu-driven program with do-while
6. Print Floyd's triangle
7. Find factorial using both loops and recursion
8. Check if a number is palindrome
9. Print diamond pattern using nested loops
10. Create a number guessing game with loop

---

**End of Notes**