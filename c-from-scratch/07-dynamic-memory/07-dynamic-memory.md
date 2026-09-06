# **7️⃣ Dynamic Memory Management in C**

In C programming, memory can be managed in two main ways: **automatically** or **manually**.
Dynamic Memory Management refers to the technique where a program **requests memory at runtime** (while the program is running), instead of deciding the memory size at compile time.

This concept is extremely important when:

* The amount of data is **unknown in advance**
* The data size can **change during execution**
* We want to create **dynamic data structures** like linked lists, trees, graphs, etc.

---

## **1. Stack Memory vs Heap Memory**

Before learning dynamic memory functions, it is essential to understand **where memory comes from**.

---

### **Stack Memory**

Stack memory is **automatically managed** by the compiler.

When a function is called:

* Its local variables are created on the **stack**
* When the function ends, the memory is **automatically destroyed**

Example:

```c
void func() {
    int x = 10;  // stored in stack memory
}
```

Key characteristics of stack memory:

* Memory allocation and deallocation happen **automatically**
* Access is **very fast**
* Size is **limited**
* Programmer has **no control** over when memory is freed

Stack memory is best suited for **small, temporary data**.

---

### **Heap Memory**

Heap memory is **manually managed** by the programmer.

Memory is:

* Requested using functions like `malloc`, `calloc`, `realloc`
* Released using `free`

Example:

```c
int *p = (int *)malloc(sizeof(int));
```

Key characteristics of heap memory:

* Allocation and deallocation are **explicit**
* Larger memory space than stack
* Slightly slower than stack
* Gives **full control** to the programmer

Heap memory is used when data must **persist beyond a function** or **change size dynamically**.

---

### **Stack vs Heap Summary**

| Aspect       | Stack     | Heap            |
| ------------ | --------- | --------------- |
| Allocation   | Automatic | Manual          |
| Deallocation | Automatic | Manual (`free`) |
| Speed        | Faster    | Slower          |
| Size         | Limited   | Large           |
| Control      | Low       | High            |

---

## **2. `malloc()` – Allocating Memory Dynamically**

The `malloc()` function is used to **allocate memory dynamically** from the heap.

### **What `malloc()` Does**

* Reserves a block of memory of specified size
* Returns the **starting address** of that memory
* The allocated memory contains **garbage values**
* Returns `NULL` if allocation fails

---

### **Syntax**

```c
void* malloc(size_t size);
```

---

### **Example**

```c
int *arr = (int *)malloc(5 * sizeof(int));
```

This statement:

* Allocates memory for **5 integers**
* Stores the base address in pointer `arr`
* Does **not initialize** the values

---

### **Important Safety Check**

```c
if (arr == NULL) {
    printf("Memory allocation failed");
}
```

Always check for `NULL` to avoid program crashes.

---

## **3. `calloc()` – Allocating and Initializing Memory**

The `calloc()` function allocates memory **and initializes all bytes to zero**.

---

### **Syntax**

```c
void* calloc(size_t num, size_t size);
```

---

### **Example**

```c
int *arr = (int *)calloc(5, sizeof(int));
```

This means:

* Memory for 5 integers is allocated
* All elements are initialized to `0`

---

### **Difference Between `malloc()` and `calloc()`**

| Feature        | malloc          | calloc          |
| -------------- | --------------- | --------------- |
| Initialization | No              | Yes (all zeros) |
| Arguments      | One             | Two             |
| Speed          | Slightly faster | Slightly slower |

---

## **4. `realloc()` – Resizing Memory**

The `realloc()` function is used to **change the size of previously allocated memory**.

---

### **Why `realloc()` Is Needed**

Sometimes:

* Initial memory is not enough
* Or allocated memory is more than required

Instead of freeing and reallocating, `realloc()` resizes the existing block.

---

### **Syntax**

```c
void* realloc(void* ptr, size_t new_size);
```

---

### **Example**

```c
arr = (int *)realloc(arr, 10 * sizeof(int));
```

This:

* Expands memory from 5 integers to 10 integers
* Preserves existing data
* May move memory to a new location

