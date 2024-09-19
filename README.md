# Welcome to Terminal Hangman Game (written in C)
This is a simple Hangman game that runs in the terminal. While there are some minor changes/improvements planned, it should work without any bugs.

## Linux
Required files:
* `dictionary`
* `hangman.c`
* `Makefile`
To build and run the game, type the following commands in your terminal:
```
make
make run
```
(gcc required)

## Windows
Required files:
* `dictionary`
* `hangman.exe`

To run the game on Windows, simply launch `hangman.exe`.

## Future improvements or known issues:
- Add difficulty selector: Implement different difficulty levels by limiting the number of incorrect guesses allowed.
- Return to main menu: Allow player to return to the main menu after a game instead of closing the program.
- Handle the dictionary better: The current dictionary is limited to 100 lines and fixed word size, which can cause issues if edited. (dynamic memory allocation)
