#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

void valueMonkey(std::string val) {
    const std::size_t startingSize = val.size();
    for (std::size_t i = 0; i < startingSize; ++i) {
        const char letter = static_cast<char>('a' + std::rand() % 26);
        val.insert(i * 2, 1, letter);
    }
    std::cout << "Oh no! The value monkeys changed our value to: " << val << '\n';
}

void refMonkey(std::string& val) {
    const std::size_t startingSize = val.size();
    for (std::size_t i = 0; i < startingSize; ++i) {
        const char letter = static_cast<char>('a' + std::rand() % 26);
        val.insert(i * 2, 1, letter);
    }
    std::cout << "Oh no! The ref monkeys changed our value to: " << val << '\n';
}

void constRefMonkey(const std::string& val) {
    // Inserting through this parameter is intentionally forbidden by const.
    std::cout << "The const-reference monkeys can only observe: " << val << '\n';
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    std::string secret = "bananas";
    std::cout << "\nMy secret started out as: " << secret << '\n';
    std::cout << "\nNow calling the value monkeys...\n";
    valueMonkey(secret);
    std::cout << "After calling the value monkeys, my value is: " << secret << '\n';
    std::cout << "\nNow calling the ref monkeys...\n";
    refMonkey(secret);
    std::cout << "After calling the ref monkeys, my value is: " << secret << '\n';
    std::cout << "\nNow calling the const-reference monkeys...\n";
    constRefMonkey(secret);
    return 0;
}
