#include <iostream>
#include <string>

int main() {
    std::string player1, player2;
    std::cout << "Player 1 (rock, paper, scissors): ";
    if (!(std::cin >> player1)) {
        std::cerr << "Input incomplete.\n";
        return 1;
    }
    std::cout << "Player 2 (rock, paper, scissors): ";
    if (!(std::cin >> player2)) {
        std::cerr << "Input incomplete.\n";
        return 1;
    }
    if ((player1 != "rock" && player1 != "paper" && player1 != "scissors") ||
        (player2 != "rock" && player2 != "paper" && player2 != "scissors")) {
        std::cerr << "Invalid choice.\n";
        return 1;
    }
    std::cout << '\n';
    if (player1 == player2) {
        std::cout << "Tie!\n";
    } else if (player1 == "rock") {
        if (player2 == "scissors") std::cout << "Player 1 wins!\n";
        else std::cout << "Player 2 wins!\n";
    } else if (player1 == "paper") {
        if (player2 == "rock") std::cout << "Player 1 wins!\n";
        else std::cout << "Player 2 wins!\n";
    } else {
        if (player2 == "paper") std::cout << "Player 1 wins!\n";
        else std::cout << "Player 2 wins!\n";
    }
    return 0;
}
