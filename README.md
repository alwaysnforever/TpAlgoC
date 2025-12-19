# Wordle Solver in C

This project implements the **Wordle** game and an automated solver in C language.  
The program reads a list of 5-letter words from a `words.txt` file, selects a random secret word, lets the user play (Part 1), then launches a solver that tries to guess the same word (Part 2). [file:1]

## Prerequisites

- Have the **gcc** compiler installed on the machine. [web:22]
- Be able to use a terminal (Linux, macOS or Windows + MinGW/WSL).
- Have the `words.txt` file in the same folder as the `.c` files and executable. [file:1][web:75]

## Installation and Compilation

In a terminal, in the project folder:

gcc main.c game.c solver.c -o wordle

This command creates the `wordle` executable. [web:22]

## Usage

In the same terminal:

./wordle

The program will:

- Load words from `words.txt`.  
- Display the number of words loaded.  
- Select a random secret word.  
- Launch **Part 1** (you play).  
- Launch **Part 2** (solver plays). [file:1][web:11]

### Example Usage (Terminal)

<img width="411" height="459" alt="Screenshot 2025-12-19 141322" src="https://github.com/user-attachments/assets/bfc9bba3-2dd3-412d-9f4c-c7672789bdc8" />

<img width="352" height="367" alt="Screenshot 2025-12-19 141402" src="https://github.com/user-attachments/assets/a119be02-43b6-43a7-a503-fbc47252e2c4" />


## Project Files

- `main.c`: `main` function that initializes, launches the game then the solver. [file:1]  
- `game.c`: game functions (`ReadDictionary`, `ChooseRandomWord`, `GetUserGuess`, `GiveFeedback`, `PlayGame`).  
- `solver.c`: solver functions (`ComputeFeedback`, `FilterCandidates`, `ComputeLetterFrequencies`, `ScoreWord`, `ChooseBestGuess`, `Solver`). [web:11]  
- `wordle.h`: constants and function prototypes.  
- `words.txt`: dictionary of 5-letter words used by the game and solver. [file:1][web:75]

## Authors

- MERAR IKRAM – L2 ISIL C  
- AITOUAMAR AYA – L2 ISIL C

