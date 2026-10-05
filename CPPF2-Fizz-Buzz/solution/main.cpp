#include <iostream>

int main() {
    for (int number = 1; number <= 50; ++number) {
        if (number % 3 == 0 && number % 5 == 0) {
            std::cout << "FizzBuzz\n";
        } else if (number % 3 == 0) {
            std::cout << "Fizz\n";
        } else if (number % 5 == 0) {
            std::cout << "Buzz\n";
        } else {
            std::cout << number << '\n';
        }
    }
    return 0;
}
