# Random-number reference

This complete lesson reference demonstrates `std::mt19937`, an explicit seed,
engine reset, and inclusive uniform distributions. It is a supplied reference,
not a learner starter project. The first line contains two equal engine values
after resetting seed 42. Five following values lie in 0 through 50 inclusive;
the final five lie in 100 through 200 inclusive. Each heading names that domain.
Repeat runs on one standard-library implementation reproduce the same output;
distribution mappings can differ between implementations. Do not use a modulo
expression while claiming an upper endpoint that the expression excludes.

Compile with `c++ -std=c++20 -Wall -Wextra -Wpedantic main.cpp -o reference`
and run `./reference`. Trace a distribution's lower and upper endpoints, then
compare resetting an engine with allowing the same engine to advance. Random
simulation here is for coursework, not cryptographic use or fairness proof.
