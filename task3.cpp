#include <iostream>

using namespace std;

const int SIZE = 9;

// Function to display the Sudoku board
void printBoard(int board[SIZE][SIZE]) {

    cout << "\n+-------+-------+-------+\n";

    for (int row = 0; row < SIZE; row++) {

        cout << "| ";

        for (int col = 0; col < SIZE; col++) {

            if (board[row][col] == 0)
                cout << ". ";
            else
                cout << board[row][col] << " ";

            if ((col + 1) % 3 == 0)
                cout << "| ";
        }

        cout << endl;

        if ((row + 1) % 3 == 0)
            cout << "+-------+-------+-------+\n";
    }
}

// Function to check whether a number is already present in a row
bool isSafeInRow(int board[SIZE][SIZE], int row, int num) {

    for (int col = 0; col < SIZE; col++) {

        if (board[row][col] == num) {
            return false;
        }
    }

    return true;
}

// Function to check whether a number is already present in a column
bool isSafeInColumn(int board[SIZE][SIZE], int col, int num) {

    for (int row = 0; row < SIZE; row++) {

        if (board[row][col] == num) {
            return false;
        }
    }

    return true;
}

// Function to check whether a number is valid inside a 3x3 box
bool isSafeInBox(int board[SIZE][SIZE],
                 int startRow,
                 int startCol,
                 int num) {

    for (int row = 0; row < 3; row++) {

        for (int col = 0; col < 3; col++) {

            if (board[startRow + row][startCol + col] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to check all Sudoku rules for a particular cell
bool isSafe(int board[SIZE][SIZE],
            int row,
            int col,
            int num) {

    return isSafeInRow(board, row, num) &&
           isSafeInColumn(board, col, num) &&
           isSafeInBox(
               board,
               row - row % 3,
               col - col % 3,
               num
           );
}

// Backtracking function that solves the Sudoku
bool solveSudoku(int board[SIZE][SIZE]) {

    int row = -1;
    int col = -1;

    bool emptyCellFound = false;

    // Find an empty cell
    for (int i = 0; i < SIZE; i++) {

        for (int j = 0; j < SIZE; j++) {

            if (board[i][j] == 0) {

                row = i;
                col = j;
                emptyCellFound = true;

                break;
            }
        }

        if (emptyCellFound)
            break;
    }

    // If there is no empty cell, Sudoku is solved
    if (!emptyCellFound) {
        return true;
    }

    // Try numbers from 1 to 9
    for (int num = 1; num <= 9; num++) {

        if (isSafe(board, row, col, num)) {

            // Place the number
            board[row][col] = num;

            // Recursively solve the remaining board
            if (solveSudoku(board)) {
                return true;
            }

            // Backtrack if solution is not possible
            board[row][col] = 0;
        }
    }

    // No valid number found
    return false;
}

// Function to validate the initial Sudoku board
bool validateInitialBoard(int board[SIZE][SIZE]) {

    for (int row = 0; row < SIZE; row++) {

        for (int col = 0; col < SIZE; col++) {

            int value = board[row][col];

            if (value < 0 || value > 9) {
                return false;
            }

            if (value != 0) {

                board[row][col] = 0;

                if (!isSafe(board, row, col, value)) {

                    board[row][col] = value;
                    return false;
                }

                board[row][col] = value;
            }
        }
    }

    return true;
}

// Main function
int main() {

    int board[SIZE][SIZE];

    cout << "========== SUDOKU SOLVER ==========\n";

    cout << "Enter Sudoku grid.\n";
    cout << "Use 0 for empty cells.\n\n";

    // Take Sudoku input
    for (int row = 0; row < SIZE; row++) {

        for (int col = 0; col < SIZE; col++) {

            cin >> board[row][col];

            // Validate input
            if (cin.fail() ||
                board[row][col] < 0 ||
                board[row][col] > 9) {

                cout << "Invalid input!\n";
                cout << "Only numbers from 0 to 9 are allowed.\n";

                return 0;
            }
        }
    }

    // Validate the initial puzzle
    if (!validateInitialBoard(board)) {

        cout << "\nInvalid Sudoku puzzle!\n";
        cout << "Duplicate numbers exist in a row, column or 3x3 box.\n";

        return 0;
    }

    cout << "\nOriginal Sudoku:";
    printBoard(board);

    // Solve Sudoku
    if (solveSudoku(board)) {

        cout << "\nSolved Sudoku:";
        printBoard(board);

    } else {

        cout << "\nThis Sudoku puzzle has no solution.\n";
    }

    return 0;
}