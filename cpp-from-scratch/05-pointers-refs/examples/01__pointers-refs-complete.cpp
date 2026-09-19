// ════════════════════════════════════════════════════════════
// Pointers and references in C++
//
// Covers, in order:
//   1.  Pointer basics: address-of (&), dereference (*), nullptr
//   2.  Pointers and const — three different meanings
//   3.  Pointers and arrays — decay, arithmetic, indexing
//   4.  Pointer to pointer (int**)
//   5.  void* — the type-erased pointer
//   6.  Pass by pointer
//   7.  Dynamic memory: new / delete / new[] / delete[]
//   8.  Reference basics — alias, must be bound, cannot rebind
//   9.  Pass by reference and pass by const reference
//  10.  Returning references — and the dangling-reference trap
//  11.  References in range-for
//  12.  rvalue references (int&&) — brief preview
//  13.  Function pointers
//  14.  Pointers vs references — choosing between them
//
// Each numbered banner prints before the corresponding demo in main().
// ════════════════════════════════════════════════════════════


#include <iostream>
#include <string>
#include <vector>
#include <utility>


// ──── 1. pointer basics: &, *, nullptr ────
// A pointer holds an ADDRESS. & takes an address, * dereferences it.
void demo_pointerBasics() {
    std::cout << "──── 1. pointer basics ────\n";

    int rollNumber = 21;
    int* rollPtr = &rollNumber;       // & = "address of" rollNumber

    std::cout << "  rollNumber       = " << rollNumber    << "\n";
    std::cout << "  &rollNumber      = " << &rollNumber   << "\n";
    std::cout << "  rollPtr          = " << rollPtr       << "\n";
    std::cout << "  *rollPtr         = " << *rollPtr      << "\n";   // 21

    *rollPtr = 22;                    // writes THROUGH the pointer
    std::cout << "  after *rollPtr = 22, rollNumber = "
              << rollNumber << "\n";                             // 22

    // nullptr — a pointer that points at nothing
    int* nothing = nullptr;
    if (nothing == nullptr) {
        std::cout << "  nothing points nowhere — safe\n";
    }
    // *nothing;   // UNDEFINED BEHAVIOUR — never dereference a null pointer
}


// ──── 2. const with pointers — three different meanings ────
// Read right-to-left from the variable name.
void demo_constPointers() {
    std::cout << "\n──── 2. const with pointers ────\n";

    int value = 10;
    int other = 99;

    const int* p1 = &value;           // pointer to CONST int
    int* const p2 = &value;           // CONST pointer to int
    const int* const p3 = &value;     // both const

    // p1 — data is locked, pointer is reseatable
    // *p1 = 20;     // ERROR: data is const
    p1 = &other;                      // OK: pointer can move
    std::cout << "  p1 reseated to &other, *p1 = " << *p1 << "\n";

    // p2 — pointer is locked, data is writable
    *p2 = 20;                         // OK: data is writable
    // p2 = &other; // ERROR: pointer is const
    std::cout << "  p2 wrote through: value = " << value << "\n";

    // p3 — both locked
    // *p3 = 20;     // ERROR
    // p3 = &other;  // ERROR
    (void)p3;
}


// ──── 3. pointers and arrays — decay, arithmetic, indexing ────
// An array's name decays into a pointer to its first element.
void demo_pointersAndArrays() {
    std::cout << "\n──── 3. pointers and arrays ────\n";

    int marks[5] = {90, 85, 70, 60, 40};
    int* p = marks;                   // same as: int* p = &marks[0];

    std::cout << "  *p        = " << *p        << " (first)\n";
    std::cout << "  *(p + 1)  = " << *(p + 1)  << " (second)\n";
    std::cout << "  p[3]      = " << p[3]      << " (pointer indexing)\n";

    // pointer arithmetic advances by sizeof(*p) — 4 bytes for int
    std::cout << "  p+1 advances by " << sizeof(int)
              << " bytes (sizeof(int))\n";

    std::cout << "  walking: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << *(p + i) << " ";  // same as p[i]
    }
    std::cout << "\n";
}


// ──── 4. pointer to pointer ────
// A pointer's address can itself be stored in another pointer.
void demo_pointerToPointer() {
    std::cout << "\n──── 4. pointer to pointer ────\n";

    int value = 5;
    int* p = &value;
    int** pp = &p;                    // pp holds the ADDRESS of p

    std::cout << "  value      = " << value     << "\n";
    std::cout << "  *p         = " << *p        << "\n";
    std::cout << "  **pp       = " << **pp      << "\n";

    **pp = 10;                        // writes through two levels
    std::cout << "  after **pp = 10, value = " << value << "\n";
}


