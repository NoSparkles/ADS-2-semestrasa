#include "fn_set.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BISHOPS 8

unsigned long long count = 0; // Global variable to count the number of solutions

int all_cells_controlled(int **board, int n) {
    int **controlled = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        controlled[i] = (int *)calloc(n, sizeof(int));
    }

    // Mark controlled cells for every bishop
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (board[row][col] == 1) { // If a bishop is present
                controlled[row][col] = 1; // Mark the bishop's cell as controlled

                // Mark all diagonals
                for (int i = 1; i < n; i++) {
                    if (row + i < n && col + i < n) controlled[row + i][col + i] = 1;
                    if (row + i < n && col - i >= 0) controlled[row + i][col - i] = 1;
                    if (row - i >= 0 && col + i < n) controlled[row - i][col + i] = 1;
                    if (row - i >= 0 && col - i >= 0) controlled[row - i][col - i] = 1;
                }
            }
        }
    }

    // Check if all cells are controlled
    int all_controlled = 1;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (!controlled[row][col]) { // If any cell is not controlled
                all_controlled = 0;
                break;
            }
        }
        if (!all_controlled) break;
    }

    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(controlled[i]);
    }
    free(controlled);

    return all_controlled;
}

// Recursive function to place bishops
int place_bishops(int **board, int bishops, int n) {
    if (bishops == 0) {
        ++count; // Increment the count of solutions
        return all_cells_controlled(board, n); // Check if all cells are controlled
    }

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (board[row][col] == 0) { // Check if the cell is empty
                board[row][col] = 1; // Place a bishop
                if (place_bishops(board, bishops - 1, n)) {
                    return 1; // If successful, return true
                }
                board[row][col] = 0; // Backtrack
            }
        }
    }
    return 0; // No solution found
}

// Function to solve the 8 bishops problem
void solve_n_bishops(int n) {

    // Allocate the board dynamically
    int **board = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        board[i] = (int *)calloc(n, sizeof(int));
    }

    if (place_bishops(board, BISHOPS, n)) {
        // Print the solution
        printf("\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%c ", board[i][j] == 1 ? 'B' : '.');
            }
            printf("\n");
        }
    } else {
        printf("No solution found.\n");
    }

    // Free the allocated memory
    for (int i = 0; i < n; i++) {
        free(board[i]);
    }
    free(board);
}