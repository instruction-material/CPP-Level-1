#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

// Supplied input helper: numeric fields occupy one complete line. Learner work
// focuses on strings, insertion and arithmetic; functions are studied in CPPF3.
bool readTextLine(std::string& text) {
    if (!std::getline(std::cin, text)) return false;
    if (!text.empty() && text.back() == '\r') text.pop_back();
    return !text.empty();
}

bool readNumberLine(double& value, double minimum, double maximum) {
    std::string line;
    if (!std::getline(std::cin, line)) return false;
    std::istringstream input(line);
    if (!(input >> value) || !std::isfinite(value)) return false;
    input >> std::ws;
    return input.eof() && value >= minimum && value <= maximum;
}

int main() {
    std::string name, sentence;
    double fahrenheit = 0.0, dollars = 0.0;
    std::cout << "Name: ";
    if (!readTextLine(name)) {
        std::cerr << "Invalid name.\n";
        return 1;
    }
    std::cout << "Sentence: ";
    if (!readTextLine(sentence)) {
        std::cerr << "Invalid sentence.\n";
        return 1;
    }
    std::cout << "Temperature in Fahrenheit [-100, 300]: ";
    if (!readNumberLine(fahrenheit, -100.0, 300.0)) {
        std::cerr << "Invalid temperature.\n";
        return 1;
    }
    std::cout << "Example US dollar amount [0, 1000000]: ";
    if (!readNumberLine(dollars, 0.0, 1000000.0)) {
        std::cerr << "Invalid amount.\n";
        return 1;
    }

    sentence.insert(0, "**achoo** ");
    const double celsius = (fahrenheit - 32.0) * (5.0 / 9.0);
    constexpr double exampleRate = 109.01;  // Fictional fixed exercise data.
    const double yen = dollars * exampleRate;
    std::cout << "\nHello, " << name << "!\n"
              << "Sneeze: " << sentence << '\n'
              << std::fixed << std::setprecision(2)
              << "Celsius: " << celsius << '\n'
              << "Example conversion at 109.01 JPY per USD: " << yen << " JPY\n";
    return 0;
}
