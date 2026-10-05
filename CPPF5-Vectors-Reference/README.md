# Vectors reference

This complete supplied lesson precedes Vector Practice; it is not a starter.
Predict the collection after each operation, then compare index-based and
range-based traversal. A vector stores ordered elements; size is its current
element count and push_back appends one element. An index is valid only when it
is less than size. front and back require a nonempty vector. Empty vectors are
valid, but they have no first or last element. Do not keep references to elements
across operations that can reallocate storage.

The driver starts with scores 88, 91 and 76, appends 95, then changes index 1
from 91 to 95. The vector's size remains 4. It prints these values:

```text
Scores stored in a vector:
Index 0: 88
Index 1: 91
Index 2: 76
Index 3: 95

The first score is 88
The last score is 95
There are 4 total scores.

After improving the second score:
88 95 76 95

Lesson labels:
- warmup
- practice
- challenge
```

The reference retains one trailing space after the final updated score.
Explain why the index-based loop uses < rather than <=, then predict the output
after changing one valid score. A const reference can let a helper observe the
collection without copying or mutating it. The required projects use that
boundary to compute summaries and handle empty collections deliberately.

Compile only this complete lesson's main.cpp with a native C++20 compiler:

```sh
c++ -std=c++20 -Wall -Wextra -Wpedantic main.cpp -o project
./project
```
