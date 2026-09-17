// ════════════════════════════════════════════════════════════
// Practice Problems — Preprocessor, Macros, Namespaces, iostream
// ════════════════════════════════════════════════════════════
// Build:
//   g++ -std=c++17 -Wall -Wextra -Wpedantic -Wshadow preprocessor_iostream.cpp -o app
//   ./app
//
// Three problems here (1, 5, 7) need a real filesystem / multiple
// translation units / a terminal, so they can't run inside one file.
// They're documented at the bottom with exact commands and the code
// to type — everything else runs live below.
//
// For problems that normally read std::cin (10, 11, 12), this file
// uses an std::istringstream loaded with fixed test data instead, so
// the behaviour is deterministic and runnable without a terminal.
// Swap `inputStream` for `std::cin` and the code is unchanged.
// ════════════════════════════════════════════════════════════

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>


// ════════════════════════════════════════════════════════════
// Problem 2 — macro vs constexpr
// ════════════════════════════════════════════════════════════
// #define is blind TEXT SUBSTITUTION before the compiler ever sees
// C++. If the argument has a side effect, that side effect gets
// pasted in wherever the macro used it — including twice.

#define SQR(x) ((x) * (x))

constexpr int sqr(int x) {
    return x * x;
}

// Observable, WELL-DEFINED double-evaluation (not UB) — a call counter.
int callCounter = 0;

int nextValue() {
    ++callCounter;
    std::cout << "    nextValue() called -> returns " << callCounter << "\n";
    return callCounter;
}


// ════════════════════════════════════════════════════════════
// Problem 3 — stringify (#) and token-paste (##)
// ════════════════════════════════════════════════════════════

#define MAKE_PAIR(NAME) int NAME##_a = 0; int NAME##_b = 0

#define STR(x) #x                  // stringize the LITERAL token
#define STR_EXPAND(x) STR(x)       // expand x first, THEN stringize


// ════════════════════════════════════════════════════════════
// Problem 4 — conditional compilation with predefined macros
// ════════════════════════════════════════════════════════════

#if defined(_WIN32)
    #define TARGET_OS "Windows"
#elif defined(__APPLE__)
    #define TARGET_OS "macOS"
#elif defined(__linux__)
    #define TARGET_OS "Linux"
#else
    #define TARGET_OS "Unknown OS"
#endif

#if defined(__clang__)
    #define TARGET_COMPILER "Clang"
#elif defined(__GNUC__)
    #define TARGET_COMPILER "GCC"
#elif defined(_MSC_VER)
    #define TARGET_COMPILER "MSVC"
#else
    #define TARGET_COMPILER "Unknown compiler"
#endif


// ════════════════════════════════════════════════════════════
// Problem 6 — namespace collision
// ════════════════════════════════════════════════════════════
// Two libraries, same function name, different namespaces.
// Zero collision because the FULL name includes the namespace.

namespace NetworkLib {
    void connect() {
        std::cout << "    NetworkLib::connect() — opening a socket\n";
    }
}

namespace DbLib {
    void connect() {
        std::cout << "    DbLib::connect() — opening a database session\n";
    }
}


// ════════════════════════════════════════════════════════════
// Problem 9 — formatted table with iomanip
// ════════════════════════════════════════════════════════════

struct Employee {
    std::string name;
    int age;
    double salary;
};


// ════════════════════════════════════════════════════════════
// Problem 10 — hand-rolled CSV split (no library delimiter helpers)
// ════════════════════════════════════════════════════════════

std::vector<std::string> splitCsv(const std::string& line) {
    std::vector<std::string> fields;
    std::size_t start = 0;

    while (start <= line.size()) {
        std::size_t comma = line.find(',', start);
        if (comma == std::string::npos) {
            fields.push_back(line.substr(start));
            break;
        }
        fields.push_back(line.substr(start, comma - start));
        start = comma + 1;
    }
    return fields;
}


