#include <iostream>
#include <random>
#include <sstream>
#include <string>

std::mt19937 generator;
bool readRange(int& minimum, int& maximum);
int chooseAnswer(int minimum, int maximum);
bool getGuess(int answer, int guessesLimit, int guessesUsed, int& guess);
int runGame();

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
	return runGame();
}

bool readRange(int& minimum, int& maximum) {
	std::cout << "Give me a minimum number to use: ";
	if (!readInteger(minimum)) return false;
	std::cout << "Give me a maximum number to use: ";
	return readInteger(maximum) && minimum <= maximum;
}
int chooseAnswer(int minimum, int maximum) {
	std::uniform_int_distribution<int> range(minimum, maximum);
	return range(generator);
}
bool getGuess(int answer, int guessesLimit, int guessesUsed, int& guess) {
	std::cout << "You have " << guessesLimit - guessesUsed
		<< (guessesLimit - guessesUsed == 1 ? " guess remaining. " : " guesses remaining. ")
		<< "What is your guess? ";
	if (!readInteger(guess)) {
		std::cerr << "Invalid guess.\n";
		return false;
	}
	if (guess < answer) std::cout << "Too low!\n";
	else if (guess > answer) std::cout << "Too high!\n";
	else std::cout << "Correct! You used " << guessesUsed + 1
		<< (guessesUsed == 0 ? " guess!\n" : " guesses!\n");
	return true;
}
int runGame() {
	constexpr int guessesLimit = 5;
	int minimum = 0, maximum = 0;
	std::cout << "\nWelcome! There are " << guessesLimit << " guesses.\n";
	if (!readRange(minimum, maximum)) {
		std::cerr << "Invalid range.\n";
		return 1;
	}
	int answer = chooseAnswer(minimum, maximum);
	std::cout << "Guess my number between " << minimum << " and " << maximum << ".\n";
	for (int used = 0; used < guessesLimit; ++used) {
		int guess = 0;
		if (!getGuess(answer, guessesLimit, used, guess)) return 1;
		if (guess == answer) return 0;
	}
	std::cout << "You're out of guesses. Better luck next time!\n";
	return 0;
}
