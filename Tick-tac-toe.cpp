#include <iostream>
#include <limits>
#include <utility>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// Represents each cell of the Tic Tac Toe board
enum Cell { Empty, X, O };

// Represents the Tic Tac Toe board
class Board {
private:
    Cell cells[3][3]; // Array to store the cells of the board

public:
    Board() {
        // Initialize all cells as empty
        reset();
    }

    // Display the Tic Tac Toe board
    void display() const {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (j > 0)
                    cout << "|";
                switch(cells[i][j]) {
                    case X:
                        cout << " X ";
                        break;
                    case O:
                        cout << " O ";
                        break;
                    case Empty:
                        cout << "   ";
                        break;
                }
            }
            cout << endl;
            if (i < 2)
                cout << "-----------" << endl;
        }
    }

    // Check if a cell is empty
    bool isCellEmpty(int row, int col) const {
        return cells[row][col] == Empty;
    }

    // Set a cell with X or O
    void setCell(int row, int col, Cell cell) {
        cells[row][col] = cell;
    }

    // Check if the board is full
    bool isFull() const {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (cells[i][j] == Empty)
                    return false;
            }
        }
        return true;
    }

    // Check if a player has won
    bool checkWin(Cell player) const {
        // Check rows
        for (int i = 0; i < 3; ++i) {
            if (cells[i][0] == player && cells[i][1] == player && cells[i][2] == player)
                return true;
        }

        // Check columns
        for (int j = 0; j < 3; ++j) {
            if (cells[0][j] == player && cells[1][j] == player && cells[2][j] == player)
                return true;
        }

        // Check diagonals
        if (cells[0][0] == player && cells[1][1] == player && cells[2][2] == player)
            return true;
        if (cells[0][2] == player && cells[1][1] == player && cells[2][0] == player)
            return true;

        return false;
    }

    // Reset the board to its initial state
    void reset() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cells[i][j] = Empty;
            }
        }
    }
};

// Represents the Tic Tac Toe game
class TicTacToe {
private:
    Board board; // The game board
    string playerXName;
    string playerOName;
    bool duoMode;
    bool hardMode;

public:
    TicTacToe() {
        srand(static_cast<unsigned int>(time(0))); // Seed for random number generation
    }

    // Start the Tic Tac Toe game
    void start() {
        bool playAgain = true;
        while (playAgain) {
            cout << "Do you want to play single or duo mode? (1 for single, 2 for duo): ";
            int mode;
            while (!(cin >> mode) || (mode != 1 && mode != 2)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter 1 for single mode or 2 for duo mode: ";
            }
            duoMode = (mode == 2);

            if (duoMode) {
                cout << "Enter name for Player X: ";
                cin >> playerXName;
                cout << "Enter name for Player O: ";
                cin >> playerOName;
                cout << "Welcome, " << playerXName << " and " << playerOName << "!" << endl;
            } else {
                playerXName = "Player X";
                playerOName = "Computer";
                cout << "Enter name for Player X: ";
                cin >> playerXName;
                cout << "Select difficulty level: (1 for Easy, 2 for Hard): ";
                int difficulty;
                while (!(cin >> difficulty) || (difficulty != 1 && difficulty != 2)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input! Please enter 1 for Easy or 2 for Hard: ";
                }
                hardMode = (difficulty == 2);
            }

            bool playerXTurn = true; // Flag to indicate player X's turn
            bool gameOver = false;
            Cell currentPlayer = X;

            while (!gameOver) {
                board.display();
                int row, col;

                // Player's move
                if (duoMode || (playerXTurn && !duoMode)) {
                    cout << (playerXTurn ? playerXName : playerOName) << "'s turn. Enter row and column (1-3): ";
                    while (!(cin >> row >> col) || row < 1 || row > 3 || col < 1 || col > 3 || !board.isCellEmpty(row - 1, col - 1)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid move! Try again. Enter row and column (1-3): ";
                    }
                    row--; // Adjust for zero-based indexing
                    col--; // Adjust for zero-based indexing
                } else {
                    if (hardMode) {
                        pair<int, int> bestMove = findBestMove();
                        row = bestMove.first;
                        col = bestMove.second;
                        cout << "Computer chose: " << row + 1 << ", " << col + 1 << endl;
                    } else {
                        do {
                            row = rand() % 3;
                            col = rand() % 3;
                        } while (!board.isCellEmpty(row, col));
                        cout << "Computer chose: " << row + 1 << ", " << col + 1 << endl;
                    }
                }

                board.setCell(row, col, currentPlayer);

                // Check for win or draw
                if (board.checkWin(currentPlayer)) {
                    board.display();
                    cout << (playerXTurn ? playerXName : playerOName) << " wins!" << endl;
                    gameOver = true;
                } else if (board.isFull()) {
                    board.display();
                    cout << "It's a draw!" << endl;
                    gameOver = true;
                }

                // Switch player
                playerXTurn = !playerXTurn;
            currentPlayer = (currentPlayer == X) ? O : X;
        }

        char choice;
        cout << "Do you want to play again? (y/n): ";
        while (!(cin >> choice) || (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N')) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter 'y' for yes or 'n' for no: ";
        }
        playAgain = (choice == 'y' || choice == 'Y');
        board.reset();
    }
}

// Minimax algorithm to find the best move
pair<int, int> findBestMove() {
    int bestVal = numeric_limits<int>::min();
    pair<int, int> bestMove = make_pair(-1, -1);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board.isCellEmpty(i, j)) {
                board.setCell(i, j, O);
                int moveVal = minimax(0, false);
                board.setCell(i, j, Empty);
                if (moveVal > bestVal) {
                    bestMove = make_pair(i, j);
                    bestVal = moveVal;
                }
            }
        }
    }

    return bestMove;
}

// Minimax algorithm
int minimax(int depth, bool isMax) {
    if (board.checkWin(O))
        return 10 - depth;
    if (board.checkWin(X))
        return depth - 10;
    if (board.isFull())
        return 0;

    if (isMax) {
        int best = numeric_limits<int>::min();
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board.isCellEmpty(i, j)) {
                    board.setCell(i, j, O);
                    best = max(best, minimax(depth + 1, !isMax));
                    board.setCell(i, j, Empty);
                }
            }
        }
        return best;
    } else {
        int best = numeric_limits<int>::max();
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board.isCellEmpty(i, j)) {
                    board.setCell(i, j, X);
                    best = min(best, minimax(depth + 1, !isMax));
                    board.setCell(i, j, Empty);
                }
            }
        }
        return best;
    }
}
};

int main() {
cout << "Welcome to Tic Tac Toe!\n" << endl;
TicTacToe game;
game.start();
return 0;
}
