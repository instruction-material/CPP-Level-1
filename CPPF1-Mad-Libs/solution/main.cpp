#include <iostream>
#include <string>

int main() {
    std::string animal, adjective, verb, secondAdjective;
    std::cout << "Enter an animal: ";
    if (!(std::cin >> animal)) {
        std::cerr << "Input incomplete.\n";
        return 1;
    }
    std::cout << "Enter an adjective: ";
    if (!(std::cin >> adjective)) {
        std::cerr << "Input incomplete.\n";
        return 1;
    }
    std::cout << "Enter a verb: ";
    if (!(std::cin >> verb)) {
        std::cerr << "Input incomplete.\n";
        return 1;
    }
    std::cout << "Enter another adjective: ";
    if (!(std::cin >> secondAdjective)) {
        std::cerr << "Input incomplete.\n";
        return 1;
    }
    std::cout << "\nLong, long ago lived a(n) " << adjective << ' ' << animal
              << ". It would always " << verb << " and was very "
              << secondAdjective << ".\n";
    return 0;
}
