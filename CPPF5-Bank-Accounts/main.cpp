#include <iostream>
#include <vector>

int calcTotalBalance(const std::vector<int>& transactions);

int main() {
    int numTransactions = 0;

    std::cout
        << "\nHello! How many transactions have you made this past month? ";
    std::cin >> numTransactions;
    if (numTransactions < 0) {
        std::cout << "Please enter a non-negative number of transactions."
                  << std::endl;
        return 1;
    }

    std::vector<int> amounts(static_cast<size_t>(numTransactions));

    std::cout << "Thank you! Please enter the amount for each transaction "
                 "made. Please make sure your withdrawals are negative: "
              << std::endl;

    for (int i = 0; i < numTransactions; ++i) {
        int amt = 0;
        std::cout << "Enter a transaction amount: ";
        std::cin >> amt;
        amounts[static_cast<size_t>(i)] = amt;
    }

    std::cout << "You have a balance of $" << calcTotalBalance(amounts)
              << " in your account at this time. Thank you!" << std::endl;
    return 0;
}

int calcTotalBalance(const std::vector<int>& transactions) {
    int sum = 0;
    for (const int transaction : transactions) {
        sum += transaction;
    }
    return sum;
}
