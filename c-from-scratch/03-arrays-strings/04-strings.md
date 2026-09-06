## **C Strings**

Strings in C are **arrays of characters** that end with a _null character_ (`'\0'`).

---

## **1. Declaring & Initializing Strings**

```c
char str1[6] = {'H', 'e', 'l', 'l', 'o', '\0'};
char str2[] = "Hello";  // automatically adds '\0'
```
- With double quotes, the null character is auto-appended.

---

## **2. Input & Output with Strings**

**Output:**
```c
char text[50] = "abcde";
printf("%s\n", text); // prints: abcde
```
**Input:**
```c
char word[100];
scanf("%s", word); // stops at whitespace, no bounds check
```
**Safer input:**
```c
fgets(word, sizeof(word), stdin);  // reads line, includes spaces, keeps newline
```

---

## **3. Common String Functions (`<string.h>`)**

| Function                | Purpose                             |
|-------------------------|-------------------------------------|
| `strlen(str)`           | Gets length (without `'\0'`)        |
| `strcpy(dest, src)`     | Copies src to dest                  |
| `strncpy(dest, src, n)` | Copies up to n characters           |
| `strcat(dest, src)`     | Appends src to dest                 |
| `strcmp(str1, str2)`    | Compares (returns 0 if same)        |
| `strchr(str, c)`        | Finds pointer to first occurrence   |
| `strstr(str, substr)`   | Finds pointer to substring          |

```c
#include <string.h>
char src[] = "abc";
char dest[10];
strcpy(dest, src);         // dest now: "abc"
int len = strlen(dest);    // 3
```

---

## **4. String Traversal**

Iterate over a string as an array:
```c
for(int i = 0; str[i] != '\0'; i++) {
    putchar(str[i]);
}
```

---

## **5. String Pitfalls**

- No automatic bounds checking. You are responsible for buffer sizes.
- Always allocate space for null character (`'\0'`).
- You cannot assign arrays directly.
  ```c
  char a[10], b[10];
  // a = b; // Invalid; use strcpy(a, b);
  ```

---

## **6. Modifying Strings**

- Use `strcpy(target, source)` to copy contents.
- To modify a particular character:
  ```c
  str[0] = 'J';
  ```

---

## **7. Multi-word Input**

- `scanf("%s", str)` stops at whitespace.
- Use `fgets(str, N, stdin)` to read a whole line, including spaces:
  ```c
  fgets(str, sizeof(str), stdin);
  ```

---

## **8. Example: Reversing a String**

```c
void reverse(char s[]) {
    int n = strlen(s);
    for(int i = 0; i < n/2; i++) {
        char tmp = s[i];
        s[i] = s[n-i-1];
        s[n-i-1] = tmp;
    }
}
```

---

## **9. String Literals vs. Character Arrays**

- `char *s = "hello";` // read-only, do not modify
- `char arr[] = "hello";` // can be modified

---

## **10. Passing Strings to Functions**

Use arrays or pointers:
```c
void printString(const char s[]) {
    printf("%s\n", s);
}
```

---

## **11. Manual Input/Output Example**

```c
char s[100];
printf("Enter a word: ");
scanf("%s", s); // reads a word
printf("You entered: %s\n", s);
```
