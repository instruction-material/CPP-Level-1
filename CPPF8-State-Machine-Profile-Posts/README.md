# CPPF8 Project 2: Profile Posts State Machine Extension

Extend the profile-posts capstone with an explicit state machine.

Practice goals:
- represent program modes with `enum class`
- use `switch` to route behavior by state
- keep profile data changes separate from command interpretation
- explain why the same command can mean different things in different states

The sample driver uses scripted commands so the program can be run repeatedly in
class. A student extension can replace the command list with user input.
