# CPPF1 Project 1: Mad Libs

Use four string variables and console input to build a short story. This preserves
the original project goal: collect words and combine them into readable text.
The required project belongs in CPPF1 after variables, strings and stream input.

## Workspace and native run

Start in `starter`, which contains an incomplete `main.cpp` and this brief. The
initial program prints a starter reminder and exits with status 2. Finish the TODOs
in `main`; a successful completed run returns 0. Open `solution` only after a
working attempt. The legacy root `main.cpp` forwards to the corrected reference
for old direct build links; importing the whole root is not a starter workflow.

With a C++20 compiler, run these commands inside either chosen folder:

```sh
c++ -std=c++20 -Wall -Wextra -Wpedantic main.cpp -o app
./app
```

The site IDE can import, edit, save and export the files. Its Build instructions
control describes native compilation; it does not execute C++ in the browser.

## Required behavior

Read four nonempty whitespace-separated tokens in this order: animal, adjective,
verb, second adjective. Prompt before each read with `Enter an animal: `,
`Enter an adjective: `, `Enter a verb: `, and `Enter another adjective: `.
Spaces and newlines both separate tokens; a multiword phrase becomes several
tokens, so use one word for each field. Further tokens after the fourth are unused.

Print a newline followed by this single story line, substituting the four values:

```text
Long, long ago lived a(n) ADJECTIVE ANIMAL. It would always VERB and was very SECOND_ADJECTIVE.
```

If input ends before all four tokens are read, write `Input incomplete.` and a
newline to the error stream, return 1, and print no partial story. The supplied
course readiness lesson explains checking an extraction with `if (!(std::cin >>
word))`; the full branching topic follows in CPPF2. Failed input ends this run,
so no stream recovery is needed inside this project.

## Fixtures and walkthrough

| Input tokens | Story |
| --- | --- |
| `fox curious jump brave` | `Long, long ago lived a(n) curious fox. It would always jump and was very brave.` |
| `owl quiet glide wise` | `Long, long ago lived a(n) quiet owl. It would always glide and was very wise.` |
| `fox curious` then end of input | Error, status 1, no story |

1. Declare one string for each story field and explain what it stores.
2. Add one prompt/read pair, compile, and confirm which token was captured.
3. Repeat for the other fields; check the failed-read path before formatting.
4. Build the story with insertion operators or string concatenation. Trace the
   adjective/animal order rather than relying on the input order.
5. Test both stories, newlines instead of spaces, empty input, and input ending
   after each of the first three tokens. Present one customized story.

Checkpoints work for individual study or an instructor-led walkthrough. Discuss
why a token read stops at whitespace and how a full-line input task would differ.
