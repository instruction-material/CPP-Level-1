#include <iostream>

int main() {
  // PART 1: Find the sum of all numbers between num1 and num2 
  int num1, num2;
  std::cout << "\nEnter a number: ";
  std::cin >> num1;

  std::cout << "Enter a larger number: ";
  std::cin >> num2;

  // using for loops
  std::cout << "The sum of the numbers from " << num1 << " to " << num2 << " is... ";
  int sum = 0;
  for (int i = num1; i <= num2; i++) {
    sum += i;
  }
  std::cout << sum << std::endl;

  // using while loops
  std::cout << "The sum of the numbers from " << num1 << " to " << num2 << " is... ";
  sum = 0;
  int j = num1;
  while (j <= num2) {
    sum += j;
    j += 1;
  }
  std::cout << sum << std::endl;


  // PART 2: Use loops to find sum and average of the numbers inputted by user
  int numEntries, amt; 

  // using for loops
  std::cout << "How many numbers would you like to enter? ";
  std::cin >> numEntries;
  
  sum = 0;
  for (int k = 0; k < numEntries; k++) {
    std::cout << "Enter a number: ";
    std::cin >> amt;
    sum += amt;
  }

  double average = double(sum)/numEntries;
  std::cout << "The sum of the numbers you entered is: " << sum << std::endl;
  std::cout << "The average of the numbers you entered is: " << average << std::endl;


  // using while loops
  std::cout << "How many numbers would you like to enter? ";
  std::cin >> numEntries;

  sum = 0;
  int m = 0;
  while (m < numEntries) {
    std::cout << "Enter a number: ";
    std::cin >> amt;
    sum += amt;
    m++;
  }

  average = double(sum)/numEntries;
  std::cout << "The sum of the numbers you entered is: " << sum << std::endl;
  std::cout << "The average of the numbers you entered is: " << average << std::endl;  
}