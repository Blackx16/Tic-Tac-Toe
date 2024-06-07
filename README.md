# Tic Tac Toe

Welcome to the Tic Tac Toe Game! This is a console-based implementation of the classic Tic Tac Toe game in C++. The game can be played in either single-player mode against the computer or in Two-player mode.

## Features

- Two game modes: Single-player and Two-player.
- Single-player mode with two difficulty levels: Easy and Hard.
- Visual representation of the Tic Tac Toe board.
- Input validation for row and column entries.
- Reset the board for a new game after each round.

## Getting Started

### Prerequisites

- A C++ compiler (e.g., `g++`).

### Compilation

To compile the code, use the following command:

```bash
g++ -o tictactoe tictactoe.cpp
```
### Running the Game
After compiling, run the game with the following command:
```bash
./tictactoe
```

## How to Play
### Game Modes
When you start the game, you will be prompted to choose between single-player and two-player mode:

- Enter ```1``` for single-player mode.
- Enter ```2``` for two-player mode.
### Single-Player Mode
In single-player mode, you will play against the computer. You will be asked to enter your name and choose the difficulty level:

- Enter ```1``` for Easy mode.
- Enter ```2``` for Hard mode.

### Two-Player Mode
In two-player mode, you and another player will take turns. You will be asked to enter the names for Player X and Player O.

### Making a Move
During the game, you will be prompted to enter the row and column numbers (1-3) to place your mark (X or O) on the board.

### Winning and Drawing
The game will check for a win or a draw after each move. The game ends when one player wins or the board is full (draw).

### Play Again
After each game, you will be asked if you want to play again. Enter ```y``` for yes or ```n``` for no.

## Code Overview
### Board Class
- __display()__: Displays the current state of the board.
- __isCellEmpty(int row, int col)__: Checks if a cell is empty.
- __setCell(int row, int col, Cell cell)__: Sets a cell with X or O.
- __isFull()__: Checks if the board is full.
- __checkWin(Cell player)__: Checks if a player has won.
- __reset()__: Resets the board to its initial state.

### TicTacToe Class
- __start()___: Starts the Tic Tac Toe game.
- **findBestMove()**: Uses the Minimax algorithm to find the best move for the computer in Hard mode.
- __minimax(int depth, bool isMax)__: Minimax algorithm to evaluate the best move.

### Main Function
Initializes and starts the Tic Tac Toe game.
Example
```bash
Welcome to Tic Tac Toe!
Do you want to play single or duo mode? (1 for single, 2 for duo): 1
Enter name for Player X: Alice
Select difficulty level: (1 for Easy, 2 for Hard): 2
Alice's turn. Enter row and column (1-3): 1 1
Computer chose: 2, 2
```
## Minimax Algorithm
The ```minimax``` function is used to determine the best move for the computer in hard mode. It recursively evaluates all possible moves and their outcomes, considering the maximum possible score for the computer and the minimum possible score for the player
