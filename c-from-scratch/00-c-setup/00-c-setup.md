# **✔️ Learn the Fundamentals — Detailed Notes**

---

# **1. What is C?**

C is a **general-purpose, procedural programming language** developed by **Dennis Ritchie** at Bell Labs in **1972**.

C is known for being:

* **Fast** — very close to machine-level execution
* **Portable** — C programs run on almost any system
* **Powerful** — gives direct control over memory
* **Foundation for other languages** — C++, Java, Python, JavaScript all have roots in C

### **Why C is important?**

* It's used in **operating systems**, **embedded systems**, **compilers**, **databases**, and **drivers**.
* Helps you understand **how memory works** (stack, heap, pointers).
* Forms the base for learning **C++, embedded programming, DSA, OS concepts**.

### **Key features of C**

* Structured programming
* Low-level memory access
* Speed & efficiency
* Rich set of built-in operators
* Supports modular programming using **functions**

---

# **2. Structure of a C Program**

A C program has a very specific layout.
Here’s the general structure:

```
#include <stdio.h>     // Header files

// Global declarations (optional)

int main() {            // Main function
    // Statements
    return 0;           // End of program
}
```

Now let’s break each part:

---

## **(i) Header Files**

```
#include <stdio.h>
#include <math.h>
#include <string.h>
```

* These are libraries that contain predefined functions.
* For example:

  * `stdio.h` → printf(), scanf()
  * `math.h` → sqrt(), pow()
  * `string.h` → strlen(), strcpy()

`#include` is a **preprocessor directive** — runs before compilation.

---

## **(ii) Main Function**

```
int main() {
    // code
}
```

* Execution **always starts** from `main()`.
* `int` means main returns an integer value to OS.
* `return 0;` → successful execution.

Without `main()`, a C program cannot run.

---

## **(iii) Statements**

Anything inside `{ }` of main is a statement:

```
int a = 10;
printf("%d", a);
```

---

## **(iv) Comments**

Used for explanations (ignored by compiler):

```
// Single-line comment

/* Multi-line
   comment */
```

---

## **(v) Example of a Complete C Program**

```
#include <stdio.h>

int main() {
    int a = 5;                      // variable declaration
    printf("Value of a = %d", a);   // output
    return 0;                       // exit code
}
```

---

# **3. printf() and scanf()**

These two functions come from **stdio.h** and are used for input and output.

---

# **A. printf() – Output Function**

Used to display text or values on the screen.

### **Syntax**

```
printf("format string", value1, value2, ...);
```

### **Common Format Specifiers**

| Type   | Specifier | Example  |
| ------ | --------- | -------- |
| int    | %d        | 10       |
| float  | %f        | 3.14     |
| char   | %c        | 'A'      |
| string | %s        | "Hello"  |
| double | %lf       | 3.141592 |

### **Examples**

```
printf("Hello World");
```

```
int age = 21;
printf("Age = %d", age);
```

```
float pi = 3.14;
printf("PI = %.2f", pi);   // prints 3.14
```

`%.2f` → prints float up to 2 decimal places.

---

# **B. scanf() – Input Function**

Used to take input from the user.

### **Syntax**

```
scanf("format string", &variable);
```

### Important:

* You MUST use **&** (address operator) for all variables except strings.

### **Example**

```
int num;
scanf("%d", &num);
```

```
float x;
scanf("%f", &x);
```

### **Multiple Inputs**

```
int a, b;
scanf("%d %d", &a, &b);
```

---

# **printf() vs scanf() – Main Difference**

* `printf()` → prints output to screen
* `scanf()` → reads input from keyboard

Both are essential for interacting with user.

---

# **✔️ Summary (Short Revision Notes)**

* C is fast, portable, and close to hardware.
* A C program starts with header files and must contain `main()`.
* `printf()` is for output.
* `scanf()` is for input.
* Format specifiers tell the compiler the type of data.

---

## **✔️ Variables & Data Types — Detailed Notes**

## **1. What is a Variable?**

A **variable** is a name given to a memory location where data is stored.

Think of it like:

* A labeled box that stores a value
* You can change the value anytime

### **Rules for naming variables**

* Must start with a letter or underscore
* Cannot contain spaces
* Cannot start with a number
* Case sensitive (age and Age are different)
* Special characters not allowed except `_`

### **Examples**

```
int age;
float salary;
char grade;
```

---

## **2. Data Types in C**

C provides different data types to store different kinds of values.

