#include <stdio.h>
#include <stdbool.h>

void input_process(int board[9][9], int row, char input[9]) {
    for (int i = 0; i < 9; i++) {
        board[row][i] = input[i] - '0'; // Convert char to int
    }
}
// Function to print the Sudoku board in a formatted way
void print_board(int board[9][9]) {
    for (int i = 0; i < 9; i++) {
        // Print a separator every 3 rows
        if (i % 3 == 0 && i != 0) {
            printf("- - - - - - - - - - - -\n");
        }

        for (int j = 0; j < 9; j++) {
            // Print a separator every 3 columns
            if (j % 3 == 0 && j != 0) {
                printf("| ");
            }

            // Print the number at the position or '.' for empty cells
            if (board[i][j] == 0) {
                printf(". ");
            } else {
                printf("%d ", board[i][j]);
            }
        }

        // Move to the next row
        printf("\n");
    }
}


bool issafe(int board[9][9], int row, int col, int dig) {
    // Horizontal
    for (int j = 0; j < 9; j++) {
        if (board[row][j] == dig) {
            return false;
        }
    }

    // Vertical
    for (int i = 0; i < 9; i++) {
        if (board[i][col] == dig) {
            return false;
        }
    }

    // Grid
    int srow = (row / 3) * 3;
    int scol = (col / 3) * 3;
    for (int i = srow; i <= srow + 2; i++) {
        for (int j = scol; j <= scol + 2; j++) {
            if (board[i][j] == dig) {
                return false;
            }
        }
    }
    return true;
}

bool helper(int board[9][9], int row, int col) {
    // Solved Stage
    if (row == 9) {
        return true;
    }

    // Next Column
    int nextrow = row;
    int nextcol = col + 1;

    // Next Row
    if (nextcol == 9) {
        nextrow = row + 1;
        nextcol = 0;
    }

    // Skip Non-Empty Cells
    if (board[row][col] != 0) {
        return helper(board, nextrow, nextcol);
    }

    // Place the Digit
    for (int dig = 1; dig <= 9; dig++) {
        if (issafe(board, row, col, dig)) {
            board[row][col] = dig;
            if (helper(board, nextrow, nextcol)) {
                return true;
            }
            board[row][col] = 0; // Backtrack
        }
    }
    return false;
}

int main() {
    int board[9][9];
    char input[9];
    printf("Welcome to the SAY Sudoku Solver\nAuthor: MD Sami Akhlaq (S.A.Y)...\n\n");
    printf("Input:\n\n");
    printf("Please enter the Sudoku Puzzle row by row......\n");
    printf("Each row should contain exactly 9 digits. Use '0' to represent empty cells......\n");
    printf("Sample: 200001400\n\n");

    for (int i = 0; i < 9; i++) {
        scanf("%s", input); // Read a string of 9 characters
        input_process(board, i, input);
    }

    printf("\n\n");
    printf("Question Board: \n\n");
    print_board(board);
    printf("\n\n");
    if (helper(board, 0, 0)) {
            printf("Solved Puzzle: \n\n");
            print_board(board);
    } else {
        printf("No solution exist\n");
    }

    return 0;
}
