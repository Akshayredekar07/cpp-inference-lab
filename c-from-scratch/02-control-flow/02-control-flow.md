
# 🚀 **CONTROL FLOW IN C — DETAILED NOTES**

Control flow simply means:

> *How your program decides what to do next.*

C gives you a set of tools to **make decisions** and **repeat actions**.
These tools are:

1. **Conditional statements**
2. **Switch-case**
3. **Loops (for, while, do-while)**
4. **Loop control (break, continue, goto)**
5. **Nested loops**

Let’s break everything down clearly.

---

# 1️⃣ **CONDITIONAL STATEMENTS**

## **1. IF Statement**

Used when you want to check a condition and run code **only if** it’s true.

```
if (condition) {
    // run this if condition is true
}
```

Example:

```
int age = 20;

if (age >= 18) {
    printf("You can vote");
}
```

---

## **2. IF – ELSE**

Runs one block if condition is true, otherwise runs the other block.

```
if (condition) {
    // true block
} else {
    // false block
}
```

Example:

```
int marks = 45;

if (marks >= 40)
    printf("Pass");
else
    printf("Fail");
```

---

## **3. ELSE IF**

Used when you have **multiple conditions** to check.

```
if (cond1) {
    ...
} else if (cond2) {
    ...
} else if (cond3) {
    ...
} else {
    // none of the above
}
```

Example:

```
int temp = 30;

if (temp > 40)
    printf("Very Hot");
else if (temp > 30)
    printf("Hot");
else if (temp > 20)
    printf("Warm");
else
    printf("Cold");
```

---

# 2️⃣ **SWITCH CASE**

A cleaner alternative to multiple `else-if`.

Use it when you compare one variable with several fixed values.

```
switch(value) {
    case 1: ...
    case 2: ...
    case 3: ...
    default: ...
}
```

⚠ **Important note**
Each `case` runs until `break` is found — otherwise it “falls through”.

Example:

```
int day = 3;

switch(day) {
    case 1: printf("Mon"); break;
    case 2: printf("Tue"); break;
    case 3: printf("Wed"); break;
    default: printf("Invalid");
}
```

---

# 3️⃣ **LOOPS**

Loops allow you to repeat code multiple times.

---

## **1. FOR LOOP**

Best when you know the number of iterations.

Syntax:

```
for (init; condition; update) {
    ...
}
```

Example:

```
for(int i = 1; i <= 5; i++) {
    printf("%d ", i);
}
```

Execution flow:

1. Initialize `i`
2. Check condition
3. Run loop body
4. Update i
5. Repeat

---

## **2. WHILE LOOP**

Use when you **don’t know** how many times it should run.

```
while(condition) {
    ...
}
```

Example:

```
int x = 5;

while (x > 0) {
    printf("%d ", x);
    x--;
}
```

⚠ Condition is checked first → loop may run zero times.

---

## **3. DO-WHILE LOOP**

Runs **at least once**, even if condition is false.

```
do {
    ...
} while(condition);
```

Example:

```
int y = 10;

do {
    printf("%d", y);
    y++;
} while(y < 5);
```

Output → still prints 10 once.

---

# 4️⃣ **LOOP CONTROL STATEMENTS**

These control the behavior inside loops.

---

## **1. break**

Immediately exits the loop.

Example:

```
for(int i = 1; i <= 10; i++) {
    if(i == 5)
        break;  
    printf("%d ", i);
}
```

Stops when `i == 5`.

---

## **2. continue**

Skips that iteration and moves to next.

```
for(int i = 1; i <= 5; i++) {
    if(i == 3)
        continue;  
    printf("%d ", i);
}
```

Output:
`1 2 4 5`
(3 is skipped)

---

## **3. goto**

Jumps to a labelled location in code.

```
start:
    printf("Hello");

goto start;   // infinite loop
```

⚠ Not recommended in real-world coding — used only in specific cases.

---

# 5️⃣ **NESTED LOOPS**

A loop inside another loop.

```
for(int i = 1; i <= 3; i++) {
    for(int j = 1; j <= 3; j++) {
        printf("(%d, %d) ", i, j);
    }
}
```

This prints a 3x3 matrix of coordinates.

Nested loops are useful for:

* Patterns
* Matrix operations
* Multiplication table
* 2D array processing

---

# ⭐ QUICK SUMMARY TABLE

| Concept      | Purpose                      |
| ------------ | ---------------------------- |
| if           | Check one condition          |
| else-if      | Multiple conditions          |
| switch       | Multiple fixed choices       |
| for          | Loop with known count        |
| while        | Loop with unknown count      |
| do-while     | Loop that runs at least once |
| break        | Exit loop                    |
| continue     | Skip iteration               |
| goto         | Jump (rarely used)           |
| nested loops | Loop inside loop             |

---
