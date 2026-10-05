# Source pack review

## Reviewed on 2026-10-05

| Project | Required learning goal | Verified behavior |
| --- | --- | --- |
| Mad Libs | Strings, token input, story construction | Word order, whitespace separators and incomplete-input cancellation |
| Chat Bot | Full-line strings, insertion and arithmetic | Short/Unicode text, LF/CRLF, complete numeric lines, bounds and fixed-data conversions |
| Number Games | For/while range printing, sums and means | Normal/reversed/one-value ranges, independent batches, zero counts, bounds and rejection phase boundaries |
| Rock/Paper/Scissors | Nested conditionals and validation | All nine pairs, invalid/missing input and no winner for invalid rounds |
| Fizz Buzz | Counted loop, remainder and branch ordering | All 50 outputs, including safe ordinary number printing |

Every listed pack has an intentionally incomplete starter, a separate reference,
a matching self-contained README and a warning-clean C++20 native build. Legacy
root entries forward to the corrected references. Native tests also exercise
sanitized references. References are not learner imports.

## Remaining audit scope

Compilation alone does not certify the later CPPF3–CPPF8 contracts or starter
roles. Their source review remains open, as do the remaining function/vector
transformation supplement and later duplicate assignment links. The unrelated
CPPF1 variable/vector transformation wrapper was moved byte-for-byte to the
inactive archive; it is not a beginner input/output assignment. The first two
modules' site links and briefs must point to the reviewed nested folders before
this source work establishes an end-to-end learner workflow. Source publication
alone does not prove application deployment.

## Fidelity

The five core project names and learning goals are preserved from the original
Juni C++ Level 1 catalog. Safety checks and explicit console fixtures are authored
clarifications. The sample exchange rate is fixed fictional exercise data. The
original Fizz Buzz optional custom-divisor bonus remains an extension; the
reference gate covers only the required fixed 3-and-5 version.