### **Basic Data Types**

| Data Type | Meaning               | Size    | Format Specifier |
| --------- | --------------------- | ------- | ---------------- |
| int       | Integer numbers       | 4 bytes | %d               |
| float     | Decimal numbers       | 4 bytes | %f               |
| double    | Large decimal numbers | 8 bytes | %lf              |
| char      | Single character      | 1 byte  | %c               |

### **Examples**

```
int marks = 90;
float pi = 3.14;
double balance = 12345.6789;
char grade = 'A';
```

---

## **3. Operators in C**

Operators are symbols used to perform operations on variables.

---

# **A. Arithmetic Operators**

Used for mathematical operations.

| Operator | Meaning             | Example |
| -------- | ------------------- | ------- |
| +        | Addition            | a + b   |
| -        | Subtraction         | a - b   |
| *        | Multiplication      | a * b   |
| /        | Division            | a / b   |
| %        | Modulus (remainder) | a % b   |

### **Example**

```
int a = 10, b = 3;
printf("%d", a % b); // Output: 1
```

---

# **B. Relational Operators**

Used to compare two values.
Result is always **true (1)** or **false (0)**.

| Operator | Meaning          |
| -------- | ---------------- |
| ==       | equal to         |
| !=       | not equal to     |
| >        | greater than     |
| <        | less than        |
| >=       | greater or equal |
| <=       | less or equal    |

### **Example**

```
printf("%d", 10 > 5);  // Output: 1
```

---

# **C. Logical Operators**

Used to combine conditions.

| Operator | Meaning     | Example      |   |      |
| -------- | ----------- | ------------ | - | ---- |
| &&       | Logical AND | (a>0 && b>0) |   |      |
| ||       | Logical OR  | (a>0         |   | b>0) |
| !        | Logical NOT | !(a>0)       |   |      |

### **Example**

```
if(age > 18 && age < 60)
```

---

# **✔️ Practice Problems (Beginner Level)**

Below are clean examples you can run directly.

---

# **1. Add Two Numbers**

```
#include <stdio.h>

int main() {
    int a, b, sum;
    
    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);

    sum = a + b;

    printf("Sum = %d", sum);
    return 0;
}
```

---

# **2. Swap Two Numbers**

### **Method 1: Using Temporary Variable**

```
#include <stdio.h>

int main() {
    int a, b, temp;

    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);

    temp = a;
    a = b;
    b = temp;

    printf("After swap: a = %d, b = %d", a, b);
    return 0;
}
```

### **Method 2: Without Temporary Variable**

```
a = a + b;
b = a - b;
a = a - b;
```

---

# **3. Simple Calculator ( +, -, *, / )**

```
#include <stdio.h>

int main() {
    char op;
    float a, b;

    printf("Enter operator (+, -, *, /): ");
    scanf("%c", &op);

    printf("Enter two numbers: ");
    scanf("%f %f", &a, &b);

    switch(op) {
        case '+': printf("Result = %.2f", a + b); break;
        case '-': printf("Result = %.2f", a - b); break;
        case '*': printf("Result = %.2f", a * b); break;
        case '/': printf("Result = %.2f", a / b); break;
        default : printf("Invalid Operator");
    }

    return 0;
}
```

---

# **4. Check Odd or Even**

```
#include <stdio.h>

int main() {
    int n;

    printf("Enter a number: ");
    scanf("%d", &n);

    if(n % 2 == 0)
        printf("Even");
    else
        printf("Odd");

    return 0;
}
```

---

# **5. Largest of 3 Numbers**

```
#include <stdio.h>

int main() {
    int a, b, c;

    printf("Enter three numbers: ");
    scanf("%d %d %d", &a, &b, &c);

    if(a >= b && a >= c)
        printf("Largest = %d", a);
    else if(b >= a && b >= c)
        printf("Largest = %d", b);
    else
        printf("Largest = %d", c);

    return 0;
}
```

---

# **✔️ Full Operator Table**


# **1️⃣ Unary Operators (operate on a single operand)**

**Highest precedence operators**

| Operator | Meaning               | Example                        |
| -------- | --------------------- | ------------------------------ |
| `++x`    | Pre-increment         | value increased **before** use |
| `x++`    | Post-increment        | value increased **after** use  |
| `--x`    | Pre-decrement         | value decreased before use     |
| `x--`    | Post-decrement        | value decreased after use      |
| `+x`     | Unary plus            | Makes number positive          |
| `-x`     | Unary minus           | Makes number negative          |
| `!x`     | Logical NOT           | `!1 → 0`, `!0 → 1`             |
| `&x`     | Address-of operator   | gives memory address           |
| `*x`     | Dereference operator  | value stored at pointer        |
| `sizeof` | Returns size in bytes | `sizeof(int)`                  |

