# While-loop forms: supplied reference

This complete CPPF2 demonstration is reference material rather than a starter
assignment. Identify a changing counter and a stopping condition before running
each loop. Use it beside the counted-loop reference and Number Games brief.

```sh
c++ -std=c++20 -Wall -Wextra -Wpedantic main.cpp -o app
./app
```

The program prints 0–10, even values 0–10, and 10 down through 0. At
`Enter a word: `, enter one ASCII word. It prints that word's characters one per
line forward, then backward. Whitespace ends the word. If input ends, the empty
word produces no character lines and the constant examples still finish.
Finally it prints `Sum of first 100 = 5050` and
`Factorial of 10 = 3628800`.

For `cat`, the character section is `c`, `a`, `t`, `t`, `a`, `c`, with one
character per line. The ASCII contract avoids confusing byte indexes with
Unicode character positions. Explain which update makes each loop terminate
and how starting above an ascending loop's bound would give zero iterations.
No learner TODOs are present in this reference.