// ──── 5. void* — the type-erased pointer ────
// Can point at anything, but cannot be dereferenced directly.
void demo_voidPointer() {
    std::cout << "\n──── 5. void* ────\n";

    int number = 42;
    void* generic = &number;

    // std::cout << *generic;   // ERROR: cannot dereference void*
    int* back = static_cast<int*>(generic);
    std::cout << "  void* cast back to int*: " << *back << "\n";
}


// ──── 6. pass by pointer ────
// The function receives the ADDRESS of the caller's variable.
void addTenByPointer(int* value) {
    if (value != nullptr) {
        *value = *value + 10;
    }
}

void demo_passByPointer() {
    std::cout << "\n──── 6. pass by pointer ────\n";

    int marks = 50;
    addTenByPointer(&marks);          // caller passes the address
    std::cout << "  after addTenByPointer: marks = " << marks << "\n";

    int* nothing = nullptr;
    addTenByPointer(nothing);         // safe — function checked for null
    std::cout << "  nullptr argument handled safely\n";
}


// ──── 7. dynamic memory: new / delete / new[] / delete[] ────
// new creates something on the heap; YOU must free it with delete.
void demo_dynamicMemory() {
    std::cout << "\n──── 7. dynamic memory ────\n";

    int* p = new int(42);             // allocate one int on the heap
    std::cout << "  *p = " << *p << "\n";
    delete p;                         // free it
    p = nullptr;                      // good practice: avoid dangling

    int* arr = new int[5];            // allocate an array of 5 ints
    for (int i = 0; i < 5; ++i) {
        arr[i] = i * 10;
    }
    std::cout << "  arr[3] = " << arr[3] << "\n";
    delete[] arr;                     // note: [] for array delete
    arr = nullptr;

    std::cout << "  freed and nulled — no leaks, no dangling\n";
}


// ──── 8. reference basics — alias, must be bound, cannot rebind ────
// A reference is another name for an existing variable.
void demo_referenceBasics() {
    std::cout << "\n──── 8. reference basics ────\n";

    int marks = 90;
    int& scoreRef = marks;            // scoreRef is ANOTHER NAME for marks

    std::cout << "  marks    = " << marks      << "\n";
    std::cout << "  scoreRef = " << scoreRef   << "\n";

    scoreRef = 95;                    // changes marks too — same object
    std::cout << "  after scoreRef = 95, marks = " << marks << "\n";
    std::cout << "  &marks == &scoreRef : "
              << (&marks == &scoreRef) << "\n";                    // 1 (true)

    // A reference CANNOT be rebound.
    int other = 50;
    int& r = marks;
    r = other;                        // does NOT rebind — assigns other's
    std::cout << "  after r = other, marks = " << marks
              << " (still bound to marks)\n";
}


// ──── 9. pass by reference and pass by const reference ────
// Reference parameters let functions reach the caller's variable
// without forcing &var at the call site.
void addTenByReference(int& value) {
    value = value + 10;
}

void printLength(const std::string& s) {
    std::cout << "  length = " << s.size() << "\n";
    // s += "!";   // ERROR: s is const here
}

void demo_passByReference() {
    std::cout << "\n──── 9. pass by reference ────\n";

    int marks = 50;
    addTenByReference(marks);         // no & at the call site
    std::cout << "  after addTenByReference: marks = "
              << marks << "\n";

    std::string name = "Karan";
    printLength(name);                // no copy, read-only access

    // const reference can also bind to a temporary
    const int& boundTemp = 5 + 5;
    std::cout << "  const& bound to temporary: " << boundTemp << "\n";
}


// ──── 10. returning references ────
// Return a reference only to something that outlives the function.
int& firstElement(std::vector<int>& v) {
    return v[0];                      // returns a reference into v
}

// Returns reference to a LOCAL — DO NOT DO THIS in real code.
// Kept here so the program makes the danger visible at compile time.
int& dangerousLocal() {
    int local = 5;
    return local;                     // local dies when function returns
}

void demo_returningReferences() {
    std::cout << "\n──── 10. returning references ────\n";

    std::vector<int> marks{90, 80, 70};
    firstElement(marks) = 100;        // write THROUGH the returned ref
    std::cout << "  after firstElement(marks) = 100, marks[0] = "
              << marks[0] << "\n";

    // Compile-time warning about returning a reference to a local.
    // Do NOT actually use the result — it is undefined behaviour.
    // int& bad = dangerousLocal();
    // (void)bad;
    std::cout << "  (skipping dangerousLocal() — undefined behaviour)\n";
}


