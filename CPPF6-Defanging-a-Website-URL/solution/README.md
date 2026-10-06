# Defanging a Website Address

Compare mutating a string through a reference with constructing and returning
a new string. Transform each original period `.` into `[.]` exactly once.
For example, `www.example.com` becomes `www[.]example[.]com`.
This is a literal-text exercise; it does not validate a URL or provide a network
security guarantee. No address is visited.

## Required behavior

Preserve the original interfaces:

```cpp
void defang(std::string& address);
std::string defangValue(const std::string& address);
```

defang modifies its caller's string. defangValue reads through a const reference,
returns a new string by value and leaves the original unchanged. Parameter
passing and return-value passing are separate decisions. Preserve every byte
other than an original ASCII period, including UTF-8 bytes. Empty helper input
returns or remains empty. No periods means no change. Consecutive, first and
last periods each expand; dots inside existing brackets also expand. This
transformation is not idempotent: applying it again expands the inserted periods.
Skip inserted `[.]` text in the in-place traversal so the same call terminates.

The console driver reads one whitespace-separated token, at most 4,096 bytes.
Spaces/tabs/newlines separate tokens; remaining tokens are ignored in this
one-shot exercise. Missing input prints `Missing website address.` to stderr
and exits 1. A token over the authored 4,096-byte limit prints
`Website address is too long.` to stderr and exits 1. Neither failure prints
a transformed result. This size limit is an exercise bound, not a URL standard.
Helpers assume inputs within that domain, and an empty helper input is allowed.

On valid input, calculate the returned value first, mutate the same original
with defang, then print both results on separate lines. They must agree. The
input prompt precedes them. Test empty helper input, plain text, a single dot,
consecutive dots, dots at both ends, brackets, UTF-8 text and the size limit.
Verify caller preservation for defangValue and exact mutation for defang.

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
