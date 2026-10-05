#include <iostream>
#include <random>
#include <sstream>
#include <string>

// Seed this engine once when implementing main.
std::mt19937 generator;
std::string flipCoin();
int diceSum();
std::string drawCard();

// Supplied token-validation helper; the project functions remain learner work.
bool readInteger(int& value) {
	std::string token;
	if (!(std::cin >> token) || token.size() > 64) return false;
	std::istringstream input(token);
	char extra;
	return static_cast<bool>(input >> value) && !(input >> extra);
}

int main() {
	// TODO: trace the README fixtures, implement the functions and connect their calls.
	std::cerr << "Complete the starter functions and main workflow.\n";
	return 2;
}