int main() {

    // ════════════════════════════════════════════════════════
    // Problem 2 — macro vs constexpr
    // ════════════════════════════════════════════════════════
    std::cout << "──── 2. macro vs constexpr ────\n";

    callCounter = 0;
    std::cout << "  SQR(nextValue()) expands to (nextValue()) * (nextValue()):\n";
    int macroResult = SQR(nextValue());
    std::cout << "  macroResult = " << macroResult
              << "   <- WRONG. Called twice: 1*2=2, not 1*1=1\n";

    callCounter = 0;
    std::cout << "  sqr(nextValue()) — the argument is evaluated ONCE:\n";
    int funcResult = sqr(nextValue());
    std::cout << "  funcResult  = " << funcResult
              << "   <- correct. One call, its result squared\n";

    std::cout << "  a stricter trap: SQR(++i) expands to ((++i) * (++i)) — TWO\n";
    std::cout << "  unsequenced modifications of the same object `i`. That is not\n";
    std::cout << "  just \"wrong\", it is UNDEFINED BEHAVIOUR per the standard.\n";
    std::cout << "  sqr(++i) has no such problem: ++i is one sequenced expression,\n";
    std::cout << "  its single result is passed by value into the function.\n";

    std::cout << "  constexpr also gives type checking, scoping, and debugger\n";
    std::cout << "  visibility that a macro — pure text substitution — never has.\n";


    // ════════════════════════════════════════════════════════
    // Problem 3 — stringify and token-paste
    // ════════════════════════════════════════════════════════
    std::cout << "\n──── 3. # and ## ────\n";

    MAKE_PAIR(point);           // expands to: int point_a = 0; int point_b = 0;
    point_a = 3;
    point_b = 4;
    std::cout << "  MAKE_PAIR(point) -> point_a=" << point_a
              << " point_b=" << point_b << "\n";

    MAKE_PAIR(velocity);
    velocity_a = 10;
    velocity_b = -5;
    std::cout << "  MAKE_PAIR(velocity) -> velocity_a=" << velocity_a
              << " velocity_b=" << velocity_b << "\n";

    std::cout << "  STR(__LINE__)        = " << STR(__LINE__)
              << "   <- stringizes the LITERAL text \"__LINE__\"\n";
    std::cout << "  STR_EXPAND(__LINE__) = " << STR_EXPAND(__LINE__)
              << "   <- expands __LINE__ to a number FIRST, then stringizes\n";
    std::cout << "  the indirection (macro calling macro) is required any time\n";
    std::cout << "  you need to stringize the VALUE of another macro\n";


    // ════════════════════════════════════════════════════════
    // Problem 4 — conditional compilation
    // ════════════════════════════════════════════════════════
    std::cout << "\n──── 4. conditional compile ────\n";

    std::cout << "  OS       = " << TARGET_OS << "\n";
    std::cout << "  compiler = " << TARGET_COMPILER << "\n";
    std::cout << "  build date/time = " << __DATE__ << " " << __TIME__ << "\n";
    std::cout << "  __cplusplus     = " << __cplusplus
              << "   (201703 = C++17)\n";
#ifdef __GNUC__
    std::cout << "  GCC version macros: " << __GNUC__ << "."
              << __GNUC_MINOR__ << "." << __GNUC_PATCHLEVEL__ << "\n";
#endif
    std::cout << "  these are resolved by the PREPROCESSOR before compilation —\n";
    std::cout << "  the losing #if branches are deleted, never even parsed\n";


    // ════════════════════════════════════════════════════════
    // Problem 6 — namespace collision
    // ════════════════════════════════════════════════════════
    std::cout << "\n──── 6. namespace collision ────\n";

    NetworkLib::connect();
    DbLib::connect();
    std::cout << "  both are named `connect`; the namespace prefix disambiguates\n";
    std::cout << "  fully — `using namespace` either one and the collision returns\n";


    // ════════════════════════════════════════════════════════
    // Problem 8 — cerr vs clog
    // ════════════════════════════════════════════════════════
    std::cout << "\n──── 8. cerr vs clog ────\n";

    // By default BOTH cerr and clog target the SAME underlying stream
    // (stderr) — plain shell redirection can't separate them, because
    // the OS only sees one file descriptor (fd 2) for both. To send
    // clog somewhere else, rebind ITS streambuf in code.
    std::ofstream progressLog("progress.log");
    std::streambuf* originalClogBuf = std::clog.rdbuf(progressLog.rdbuf());

    int workUnits = 5;
    int simulatedFailureAt = 3;
    bool workFailed = false;

    for (int unit = 1; unit <= workUnits; ++unit) {
        std::clog << "progress: step " << unit << "/" << workUnits << " done\n";
        if (unit == simulatedFailureAt) {
            workFailed = true;
        }
    }

    std::clog.rdbuf(originalClogBuf);   // restore clog to normal stderr
    progressLog.close();

    if (workFailed) {
        // cerr is UNBUFFERED — this write hits the OS immediately, so
        // it is not lost even if the process aborts one line later.
        std::cerr << "error: step " << simulatedFailureAt << " reported a failure\n";
    }

    std::ifstream logCheck("progress.log");
    std::string firstLoggedLine;
    std::getline(logCheck, firstLoggedLine);
    std::cout << "  progress.log first line: \"" << firstLoggedLine << "\"\n";
    std::cout << "  clog is BUFFERED (fine for high-volume logs); cerr is\n";
    std::cout << "  UNBUFFERED (safe for the last message before a crash)\n";
    std::cout << "  verify from a shell: ./app 2> error.txt   then cat error.txt\n";
    std::cout << "  and cat progress.log — two separate files, one program\n";


    // ════════════════════════════════════════════════════════
    // Problem 9 — formatted table
    // ════════════════════════════════════════════════════════
    std::cout << "\n──── 9. iomanip table ────\n";

    std::vector<Employee> staff{
        {"Karan",   24, 58000.5},
        {"Drishya", 29, 124500.0},
        {"Rohit",   31, 76250.75}
    };

    std::cout << "  "
              << std::left  << std::setw(10) << "Name"
              << std::right << std::setw(6)  << "Age"
              << std::right << std::setw(14) << "Salary" << "\n";
    std::cout << "  " << std::string(30, '-') << "\n";

    for (const auto& e : staff) {
        std::cout << "  "
                  << std::left  << std::setw(10) << e.name
                  << std::right << std::setw(6)  << e.age
                  << std::right << std::setw(14) << std::fixed << std::setprecision(2)
                  << e.salary << "\n";
    }
    std::cout << "  left-align for text, right-align for numbers — matches how\n";
    std::cout << "  people actually scan a column of numbers (by their last digit)\n";


    // ════════════════════════════════════════════════════════
    // Problem 10 — hand-rolled CSV split
    // ════════════════════════════════════════════════════════
    std::cout << "\n──── 10. CSV split ────\n";

    std::string csvLine = "Karan,24,AI Engineer,Pune";
    std::vector<std::string> fields = splitCsv(csvLine);

    std::cout << "  input: " << csvLine << "\n";
    for (std::size_t i = 0; i < fields.size(); ++i) {
        std::cout << "  field[" << i << "] = \"" << fields[i] << "\"\n";
    }

    std::string trailingComma = "a,b,";
    std::vector<std::string> trailingFields = splitCsv(trailingComma);
    std::cout << "  \"a,b,\" -> " << trailingFields.size()
              << " fields (trailing comma leaves a final empty field)\n";


    // ════════════════════════════════════════════════════════
    // Problem 11 — stream state machine: read ints, recover from bad input
    // ════════════════════════════════════════════════════════
    std::cout << "\n──── 11. stream state machine ────\n";

    // Simulated stdin: two valid ints, one bad token, one more valid int.
    std::istringstream inputStream("10 20 notAnInt 30");

    int sum = 0;
    int count = 0;
    int recoveries = 0;

    while (true) {
        int n = 0;
        if (inputStream >> n) {
            sum += n;
            ++count;
        } else if (inputStream.eof()) {
            break;                              // clean end of input
        } else {
            // failbit set, but NOT eof -> a bad token, not the end.
            inputStream.clear();                // reset the error flags
            std::string garbage;
            inputStream >> garbage;             // consume the bad token
            ++recoveries;
            std::cout << "  recovered from bad token: \"" << garbage << "\"\n";
        }
    }

    std::cout << "  sum=" << sum << " count=" << count
              << " recoveries=" << recoveries << "\n";
    std::cout << "  operator>> sets failbit (not badbit) on a type mismatch —\n";
    std::cout << "  clear() resets the stream, but the bad token is still\n";
    std::cout << "  sitting unread until you consume it yourself\n";


    // ════════════════════════════════════════════════════════
    // Problem 12 — the classic >> / getline bug
    // ════════════════════════════════════════════════════════
    std::cout << "\n──── 12. >> / getline bug ────\n";

    // BROKEN version: cin >> age leaves the trailing '\n' in the
    // buffer; the very next getline reads that leftover '\n' as an
    // EMPTY line instead of the name the user actually typed.
    {
        std::istringstream brokenInput("23\nKaran\n");
        int age = 0;
        std::string name;

        brokenInput >> age;                 // reads "23", leaves "\nKaran\n"
        std::getline(brokenInput, name);    // reads up to the NEXT '\n' -> ""

        std::cout << "  broken: age=" << age << " name=\"" << name
                  << "\"   <- empty! getline ate the leftover newline\n";
    }

    // FIX 1: explicitly discard everything up to and including the
    // next newline before calling getline.
    {
        std::istringstream fixedInput("23\nKaran\n");
        int age = 0;
        std::string name;

        fixedInput >> age;
        fixedInput.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(fixedInput, name);

        std::cout << "  fixed (ignore): age=" << age << " name=\"" << name << "\"\n";
    }

    // FIX 2: read EVERYTHING as lines and parse manually — avoids
    // mixing >> and getline on the same stream at all.
    {
        std::istringstream fixedInput2("23\nKaran\n");
        std::string ageLine, name;

        std::getline(fixedInput2, ageLine);
        int age = std::stoi(ageLine);
        std::getline(fixedInput2, name);

        std::cout << "  fixed (all getline): age=" << age << " name=\"" << name << "\"\n";
    }

    std::cout << "  rule: never mix >> and getline on the same stream without\n";
    std::cout << "  either ignore()-ing the newline or committing to one style\n";


    std::cout << "\n──── done ────\n";

    return 0;
}


