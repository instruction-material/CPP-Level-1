# CPPF8 Project 2: Profile Posts State Machine Extension

This optional extension follows the required interactive Profile Posts capstone.
Practice explicit modes and command interpretation, with at least three active
states plus `Quit`: `MainMenu`, `ViewingPosts`, `EditingPost`, and `Quit`.
Use `enum class`, `switch`, and a written state diagram. The same command can
have different effects in different states. Keep data changes inside `Profile`.

Import only `starter`, complete its TODOs, then compare with `solution`. Both
contain this complete brief and a separate `main.cpp`. The untouched starter
exits with status 2 and a reminder. From one extracted pack:
```sh
c++ -std=c++20 -Wall -Wextra -Wpedantic -Werror main.cpp -o profile-states
./profile-states
```
The site IDE edits, saves and exports source; compile natively. From the project
root, `make` selects `solution`, or `make PACK=starter` selects the incomplete
pack. Never combine the independent programs. The root `main.cpp` forwards to
the reference for older links.

## States and commands

| Current state | Command | Result |
| --- | --- | --- |
| MainMenu | view | ViewingPosts |
| MainMenu | edit | EditingPost only if a post exists; otherwise MainMenu |
| MainMenu | quit | Quit |
| ViewingPosts | back | MainMenu |
| ViewingPosts | edit | EditingPost only if a post exists; otherwise ViewingPosts |
| EditingPost | like-first | Add 5 hearts to index 0 if valid; remain EditingPost |
| EditingPost | back | MainMenu |
| Quit | any command | Quit, without mutation |

Every ViewingPosts command displays the current profile, as in the supplied
example. Unknown/state-inappropriate commands leave the state and data unchanged
and print the relevant choices. In particular, `quit` is a MainMenu command.
Invalid edit indexes and rejected heart updates preserve data. Use the same
authored bounds as the core capstone: at most 1000 posts, 1..4096 caption bytes,
and 0..1000000 hearts per post. Check signed changes before adding.

## Repeatable driver and completion evidence

The required reference intentionally uses scripted commands so it runs repeatedly
in class. Seed two fictional posts with 24 and 31 hearts; process `view`, `edit`,
`like-first`, `back`, `view`, `back`, `quit`. Finish in Quit with 29 and 31 hearts.
Replacing the script with user input is an optional bonus, not a requirement.

Check every transition, an empty profile's edit commands, unknown commands in
each active state, repeated likes at the upper bound, and commands after Quit.
Preserve the first post when another post is edited. Draw the state diagram and
explain why this exercise's explicit modes differ from the core's single menu.
No real account, public posting, persistence or networking is involved.