---

# **2️⃣ Arithmetic Operators**

| Operator | Meaning             | Example |
| -------- | ------------------- | ------- |
| `+`      | Addition            | a + b   |
| `-`      | Subtraction         | a - b   |
| `*`      | Multiplication      | a * b   |
| `/`      | Division            | a / b   |
| `%`      | Modulus (remainder) | a % b   |

---

# **3️⃣ Relational Operators (comparison)**

| Operator | Meaning          | Example |
| -------- | ---------------- | ------- |
| `==`     | Equal to         | a == b  |
| `!=`     | Not equal to     | a != b  |
| `>`      | Greater than     | a > b   |
| `<`      | Less than        | a < b   |
| `>=`     | Greater or equal | a >= b  |
| `<=`     | Less or equal    | a <= b  |

---

# **4️⃣ Logical Operators**

| Operator | Meaning     | Example      |
| -------- | ----------- | ------------ |
| `&&`     | Logical AND | (a>0 && b>0) |
| `\|\|`   | Logical OR  | (a>0 || b>0) |
| `!`      | Logical NOT | !a           |

---

# **5️⃣ Bitwise Operators (operate on bits)**

(Medium/advanced topic, very useful for DSA)

| Operator | Meaning     | Example    |   |   |
| -------- | ----------- | ---------- | - | - |
| `&`      | Bitwise AND | a & b      |   |   |
| `        | `           | Bitwise OR | a | b |
| `^`      | Bitwise XOR | a ^ b      |   |   |
| `~`      | Bitwise NOT | ~a         |   |   |
| `<<`     | Left shift  | a << 1     |   |   |
| `>>`     | Right shift | a >> 1     |   |   |

---

# **6️⃣ Assignment Operators**

| Operator | Meaning             | Example           |   |     |
| -------- | ------------------- | ----------------- | - | --- |
| `=`      | Assign              | a = b             |   |     |
| `+=`     | Add and assign      | a += 5            |   |     |
| `-=`     | Subtract and assign | a -= 5            |   |     |
| `*=`     | Multiply and assign | a *= 2            |   |     |
| `/=`     | Divide and assign   | a /= 2            |   |     |
| `%=`     | Modulo and assign   | a %= 2            |   |     |
| `&=`     | Bitwise AND assign  | a &= b            |   |     |
| `        | =`                  | Bitwise OR assign | a | = b |
| `^=`     | Bitwise XOR assign  | a ^= b            |   |     |
| `<<=`    | Left shift assign   | a <<= 1           |   |     |
| `>>=`    | Right shift assign  | a >>= 2           |   |     |

---

# **7️⃣ Conditional (Ternary) Operator**

| Operator | Meaning               | Example         |
| -------- | --------------------- | --------------- |
| `?:`     | Shorthand for if-else | `(a>b ? a : b)` |

---

# **8️⃣ Comma Operator**

| Operator | Meaning                                                | Example    |
| -------- | ------------------------------------------------------ | ---------- |
| `,`      | Evaluates expressions left → right, returns last value | `a=1, b=2` |

---

# **9️⃣ Special Operators**

| Operator | Meaning                        | Example |
| -------- | ------------------------------ | ------- |
| `&`      | Address-of                     | &a      |
| `*`      | Pointer dereference            | *ptr    |
| `->`     | Access struct member (pointer) | p->age  |
| `.`      | Access struct member           | s.age   |

---

# **🔟 Precedence Order (Shortcut)**

Highest → Lowest

1. **Unary operators** (++ -- ! sizeof)
2. Multiplicative (* / %)
3. Additive (+ -)
4. Relational (< <= > >=)
5. Equality (== !=)
6. Logical AND (&&)
7. Logical OR (||)
8. Assignment (= += -= )
9. Comma (,)

---



# **✔️ Operator Precedence & Associativity in C (Detailed Notes)**

* **Operator Precedence** (which operator runs first)
* **Associativity** (when operators have same precedence → left→right or right→left)
  
When an expression has multiple operators, C uses:

1. **Precedence** → priority
2. **Associativity** → direction

---

## **1️⃣ Operator Precedence Table (Highest → Lowest)**

