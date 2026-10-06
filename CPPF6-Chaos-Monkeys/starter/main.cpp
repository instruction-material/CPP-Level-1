#include <iostream>
#include <string>

void valueMonkey(std::string val) {
    // TODO: scramble a local copy and print it; preserve the caller.
    static_cast<void>(val);
}
void refMonkey(std::string& val) {
    // TODO: scramble caller-owned text with a fixed original-size bound.
    static_cast<void>(val);
}
void constRefMonkey(const std::string& val) {
    // TODO: observe and print without attempting to insert through const.
    static_cast<void>(val);
}
int main() {
    // TODO: seed once, predict and compare caller state after all three calls.
    std::cerr << "Complete the chaos-monkeys starter and its checks.\n";
    return 2;
}
