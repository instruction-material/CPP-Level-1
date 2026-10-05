#include "cat.h"
#include <iostream>

int main() {
    Cat someCat;
    std::cout << someCat.toString() << '\n';
    someCat.pet();
    Cat vimCat("vim", "shell", 1991, "black and white");
    std::cout << vimCat.toString() << '\n';
    vimCat.meow(5);
    // Preserve the original fictional signed-age example; encapsulation is not validation.
    vimCat.changeAge(-1);
    vimCat.changeBreed("zsh");
    std::cout << vimCat.toString() << '\n';
}
