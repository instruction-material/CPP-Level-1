#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

int add(int a, int b);
double average(int a, int b);
bool isEven(int a);
double smallest(double a, double b, double c);
int factorial(int a);
int exponent(int b, int p);

bool readInteger(int& value) {
	std::string token;
	if (!(std::cin >> token) || token.size() > 64) return false;
	std::istringstream input(token);
	char extra;
	return static_cast<bool>(input >> value) && !(input >> extra);
}

int main() {
	int first = 0, second = 0, number = 0, base = 0, power = 0;
	std::cout << "Enter two integers (-1000000 through 1000000): ";
	if (!readInteger(first) || !readInteger(second) ||
		first < -1000000 || first > 1000000 ||
		second < -1000000 || second > 1000000) {
		std::cerr << "Invalid pair.\n";
		return 1;
	}
	std::cout << "Enter a factorial number (1 through 12): ";
	if (!readInteger(number) || number < 1 || number > 12) {
		std::cerr << "Invalid factorial number.\n";
		return 1;
	}
	std::cout << "Enter a base (1 through 10) and power (0 through 9): ";
	if (!readInteger(base) || !readInteger(power) ||
		base < 1 || base > 10 || power < 0 || power > 9) {
		std::cerr << "Invalid base or power.\n";
		return 1;
	}
	std::cout << "\nSum = " << add(first, second)
		<< "\nAverage = " << std::fixed << std::setprecision(2) << average(first, second)
		<< "\nIs " << first << " even? " << std::boolalpha << isEven(first)
		<< "\nSmallest = " << std::setprecision(5) << smallest(3.14159, 2.71828, 1.61803)
		<< "\n" << number << "! = " << factorial(number)
		<< "\n" << base << "^" << power << " = " << exponent(base, power) << '\n';
	return 0;
}

int add(int a, int b) { return a + b; }
double average(int a, int b) { return (static_cast<double>(a) + b) / 2.0; }
bool isEven(int a) { return a % 2 == 0; }
double smallest(double a, double b, double c) {
	double result = a;
	if (b < result) result = b;
	if (c < result) result = c;
	return result;
}
int factorial(int a) {
	int result = 1;
	for (int factor = 1; factor <= a; ++factor) result *= factor;
	return result;
}
int exponent(int b, int p) {
	int result = 1;
	for (int count = 0; count < p; ++count) result *= b;
	return result;
}
