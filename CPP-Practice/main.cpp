#include <iostream>
#include <map>
#include <string>

// Write a C++ function that takes in a string and determines if it is a palindrome. Please do not generate additional strings in your algorithm. Please do not reference past work!

// Write a C++ function that finds the occurrences of each letter in a string. Think about what data structure we talked about to accomplish this!

// Instructions: Write a program to simulate a bank account. Initialize a 2D array that can store a set number of transactions, and for each transaction store the following five pieces of information: the transaction number, the date the transaction took place (in MMDDYYYY format), the account balance before the transaction, the amount of the transaction (positive if it was a deposit, negative if it was a withdrawal), and the ending balance. Ask the user to input information for each transaction, and use that information to fill the 2D array. Once the user has finished entering in the transaction details, print out the details for each transaction.

// Column 1 = transaction number
// Column 2 = month
// Column 3 = day
// Column 4 = year
// Column 5 = Balance before
// Column 6 = How much money changed [negative for withdrawl, positive for deposit]
// Column 7 = Ending balance

bool isPalindromeButOptimized(const std::string& str) {
  if (str.empty()) {
    return true;
  }

  std::string::size_type pos1 = 0;
  std::string::size_type pos2 = str.size() - 1;

  while (pos1 < str.size() / 2 && pos1 != pos2) {
    if (str[pos1] != str[pos2]) {
      return false;
    }
    ++pos1;
    --pos2;
  }

  return true;
}

void newTransactionInput(int& month, int& day, int& year, int& modifier, int money,
                         int& beforeBalance, int& afterBalance) {
  std::cout << "What day is it? ";
  std::cin >> day;

  std::cout << "What month is it? (month number) ";
  std::cin >> month;

  std::cout << "What year is it? ";
  std::cin >> year;

  std::cout << "How much money are you withdrawing/depositting? (negative number for withdraw, positive for deposit) ";
  std::cin >> modifier;

  beforeBalance = money;
  afterBalance = money + modifier;
}

void printTransaction(const int* transactionRow) {
  std::cout << "Transaction number: " << transactionRow[0] << std::endl;
  std::cout << "Date: " << transactionRow[1] << "/" << transactionRow[2] << "/" << transactionRow[3] << std::endl;
  std::cout << "Balance before: " << transactionRow[4] << std::endl;
  std::cout << "Money desposited/withdrawn: " << transactionRow[5] << std::endl;
  std::cout << "Balance after: " << transactionRow[6] << std::endl;
}

void letterMap(const std::string& str) {
  std::map<char, int> frequency;
  for (const char letter : str) {
    ++frequency[letter];
  }

  for (const auto& entry : frequency) {
    std::cout << "Letter: " << entry.first << "\nFrequency: " << entry.second << "\n\n";
  }
}

int main() {
  const std::string str = "inanimate insanity invitational";
  // std::cout << std::boolalpha << isPalindromeButOptimized(str) << std::endl;
  // letterMap(str);

  int transactions[2][7];
  int money = 2763;
  int day = 0;
  int month = 0;
  int year = 0;
  int modifier = 0;
  int before_balance = 0;
  int after_balance = 0;
  int i = 0;

  std::cout << "Balance: " << money << std::endl;

  while (i < 2) {
    newTransactionInput(month, day, year, modifier, money, before_balance, after_balance);
    transactions[i][0] = i + 1;
    transactions[i][1] = month;
    transactions[i][2] = day;
    transactions[i][3] = year;
    transactions[i][4] = before_balance;
    transactions[i][5] = modifier;
    transactions[i][6] = after_balance;
    std::cout << "\n";
    money = after_balance;
    ++i;
  }

  printTransaction(transactions[0]);
  std::cout << "\n";
  printTransaction(transactions[1]);
}
