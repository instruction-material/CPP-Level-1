#include <iostream>

int main() {
  std::cout << "\nEnter \"rock\", \"paper\", or \"scissors\"!";

  std::string player1, player2;
  std::cout << "\nPlayer 1: ";
  std::cin >> player1;
  std::cout << "Player 2: ";
  std::cin >> player2;
  std::cout << "\n";

  if (player1 == "rock") {
    if (player2 == "rock") {
      std::cout << "Tie!\n";
    } else if (player2 == "paper") {
      std::cout << "Player 2 wins!\n";
    } else if (player2 == "scissors") {
      std::cout << "Player 1 wins!\n";
    } else {
      std::cout << "Player 2 did not pick rock, paper, or scissors! Player 1 wins!\n";
    }
  } else if (player1 == "paper") {
    if (player2 == "rock") {
      std::cout << "Player 1 wins!\n";
    } else if (player2 == "paper") {
      std::cout << "Tie!\n";
    } else if (player2 == "scissors") {
      std::cout << "Player 2 wins!\n";
    } else {
      std::cout << "Player 2 did not pick rock, paper, or scissors! Player 1 wins!\n";
    }
  } else if (player1 == "scissors") {
    if (player2 == "rock") {
      std::cout << "Player 2 wins!\n";
    } else if (player2 == "paper") {
      std::cout << "Player 1 wins!\n";
    } else if (player2 == "scissors") {
      std::cout << "Tie!\n";
    } else {
      std::cout << "Player 2 did not pick rock, paper, or scissors! Player 1 wins!\n";
    }
  } else {
    std::cout << "Player 1 did not pick rock, paper, or scissors! Player 2 wins!\n";
  }
}