#include <iostream>
#include <string>

int main() {

    // A declaration is a statement.
    // The variable exists from this point until the end of its scope.

    int accountBalance = 5000;

    std::cout << "accountBalance=" << accountBalance << "\n";


    // An expression statement changes existing state.

    accountBalance += 1500;

    std::cout << "after deposit=" << accountBalance << "\n";


    // A block creates a new scope.
    // This is useful when a variable is needed only for a specific operation.

    {
        int withdrawal = 1000;

        accountBalance -= withdrawal;

        std::cout << "after withdrawal=" << accountBalance << "\n";
    }


    // withdrawal no longer exists here.
    // std::cout << withdrawal;


    // A variable declared inside an if block belongs to that block.

    if (accountBalance > 5000) {
        int bonus = 500;

        accountBalance += bonus;

        std::cout << "bonus applied=" << bonus << "\n";
    }


    // bonus is not available here.
    // std::cout << bonus;


    // The loop variable has scope limited to the for statement.

    for (int month = 1; month <= 3; ++month) {
        std::cout << "processing month " << month << "\n";
    }

    // month is not available here.
    // std::cout << month;


    // Nested scopes can access variables from their outer scopes.

    int orderTotal = 1200;

    {
        int tax = 120;

        {
            int shipping = 50;

            int finalTotal = orderTotal + tax + shipping;

            std::cout << "finalTotal=" << finalTotal << "\n";
        }
    }


    // An inner scope can hide a variable from an outer scope.
    // This is called shadowing.

    std::string status = "pending";

    {
        std::string status = "approved";

        std::cout << "inner status=" << status << "\n";
    }

    std::cout << "outer status=" << status << "\n";


    // A block can limit the lifetime of temporary data.
    // Once the block ends, the object is destroyed.

    {
        std::string transactionId = "TXN-10025";

        std::cout << "processing " << transactionId << "\n";
    }


    // transactionId no longer exists here.
    // std::cout << transactionId;


    // Statements can contain expressions.
    // The assignment below is an expression statement.

    int quantity = 4;
    double price = 249.50;

    double total = price * quantity;

    std::cout << "total=" << total << "\n";


    // A block can be used to isolate a calculation.

    double finalAmount;

    {
        double subtotal = 1000.0;
        double tax = subtotal * 0.18;

        finalAmount = subtotal + tax;
    }

    std::cout << "finalAmount=" << finalAmount << "\n";


    // return is also a statement.
    // Reaching the end of main implicitly returns 0.

    std::cout << "\n──── done ────\n";

    return 0;
}