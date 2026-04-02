#include <iostream>
#include <string>

bool done() {
  for (int x = 0; x < 100000; ++x) {
  }
  return true;
}

int main() {
  int i = 0;
  while (i <= 10) {
    std::cout << i << std::endl;
    ++i;
  }

  i = 0;
  while (i <= 10) {
    std::cout << i << std::endl;
    i += 2;
  }

  // while (!done()) {
  // }

  i = 10;
  while (i >= 0) {
    std::cout << i << std::endl;
    --i;
  }

  std::string word;
  std::cout << "Enter a word: ";
  std::cin >> word;

  std::string::size_type index = 0;
  while (index < word.length()) {
    std::cout << word[index] << std::endl;
    ++index;
  }

  index = word.length();
  while (index > 0) {
    std::cout << word[index - 1] << std::endl;
    --index;
  }

  int sum = 0;
  i = 0;
  while (i <= 100) {
    sum += i;
    ++i;
  }
  std::cout << "Sum of first 100 = " << sum << std::endl;

  int factorial = 1;
  i = 1;
  while (i <= 10) {
    factorial *= i;
    ++i;
  }
  std::cout << "Factorial of 10 = " << factorial << std::endl;
  return 0;
}