// ════════════════════════════════════════════════════════════
// SHELL / MULTI-FILE DRILLS — cannot run inside one .cpp
// ════════════════════════════════════════════════════════════
//
// [1] Preprocessor peek
//     // small.cpp
//     #include <iostream>
//     int main() { std::cout << "hi\n"; }
//
//     g++ -std=c++17 -E small.cpp | head -50
//     # look for a line marker like:
//     #   # 1 "/usr/include/c++/13/iostream" 1 3
//     # that is the preprocessor recording where <iostream>'s content
//     # was pasted in — everything after it, until the matching pop,
//     # IS the header's expanded content.
//
// [5] #pragma once everywhere
//     // before (classic guard)
//     #ifndef MATH_UTILS_H
//     #define MATH_UTILS_H
//     ...
//     #endif
//
//     // after
//     #pragma once
//     ...
//
//     # convert 3 of your own headers this way, then build the SAME
//     # project both orders (swap #include order in main.cpp) to
//     # confirm neither order breaks:
//     g++ -std=c++17 main.cpp a.cpp b.cpp -o app1
//     # edit main.cpp: swap the two #include lines, then:
//     g++ -std=c++17 main.cpp a.cpp b.cpp -o app2
//     diff <(./app1) <(./app2)   # should be identical
//
// [7] Anonymous namespace — internal linkage across TUs
//     // helper.cpp
//     namespace {
//         int secretHelper(int x) { return x * 2; }
//     }
//     int useHelper(int x) { return secretHelper(x); }   // fine, same TU
//
//     // main.cpp
//     int secretHelper(int x);   // declared, hoping to reuse it
//     int main() {
//         return secretHelper(5);
//     }
//
//     g++ -std=c++17 -c helper.cpp -o helper.o
//     g++ -std=c++17 -c main.cpp -o main.o
//     g++ helper.o main.o -o app
//     # /usr/bin/ld: main.o: in function `main':
//     # undefined reference to `secretHelper(int)'
//     #
//     # an anonymous namespace gives internal linkage — the symbol
//     # exists ONLY inside helper.o, invisible to the linker elsewhere.
//     # useHelper(int), declared normally, links fine from main.cpp.
//
// ──── build this file ────
// g++ -std=c++17 -Wall -Wextra -Wpedantic -Wshadow preprocessor_iostream.cpp -o app
// ./app