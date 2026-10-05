# Vector Practice

Build growable collections and read them through const-reference helper functions.
Create a vector containing the ten perfect squares for integers 0 through 9.
Print them in order, compare the first and last values, compute their sum and
count the letters in the ASCII words `vector`, `practice` and `lesson`.

## Required behavior

Keep these original helper signatures:

```cpp
bool firstLastMatch(const std::vector<int>& nums);
int sumVector(const std::vector<int>& nums);
int sumLetters(const std::vector<std::string>& words);
```

firstLastMatch returns false for an empty vector, true for one value or matching
ends, and false for different ends. Check empty before calling front or back.
sumVector returns the sum without changing the input; an empty sum is 0.
sumLetters returns the total ASCII string length without changing the words;
empty words contribute 0 and an empty collection totals 0. Spaces and punctuation
also occupy bytes. This exercise uses ASCII, where each character is one byte;
std::string length is not a Unicode character or grapheme count.

For this bounded exercise, number vectors contain at most 1,000 values, each
from -1,000,000 through 1,000,000. Word collections use ASCII and at most
1,000,000 total bytes. These preconditions keep each int accumulation within
range on the required toolchain with at least a 32-bit int. The helpers do not
validate arbitrary collections outside this domain. A generalized overflow-aware
or Unicode-aware API would require a separate stated contract.

Use push_back to construct the squares, then compare index-based and range-based
iteration. The supplied demonstration ends with these results:

```text
Perfect squares: 0 1 4 9 16 25 36 49 64 81
First and last match? 0
Sum of squares: 285
Total letters: 20
```

The reference retains a space after the last printed square. Test empty, one-item,
matching-end and different-end vectors, negative values, mixed signs, both numeric
bounds and empty words. Confirm that no helper changes its input. Present why
const-reference input avoids a collection copy while preventing modification.
Optional practice can return a new filtered vector or search result while keeping
the original unchanged; define its empty and no-match cases before implementing it.

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
