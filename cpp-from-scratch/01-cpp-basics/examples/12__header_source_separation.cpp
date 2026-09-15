#include <iostream>
#include <string>
#include <sstream>
#include <vector>

// ──── what header/source separation means ────
// .h  / .hpp -> declarations: prototypes, class/struct defs, templates,
//               inline functions, inline/constexpr variables.
// .cpp/ .cc  -> definitions: function bodies, non-inline members, file statics.
//
// Why split:
//   - compilation speed : edit one .cpp, only that .cpp recompiles
//   - sharing           : many .cpp files include the same header
//   - encapsulation     : header exposes interface, source hides impl
//
// This single file simulates that layout so it stays runnable.
// Each block is labelled with the file it would normally live in.


// ════════════════════════════════════════════════════════════
// FILE: greet_utils.h
// ════════════════════════════════════════════════════════════
// #pragma once
// #include <string>
//
// Declarations only. No bodies here.

std::string greet(const std::string& name);
std::string farewell(const std::string& name);
int wordCount(const std::string& sentence);


// ════════════════════════════════════════════════════════════
// FILE: greet_utils.cpp
// ════════════════════════════════════════════════════════════
// #include "greet_utils.h"
//
// Definitions live here. Editing a body recompiles only this file.

std::string greet(const std::string& name) {
    return "Namaste, " + name + "!";
}

std::string farewell(const std::string& name) {
    return "Alvida, " + name + ".";
}

int wordCount(const std::string& sentence) {
    std::istringstream stream(sentence);
    std::string word;
    int count = 0;
    while (stream >> word) {
        ++count;
    }
    return count;
}


// ════════════════════════════════════════════════════════════
// FILE: common.h  ──  include guards
// ════════════════════════════════════════════════════════════
// Without a guard, including this header twice into one .cpp gives:
//   error: redefinition of 'struct Student'
//
// Modern form:
//     #pragma once
//
// Portable form:
//     #ifndef COMMON_H
//     #define COMMON_H
//     ... contents ...
//     #endif // COMMON_H

struct Student {
    std::string name;
    int rollNumber;
};


// ════════════════════════════════════════════════════════════
// FILE: score_utils.h  ──  inline function definitions
// ════════════════════════════════════════════════════════════
// A NON-inline body in a header, included by two .cpp files, gives a
// LINKER error: multiple definition of 'totalScore(int, int, int)'.
// 'inline' tells the linker "one definition rule is satisfied, merge them".

inline int totalScore(int a, int b, int c) {
    return a + b + c;
}

inline double average(int total, int subjects) {
    return static_cast<double>(total) / subjects;
}

inline std::string grade(double avg) {
    if (avg >= 90.0) return "A";
    if (avg >= 75.0) return "B";
    if (avg >= 60.0) return "C";
    return "D";
}


// ════════════════════════════════════════════════════════════
// FILE: config.h  ──  inline variables (C++17)
// ════════════════════════════════════════════════════════════
// Before C++17 a header could only DECLARE a global (extern) and one
// .cpp had to DEFINE it. C++17 'inline' gives every translation unit
// the SAME single object, defined in the header.

inline constexpr int      MAX_STUDENTS = 60;
inline constexpr double   PASS_MARK    = 33.0;
inline const std::string  APP_NAME     = "campus-tracker";


// ════════════════════════════════════════════════════════════
// FILE: report.h  ──  templates must be in the header
// ════════════════════════════════════════════════════════════
// A template is not code until instantiated, so its definition must be
// visible wherever it is used. Put it in the header, not the .cpp.

template <typename T>
void printPair(const std::string& label, T value) {
    std::cout << label << " = " << value << "\n";
}


// ════════════════════════════════════════════════════════════
// FILE: registry.h  ──  forward declaration
// ════════════════════════════════════════════════════════════
// Only a reference/pointer is needed, so declare the type instead of
// including its full header. Cuts compile-time coupling.

struct Course;                       // forward declaration
void enrollIn(const Course& course); // fine: reference only


// ════════════════════════════════════════════════════════════
// FILE: registry.cpp  ──  full definition needed here
// ════════════════════════════════════════════════════════════

struct Course {
    std::string title;
    int credits;
};

void enrollIn(const Course& course) {
    std::cout << "enrolled in " << course.title
              << " (" << course.credits << " credits)\n";
}


// ════════════════════════════════════════════════════════════
// FILE: counters.cpp  ──  internal linkage
// ════════════════════════════════════════════════════════════
// 'static' at file scope = private to this .cpp. Another .cpp can have
// its own 'seatsTaken' with no clash. An anonymous namespace does the same
// and is the preferred modern form.

static int seatsTaken = 0;