Memorize the top 5… rest you’ll remember naturally as you code.

---

## **🔵 Highest Precedence (Executed First)**

### **1. Unary Operators**

```
++  --  !   +   -   &   *  sizeof
```

**Associativity:** Right → Left

Example:

```
++a; 
--b;
!flag;
```

---

### **2. Multiplicative**

```
*   /   %
```

**Associativity:** Left → Right

Example:

```
a * b / c % d
```

---

### **3. Additive**

```
+   -
```

**Associativity:** Left → Right

Example:

```
a + b - c
```

---

### **4. Relational**

```
<   >   <=   >=
```

**Associativity:** Left → Right

---

### **5. Equality**

```
==   !=
```

**Associativity:** Left → Right

---

### **6. Logical AND**

```
&&
```

**Associativity:** Left → Right

---

### **7. Logical OR**

```
||
```

**Associativity:** Left → Right

---

### **8. Assignment =**

Includes:

```
=   +=   -=   *=   /=   %=
```

**Associativity:** Right → Left
(Most assignment operators work right-to-left)

Example:

```
a = b = c = 10;
```

---

### **9. Comma Operator**

```
,
```

**Associativity:** Left → Right
Lowest precedence in C.

---

# **2️⃣ Associativity Rules (Quick Summary)**

| Operator Type    | Associativity |
| ---------------- | ------------- |
| Unary            | Right-to-Left |
| Multiplicative   | Left-to-Right |
| Additive         | Left-to-Right |
| Relational       | Left-to-Right |
| Equality         | Left-to-Right |
| Logical AND / OR | Left-to-Right |
| Assignment       | Right-to-Left |
| Comma            | Left-to-Right |

---

# **3️⃣ Examples to Understand Both**

---

### **Example 1:**

```
int x = 10 + 5 * 2;
```

Multiplication (*) has higher precedence:

```
5 * 2 = 10
10 + 10 = 20
```

---

### **Example 2:**

```
a > b > c
```

Relational operators have **left-to-right** associativity.

So it becomes:

```
(a > b) > c
```

If (a > b) is true → gives **1**, else **0**.

Then it checks:

```
1 > c   or   0 > c
```

---

### **Example 3:**

```
a++ * b + a
```

Evaluation order:

1. `a++` uses old value, then increments afterwards
2. `*` has higher precedence than `+`

---

### **Example 4:**

```
a++ && ++a || a--
```

Order:

* `&&` is evaluated before `||`
* But short-circuiting also affects evaluation
* `a++` evaluates first, but increments later

---

# **4️⃣ Want a quick trick to remember?**

### **Multiplication beats addition**

Just like math.

### **Comparisons come after arithmetic**

Do math first, compare later.

### **Logical operators always come last**

&& happens before ||.

### **Assignments are right → left**

a = b = 10;

---

# **✔️ 10 Medium to Advanced Questions — Operators in C**

---

### **1️⃣ What will be the output of the following code? Explain why.**

```
int a = 10, b = 3;
printf("%d", a / b * b + a % b);
```

---

### **2️⃣ Predict the output:**

```
int x = 5;
printf("%d", x > 3 && x < 10 || x == 2);
```

---

### **3️⃣ What will this print?**

```
int a = 10, b = 20, c = 5;
printf("%d", a > b > c);
```

(Hint: relational operators evaluate left to right.)

---

### **4️⃣ Without using if-else, write an expression to check if a number `n` is even or odd.**

(Use only **arithmetic / logical / relational** operators.)

---

### **5️⃣ Write a single expression (no if-else) to find the **largest** of 3 numbers a, b, c using ONLY operators.**

---

### **6️⃣ What is the output?**

```
int a = 5, b = 2;
printf("%d", a++ * b + a);
```

---

### **7️⃣ Evaluate the expression and explain every step:**

```
int x = 4, y = 10;
int z = x++ + ++y > 15 && y-- < 12;
printf("%d %d %d", x, y, z);
```

---

### **8️⃣ Rewrite this condition using only logical operators, no relational operators:**

```
if(a == 0)
```

(Hint: logical NOT `!`)

---

### **9️⃣ Which of the following expressions is true and why?**

```
(a + b > c) == (a > c - b)
```

Is this always true? If not, give an example where it fails.

---

### **🔟 What will be the result of this tricky expression?**

```
int a = 1;
printf("%d", a++ && ++a || a--);
```

(Hint: short-circuit behavior is the key.)

---
