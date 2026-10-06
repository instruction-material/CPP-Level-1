#include <iostream>
#include <string>

void defang(std::string& address) {
    // TODO: expand each original period once, skipping inserted replacements.
    static_cast<void>(address);
}
std::string defangValue(const std::string& address) {
    // TODO: return transformed text without changing the caller's string.
    static_cast<void>(address);
    return {};
}
int main() {
    // TODO: read and validate one token, compare both transformations.
    std::cerr << "Complete the defanging starter and its checks.\n";
    return 2;
}
