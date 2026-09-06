#include <iostream>
#include <string>

// ──── namespaces ────────────────────────────────────────────
namespace billing {
    void printInvoice() { std::cout << "Invoice printed\n"; }
}

// ──── scope resolution :: ───────────────────────────────────
class Counter {
public:
    static int total;
};
int Counter::total = 0;

// ──── constexpr ─────────────────────────────────────────────
constexpr int square(int x) { return x * x; }

// ──── enums ──────────────────────────────────────────────────
enum Status { PENDING, APPROVED, REJECTED };
enum class Level { LOW, MEDIUM, HIGH };

// ──── structs ────────────────────────────────────────────────
struct Employee {
    std::string name;
    int id;
    double salary;
};

// ──── union ──────────────────────────────────────────────────
union DataValue {
    int i;
    float f;
    char c;
};

// ──── preprocessor macros ───────────────────────────────────
#define MAX_LIMIT 100
#define SQUARE(x) ((x) * (x))

#ifdef DEBUG_MODE
    #define LOG(msg) std::cout << "[DEBUG] " << msg << "\n"
#else
    #define LOG(msg)
#endif

int main() {

    // ──── program structure ─────────────────────────────────
    std::cout << "──── program structure ────\n";
    std::cout << "Program started\n";

    // ──── iostream: cin, cout, cerr ─────────────────────────
    std::cout << "\n──── iostream ────\n";
    int a = 10, b = 0;
    std::cout << "a=" << a << "\n";
    if (b == 0) std::cerr << "cerr: division by zero avoided\n";

    // ──── namespaces ────────────────────────────────────────
    std::cout << "\n──── namespaces ────\n";
    billing::printInvoice();

    // ──── variables & data types ────────────────────────────
    std::cout << "\n──── variables & types ────\n";
    int age = 25;
    float price = 99.5f;
    double distance = 1234.5678;
    char grade = 'A';
    bool isActive = true;
    unsigned int userCount = 4000000000;
    long long fileSize = 9999999999LL;
    std::cout << age << " " << price << " " << distance << " " << grade << " " << isActive << "\n";
    std::cout << userCount << " " << fileSize << "\n";

    // ──── operators ─────────────────────────────────────────
    std::cout << "\n──── operators ────\n";
    int x = 10, y = 3;
    std::cout << (x + y) << " " << (x - y) << " " << (x * y) << " " << (x / y) << " " << (x % y) << "\n";
    std::cout << (x == y) << " " << (x != y) << " " << (x < y) << " " << (x && y) << "\n";
    Counter::total = 10;
    std::cout << "Counter::total=" << Counter::total << "\n";

    // ──── comments ──────────────────────────────────────────
    std::cout << "\n──── comments ────\n";
    int total = 100; // running total
    /* discount applied
       only on weekends */
    std::cout << total << "\n";

    // ──── constants ─────────────────────────────────────────
    std::cout << "\n──── constants ────\n";
    const double PI = 3.14159;
    constexpr int result = square(5);
    const int MAX_USERS = 100;
    std::cout << PI << " " << result << " " << MAX_USERS << "\n";

    // ──── enums, structs, unions ────────────────────────────
    std::cout << "\n──── enums, structs, unions ────\n";
    Status orderStatus = APPROVED;
    Level riskLevel = Level::HIGH;
    std::cout << orderStatus << " " << static_cast<int>(riskLevel) << "\n";

    Employee emp1 = {"Arjun", 101, 55000.0};
    std::cout << emp1.name << " " << emp1.id << " " << emp1.salary << "\n";

    DataValue val;
    val.i = 65;
    std::cout << val.i << "\n";
    val.c = 'Z';
    std::cout << val.c << "\n";

    // ──── preprocessor macros ───────────────────────────────
    std::cout << "\n──── preprocessor macros ────\n";
    std::cout << MAX_LIMIT << " " << SQUARE(6) << "\n";
    LOG("This only prints if DEBUG_MODE is defined");

    std::cout << "\n──── done ────\n";
    return 0;
}