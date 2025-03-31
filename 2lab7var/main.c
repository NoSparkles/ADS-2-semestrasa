#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fn_set.h"

unsigned long long iterations = 0;
int BISHOPS = 8;
int result_status = 0; // Indicates the result (0 for no solution, 1 for success, -1 for timeout)

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s [-|failo_vardas] [-mode [fullSearch|firstMatchSearch|heuristic heuristic_number]] [-timeout miliseconds]\n", argv[0]);
        return 1;
    }

    FILE *input = NULL;
    if (strcmp(argv[1], "-") == 0) {
        input = stdin;
    } else {
        input = fopen(argv[1], "r");
        if (input == NULL) {
            printf("Failed to open file: %s\n", argv[1]);
            return 1;
        }
    }

    int n;
    if (fscanf(input, "%d", &n) != 1) {
        printf("Failed to read number from input.\n");
        if (input != stdin) fclose(input);
        return 1;
    }
    if (input != stdin) fclose(input);

    // Pranešti apie pradinius duomenis
    printf("N = %d\n", n);

    // Apdorojame papildomus parametrus (-mode arba -timeout)
    int heuristic_number = -1;
    int timeout = -1;
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-timeout") == 0 && i + 1 < argc) {
            timeout = atoi(argv[++i]);
            //printf("Timeout set to %d milliseconds.\n", timeout);
        } else if (strcmp(argv[i], "-mode") == 0 && i + 1 < argc) {
            if (strcmp(argv[++i], "heuristic") == 0 && i + 1 < argc) {
                heuristic_number = atoi(argv[++i]);
                //printf("Selected heuristic number: %d\n", heuristic_number);
            } else {
                //printf("Selected mode: %s\n", argv[i]);
            }
        }
    }

    // Apdoroti euristiką
    if (heuristic_number > 0) {
        printf("Euristika dar nerealizuota.\n");
        return 0;
    }

    // Paleisti problemos sprendimą
    int **board = solve_n_bishops(n, timeout);

    if (result_status == 1) {
        printf("Solution:\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%c ", board[i][j] == 1 ? 'B' : '.');
            }
            printf("\n");
        }
    } else if (result_status == -1) {
        handle_timeout(iterations, combination(n * n, BISHOPS));
    } else {
        printf("No solution found.\n");
    }
    if (board != NULL) {
        for (int i = 0; i < n; i++) {
            if (board[i] != NULL) {
                free(board[i]);
            }
        }
        free(board);
    }
    return 0;
}
