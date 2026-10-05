# CPPF2 Project 2: Rock, Paper, Scissors

Use nested conditionals and Boolean expressions to choose the outcome of one
two-player round. This is a required original project in CPPF2. Randomness
and computer opponents belong to later extensions, not this completion contract.

## Workspace and native run

Implement `starter/main.cpp` first. Its starter reminder returns 2 until the program
is completed. Keep decisions inside `main` for this conditionals lesson. Review
the separate `solution` after a working attempt. The root entry forwards to that
reference for old build links; import `starter`, not the mixed root.

Inside the chosen folder:

```sh
c++ -std=c++20 -Wall -Wextra -Wpedantic main.cpp -o app
./app
```

The site IDE offers confirmed import, editing, saving, ZIP export and native
build instructions. It does not execute C++ in the browser.

## Required behavior

Read two whitespace-separated tokens, player 1 first. Each must be exactly one
of the lowercase strings `rock`, `paper`, or `scissors`. Spaces, LF and CRLF
separate tokens. No case conversion is required. Extra tokens after the two
choices are unused.

Prompt with `Player 1 (rock, paper, scissors): ` and
`Player 2 (rock, paper, scissors): `. If input ends before both tokens are read,
write `Input incomplete.` and a newline to the error stream and return 1. After
both reads, validate both choices before deciding a winner. If either is invalid,
write `Invalid choice.` and a newline and return 1. Invalid inputs never award a
win, including when both inputs are invalid.

On valid input, print a newline followed by exactly one result line, then return
0. Equal choices yield `Tie!`. Otherwise rock beats scissors, scissors beats
paper and paper beats rock; print `Player 1 wins!` or `Player 2 wins!`.

| Player 1 / Player 2 | rock | paper | scissors |
| --- | --- | --- | --- |
| rock | Tie! | Player 2 wins! | Player 1 wins! |
| paper | Player 1 wins! | Tie! | Player 2 wins! |
| scissors | Player 2 wins! | Player 1 wins! | Tie! |

## Walkthrough and verification

1. Read both tokens into separate strings and trace the stored values.
2. Check input success, then validate the allowed-choice domain. Explain why a
   capitalized choice such as `Rock` is rejected.
3. Handle equal choices, then use nested conditions for each remaining matchup.
4. Test all nine table cells, an invalid first choice, an invalid second choice,
   both invalid choices, empty input and input containing only one choice.
5. Present a branch trace for a win, a loss, a tie and an invalid round.

Self-check: swapping the two players swaps the winning player while ties
stay ties. Validation must happen before the winner logic.
