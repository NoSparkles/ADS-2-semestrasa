#include "fn_set.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

extern int BISHOPS;
extern unsigned long long iterations;// Global variable to count the number of solutions
extern int result_status; // Indicates the result (0 for no solution, 1 for success, -1 for timeout)
clock_t start_time; // Global variable to store the start time
int timeout_ms; // Timeout in milliseconds

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

int place_bishops_with_timeout(int **board, int bishops, int n) {
    if (bishops == 0) {
        ++iterations; // Increment the count of solutions
        return all_cells_controlled(board, n); // Check if all cells are controlled
    }

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            // Check elapsed time
            if (timeout_ms != -1 && ((clock() - start_time) * 1000 / CLOCKS_PER_SEC) > timeout_ms) {
                result_status = -1; // Update global result to timeout
                printf("Timeout reached!\n");
                return -1; // Indicate timeout
            }

            if (board[row][col] == 0) { // Check if the cell is empty
                board[row][col] = 1; // Place a bishop
                int result = place_bishops_with_timeout(board, bishops - 1, n);
                if (result == 1) {
                    result_status = 1; // Update global result to success
                    return 1; // If successful, return true
                } else if (result == -1) {
                    return -1; // Timeout encountered
                }
                board[row][col] = 0; // Backtrack
            }
        }
    }
    return 0; // No solution found
}

int **solve_n_bishops(int n, int timeout) {
    timeout_ms = timeout; // Set the timeout in milliseconds

    // Allocate the board dynamically
    int **board = (int **)malloc(n * sizeof(int *));
    if (!board) {
        fprintf(stderr, "Memory allocation failed for board.\n");
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        board[i] = (int *)calloc(n, sizeof(int));
        if (!board[i]) {
            fprintf(stderr, "Memory allocation failed for board row %d.\n", i);
            for (int j = 0; j < i; j++) {
                free(board[j]);
            }
            free(board);
            return NULL;
        }
    }

    // Start the timer
    start_time = clock();

    // Call the recursive function and check the result
    result_status = place_bishops_with_timeout(board, BISHOPS, n);

    if (result_status == 1) {
        return board; // Return the board if a solution is found
    }

    // If no solution or timeout, clean up and return NULL
    for (int i = 0; i < n; i++) {
        free(board[i]);
    }
    free(board);
    return NULL;
}

