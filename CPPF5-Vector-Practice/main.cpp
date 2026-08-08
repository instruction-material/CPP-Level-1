#include <iostream>
#include <string>
#include <vector>

bool firstLastMatch(const std::vector<int>& nums) {
    if (nums.empty()) {
        return false;
    }
    return nums.front() == nums.back();
}

int sumVector(const std::vector<int>& nums) {
    int total = 0;
    for (const int num : nums) {
        total += num;
    }
    return total;
}

int sumLetters(const std::vector<std::string>& words) {
    int total = 0;
    for (const std::string& word : words) {
        total += static_cast<int>(word.size());
    }
    return total;
}

int main() {
    std::vector<int> perfectSquares;
    for (int i = 0; i < 10; ++i) {
        perfectSquares.push_back(i * i);
    }

    std::cout << "Perfect squares: ";
    for (const int square : perfectSquares) {
        std::cout << square << " ";
    }
    std::cout << std::endl;

    std::cout << "First and last match? " << firstLastMatch(perfectSquares)
              << std::endl;
    std::cout << "Sum of squares: " << sumVector(perfectSquares) << std::endl;

    const std::vector<std::string> words = {"vector", "practice", "lesson"};
    std::cout << "Total letters: " << sumLetters(words) << std::endl;

    return 0;
}
