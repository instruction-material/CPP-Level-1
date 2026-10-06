# Source pack review

## Reviewed on 2026-10-05

| Project | Learning goal | Verified behavior |
| --- | --- | --- |
| Mad Libs | Strings, token input, story construction | Word order, whitespace separators and incomplete-input cancellation |
| Chat Bot | Full-line strings, insertion and arithmetic | Short/Unicode text, LF/CRLF, complete numeric lines, bounds and fixed-data conversions |
| Number Games | For/while range printing, sums and means | Normal/reversed/one-value ranges, independent batches, zero counts, bounds and rejection phase boundaries |
| Rock/Paper/Scissors | Nested conditionals and validation | All nine pairs, invalid/missing input and no winner for invalid rounds |
| Fizz Buzz | Counted loop, remainder and branch ordering | All 50 outputs, including safe ordinary number printing |
| Function Practice | Declarations, parameters and returned math values | Precise averages, negative parity, distinct-double minima, safe factorial/power bounds and all-field cancellation |
| Probability Events and Random | Returned coin, two-die and card simulations | Outcome domains, all observed coin/sum/card outcomes, two independent dice, explicit seed and same-library repeatability |
| Number Guesser | Range/answer/guess/game decomposition | Initialized first guess, early wins, five valid guesses, higher/lower feedback, range/guess cancellation and full signed-endpoint domains |
| Person Class | Header/source split, constructors, private state and accessors | Every public method, defaults, height formatting, setters, copy independence, private-access rejection and equivalent member-initializer lesson |
| Cat Class | Constructors, member initialization and interacting methods | Authored defaults, signed-age updates, exact age-one pluralization bonus, breed independence, meow/eat/pet actions and copy independence |
| Vector Practice | Growable sequences and const-reference summaries | Empty/end comparisons, bounded signed sums, ASCII lengths, input preservation and supplied lesson output |
| Bank Accounts | Bounded transaction collection and summary function | Complete integer tokens, zero/negative amounts, both limits, count limits and cancellation before any claimed balance |
| Parameter Passing Tracing | Predictions, copies, aliases and const observation | Every helper, correct copy prediction, separate/aliased caller state and rejected const mutation |
| Defanging a Website Address | Mutable string reference versus returned value | Single-pass original-period expansion, empty/bracket/UTF-8 cases, preserved input and missing/overlength cancellation |
| Chaos Monkeys | Growing-string loop bounds and parameter passing | Doubled ASCII size, original-byte order, copy/reference/observer boundaries and seeded repetition |
| Matrix Addition | Required equal-dimension 2D-vector addition | Complete tokens, both dimension/cell limits, rectangular fixtures and cancellation before any claimed sum |
| Grid Statistics | Optional const-reference grid summaries | Empty/zero-column/wide/tall grids, bounded sums, negative/tied maxima, unchanged inputs and exact driver output |

Every listed pack has an intentionally incomplete starter, a separate reference,
a matching self-contained README and a warning-clean C++20 native build. Legacy
root entries forward to the corrected references. Native tests also exercise
sanitized references. References are not learner imports.

## Remaining audit scope

Compilation alone does not certify the remaining CPPF8 contracts or starter
roles. That source review remains open, as do later duplicate assignment links.
The unrelated
CPPF1 variable/vector transformation wrapper was moved byte-for-byte to the
inactive archive; it is not a beginner input/output assignment. Its duplicate
CPPF3 wrapper is also archived byte-for-byte because it introduces vector and
reference operations ahead of their modules without a functions-specific brief.
The first seven
modules' site links and briefs must point to the reviewed nested folders before
this source work establishes an end-to-end learner workflow. Source publication
alone does not prove application deployment.

## Fidelity

The first four modules' ten core project names and learning goals are preserved
from the original Juni C++ Level 1 catalog. Safety checks and explicit console fixtures are authored
clarifications. The sample exchange rate is fixed fictional exercise data. The
original Fizz Buzz optional custom-divisor bonus remains an extension; the
reference gate covers only the required fixed 3-and-5 version.

The original Function Practice archive remains unchanged; an active starter and
reference restore its missing catalog assignment. Input limits and explicit
zero-power behavior are authored safety clarifications. Its original factorial
range (1 through 12), positive-base goal, function names and distinct-double
minimum goal are retained. The number game's optional repeat/quit bonus remains
an extension outside the required reference gate. Original function project
source is retained in Git history. No fairness or cross-library random-output
claim follows from the observed-outcome tests.

CPPF4 retains the original Person public signatures and archived files.
The active reference now defines previously missing accessor methods. Cat
default breed is corrected to the authored `unknown`; the original fictional
negative-age driver remains. Encapsulation does not imply domain validation.
The historical BMI name means member initialization, not body mass index.
The supplied initializer lesson changes constructors while preserving the
complete Person interface and checked output. Source review does not certify
the pending application import/export workflow until its browser gate passes.

CPPF5 keeps the deliberate vectors-first module from the current source
restructuring; the historical raw-memory module remains in Level 2. Integer
collection/count/amount limits and ASCII-only length semantics are authored
clarifications, not inherited financial or Unicode policies. The original Vector
Practice output and Bank Accounts zero/withdrawal goals are retained. A missing,
malformed or out-of-range requested value now cancels before any claimed balance.
The complete vector example retains its exact original program bytes. Application
briefs, source pins and browser workflow coverage remain a separate pending gate.

CPPF6 preserves all three required projects from the original Juni catalog.
The tracing starter deliberately provides helper bodies; prediction comments
and the driver remain incomplete. Its reference now prints the correct unchanged
copy value and calls the formerly omitted const-reference sum helper. Defanging
keeps both original signatures, processes only original periods during a call
and removes the unchecked size multiplication. Missing/overlength console input
cancels before transformed results. The bounded token limit is authored exercise
policy. Chaos explicitly includes random/time declarations, uses size_t and a
fixed original-size bound, and supplies a valid const observer. Its randomness
claims are limited to the lowercase domain and within-library seeded repetition.
No probability-uniformity or security guarantee is implied. Introduction/struct
program bytes are retained; numeric phone fields are explicitly fictional
historical example data. CPPF8 behavioral review remains open; CPPF7 application review is pending. Application source links and actual browser workflows remain required for
end-to-end delivery of the reviewed CPPF6 packs.


## CPPF7 grid projects

Matrix Addition retains the current vectors-first structure and original row/
column domain 1..100. Complete-token and cell bounds are authored clarifications;
missing/invalid cells cancel before any claimed sum, correcting the observed
zero-filled output and signed-overflow cases. Grid Statistics remains optional
rectangular-grid practice. Its helper signatures, fixed driver output and
row-major tie behavior are retained, with explicit empty/zero-column and bounded
integer preconditions. Ragged-grid validation is still an extension, not a
claim that unsupported ragged inputs were previously promised. The complete grid
lesson keeps its tracked program bytes. Both new project packs have equal full
briefs, incomplete reminders and separate one-program builds. Application
source pins, full brief parity and browser workflows remain pending.
