#include <iostream>
#include <random>

int main() {
	std::mt19937 generator(42);
	auto first = generator();
	generator.seed(42);
	std::cout << "Same seed, same engine value: " << first << ' ' << generator() << '\n';
	std::uniform_int_distribution<int> small(0, 50);
	std::cout << "Five values in the inclusive range 0 through 50:\n";
	for (int count = 0; count < 5; ++count) std::cout << small(generator) << '\n';
	std::uniform_int_distribution<int> large(100, 200);
	std::cout << "Five values in the inclusive range 100 through 200:\n";
	for (int count = 0; count < 5; ++count) std::cout << large(generator) << '\n';
	return 0;
}
