#include <iostream>
#include <random>
#include <sstream>
#include <string>

// Seed once in main. Each event advances this shared engine.
std::mt19937 generator;
std::string flipCoin();
int diceSum();
std::string drawCard();

bool readInteger(int& value) {
	std::string token;
	if (!(std::cin >> token) || token.size() > 64) return false;
	std::istringstream input(token);
	char extra;
	return static_cast<bool>(input >> value) && !(input >> extra);
}

int main() {
	int seed = 0;
	std::cout << "Enter a seed (0 through 2147483647): ";
	if (!readInteger(seed) || seed < 0) {
		std::cerr << "Invalid seed.\n";
		return 1;
	}
	generator.seed(static_cast<std::mt19937::result_type>(seed));
	std::cout << "\nCoin: " << flipCoin()
		<< "\nDice sum: " << diceSum()
		<< "\nCard: " << drawCard() << '\n';
	return 0;
}

std::string flipCoin() {
	std::uniform_int_distribution<int> coin(0, 1);
	return coin(generator) == 0 ? "heads" : "tails";
}
int diceSum() {
	std::uniform_int_distribution<int> die(1, 6);
	return die(generator) + die(generator);
}
std::string drawCard() {
	std::uniform_int_distribution<int> rank(1, 13);
	std::uniform_int_distribution<int> suit(1, 4);
	int value = rank(generator);
	int suitNumber = suit(generator);
	std::string card;
	if (value == 1) card = "Ace";
	else if (value == 11) card = "Jack";
	else if (value == 12) card = "Queen";
	else if (value == 13) card = "King";
	else card = std::to_string(value);
	card += " of ";
	if (suitNumber == 1) card += "Spades";
	else if (suitNumber == 2) card += "Clubs";
	else if (suitNumber == 3) card += "Hearts";
	else card += "Diamonds";
	return card;
}
