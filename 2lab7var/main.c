#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 8

// Function to print the chessboard
void printBoard(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

// Function to check if the bishop can attack a square
bool isAttacked(int x, int y, int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 1) {  // There's a bishop at (i, j)
                if (abs(x - i) == abs(y - j)) {  // Same diagonal
                    return true;
                }
            }
        }
    }
    return false;
}

// Function to place bishops on the chessboard
bool placeBishops(int board[SIZE][SIZE], int bishops) {
    if (bishops == 0) {
        // Check if all squares are attacked
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (!isAttacked(i, j, board)) {
                    return false;
                }
            }
        }
        return true;
    }

    // Try to place the next bishop
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0 && !isAttacked(i, j, board)) {
                board[i][j] = 1;  // Place a bishop
                printf("%d", bishops);
                printf("\n");
                if (placeBishops(board, bishops - 1)) {
                    return true;
                }
                board[i][j] = 0;  // Backtrack
            }
        }
    }
    return false;
}

int main() {
    int board[SIZE][SIZE] = {0};
    int bishops = 8;

    if (placeBishops(board, bishops)) {
        printf("Solution found:\n");
        printBoard(board);
    } else {
        printf("No solution exists.\n");
    }

    return 0;
}
