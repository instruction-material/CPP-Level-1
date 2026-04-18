#include <iostream>

// Function that gets a range of numbers from the user, and then returns a randomly generated number
int chooseAnswer() {
  // Ask the user for the min and max values they want to pick from:
  int minVal;
  int maxVal;

  std::cout << "\nGive me a minimum number to use: ";
  std::cin >> minVal;
  std::cout << "Give me a maximum number to use: ";
  std::cin >> maxVal;

  std::cout << "\nGreat! Now, guess my number between " << minVal << " and " << maxVal << std::endl;

  return rand() % (maxVal - minVal + 1) + minVal;
}

// Gets a guess from the user and prints out some feedback
int getGuess(int answer, int guessesLimit, int guessesUsed) {
  // Get the guess from the user
  int guess;
  std::cout << "You have " << guessesLimit - guessesUsed << " guesses remaining. What is your guess? ";
  std::cin >> guess;

  // Prints out some feedback for the user
  if (guess == answer) {
    std::cout << "Wow! Good work! That was the number! You used " << guessesUsed + 1 << " guesses!" << std::endl;
  } else if (guess < answer) {
    std::cout << "Too low!" << std::endl;
  } else if (guess > answer) {
    std::cout << "Too high!" << std::endl;
  }
  
  return guess;
}

// Run the main game loop
void runGame() {
  // Introduce the user to the program
  int guessesLimit = 5;
  std::cout << "\nWelcome! In this program, you'll have " << guessesLimit << " guesses to guess the number I'm thinking of in the range that you provide. Let's get started! " << std::endl;

  // Get the answer from the user
  int answer = chooseAnswer();

  // Keep track of the user's guess
  int guess;

  // Guess loop – will automatically exit if guess is correct or the guess limit is reached
  int guessesUsed = 0;
  while (guessesUsed < guessesLimit && guess != answer) {
    guess = getGuess(answer, guessesLimit, guessesUsed);
    guessesUsed++;
  }

  // Print out some ending feedback for the user
  if (guess != answer) {
    std::cout << "You're out of guesses. Better luck next time!" << std::endl;
  }
}

int main() {
  // Initialize the seed
  srand(time(0));
  runGame();

  /** BONUS: while the user doesn't enter in a quit sequence, keep on looping
  
  std::string input = "";
  do {
    runGame();
    std::cout << "\nHello! You can keep on running this program with any input, or type !quit to exit. ";
    std::cin >> input;
  } while (input != "!quit");
  */
}