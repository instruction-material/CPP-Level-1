#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

static_assert(std::numeric_limits<int>::max() >= 1000000000,
              "This exercise requires at least a 32-bit int.");

int calcTotalBalance(const std::vector<int>& transactions);

bool readInteger(int& value) {
    std::string token;
    if (!(std::cin >> token) || token.size() > 64) return false;
    std::istringstream input(token);
    char extra;
    return static_cast<bool>(input >> value) && !(input >> extra);
}

int main() {
    int numTransactions = 0;
    std::cout << "\nHello! How many transactions have you made this past month? ";
    if (!readInteger(numTransactions) || numTransactions < 0 || numTransactions > 1000) {
        std::cerr << "Invalid transaction count.\n";
        return 1;
    }

    std::vector<int> amounts(static_cast<std::size_t>(numTransactions));
    std::cout << "Thank you! Please enter the amount for each transaction made. "
                 "Please make sure your withdrawals are negative:\n";
    for (int i = 0; i < numTransactions; ++i) {
        int amount = 0;
        std::cout << "Enter a transaction amount: ";
        if (!readInteger(amount) || amount < -1000000 || amount > 1000000) {
            std::cerr << "Invalid transaction amount.\n";
            return 1;
        }
        amounts[static_cast<std::size_t>(i)] = amount;
    }
    std::cout << "You have a balance of $" << calcTotalBalance(amounts)
              << " in your account at this time. Thank you!\n";
    return 0;
}

// The caller supplies the bounded collection domain stated in README.md.
int calcTotalBalance(const std::vector<int>& transactions) {
    int sum = 0;
    for (const int transaction : transactions) sum += transaction;
    return sum;
}
