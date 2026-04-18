#include <iostream>

// Declare the functions so that main can use them
std::string flipCoin();
int diceSum();
std::string drawCard();

int main() {
  // Initialize the seed
  srand(time(0)); 

  std::cout << "\nI'm flipping a coin... it's " << flipCoin() << std::endl;
  std::cout << "I'm rolling two dice... their sum is " << diceSum() << std::endl;
  std::cout << "I'm drawing a card... it's a " << drawCard() << std::endl;
}

std::string flipCoin() {
  int flip = rand() % 2;
  if (flip == 0) {
    return "heads";
  } 
  return "tails";
}

int diceSum() {
  int dice1 = rand() % 6 + 1;
  int dice2 = rand() % 6 + 1;
  return dice1 + dice2;
}

std::string drawCard() {
  std::string card = "";
  // Generate a value between 1 and 4
  int suit = rand() % 4 + 1;
  // Generate a value between 1 and 13
  int value = rand() % 13 + 1;

  if (value == 1) {
    card += "Ace";
  } else if (value > 10) {
    if (value == 11) {
      card += "Jack";
    } else if (value == 12) {
      card += "Queen";
    } else if (value == 13) {
      card += "King";
    }
  } else {
    card += std::to_string(value);
  }
  
  card += " of ";

  if (suit == 1) {
    card += "Spades";
  } else if (suit == 2) {
    card += "Clubs";
  } else if (suit == 3) {
    card += "Hearts";
  } else if (suit == 4) {
    card += "Diamonds";
  }

  return card;
}