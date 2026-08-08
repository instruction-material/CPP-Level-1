#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<int> scores = {88, 91, 76};
    scores.push_back(95);

    std::cout << "Scores stored in a vector:" << std::endl;
    for (size_t i = 0; i < scores.size(); ++i) {
        std::cout << "Index " << i << ": " << scores[i] << std::endl;
    }

    std::cout << "\nThe first score is " << scores.front() << std::endl;
    std::cout << "The last score is " << scores.back() << std::endl;
    std::cout << "There are " << scores.size() << " total scores." << std::endl;

    scores[1] += 4;
    std::cout << "\nAfter improving the second score:" << std::endl;
    for (const int score : scores) {
        std::cout << score << " ";
    }
    std::cout << std::endl;

    std::vector<std::string> labels;
    labels.push_back("warmup");
    labels.push_back("practice");
    labels.push_back("challenge");

    std::cout << "\nLesson labels:" << std::endl;
    for (const std::string& label : labels) {
        std::cout << "- " << label << std::endl;
    }

    return 0;
}
