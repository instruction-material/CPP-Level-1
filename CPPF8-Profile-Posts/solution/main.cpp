#include "profile.h"
#include <iostream>
#include <sstream>
#include <string>

enum class Screen { MainMenu, Quit };
enum class InputStatus { Value, Invalid, End };

InputStatus readInteger(const std::string& prompt, int& value) {
    std::cout << prompt;
    std::string line;
    if (!std::getline(std::cin, line)) {
        return InputStatus::End;
    }
    std::istringstream input(line);
    if (!(input >> value)) {
        std::cout << "Invalid integer. Operation cancelled.\n";
        return InputStatus::Invalid;
    }
    input >> std::ws;
    if (!input.eof()) {
        std::cout << "Invalid integer. Operation cancelled.\n";
        return InputStatus::Invalid;
    }
    return InputStatus::Value;
}

InputStatus readPostIndex(std::size_t& index) {
    int number = 0;
    const InputStatus status = readInteger("Post number (1-based): ", number);
    if (status != InputStatus::Value) {
        return status;
    }
    if (number < 1 || number > static_cast<int>(maxProfilePosts)) {
        std::cout << "Invalid post number. Operation cancelled.\n";
        return InputStatus::Invalid;
    }
    index = static_cast<std::size_t>(number - 1);
    return InputStatus::Value;
}

bool addPostFromInput(Profile& profile) {
    std::cout << "Fictional caption: ";
    std::string caption;
    if (!std::getline(std::cin, caption)) {
        return false;
    }
    if (caption.empty() || caption.size() > maxCaptionBytes) {
        std::cout << "Invalid caption. Operation cancelled.\n";
        return true;
    }
    int hearts = 0;
    const InputStatus status = readInteger("Initial hearts (0..1000000): ", hearts);
    if (status == InputStatus::End) {
        return false;
    }
    if (status == InputStatus::Value) {
        profile.addPost({caption, hearts});
    }
    return true;
}

bool handlePostCommand(int command, Profile& profile) {
    std::size_t index = 0;
    const InputStatus status = readPostIndex(index);
    if (status == InputStatus::End) {
        return false;
    }
    if (status == InputStatus::Invalid) {
        return true;
    }
    switch (command) {
    case 3:
        profile.printPost(index);
        break;
    case 4: {
        int change = 0;
        const InputStatus changeStatus = readInteger("Heart change (signed): ", change);
        if (changeStatus == InputStatus::End) {
            return false;
        }
        if (changeStatus == InputStatus::Value) {
            profile.addHearts(index, change);
        }
        break;
    }
    case 5:
        profile.removePost(index);
        break;
    default:
        break;
    }
    return true;
}

int main() {
    Profile profile;
    Screen screen = Screen::MainMenu;
    while (screen != Screen::Quit) {
        std::cout << "\n1 Add | 2 View all | 3 View one | 4 Update hearts | "
                     "5 Remove | 6 Total hearts | 0 Quit\n";
        int command = 0;
        const InputStatus status = readInteger("Command: ", command);
        if (status == InputStatus::End) {
            screen = Screen::Quit;
            continue;
        }
        if (status == InputStatus::Invalid) {
            continue;
        }
        bool keepRunning = true;
        switch (command) {
        case 0:
            screen = Screen::Quit;
            break;
        case 1:
            keepRunning = addPostFromInput(profile);
            break;
        case 2:
            profile.printPosts();
            break;
        case 3:
        case 4:
        case 5:
            keepRunning = handlePostCommand(command, profile);
            break;
        case 6:
            std::cout << "Total hearts: " << profile.sumHearts() << '\n';
            break;
        default:
            std::cout << "Invalid command.\n";
            break;
        }
        if (!keepRunning) {
            screen = Screen::Quit;
        }
    }
    std::cout << "Goodbye.\n";
    return 0;
}
