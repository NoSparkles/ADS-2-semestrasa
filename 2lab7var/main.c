#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Function to check if placing a bishop is safe
bool is_safe(int **board, int row, int col, int n) {
    // Check upper left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 1) {
            return false;
        }
    }

    // Check upper right diagonal
    for (int i = row, j = col; i >= 0 && j < n; i--, j++) {
        if (board[i][j] == 1) {
            return false;
        }
    }

    return true;
}

// Function to solve the bishops problem using backtracking
bool solve_bishops(int **board, int row, int n) {
    if (row >= n) { // All bishops placed successfully
        return true;
    }

    for (int col = 0; col < n; col++) {
        if (is_safe(board, row, col, n)) {
            board[row][col] = 1; // Place bishop
            if (solve_bishops(board, row + 1, n)) {
                return true;
            }
            board[row][col] = 0; // Backtrack
        }
    }

    return false;
}

// Function to print the chessboard
void print_board(int **board, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n;
    printf("Enter the size of the chessboard (N x N): ");
    scanf("%d", &n);

    // Dynamically allocate memory for the chessboard
    int **board = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        board[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            board[i][j] = 0; // Initialize the chessboard with zeros
        }
    }

    if (solve_bishops(board, 0, n)) {
        printf("Solution:\n");
        print_board(board, n);
    } else {
        printf("No solution found.\n");
    }

    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(board[i]);
    }
    free(board);

    return 0;
}