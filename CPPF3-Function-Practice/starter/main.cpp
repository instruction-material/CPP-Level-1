#include <iostream>
#include <random>
#include <sstream>
#include <string>

int add(int a, int b);
double average(int a, int b);
bool isEven(int a);
double smallest(double a, double b, double c);
int factorial(int a);
int exponent(int b, int p);

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
