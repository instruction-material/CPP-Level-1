#include <iostream>
#include <string>

int main() {
  for (int i = 11; i <= 20; ++i) {
    std::cout << i << std::endl;
  }

  for (int i = 2; i <= 10; i += 2) {
    std::cout << i << std::endl;
  }

  for (int i = 10; i >= 0; --i) {
    std::cout << i << std::endl;
  }

  std::string word;
  std::cout << "Enter a word: ";
  std::cin >> word;

  for (std::string::size_type i = 0; i < word.length(); ++i) {
    std::cout << word[i] << std::endl;
  }

  for (std::string::size_type i = word.length(); i > 0; --i) {
    std::cout << word[i - 1] << std::endl;
  }

  int sum = 0;
  for (int i = 0; i <= 100; ++i) {
    sum += i;
  }
  std::cout << "Sum of first 100 = " << sum << std::endl;

  int factorial = 1;
  for (int i = 1; i <= 10; ++i) {
    factorial *= i;
  }
  std::cout << "Factorial of 10 = " << factorial << std::endl;

  int i = 0;
  for (; i < 10; ++i) {
    std::cout << i << std::endl;
  }

  int j = 0;
  for (;;) {
    if (j == 10) {
      break;
    }

    std::cout << j++ << std::endl;
  }

  // Examples of valid loop forms that intentionally do no work.
  for (int k = 0; k < 10; ++k) {
  }

  i = 0;
  for (; i < 10; ++i) {
  }

  // for (;;) {
  //   std::cout << "Hello World!" << std::endl;
  // }

  return 0;
}
