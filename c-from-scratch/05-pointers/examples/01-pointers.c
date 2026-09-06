#include <stdio.h>
#include <stdlib.h>

int add(int a, int b);
int sub(int a, int b);
int mul(int a, int b);
int divide(int a, int b);  // renamed from div to avoid conflict with stdlib.h
int mod(int a, int b);
int power(int a, int b);   // renamed from pow to avoid conflict with math.h
int square_root(int a);    // renamed from sqrt to avoid conflict with math.h


int main(){

    int a = 10;
    int *p = &a;

    // Initialization means assigning a valid memory address to a pointer. 
    // This is done using the address-of operator (&).

    printf("Value of a: %d\n", a);
    printf("Address of a: %p\n", (void*)&a); // address of the variable a
    printf("Value of p: %p\n", (void*)p); // value of the pointer p which is the address of the variable a
    printf("Value of *p: %d\n", *p); // dereferencing the pointer

    *p = 20; // modifying the value of the variable a through the pointer p
    printf("Value of a: %d\n", a);
    printf("Value of *p: %d\n", *p);

    // different types of pointers
    int *p1;
    char *p2;
    float *p3;
    double *p4;
    // Correct ways to declare struct/union pointers need a type.
    struct student { int id; char name[20]; };
    struct student st = {2, "Jhon"};
    struct student *p5 = &st; // struct pointer can store the address of a struct variable  

    union utype { int id; char name[20]; };
    union utype ut;
    union utype *p6 = &ut; // union pointer can store the address of a union variable  

    // enum pointers are rarely used, demonstrate with declared type:
    enum level { LOW, MEDIUM, HIGH };
    enum level lev = MEDIUM;
    enum level *p7 = &lev; // enum pointer can store the address of an enum variable  

    void *p8 = NULL;    // void pointer can store the address of any data type but cannot be dereferenced directly  
    printf("Value of p8: %p\n", (void*)p8);
    // Note: Cannot directly dereference void*, must cast first (removed invalid *p8 line)
    printf("Address of p8: %p\n", (void*)&p8);
    printf("Value of *p8 as int: %d\n", (*(int *)p8));
    printf("Value of *p8 as char: %c\n", (*(char *)p8));
    printf("Value of *p8 as float: %f\n", (*(float *)p8));
    printf("Value of *p8 as double: %lf\n", (*(double *)p8));
    printf("Value of *p8 as struct: %s\n", (*(struct student *)p8));
    printf("Value of *p8 as union: %d\n", (*(union utype *)p8));

    char ch = 'A';
    char *p9 = &ch;
    printf("Value of ch: %c\n", ch);
    printf("Address of ch: %p\n", (void*)&ch);
    printf("Value of p9: %p\n", (void*)p9);
    printf("Value of *p9: %c\n", *p9);

    double d = 10.5;
    double *p10 = &d;
    printf("Value of d: %lf\n", d);
    printf("Address of d: %p\n", (void*)&d);
    printf("Value of p10: %p\n", (void*)p10);
    printf("Value of *p10: %lf\n", *p10);

    float f = 10.5;
    float *p11 = &f;
    printf("Value of f: %f\n", f);
    printf("Address of f: %p\n", (void*)&f);
    printf("Value of p11: %p\n", (void*)p11);
    printf("Value of *p11: %f\n", *p11);

    struct student s = {1, "John"};
    struct student *p12 = &s;
    printf("s.id from struct pointer: %d\n", (*p12).id);
    printf("s.name from struct pointer: %s\n", (*p12).name);

    union utype u;
    u.id = 123;
    union utype *p13 = &u;
    printf("u.id from union pointer: %d\n", p13->id);

    enum level e = HIGH;
    enum level *p14 = &e;
    printf("Value of *p14 (enum): %d\n", *p14);

    void *p15 = &a;
    printf("Value of a: %d\n", a);
    printf("Address of a: %p\n", (void*)&a);
    printf("Value of p15: %p\n", p15);
    printf("Value of *p15 as int: %d\n", (*(int *)p15));   
    // Note: Dereferencing void* as char/double/float makes sense only if you point it to those types
    // Avoiding unsafe dereference of p15 as other types

    // Do not free stack address!
    // free(p15); // WRONG: never free memory you didn't allocate with malloc/calloc/realloc
    p15 = NULL; 

    if(p15 == NULL){
        printf("p15 is NULL\n");
    }
    if(p15 != NULL){
        printf("p15 is not NULL\n");
    }
    if(p15 == NULL){
        printf("p15 is NULL\n");
    }

    // Variables for array of pointers
    int b = 30, c = 40;
    int *arr[3] = {&a, &b, &c};
    printf("Value of arr[0]: %d\n", *arr[0]);
    printf("Value of arr[1]: %d\n", *arr[1]);
    printf("Value of arr[2]: %d\n", *arr[2]);
    printf("Address of arr[0]: %p\n", (void*)arr[0]);
    printf("Address of arr[1]: %p\n", (void*)arr[1]);
    printf("Address of arr[2]: %p\n", (void*)arr[2]);

    //POINTER ARITHMETIC
    int *p17 = &a;
    printf("Value of p17: %d\n", *p17);
    printf("Address of p17: %p\n", (void*)p17);
    // Pointer arithmetic demonstration on a single variable is not meaningful: use array
    p17 = arr[0];
    p17 += 2;
    printf("Value of p17 now: %d\n", *p17);
    printf("Address of p17: %p\n", (void*)p17);
    p17 -= 2;
    printf("Value of p17: %d\n", *p17);
    printf("Address of p17: %p\n", (void*)p17);


    // POINTER TO FUNCTIONS
    // First, declare a function prototype at the top of your file:
    // int add(int, int);
    // Now, declare and assign the function pointer:
    int (*fp)(int, int) = add; // pointer to function that takes two ints and returns an int
    printf("Value returned by fp(2, 3): %d\n", fp(2, 3));
    printf("Address stored in fp: %p\n", (void*)fp);

    // Demonstrate calling through dereferencing (usual and one level only!)
    printf("Value returned by (*fp)(2, 3): %d\n", (*fp)(2, 3));
    printf("Address accessed by *fp: %p\n", (void*)*fp);

    // Remove invalid multiple dereferences, as that is not valid in C:
    // For function pointers, *fp and fp mean the same thing.
    // **fp, ***fp, etc. are invalid and will produce a compilation error.

    // i have defined other also sub, mul, divide, mod, power, square_root functions
    int (*fp2)(int, int) = sub;
    printf("Value returned by fp2(2, 3): %d\n", fp2(2, 3));
    printf("Address stored in fp2: %p\n", (void*)fp2);

    int (*fp3)(int, int) = mul;
    printf("Value returned by fp3(2, 3): %d\n", fp3(2, 3));
    printf("Address stored in fp3: %p\n", (void*)fp3);

    int (*fp4)(int, int) = divide;
    printf("Value returned by fp4(2, 3): %d\n", fp4(2, 3));
    printf("Address stored in fp4: %p\n", (void*)fp4);

    int (*fp5)(int, int) = mod;
    printf("Value returned by fp5(2, 3): %d\n", fp5(2, 3));
    printf("Address stored in fp5: %p\n", (void*)fp5);

    int (*fp6)(int, int) = power;
    printf("Value returned by fp6(2, 3): %d\n", fp6(2, 3));
    printf("Address stored in fp6: %p\n", (void*)fp6);
    
    // Note: square_root takes one parameter, so it cannot be assigned to a two-parameter function pointer
    int (*fp7)(int) = square_root;
    printf("Value returned by fp7(9): %d\n", fp7(9));
    printf("Address stored in fp7: %p\n", (void*)fp7);

    // CONST WITH POINTERS
    // Use a different name for the pointer to avoid conflict with earlier declaration
    const int *cp = &a;
    cp = &b;
    printf("Value pointed to by cp: %d\n", *cp);
    printf("Address stored in cp: %p\n", (void*)cp);
    cp = &c;
    printf("Value pointed to by cp: %d\n", *cp);
    printf("Address stored in cp: %p\n", (void*)cp);
    cp = &a;
    printf("Value pointed to by cp: %d\n", *cp);
    printf("Address stored in cp: %p\n", (void*)cp);
    cp = &b;
    printf("Value pointed to by cp: %d\n", *cp);
    printf("Address stored in cp: %p\n", (void*)cp);
    cp = &c;
    printf("Value pointed to by cp: %d\n", *cp);
    printf("Address stored in cp: %p\n", (void*)cp);


    return 0;
}

// Function implementations
int add(int a, int b) {
    return a + b;
}

int sub(int a, int b) {
    return a - b;
}

int mul(int a, int b) {
    return a * b;
}

int divide(int a, int b) {
    if (b == 0) return 0;  // Avoid division by zero
    return a / b;
}

int mod(int a, int b) {
    if (b == 0) return 0;  // Avoid division by zero
    return a % b;
}

int power(int a, int b) {
    int result = 1;
    for (int i = 0; i < b; i++) {
        result *= a;
    }
    return result;
}

int square_root(int a) {
    if (a < 0) return 0;  // Handle negative numbers
    if (a == 0 || a == 1) return a;
    // Simple integer square root implementation
    int x = a;
    int y = (x + 1) / 2;
    while (y < x) {
        x = y;
        y = (x + a / x) / 2;
    }
    return x;
}