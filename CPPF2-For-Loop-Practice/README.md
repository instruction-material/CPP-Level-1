# For-loop forms: supplied reference

This complete CPPF2 demonstration is reference material, not incomplete project
code. Predict initialization, stopping condition and update for one loop at a
time, run it, then apply the same reasoning to the required Number Games project.

```sh
c++ -std=c++20 -Wall -Wextra -Wpedantic main.cpp -o app
./app
```

The program prints 11–20, even values 2–10, and 10 down through 0. Enter one
ASCII word at `Enter a word: `; the program prints its characters on separate
lines first forward and then backward. Spaces end the word. If input ends at
that prompt, the empty string produces no character lines and the remaining
constant examples still run.

It then prints `Sum of first 100 = 5050`, `Factorial of 10 = 3628800`, and
0–9 twice to illustrate two additional valid loop forms. The last two empty-body
loops intentionally produce no output. These forms are comparison examples,
not extra projects. For input `cat`, the character section is `c`, `a`, `t`,
`t`, `a`, `c`, one character per line. A one-character word prints twice.

The ASCII word contract makes byte indexing visible. New project input
validation is specified separately in the Number Games brief. No TODOs or
reference comparison step is required for this supplied program.