---

### **Safe Usage Pattern**

```c
int *temp = realloc(arr, new_size);
if (temp != NULL) {
    arr = temp;
}
```

This prevents losing the original pointer if reallocation fails.

---

## **5. `free()` – Deallocating Memory**

The `free()` function releases heap memory back to the operating system.

---

### **Example**

```c
free(arr);
arr = NULL;
```

Why set pointer to `NULL`?

* Prevents accidental access
* Avoids dangling pointers

---

## **6. Memory Leaks**

### **What Is a Memory Leak**

A memory leak occurs when:

* Memory is allocated using `malloc` / `calloc`
* The memory is **never freed**
* The pointer to that memory is lost

---

### **Example of Memory Leak**

```c
void leak() {
    int *p = malloc(100 * sizeof(int));
}
```

After function ends:

* Pointer `p` is destroyed
* Allocated memory remains unreachable

---

### **How to Avoid Memory Leaks**

* Always pair `malloc` / `calloc` with `free`
* Free memory before reassigning pointers
* Free memory before program termination
* Use disciplined memory ownership rules

---

## **7. Dangling Pointers**

### **Definition**

A dangling pointer is a pointer that **points to memory that has already been freed**.

---

### **Example**

```c
int *p = malloc(sizeof(int));
free(p);
// p is now dangling
```

Accessing `p` now leads to **undefined behavior**.

---

### **Correct Practice**

```c
free(p);
p = NULL;
```

A `NULL` pointer is safe and easy to check.

---

## **8. Memory Fragmentation**

### **What Is Memory Fragmentation**

Memory fragmentation occurs when:

* Free memory is broken into small pieces
* Large continuous memory blocks become unavailable

---

### **Types**

**External Fragmentation**

* Free blocks exist but are scattered

**Internal Fragmentation**

* Allocated block has unused space

---

### **How to Reduce Fragmentation**

* Free unused memory early
* Reuse allocated memory
* Use `realloc()` carefully
* Prefer fixed-size allocations where possible

---

# **Practice Programs (With Explanation)**

---

## **1️⃣ Creating a Dynamic Array**

```c
int n;
scanf("%d", &n);

int *arr = malloc(n * sizeof(int));

for (int i = 0; i < n; i++) {
    arr[i] = i + 1;
}

free(arr);
```

This program:

* Takes size at runtime
* Allocates memory dynamically
* Uses and releases memory safely

---

## **2️⃣ Resizing an Array at Runtime**

```c
int *arr = malloc(3 * sizeof(int));
arr = realloc(arr, 6 * sizeof(int));
free(arr);
```

The array grows dynamically during execution.

---

## **3️⃣ Dynamic 2D Matrix**

```c
int rows = 3, cols = 4;

int **matrix = malloc(rows * sizeof(int*));

for (int i = 0; i < rows; i++)
    matrix[i] = malloc(cols * sizeof(int));

for (int i = 0; i < rows; i++)
    free(matrix[i]);

free(matrix);
```

Each row is allocated separately on the heap.

---

## **4️⃣ Dynamic String Operations**

```c
char *str = malloc(50);
strcpy(str, "Hello");

str = realloc(str, 100);
strcat(str, " World");

free(str);
```

Strings grow dynamically as needed.

---

## **5️⃣ Linked List Using Dynamic Memory**

```c
struct Node {
    int data;
    struct Node *next;
};

struct Node *head = malloc(sizeof(struct Node));
head->data = 10;
head->next = NULL;
```

Linked lists are impossible without dynamic memory.

---

## **6️⃣ Memory Leak Detection Practice**

### **Wrong Code**

```c
int *p = malloc(100);
p = malloc(200);   // memory leak
```

### **Correct Code**

```c
int *p = malloc(100);
free(p);
p = malloc(200);
free(p);
```

---

## **Final Understanding**

Dynamic Memory Management gives C its **power and flexibility**, but it also introduces **responsibility**.
Correct use leads to efficient programs.
Incorrect use leads to crashes, leaks, and undefined behavior.
