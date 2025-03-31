#include "fn_set.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BISHOPS 8

unsigned long long count = 0; // Global variable to count the number of solutions

// Function to check if all cells are controlled by bishops
int all_cells_controlled(int **board, int n) {
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            int controlled = 0;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (board[i][j] == 1 && abs(row - i) == abs(col - j)) {
                        controlled = 1;
                        break;
                    }
                }
                if (controlled) break;
            }
            if (!controlled) return 0; // If any cell is not controlled
        }
    }
    return 1; // All cells are controlled
}

// Recursive function to place bishops
int place_bishops(int **board, int bishops, int n) {
    if (bishops < 0) {
        return all_cells_controlled(board, n); // Check if all cells are controlled
    }

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (board[row][col] == 0) { // Check if the cell is empty
                ++count; // Increment the count of solutions
                if (count % 10000000 == 0) { // Print every millionth solution
                    printf("count: %llu\n", count);
                    printf("\n");
                    for (int i = 0; i < n; i++) {
                        for (int j = 0; j < n; j++) {
                            printf("%c ", board[i][j] == 1 ? 'B' : '.');
                        }
                        printf("\n");
                    }
                }
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