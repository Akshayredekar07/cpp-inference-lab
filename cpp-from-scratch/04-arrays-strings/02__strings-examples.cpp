// ════════════════════════════════════════════════════════════
// Strings in C++ — complete demo
//
// Covers, in order:
//   1.  C-style strings (char arrays, null terminator)
//   2.  <cstring> functions (strlen, strcmp, strcpy, strcat, strstr)
//   3.  std::string construction and assignment
//   4.  Concatenation (+, +=, append, push_back)
//   5.  Comparison operators
//   6.  Length, capacity, reserve, resize, small-string optimization
//   7.  Access: [], at(), front(), back(), c_str()
//   8.  Substring, find, replace
//   9.  Modifiers: insert, erase, clear, remove-erase idiom
//  10.  Iteration (range-for, index, iterator, reverse)
//  11.  Numeric conversions: stoi/stod/to_string
//  12.  std::string_view (C++17) for cheap parameters
//  13.  Stream input: >> vs getline and the leftover newline gotcha
//  14.  Common pitfalls (dangling c_str, dangling string_view)
//
// Each numbered banner prints before the corresponding demo in main().
// ════════════════════════════════════════════════════════════

#include <algorithm>
#include <cstring>
#include <iostream>
#include <iterator>
#include <limits>
#include <string>
#include <string_view>

// ──── 1. C-style strings ────
// A C-string is a char array whose last element is '\0'. Functions
// like strlen, strcpy walk until they find that zero byte.
void demo_c_strings() {
    std::cout << "──── 1. C-style strings ────\n";

    char greeting[] = "hello";
    std::cout << "  sizeof(greeting)   = " << sizeof(greeting)
              << " (includes '\\0')\n";
    std::cout << "  std::strlen(s)     = " << std::strlen(greeting)
              << " (characters only)\n";

    // Constructing the same thing explicitly:
    char spelled[6] = {'h', 'e', 'l', 'l', 'o', '\0'};
    std::cout << "  spelled             = " << spelled << "\n";

    // Forgetting the terminator is undefined behavior — do not do it.
    // char bad[5] = {'h','e','l','l','o'};   // NO '\0' — UB
}


// ──── 2. <cstring> functions ────
// The C library gives you strlen, strcmp, strcpy, strcat, strchr,
// strstr, and safer n-bounded variants. They walk until '\0'.
void demo_cstring_funcs() {
    std::cout << "──── 2. <cstring> functions ────\n";

    char a[32] = "Hello, ";
    char b[]   = "world!";

    std::cout << "  std::strlen(a)         = " << std::strlen(a) << "\n";
    std::cout << "  std::strcmp(a,b)       = " << std::strcmp(a, b)
              << " (negative: a<b)\n";

    // strcpy / strcat will happily overflow — use the n-bounded forms.
    std::strncpy(a + std::strlen(a), b, sizeof(a) - std::strlen(a) - 1);
    a[sizeof(a) - 1] = '\0';
    std::cout << "  after strncpy, a       = " << a << "\n";

    const char* haystack = "the quick brown fox";
    const char* needle   = "brown";
    const char* hit      = std::strstr(haystack, needle);
    std::cout << "  strstr found 'brown'   = "
              << (hit ? hit : "(not found)") << "\n";
}


// ──── 3. std::string construction and assignment ────
void demo_std_string_construction() {
    std::cout << "──── 3. std::string construction ────\n";

    std::string s1;                       // empty
    std::string s2 = "hello";             // from literal
    std::string s3("hello");              // parenthesized
    std::string s4(5, 'x');               // "xxxxx"
    std::string s5 = s2;                  // copy
    std::string s6(s2, 1, 3);             // "ell" — from s2, idx 1, len 3
    std::string s7(s2.begin(), s2.end()); // full copy via iterators

    std::cout << "  s2 = " << s2 << "\n";
    std::cout << "  s4 = " << s4 << "\n";
    std::cout << "  s6 = " << s6 << "\n";
    std::cout << "  s7 = " << s7 << "\n";

    s1 = s2;                              // assignment copies
    std::cout << "  s1 after assignment  = " << s1 << "\n";
}


// ──── 4. concatenation ────
void demo_concatenation() {
    std::cout << "──── 4. concatenation ────\n";

    std::string a = "Hello, ";
    std::string b = "world";
    std::string c = a + b;                // "Hello, world"
    a += b;                               // a becomes "Hello, world"
    a += '!';                             // append one char

    std::cout << "  c        = " << c << "\n";
    std::cout << "  a after  = " << a << "\n";

    // "+" of two string literals is a compile error (pointer+pointer).
    // auto bad = "Hello, " + "world";   // ERROR

    // Mixing std::string + literal works because of implicit conversion.
    auto ok = std::string("Hello, ") + "world";
    std::cout << "  ok       = " << ok << "\n";

    std::string s = "abc";
    s.append("def");                      // "abcdef"
    s.append(3, '!');                     // "abcdef!!!"
    s.push_back('?');                     // "abcdef!!!?"
    std::cout << "  s        = " << s << "\n";
}