namespace {
    int helperCalls = 0;
}

int takeSeat() {
    ++helperCalls;
    return ++seatsTaken;
}


// ════════════════════════════════════════════════════════════
// FILE: stats.h / stats.cpp  ──  extern variable (pre-C++17 pattern)
// ════════════════════════════════════════════════════════════
// stats.h :  extern int totalEnrollments;   // declaration
// stats.cpp:        int totalEnrollments = 0; // one definition

extern int totalEnrollments;   // declaration
int totalEnrollments = 0;      // definition (would be in stats.cpp)


// ════════════════════════════════════════════════════════════
// FILE: enroll.cpp  ──  consumer of the headers above
// ════════════════════════════════════════════════════════════

void enroll(const std::string& name, int currentCount) {
    if (currentCount >= MAX_STUDENTS) {
        std::cout << "[" << APP_NAME << "] seats full, rejected " << name << "\n";
        return;
    }
    ++totalEnrollments;
    std::cout << "[" << APP_NAME << "] enrolled " << name
              << " (seat " << takeSeat() << ")\n";
}


// ════════════════════════════════════════════════════════════
// FILE: main.cpp
// ════════════════════════════════════════════════════════════

int main() {

    // ──── basic split: declaration in .h, body in .cpp ────
    std::cout << "──── basic split ────\n";

    std::string karan = "Karan";
    std::string tanvi = "Tanvi";

    std::cout << greet(karan) << "\n";
    std::cout << greet(tanvi) << "\n";
    std::cout << farewell(karan) << "\n";

    std::string sentence = "Rohit is learning header and source separation";
    std::cout << "wordCount=" << wordCount(sentence) << "\n";


    // ──── include guards ────
    std::cout << "\n──── include guards ────\n";

    Student drishya{"Drishya", 21};
    Student arjun{"Arjun", 22};

    std::cout << drishya.name << " roll=" << drishya.rollNumber << "\n";
    std::cout << arjun.name   << " roll=" << arjun.rollNumber   << "\n";
    std::cout << "without #pragma once a second include = redefinition error\n";


    // ──── inline functions in a header ────
    std::cout << "\n──── inline functions ────\n";

    int total = totalScore(85, 90, 78);
    double avg = average(total, 3);

    std::cout << "Arjun total=" << total
              << " avg=" << avg
              << " grade=" << grade(avg) << "\n";

    total = totalScore(60, 55, 70);
    avg   = average(total, 3);

    std::cout << "Drishya total=" << total
              << " avg=" << avg
              << " grade=" << grade(avg) << "\n";


    // ──── inline variables (C++17) ────
    std::cout << "\n──── inline variables ────\n";

    std::cout << "app=" << APP_NAME << "\n";
    std::cout << "maxStudents=" << MAX_STUDENTS << "\n";
    std::cout << "passMark=" << PASS_MARK << "\n";


    // ──── templates belong in the header ────
    std::cout << "\n──── templates in header ────\n";

    printPair("credits", 4);
    printPair("cgpa", 8.15);
    printPair("topper", std::string("Tanvi"));


    // ──── forward declaration ────
    std::cout << "\n──── forward declaration ────\n";

    Course dsa{"Data Structures", 4};
    Course os{"Operating Systems", 3};

    enrollIn(dsa);
    enrollIn(os);


    // ──── internal linkage: static / anonymous namespace ────
    std::cout << "\n──── internal linkage ────\n";

    std::cout << "seat=" << takeSeat() << "\n";
    std::cout << "seat=" << takeSeat() << "\n";
    std::cout << "these counters are invisible to other .cpp files\n";


    // ──── extern variable across files ────
    std::cout << "\n──── extern variable ────\n";

    enroll("Vikram", 58);
    enroll("Sneha", 59);
    enroll("Neha", 60);

    std::cout << "totalEnrollments=" << totalEnrollments << "\n";


    // ──── rules summary ────
    std::cout << "\n──── rules summary ────\n";

    std::cout << "header: prototypes, types, templates, inline fn, inline/constexpr vars\n";
    std::cout << "source: non-inline bodies, file statics, extern definitions\n";
    std::cout << "never put 'using namespace std;' in a header\n";
    std::cout << "forward declare instead of including when only ref/ptr is needed\n";


    std::cout << "\n──── done ────\n";

    return 0;
}

// ──── build (real multi-file layout) ────
// g++ -std=c++17 -Wall -Wextra main.cpp greet_utils.cpp registry.cpp
//     counters.cpp stats.cpp enroll.cpp -o app
// ./app
//
// ──── build (this single file) ────
// g++ -std=c++17 -Wall -Wextra header_source_separation.cpp -o app
// ./app