// ──── 11. references in range-for ────
// int& writes, const int& reads without copying.
void demo_rangeForReferences() {
    std::cout << "\n──── 11. references in range-for ────\n";

    std::vector<int> nums{60, 70, 80};

    // int&  — modifies each element
    for (int& n : nums) {
        n += 5;
    }
    std::cout << "  after int& loop, nums[0] = " << nums[0] << "\n";

    // const int& — read-only, no copy
    std::cout << "  read-only: ";
    for (const int& n : nums) {
        std::cout << n << " ";
    }
    std::cout << "\n";
}


// ──── 12. rvalue references (brief preview) ────
// int&& binds to temporaries and enables move semantics.
void handle(int& x)  { std::cout << "  lvalue overload,  x=" << x   << "\n"; }
void handle(int&& x) { std::cout << "  rvalue overload,  x=" << x   << "\n"; }

void demo_rvalueReferences() {
    std::cout << "\n──── 12. rvalue references (preview) ────\n";

    int a = 5;
    handle(a);                        // lvalue overload — a is named
    handle(10);                       // rvalue overload — 10 is temporary
    handle(a + 1);                    // rvalue overload — expression result
}


// ──── 13. function pointers ────
// A variable that holds the address of a function.
int add(int a, int b)       { return a + b; }
int multiply(int a, int b) { return a * b; }

int apply(int (*op)(int, int), int x, int y) {
    return op(x, y);
}

void demo_functionPointers() {
    std::cout << "\n──── 13. function pointers ────\n";

    int (*operation)(int, int) = add;
    std::cout << "  apply(add, 3, 4)      = "
              << apply(operation, 3, 4) << "\n";

    operation = multiply;             // reseat to a different function
    std::cout << "  apply(multiply, 3, 4) = "
              << apply(operation, 3, 4) << "\n";
}


// ──── 14. pointer vs reference — choosing between them ────
// Prefer references by default. Use pointers when null is a real
// possibility or when reseating is needed.
void maybeUpdate(int* p) {
    if (p) *p = 100;
}

void demo_pointerVsReference() {
    std::cout << "\n──── 14. pointer vs reference ────\n";

    int x = 1;

    // Reference — must refer to something real, never null
    int& r = x;
    r = 10;
    std::cout << "  via reference, x = " << x << "\n";

    // Pointer — can be null, can be reseated
    int y = 2;
    int* p = &x;
    p = &y;                           // reseat
    std::cout << "  via reseated pointer, y = " << *p << "\n";

    // Pointer can express "no value"
    maybeUpdate(nullptr);             // safe — function checked for null
    std::cout << "  nullptr handled cleanly by maybeUpdate\n";
}


int main() {

    // ──── 1. pointer basics ────
    std::cout << "════ 1. pointer basics ════\n";
    demo_pointerBasics();


    // ──── 2. const with pointers ────
    std::cout << "\n════ 2. const with pointers ════\n";
    demo_constPointers();


    // ──── 3. pointers and arrays ────
    std::cout << "\n════ 3. pointers and arrays ════\n";
    demo_pointersAndArrays();


    // ──── 4. pointer to pointer ────
    std::cout << "\n════ 4. pointer to pointer ════\n";
    demo_pointerToPointer();


    // ──── 5. void* ────
    std::cout << "\n════ 5. void* ════\n";
    demo_voidPointer();


    // ──── 6. pass by pointer ────
    std::cout << "\n════ 6. pass by pointer ════\n";
    demo_passByPointer();


    // ──── 7. dynamic memory ────
    std::cout << "\n════ 7. dynamic memory ════\n";
    demo_dynamicMemory();


    // ──── 8. reference basics ────
    std::cout << "\n════ 8. reference basics ════\n";
    demo_referenceBasics();


    // ──── 9. pass by reference ────
    std::cout << "\n════ 9. pass by reference ════\n";
    demo_passByReference();


    // ──── 10. returning references ────
    std::cout << "\n════ 10. returning references ════\n";
    demo_returningReferences();


    // ──── 11. references in range-for ────
    std::cout << "\n════ 11. references in range-for ════\n";
    demo_rangeForReferences();


    // ──── 12. rvalue references (preview) ────
    std::cout << "\n════ 12. rvalue references (preview) ════\n";
    demo_rvalueReferences();


    // ──── 13. function pointers ────
    std::cout << "\n════ 13. function pointers ════\n";
    demo_functionPointers();


    // ──── 14. pointer vs reference ────
    std::cout << "\n════ 14. pointer vs reference ════\n";
    demo_pointerVsReference();


    std::cout << "\n════ done ════\n";

    return 0;
}


// ════════════════════════════════════════════════════════════
// End of pointers and references demo.
// Companion notes live in:
//   05-pointers-refs/05-pointers-refs.md
//   05-pointers-refs/01-references.md
// ════════════════════════════════════════════════════════════
