# Number Guesser

Create a function-decomposed game that selects a random integer in a range
chosen by the player. Give higher/lower feedback and allow at most five guesses.

## Required behavior

1. Read a seed from 0 through 2147483647 and seed one `std::mt19937` engine.
2. `readRange` reads the inclusive minimum and maximum. Accept signed 32-bit
   integer endpoints, including negative or equal values; require minimum
   to be no greater than maximum. Reject a reversed range before random selection.
3. `chooseAnswer(minimum, maximum)` uses an inclusive uniform integer distribution.
   Avoid computing `maximum - minimum + 1` in signed integer arithmetic.
4. `getGuess` reads a complete integer token before comparing it, prints
   `Too low!`, `Too high!` or a correct message, and reports whether input succeeded.
5. `runGame` counts successful integer guesses and ends immediately on a correct
   guess or after the fifth incorrect guess. An integer outside the selected
   range still receives feedback and counts as a guess.

Whitespace, LF and CRLF all separate tokens. Missing, malformed, fractional or
overflowing seed/range/guess input aborts with exit status 1 and `Invalid seed.`,
`Invalid range.` or `Invalid guess.` on stderr. No feedback is awarded to a
malformed guess, and cancellation must not claim that all five guesses were used.
A completed win or loss exits with status 0. The chosen answer remains hidden.

For input `42 5 5 4 6 5`, the feedback is too low, too high, then correct after
three guesses. For `42 5 5 5`, the game ends after one guess. Five copies of 4
after `42 5 5` exhaust the limit. Test each of these and a reversed `2 1` range.

Use declarations before `main` and definitions afterward. Trace the first guess
before checking any ending condition. A supplied shared engine and integer-input
helper keep the focus on decomposition; reference parameters are taught later.
The same seed/call order is repeatable on one standard-library implementation;
distribution mappings may differ between implementations.

Demonstrate the game and explain each function's job. An optional later extension
can offer another round and an explicit quit command; it is outside the required
five-guess reference contract.

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
with the reference. Resolve compiler errors before running the
program. Instructor walkthroughs can pause at the same trace, function and test
checkpoints; the brief also contains the information needed for independent work.
