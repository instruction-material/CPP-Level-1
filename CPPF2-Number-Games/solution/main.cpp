#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

// Supplied input helper: reject incomplete tokens such as "2x" or "2.5".
// The learner writes the for/while loops, sums and averages in main.
bool readInteger(int& value) {
    std::string token;
    if (!(std::cin >> token) || token.size() > 64) return false;
    std::istringstream input(token);
    if (!(input >> value)) return false;
    input >> std::ws;
    return input.eof();
}

int main() {
    int first = 0, last = 0;
    std::cout << "Range endpoints [-1000, 1000]: ";
    if (!readInteger(first) || !readInteger(last)) {
        std::cerr << "Invalid integer input.\n";
        return 1;
    }
    if (first < -1000 || first > 1000 || last < -1000 || last > 1000) {
        std::cerr << "Invalid range.\n";
        return 1;
    }

    long long rangeSum = 0;
    std::cout << "\nRange (for):";
    if (first > last) std::cout << " empty";
    for (int number = first; number <= last; ++number) {
        std::cout << ' ' << number;
        rangeSum += number;
    }
    std::cout << "\nRange sum (for): " << rangeSum << '\n';
    int number = first;
    rangeSum = 0;
    std::cout << "Range (while):";
    if (first > last) std::cout << " empty";
    while (number <= last) {
        std::cout << ' ' << number;
        rangeSum += number;
        ++number;
    }
    std::cout << "\nRange sum (while): " << rangeSum << '\n';

    int count = 0;
    std::cout << "Count for for-loop batch [0, 100]: ";
    if (!readInteger(count)) {
        std::cerr << "Invalid integer input.\n";
        return 1;
    }
    if (count < 0 || count > 100) {
        std::cerr << "Invalid count.\n";
        return 1;
    }
    long long sum = 0;
    for (int index = 0; index < count; ++index) {
        int value = 0;
        std::cout << "Value [-1000000, 1000000]: ";
        if (!readInteger(value)) {
            std::cerr << "Invalid integer input.\n";
            return 1;
        }
        if (value < -1000000 || value > 1000000) {
            std::cerr << "Invalid value.\n";
            return 1;
        }
        sum += value;
    }
    std::cout << "\nSum (for): " << sum << "\nAverage (for): ";
    if (count == 0) std::cout << "undefined\n";
    else std::cout << std::fixed << std::setprecision(2)
                   << static_cast<double>(sum) / count << '\n';

    std::cout << "Count for while-loop batch [0, 100]: ";
    if (!readInteger(count)) {
        std::cerr << "Invalid integer input.\n";
        return 1;
    }
    if (count < 0 || count > 100) {
        std::cerr << "Invalid count.\n";
        return 1;
    }
    sum = 0;
    int index = 0;
    while (index < count) {
        int value = 0;
        std::cout << "Value [-1000000, 1000000]: ";
        if (!readInteger(value)) {
            std::cerr << "Invalid integer input.\n";
            return 1;
        }
        if (value < -1000000 || value > 1000000) {
            std::cerr << "Invalid value.\n";
            return 1;
        }
        sum += value;
        ++index;
    }
    std::cout << "\nSum (while): " << sum << "\nAverage (while): ";
    if (count == 0) std::cout << "undefined\n";
    else std::cout << std::fixed << std::setprecision(2)
                   << static_cast<double>(sum) / count << '\n';
    return 0;
}
