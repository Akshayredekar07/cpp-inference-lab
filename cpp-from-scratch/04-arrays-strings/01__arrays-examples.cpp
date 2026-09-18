// ════════════════════════════════════════════════════════════
// Arrays in C++ — complete demo
//
// Covers, in order:
//   1.  Declaration and initialization
//   2.  Indexing and bounds (no built-in check)
//   3.  Size: sizeof, std::size, std::ssize
//   4.  Iteration: classic for, range-for, pointer loop
//   5.  Multidimensional arrays (row-major layout)
//   6.  Array-to-pointer decay
//   7.  Passing arrays to functions (pointer + length vs reference)
//   8.  std::array — fixed-size with members
//   9.  Arrays of structs
//  10.  const arrays (lookup tables)
//  11.  Common pitfalls (off-by-one, decay losing size, ==)
//
// Each numbered banner prints before the corresponding demo in main().
// ════════════════════════════════════════════════════════════

#include <array>
#include <cstddef>
#include <iostream>
#include <iterator>

// ──── 1. declaration and initialization ────
// C arrays need a compile-time size. Lists shorter than the size
// are zero-padded; lists longer are a compile error.
void demo_declaration() {
    std::cout << "──── 1. declaration and initialization ────\n";

    int uninit[5];                     // garbage values
    int zero[5] = {};                  // all five are 0
    int partial[5] = {1, 2};           // [1,2,0,0,0]
    int primes[] = {2, 3, 5, 7, 11};   // size inferred: 5

    std::cout << "  zero[0]=" << zero[0]
              << " partial[2]=" << partial[2] << "\n";
    std::cout << "  primes inferred size = "
              << sizeof(primes) / sizeof(primes[0]) << "\n";
}


// ──── 2. indexing and bounds ────
// operator[] does NOT check bounds. Reading or writing past the end
// is undefined behavior. std::array::at() does check.
void demo_indexing() {
    std::cout << "──── 2. indexing and bounds ────\n";

    int a[5] = {10, 20, 30, 40, 50};

    std::cout << "  a[0]=" << a[0] << " (first)\n";
    std::cout << "  a[4]=" << a[4] << " (last valid)\n";

    std::array<int, 5> sa = {10, 20, 30, 40, 50};
    std::cout << "  std::array at(2)=" << sa.at(2) << " (safe)\n";

    try {
        (void)sa.at(100);             // throws std::out_of_range
    } catch (const std::out_of_range& e) {
        std::cout << "  caught out_of_range: " << e.what() << "\n";
    }
}


// ──── 3. size: sizeof, std::size, std::ssize ────
// Plain arrays do not have a .size() — you compute it from sizeof
// or use std::size / std::ssize (C++17 / C++20).
void demo_size() {
    std::cout << "──── 3. size helpers ────\n";

    int a[7] = {1, 2, 3, 4, 5, 6, 7};
    std::cout << "  sizeof(a)              = " << sizeof(a) << " bytes\n";
    std::cout << "  sizeof(a)/sizeof(a[0]) = "
              << sizeof(a) / sizeof(a[0]) << " elements\n";
    std::cout << "  std::size(a)           = " << std::size(a) << "\n";
    std::cout << "  std::ssize(a)          = " << std::ssize(a)
              << " (signed)\n";
}


// ──── 4. iteration ────
// Three styles for walking an array.
void demo_iteration() {
    std::cout << "──── 4. iteration ────\n";

    int a[5] = {1, 2, 3, 4, 5};

    std::cout << "  classic: ";
    for (std::size_t i = 0; i < std::size(a); ++i) {
        std::cout << a[i] << " ";
    }
    std::cout << "\n";

    std::cout << "  range-for (read):  ";
    for (int x : a) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    std::cout << "  range-for (write): ";
    for (int& x : a) {
        x *= 10;                      // doubles — no, multiplies by 10
    }
    for (int x : a) std::cout << x << " ";
    std::cout << "\n";

    std::cout << "  pointer loop:      ";
    for (int* p = a; p < a + std::size(a); ++p) {
        std::cout << *p << " ";
    }
    std::cout << "\n";
}


// ──── 5. multidimensional arrays ────
// Stored row-major: all rows contiguous in memory.
void demo_multidim() {
    std::cout << "──── 5. multidimensional arrays ────\n";

    int m[3][4] = {
        { 1,  2,  3,  4},
        { 5,  6,  7,  8},
        { 9, 10, 11, 12}
    };

    std::cout << "  m[1][2] = " << m[1][2] << "\n";

    std::cout << "  print row-major:\n";
    for (int i = 0; i < 3; ++i) {
        std::cout << "    ";
        for (int j = 0; j < 4; ++j) {
            std::cout << m[i][j] << "\t";
        }
        std::cout << "\n";
    }

    // Show that the inner array's size can be deduced from the type.
    std::cout << "  sizeof(int[4]) = " << sizeof(int[4]) << " bytes\n";
}


// ──── 6. array-to-pointer decay ────
// In most expressions the array name becomes a pointer to its first
// element. sizeof, &, and references to arrays are the exceptions.
void demo_decay(const int* p, std::size_t n) {   // helper for demo 7
    for (std::size_t i = 0; i < n; ++i) {
        std::cout << p[i] << " ";
    }
    std::cout << "\n";
}