// ──── 5. comparison ────
// Lexicographic comparison via overloaded operators.
void demo_comparison() {
    std::cout << "──── 5. comparison ────\n";

    std::string a = "apple";
    std::string b = "banana";

    std::cout << "  a == b   : " << (a == b) << "\n";
    std::cout << "  a != b   : " << (a != b) << "\n";
    std::cout << "  a <  b   : " << (a <  b) << "\n";
    std::cout << "  a == \"apple\" : "
              << (a == std::string("apple")) << "\n";
}


// ──── 6. length, capacity, reserve ────
// size() == length(). capacity() is how much fits before reallocation.
// reserve(n) asks for at least n up front; resize(n) changes the size.
void demo_length_capacity() {
    std::cout << "──── 6. length, capacity, reserve ────\n";

    std::string s;
    std::cout << "  initial: size=" << s.size()
              << " capacity=" << s.capacity() << "\n";

    s.reserve(100);                       // avoid repeated reallocations
    std::cout << "  after reserve(100): size=" << s.size()
              << " capacity=" << s.capacity() << "\n";

    s.resize(10, 'x');                    // grow, pad with 'x'
    std::cout << "  after resize(10,'x'):  \"" << s << "\"\n";

    s.resize(3);                          // shrink — drops trailing chars
    std::cout << "  after resize(3):       \"" << s << "\"\n";
}


// ──── 7. accessing characters ────
// operator[] is unchecked; .at() throws; .c_str() returns a
// null-terminated const char* usable by C APIs.
void demo_access() {
    std::cout << "──── 7. accessing characters ────\n";

    std::string s = "hello";
    std::cout << "  s[0]      = " << s[0] << "\n";
    std::cout << "  s.at(0)   = " << s.at(0) << "\n";
    std::cout << "  s.front() = " << s.front() << "\n";
    std::cout << "  s.back()  = " << s.back() << "\n";

    s.front() = 'H';
    s.back()  = '!';
    std::cout << "  after     = " << s << "\n";

    const char* cstr = s.c_str();
    std::cout << "  c_str()   = " << cstr << " (C-API ready)\n";

    try {
        (void)s.at(100);
    } catch (const std::out_of_range& e) {
        std::cout << "  caught out_of_range from at(100)\n";
    }
}


// ──── 8. substr, find, replace ────
// All return size_t positions or std::string::npos when not found.
void demo_substr_find_replace() {
    std::cout << "──── 8. substr, find, replace ────\n";

    std::string s = "Hello, world";

    std::cout << "  substr(7)    = \"" << s.substr(7) << "\"\n";
    std::cout << "  substr(7,5)  = \"" << s.substr(7, 5) << "\"\n";

    std::size_t pos = s.find("world");
    std::cout << "  find(\"world\") = " << pos
              << " (npos=" << std::string::npos << ")\n";

    std::size_t miss = s.find("xyz");
    std::cout << "  find(\"xyz\")   = " << miss
              << " (== npos? " << (miss == std::string::npos) << ")\n";

    std::string r = "I hate C++";
    r.replace(2, 4, "love");              // idx 2, replace 4 chars
    std::cout << "  after replace = \"" << r << "\"\n";
}


// ──── 9. modifiers ────
void demo_modifiers() {
    std::cout << "──── 9. modifiers (insert, erase, remove-erase) ────\n";

    std::string s = "Hello world";
    s.insert(5, ",");                     // "Hello, world"
    std::cout << "  insert(5,\",\")   = \"" << s << "\"\n";

    s.erase(5, 1);                        // drop the comma
    std::cout << "  erase(5,1)        = \"" << s << "\"\n";

    s.clear();
    std::cout << "  after clear       = \"" << s << "\" (empty="
              << s.empty() << ")\n";

    // remove-erase idiom — drop all commas.
    std::string t = "a,b,c,d";
    t.erase(std::remove(t.begin(), t.end(), ','), t.end());
    std::cout << "  remove-erase ','  = \"" << t << "\"\n";
}


