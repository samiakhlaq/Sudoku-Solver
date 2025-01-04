#include <stdio.h>
#include <stdbool.h>

// Function to process user input and populate the Sudoku board
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

// Function to check if placing a digit is safe
bool issafe(int board[9][9], int row, int col, int dig) {
    // Check horizontally
    for (int j = 0; j < 9; j++) {
        if (board[row][j] == dig) {
            return false;
        }
    }

    // Check vertically
    for (int i = 0; i < 9; i++) {
        if (board[i][col] == dig) {
            return false;
        }
    }

    // Check the 3x3 grid
    int srow = (row / 3) * 3;
    int scol = (col / 3) * 3;
    for (int i = srow; i < srow + 3; i++) {
        for (int j = scol; j < scol + 3; j++) {
            if (board[i][j] == dig) {
                return false;
            }
        }
    }
    return true;
}

// Helper function for solving the Sudoku
bool helper(int board[9][9], int row, int col) {
    // Solved stage
    if (row == 9) {
        return true;
    }

    // Calculate next row and column
    int nextrow = row;
    int nextcol = col + 1;
    if (nextcol == 9) {
        nextrow = row + 1;
        nextcol = 0;
    }

    // Skip non-empty cells
    if (board[row][col] != 0) {
        return helper(board, nextrow, nextcol);
    }

    // Try placing digits
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

// Main function
int main() {
    int board[9][9] = {0}; // Initialize the board
    char input[10];        // Buffer to read input
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
        printf("No solution exists\n");
    }

    return 0;
}
