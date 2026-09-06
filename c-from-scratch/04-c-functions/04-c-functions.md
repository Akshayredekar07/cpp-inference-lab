# 4️⃣ **Functions in C**

## **What is a Function?**
A function is a block of code designed to perform a specific task. In C, functions help modularize programs, avoid code repetition, and improve clarity.

---

## **Why Use Functions?**
- **Modularity:** Breaks code into logical sections.
- **Reusability:** Function can be called multiple times.
- **Maintainability:** Easier to debug and update.

---

## **Function Syntax**

**Types of functions:**
1. **Library functions** (e.g., `printf()`, `scanf()`, `strlen()`)
2. **User-defined functions** (you create these)

**Basic structure:**
```c
return_type function_name(parameter_list) {
    // code
    return value; // if not void
}
```

**Example:**
```c
int add(int a, int b) {
    return a + b;
}
```
To call: `int sum = add(2, 3);`

---

## **Parts of a Function**
- **Declaration/Prototype:** Informs compiler of a function’s existence and signature.
    ```c
    int add(int, int);
    ```
- **Definition:** Contains the actual code/logic.
- **Call:** Executes the function.

---

## **Function Arguments and Return Types**

- **Arguments:** Variables passed to the function.
    - *Example:* `int add(int a, int b)`
- **Return Type:** Type of value returned.
    - *Example:* `int`, `void`, `float`

---

## **Pass by Value vs Pass by Reference**

- **Pass by value** *(default in C)*:
    - Function gets a copy of data. Changes inside the function **do not affect** the original value.
    - Example:
      ```c
      void foo(int x) { x = 10; }
      ```
- **Pass by reference** *(simulate using pointers)*:
    - Function gets address of data (pointer). Changes **do affect** original value.
    - Example:
      ```c
      void change(int *x) { *x = 10; }
      ```

---

## **Function Prototype**
A function prototype is a declaration that tells the compiler about the function’s name, return type, and parameters before its actual definition.
```c
int max(int, int); // prototype
...
int max(int a, int b) { ... }
```
Prototypes are **required** if function is defined after it is called.

---

## **Recursion**
A function that calls itself is **recursive**. Every recursive function must have:
- **Base case(s):** Condition(s) to stop recursion.
- **Recursive case:** Function calls itself with new arguments.

**Example:** Factorial
```c
int factorial(int n) {
    if (n <= 1) return 1;   // base case
    return n * factorial(n-1); // recursive case
}
```

---

## **Inline Functions**
C99 introduced the `inline` keyword (use is rare in plain C). Used to suggest replacing function call with function code (optimization).

---

## **Practice Examples**

### **1. Factorial (Recursion)**
```c
int factorial(int n) {
    if (n == 0) return 1;
    return n * factorial(n-1);
}
```

### **2. Fibonacci (Recursion)**
```c
int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n-1) + fibonacci(n-2);
}
```

### **3. GCD (Greatest Common Divisor)**
```c
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}
```

### **4. LCM (Least Common Multiple)**
```c
int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}
```

### **5. Power Function (Exponentiation)**
```c
int power(int base, int exp) {
    int result = 1;
    for(int i = 0; i < exp; i++)
        result *= base;
    return result;
}
```

### **6. Tower of Hanoi**
```c
void towerOfHanoi(int n, char from, char to, char aux) {
    if (n == 1) {
        printf("Move disk 1 from %c to %c\n", from, to);
        return;
    }
    towerOfHanoi(n-1, from, aux, to);
    printf("Move disk %d from %c to %c\n", n, from, to);
    towerOfHanoi(n-1, aux, to, from);
}
```

### **7. Number System Conversion**
```c
void printBinary(int n) {
    if (n > 1) printBinary(n/2);
    printf("%d", n%2);
}
```
Similar logic can be applied for hexadecimal and other bases.

---

## **Tips**
- Always declare prototypes **before main()** if definitions are below.
- **Arguments** are separated by commas.
- Use `void` for functions with no return value.
- Use `void` in parameters if function takes no arguments (`void foo(void)`).

---
