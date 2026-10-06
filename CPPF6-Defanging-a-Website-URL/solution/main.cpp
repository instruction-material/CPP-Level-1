#include <cstddef>
#include <iostream>
#include <string>

void defang(std::string& address) {
    std::size_t i = 0;
    while (i < address.size()) {
        if (address[i] == '.') {
            address.replace(i, 1, "[.]");
            i += 3; // Skip the inserted replacement; process original bytes once.
        } else {
            ++i;
        }
    }
}

std::string defangValue(const std::string& address) {
    std::string result;
    for (const char byte : address) {
        if (byte == '.') result += "[.]";
        else result += byte;
    }
    return result;
}

int main() {
    std::string address;
    std::cout << "\nEnter a website: ";
    if (!(std::cin >> address)) {
        std::cerr << "Missing website address.\n";
        return 1;
    }
    if (address.size() > 4096) {
        std::cerr << "Website address is too long.\n";
        return 1;
    }
    const std::string returnedValue = defangValue(address);
    defang(address);
    std::cout << returnedValue << '\n' << address << '\n';
    return 0;
}
