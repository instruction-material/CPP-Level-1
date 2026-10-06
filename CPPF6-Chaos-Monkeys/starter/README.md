# Chaos Monkeys

Required practice compares string copies, mutable references and const
references while the string grows. Insert one random lowercase ASCII letter
before each original byte. Snapshot the original size so the loop does not
keep chasing the growing string.

## Required behavior

Preserve valueMonkey(std::string), refMonkey(std::string&) and add the valid
observer constRefMonkey(const std::string&). Use ASCII exercise strings with
at most 4,096 bytes, including the empty string. These are authored bounds;
the helper functions assume them rather than validating arbitrary strings.

valueMonkey changes and prints its local copy, leaving the caller unchanged.
refMonkey changes and prints caller-owned text. For either mutation, output
size is exactly twice the original size: positions 0, 2, 4 and so on hold letters
from a through z, and positions 1, 3, 5 and so on retain the original bytes in
order. Empty input stays empty. Const-reference code cannot insert through its
read-only parameter; constRefMonkey prints the observed string without changing
it. Keep an attempted insertion only as a separate compile-failure experiment,
then restore the valid observer.

The supplied driver begins with `bananas`, calls the value helper, prints the
caller afterward, then calls the reference helper and prints that caller again.
Finally it calls the const observer. Predict which caller values change before
running. First make the loop terminate with a fixed letter, then use
std::rand() % 26 to choose lowercase letters. Seed once with std::srand before
the experiment. A fixed seed can repeat results within the same C++ library;
time-based seeds may repeat within one second, and different libraries may
produce different strings. This demonstration promises a letter domain and
mutation boundary, not uniform probabilities or cryptographic randomness.

Check empty, one-byte, repeated-letter, mixed-case and maximum-size ASCII inputs.
Verify original-byte order, doubled length and caller preservation as well as
the printed messages. Optional extra scrambling functions need their own size,
mutation and termination rules.

## Starter, reference and native workflow

Import only `starter` after confirming the site IDE import. Write a prediction
before each call, then complete one `TODO` and check it. The incomplete driver
prints a reminder to stderr and exits with status 2 without completed results.
Save/export the attempt before comparing with the separate `solution` reference.
Both packs contain this complete brief and preserve the original main.cpp name.
The root main.cpp forwards to the reference for older direct build links.

The site IDE imports, edits, saves and exports C++ files. Download and unzip
one pack, then compile it with a native C++20 compiler:

```sh
c++ -std=c++20 -Wall -Wextra -Wpedantic main.cpp -o project
./project
```

Resolve compiler errors before running. Root `make` selects only `solution`;
`make PART=starter` selects only the incomplete pack. Never combine the root
entry, starter and reference in one build. Explain the prediction, observed
result and any correction. The checkpoints support independent work or a
course-facilitator walkthrough.
