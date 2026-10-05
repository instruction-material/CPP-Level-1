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
    // TODO 1: Read bounded endpoints; print and sum the range with each loop kind.
    // TODO 2: Read the first count/values; compute a sum and average with for.
    // TODO 3: Read a separate second count/values; repeat the work with while.
    // TODO 4: Handle zero counts and rejected input using README.md's contract.
    // Replace this reminder and return success only after completing the program.
    std::cerr << "Complete the Number Games TODOs using README.md.\n";
    return 2;
}
