/**
 * UNIONS IN C - Complete & Clear Example
 * 
 * Key Points:
 *  - All members of a union SHARE the same memory location
 *  - Only ONE member can hold a value at a time
 *  - Size of union = size of its LARGEST member
 *  - Used for: saving memory, type punning, variant types (with tag)
 */

 #include <stdio.h>
 #include <string.h>
 
 // =============================================
 // 1. BASIC UNION - All members share memory
 // =============================================
 union Data {
     int   i;      // 4 bytes
     float f;      // 4 bytes
     char  str[9]; // 9 bytes → this is the largest!
     char  c;      // 1 byte
 };
 
 void basic_union_demo() {
     printf("=== 1. BASIC UNION DEMO ===\n");
     
     union Data data;
 
     printf("Size of union Data: %zu bytes\n", sizeof(data));
     printf("(Because largest member 'str[9]' takes 9 bytes + padding → usually 12)\n\n");
 
     // Let's see memory addresses (all same!)
     printf("Memory addresses inside union:\n");
     printf("  &data.i   = %p\n", (void*)&data.i);
     printf("  &data.f   = %p\n", (void*)&data.f);
     printf("  &data.str = %p\n", (void*)&data.str);
     printf("  &data.c   = %p\n", (void*)&data.c);
     printf("(All point to the SAME starting address!)\n\n");
 
     // Assign different values → see how they overwrite each other
     data.i = 1000;
     printf("Set data.i = 1000\n");
     printf("→ data.i   = %d\n", data.i);
     printf("→ data.f   = %f (garbage)\n", data.f);
     printf("→ data.str = '%s' (garbage)\n\n", data.str);
 
     data.f = 3.14159f;
     printf("Set data.f = 3.14159\n");
     printf("→ data.f   = %.5f\n", data.f);
     printf("→ data.i   = %d (now corrupted!)\n\n", data.i);
 
     strcpy(data.str, "HELLO");
     printf("Set data.str = \"HELLO\"\n");
     printf("→ data.str = %s\n", data.str);
     printf("→ data.i   = %d (overwritten again)\n", data.i);
     printf("→ data.f   = %f (overwritten)\n\n", data.f);
 }
 
 // =============================================
 // 2. TAGGED UNION (Real-world safe usage)
 // =============================================
 typedef enum {
     TYPE_INT,
     TYPE_FLOAT,
     TYPE_STRING
 } ValueType;
 
 typedef struct {
     ValueType type;  // tells us which field in union is valid
     union {
         int     i;
         float   f;
         char    str[20];
     } value;
 } Variant;
 
 void print_variant(Variant v) {
     switch (v.type) {
         case TYPE_INT:
             printf("Integer: %d\n", v.value.i);
             break;
         case TYPE_FLOAT:
             printf("Float: %.2f\n", v.value.f);
             break;
         case TYPE_STRING:
             printf("String: \"%s\"\n", v.value.str);
             break;
     }
 }
 
 void tagged_union_demo() {
     printf("=== 2. TAGGED UNION (Safe & Practical) ===\n");
 
     Variant v1, v2, v3;
 
     // Store an integer
     v1.type = TYPE_INT;
     v1.value.i = 42;
 
     // Store a float
     v2.type = TYPE_FLOAT;
     v2.value.f = 9.99f;
 
     // Store a string
     v3.type = TYPE_STRING;
     strcpy(v3.value.str, "C Programming");
 
     printf("Size of Variant: %zu bytes\n", sizeof(Variant));
     printf("(union takes ~20 bytes + 4-byte enum + padding = ~24 bytes)\n\n");
 
     print_variant(v1);
     print_variant(v2);
     print_variant(v3);
     printf("\n");
 }
 
 // =============================================
 // 3. STRUCT vs UNION - Memory Comparison
 // =============================================
 struct StructExample {
     int   i;      // 4 bytes
     float f;      // 4 bytes
     char  c;      // 1 byte + 3 padding
 }; // Total: 12 bytes (with padding)
 
 union UnionExample {
     int   i;      // 4 bytes
     float f;      // 4 bytes
     char  c;      // 1 byte
 }; // Total: 4 bytes (only largest member)
 
 void size_comparison() {
     printf("=== 3. STRUCT vs UNION Size Comparison ===\n");
     printf("struct StructExample size = %zu bytes\n", sizeof(struct StructExample));
     printf("union  UnionExample  size = %zu bytes\n", sizeof(union UnionExample));
     printf("→ Union saves memory when only one field is used at a time!\n\n");
 }
 
 // =============================================
 // MAIN FUNCTION
 // =============================================
 int main() {
     printf("UNIONS IN C - Complete Clear Example\n");
     printf("========================================\n\n");
 
     basic_union_demo();
     tagged_union_demo();
     size_comparison();
 
     printf("Key Takeaway:\n");
     printf("Use UNION when you need to store ONLY ONE type at a time → saves memory\n");
     printf("Always pair with a 'tag' (enum) in real code for safety!\n");
 
     return 0;
 }