// ──── 10. iteration ────
void demo_iteration() {
    std::cout << "──── 10. iteration ────\n";

    std::string s = "hello";

    std::cout << "  range-for:    ";
    for (char c : s) std::cout << c << ' ';
    std::cout << "\n";

    std::cout << "  index loop:   ";
    for (std::size_t i = 0; i < s.size(); ++i) {
        std::cout << s[i] << ' ';
    }
    std::cout << "\n";

    std::cout << "  iterators:    ";
    for (auto it = s.begin(); it != s.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << "\n";

    std::cout << "  reverse:      ";
    for (auto it = s.rbegin(); it != s.rend(); ++it) {
        std::cout << *it;
    }
    std::cout << "\n";
}


// ──── 11. numeric conversions ────
void demo_numeric_conversions() {
    std::cout << "──── 11. numeric conversions ────\n";

    int    i = std::stoi("42");
    double f = std::stod("3.14");
    int    b = std::stoi("1010", nullptr, 2);   // base 2
    int    h = std::stoi("ff",   nullptr, 16);  // base 16

    std::cout << "  stoi(\"42\")        = " << i   << "\n";
    std::cout << "  stod(\"3.14\")      = " << f   << "\n";
    std::cout << "  stoi(\"1010\",,2)   = " << b   << " (binary)\n";
    std::cout << "  stoi(\"ff\",,16)    = " << h   << " (hex)\n";

    std::string s1 = std::to_string(42);
    std::string s2 = std::to_string(3.14);
    std::cout << "  to_string(42)      = \"" << s1 << "\"\n";
    std::cout << "  to_string(3.14)    = \"" << s2 << "\"\n";
}


// ──── 12. std::string_view (C++17) ────
// A non-owning pointer + length. Cheap to pass, zero allocation.
// The underlying storage must outlive the view.
void print_twice(std::string_view sv) {
    std::cout << "  print_twice: \"" << sv << "\" \"" << sv << "\"\n";
}

void demo_string_view() {
    std::cout << "──── 12. std::string_view ────\n";

    std::string owned = "hello";
    const char* lit   = "world";
    char raw[]        = "raw";

    print_twice(owned);                  // std::string converts
    print_twice(lit);                    // const char* converts
    print_twice(raw);                    // char[] converts

    // Cheap substring without copying:
    std::string path = "/home/user/file.txt";
    std::string_view filename = path;
    filename.remove_prefix(filename.find_last_of('/') + 1);
    std::cout << "  filename view     = \"" << filename << "\"\n";
}


// ──── 13. stream input ────
// >> reads one whitespace-delimited word. getline reads the whole
// line. Mixing them needs care because >> leaves a trailing '\n'.
void demo_stream_input() {
    std::cout << "──── 13. stream input (>> vs getline) ────\n";

    // We can't really call std::cin here without a real terminal,
    // but we can show the pieces of the pattern.

    std::cout << "  pattern: read int, then discard newline, then getline\n";
    std::cout << "      int n; std::cin >> n;\n";
    std::cout << "      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\\n');\n";
    std::cout << "      std::string line; std::getline(std::cin, line);\n";

    // Show that getline returns the stream, useful for testing EOF.
    std::cout << "  while (std::getline(std::cin, line)) { ... } works until EOF\n";
}


// ──── 14. common pitfalls ────
void demo_pitfalls() {
    std::cout << "──── 14. common pitfalls ────\n";

    // (a) Returning a string_view to a local std::string.
    // Uncomment to see dangling; we just illustrate by NOT calling it.
    auto bad_view = []() -> std::string_view {
        std::string local = "temporary";   // dies at function end
        return local;                       // dangles
    };
    std::string_view dangling = bad_view();
    // DO NOT use dangling — just demonstrate that it compiles.
    std::cout << "  (a) string_view from local string compiles but dangles\n";

    // (b) c_str() valid only as long as the string is unchanged.
    const char* p;
    {
        std::string s = "scoped";
        p = s.c_str();
        std::cout << "  (b) inside scope, c_str() = " << p << "\n";
    }
    // p is now dangling — do not use.

    // (c) Modifying while iterating by index can skip characters.
    std::string s = "abc";
    for (std::size_t i = 0; i < s.size(); ++i) {
        if (s[i] == 'b') {
            s.erase(i, 1);                  // 'c' now sits at index i
            --i;                            // re-check this index
        }
    }
    std::cout << "  (c) careful erase-by-index: \"" << s << "\"\n";
}


// ════════════════════════════════════════════════════════════
// main — runs every demo in order.
// ════════════════════════════════════════════════════════════
int main() {
    demo_c_strings();
    demo_cstring_funcs();
    demo_std_string_construction();
    demo_concatenation();
    demo_comparison();
    demo_length_capacity();
    demo_access();
    demo_substr_find_replace();
    demo_modifiers();
    demo_iteration();
    demo_numeric_conversions();
    demo_string_view();
    demo_stream_input();
    demo_pitfalls();
    return 0;
}
