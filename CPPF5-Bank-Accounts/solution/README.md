# Bank Accounts

Model fictional integer-dollar transactions in a vector and calculate a balance.
Deposits are positive, withdrawals are negative and zero is a valid amount.
The account begins at 0. Use fabricated exercise values throughout.

## Required behavior

Read a transaction count from 0 through 1,000, then exactly that many amounts,
each from -1,000,000 through 1,000,000 inclusive. Whitespace separates complete
integer tokens, so spaces, tabs, LF and CRLF work. An optional leading + or - is
allowed; fractional amounts, trailing token text, missing tokens and out-of-range
values are invalid. Allocate the vector only after the count passes validation.
These are authored console-exercise limits, not real banking rules.

Preserve `int calcTotalBalance(const std::vector<int>& transactions)`. Return the
sum without changing the vector. Empty transactions return 0. The helper's
preconditions match the driver: at most 1,000 integer-dollar amounts in the stated
range. Their absolute total is at most 1,000,000,000, which fits the required
toolchain's at least 32-bit int. Arbitrary unbounded inputs need a separate
overflow policy. A deposit of 100, withdrawal of -25 and deposit of 10 total 85.

After all requested values are valid, print one balance line in this format:

```text
You have a balance of $85 in your account at this time. Thank you!
```

A valid count of 0 prints a balance of $0. A missing, malformed or out-of-range
count prints `Invalid transaction count.` to stderr and exits with status 1.
An invalid or missing requested amount prints `Invalid transaction amount.` to
stderr and exits with status 1. Neither failure prints a balance. Do not replace
failed extraction with an initialized zero. Tokens after the requested values
are outside this one-shot exercise and are ignored.

First implement and test the pure sum helper, then count validation, bounded
collection construction, amount validation and final reporting. Test zero,
positive-only and withdrawal-only data, mixed signs, cancellation to zero, both
amount limits, the count limit, missing fields and malformed count/amount tokens.
For each invalid run, verify exit status 1 and the absence of a balance line.
An optional running-balance extension can show the total after each valid
transaction; define whether an invalid later token cancels all results first.

## Starter, reference and native workflow

Import only `starter` after confirming the site IDE import. Implement one `TODO`
at a time and test it before continuing. The incomplete starter builds, prints
a reminder to stderr and exits with status 2; it supplies no completed results.
Save/export the attempt before comparing with the separate `solution` reference.
The root main.cpp forwards to the reference for older direct links. Both packs
include this complete brief and preserve the original main.cpp filename.

The site IDE imports, edits, saves and exports C++ files. Download and unzip the
chosen pack, then compile it with a native C++20 compiler:

```sh
c++ -std=c++20 -Wall -Wextra -Wpedantic main.cpp -o project
./project
```

Resolve compiler errors before running the program. At the root, `make` chooses
only `solution`; `make PART=starter` chooses only the incomplete pack. Never mix
the root entry with a nested pack or combine both packs in one build. Predict
each collection's contents and the returned result before running the checks.
The same checkpoints support independent work or a course-facilitator walkthrough.
