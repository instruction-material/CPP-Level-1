# Probability Events and Random

Write `flipCoin()`, `diceSum()` and `drawCard()` functions, call them from `main`
and use their return values to display one round of simulated events.

## Required behavior

- `flipCoin()` returns exactly `heads` or `tails`, using two equally likely choices.
- `diceSum()` rolls two independent six-sided dice and returns their sum, 2
  through 12. Do not draw a uniformly distributed sum: sums such as 7 have
  more combinations than 2 or 12.
- `drawCard()` chooses one rank and one suit independently. Ranks are Ace,
  2 through 10, Jack, Queen and King. Suits are Spades, Clubs, Hearts and
  Diamonds. Return text such as `10 of Diamonds` or `King of Spades`.

Use one `std::mt19937` engine, seed it once in `main`, and advance it for each
event. A shared engine is supplied for this function exercise; passing engines
by reference is introduced later in the course. Use
`std::uniform_int_distribution<int>` with inclusive bounds for each draw.

Read one integer seed from 0 through 2147483647. Reject missing, malformed,
negative, fractional or overflowing input with exit status 1 and `Invalid seed.`
on stderr, without printing events. Print `Coin:`, `Dice sum:` and `Card:` lines
after the seed prompt for a valid round. Input `42` is a useful repeatability
check. Repeating a seed and call order on the same standard-library implementation
repeats the result. Distribution mappings can differ between implementations;
do not promise a particular seed's card across every compiler/library.

Check all returned domains and explain the two independent die rolls. Show a
short demonstration of the three functions and explain their parameters,
return types and possible outcomes. Randomness tests establish observed domains
and repeatability, not cryptographic security or statistical fairness proof.

## Starter, reference and native workflow

Open only the `starter` folder in the site IDE, confirm the import, then inspect
the supplied function declarations and requirements. The starter compiles but
prints a reminder to stderr and exits with status 2 until the learner implements
the program. It supplies no calculated or game result. Write one function at a
time, test a normal case and a boundary, then connect the calls in `main`.
The separate `solution` folder is a complete reference for comparison after an
attempt. Each folder includes this same brief. The legacy root `main.cpp`
forwards to the reference and is not a learner starter.

The site IDE imports, edits, saves and exports C++ files. Download/unzip the
project and run it with a native C++20 compiler:

```sh
c++ -std=c++20 -Wall -Wextra -Wpedantic main.cpp -o project
./project
```

Select just one project folder at a time. Save and export edits before comparing
with the reference. A compiler error should be resolved before running the
program. Instructor walkthroughs can pause at the same trace, function and test
checkpoints; the brief also contains the information needed for independent work.