void demo_array_decay() {
    std::cout << "──── 6. array-to-pointer decay ────\n";

    int a[5] = {10, 20, 30, 40, 50};

    int* p = a;                       // a decays to &a[0]
    std::cout << "  *p       = " << *p << "\n";
    std::cout << "  p[2]     = " << p[2] << " (pointer + index)\n";

    // Exceptions to decay:
    std::cout << "  sizeof(a)        = " << sizeof(a) << " (full array)\n";
    std::cout << "  sizeof(p)        = " << sizeof(p) << " (just a pointer)\n";

    int (*pa)[5] = &a;                // pointer to the whole array
    std::cout << "  (*pa)[0] = " << (*pa)[0] << " via pointer-to-array\n";

    int (&ra)[5] = a;                 // reference to the array — no decay
    std::cout << "  ra[4]    = " << ra[4] << " via reference\n";

    demo_decay(a, std::size(a));      // a decays to int* when passed
}


// ──── 7. passing arrays to functions ────
// Option A: pointer + length (C style).
void print_ptr(const int* p, std::size_t n) {
    std::cout << "  print_ptr:    ";
    for (std::size_t i = 0; i < n; ++i) std::cout << p[i] << " ";
    std::cout << "\n";
}

// Option B: reference to a fixed-size array (compile-time size check).
void print_ref_fixed(const int (&arr)[5]) {
    std::cout << "  print_ref5:   ";
    for (int x : arr) std::cout << x << " ";
    std::cout << "\n";
}

// Option C: template that deduces the size.
template <std::size_t N>
void print_ref_any(const int (&arr)[N]) {
    std::cout << "  print_refN:   ";
    for (int x : arr) std::cout << x << " ";
    std::cout << " (N=" << N << ")\n";
}

void demo_passing() {
    std::cout << "──── 7. passing arrays to functions ────\n";

    int a[5] = {1, 2, 3, 4, 5};

    print_ptr(a, std::size(a));       // pointer + length
    print_ref_fixed(a);               // reference, fixed size
    print_ref_any(a);                 // template, size deduced
}


// ──── 8. std::array ────
// Fixed size known at compile time, but with .size(), .at(), copy,
// assignment, and STL compatibility.
void demo_std_array() {
    std::cout << "──── 8. std::array ────\n";

    std::array<int, 5> a = {1, 2, 3, 4, 5};
    std::array<int, 5> b{};

    std::cout << "  a.size() = " << a.size() << "\n";
    std::cout << "  a.at(3)  = " << a.at(3) << "\n";

    b = a;                            // copy assignment works
    b.fill(0);                        // all five become 0
    std::cout << "  b after fill(0): ";
    for (int x : b) std::cout << x << " ";
    std::cout << "\n";

    b.swap(a);                        // contents swap
    std::cout << "  b after swap:   ";
    for (int x : b) std::cout << x << " ";
    std::cout << "\n";
}


// ──── 9. arrays of structs ────
// Each element is a full struct, stored inline in the array.
struct Point {
    double x;
    double y;
};

void demo_array_of_structs() {
    std::cout << "──── 9. arrays of structs ────\n";

    Point polyline[3] = {
        {0.0, 0.0},
        {1.5, 2.0},
        {3.0, 4.5}
    };

    polyline[1].x = 1.6;              // dot access on the element
    std::cout << "  polyline[1] = (" << polyline[1].x
              << ", " << polyline[1].y << ")\n";

    double sumX = 0.0;
    for (const Point& p : polyline) {
        sumX += p.x;
    }
    std::cout << "  sum of x = " << sumX << "\n";
}


// ──── 10. const arrays (lookup tables) ────
// A const array is read-only after initialization.
void demo_const_array() {
    std::cout << "──── 10. const arrays ────\n";

    const int daysInMonth[] = {31, 28, 31, 30, 31, 30,
                               31, 31, 30, 31, 30, 31};
    // daysInMonth[0] = 99;          // would be a compile error

    std::cout << "  days in February = "
              << daysInMonth[1] << "\n";
}


// ──── 11. common pitfalls ────
void demo_pitfalls() {
    std::cout << "──── 11. common pitfalls ────\n";

    // (a) Comparing two arrays with == compares pointers, not contents.
    int a[3] = {1, 2, 3};
    int b[3] = {1, 2, 3};
    std::cout << "  (a==b) compares pointers, not contents: "
              << (a == b ? "true" : "false") << " (always false here)\n";

    // (b) sizeof on a decayed pointer is the size of a pointer.
    int* p = a;
    std::cout << "  sizeof(a)=" << sizeof(a)
              << "  sizeof(p)=" << sizeof(p) << "\n";

    // (c) Off-by-one — writing one past the end.
    int small[3] = {1, 2, 3};
    for (std::size_t i = 0; i <= std::size(small); ++i) {  // BUG: <= should be <
        if (i < std::size(small)) {
            std::cout << "  small[" << i << "]=" << small[i] << "\n";
        } else {
            std::cout << "  skipping index " << i
                      << " (out of bounds — would be UB)\n";
        }
    }
}


// ════════════════════════════════════════════════════════════
// main — runs every demo in order.
// ════════════════════════════════════════════════════════════
int main() {
    demo_declaration();
    demo_indexing();
    demo_size();
    demo_iteration();
    demo_multidim();
    demo_array_decay();
    demo_passing();
    demo_std_array();
    demo_array_of_structs();
    demo_const_array();
    demo_pitfalls();
    return 0;
}
