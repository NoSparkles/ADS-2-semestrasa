#include <stdio.h>
#include <string.h>
#include "fn_set.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [-|failo_vardas] [-mode [fullSearch|firstMatchSearch|heuristic heuristic_number]] [-timeout miliseconds]\n", argv[0]);
        return 1;
    }

    FILE *input = NULL;

    if (strcmp(argv[1], "-") == 0) {
        input = stdin;
    } else {
        input = fopen(argv[1], "r");
        if (input == NULL) {
            fprintf(stderr, "Failed to open file: %s\n", argv[1]);
            return 1;
        }
    }

    int n;
    if (fscanf(input, "%d", &n) != 1) {
        fprintf(stderr, "Failed to read number from input.\n");
        if (input != stdin) fclose(input);
        return 1;
    }

    if (input != stdin) fclose(input);

    solve_n_bishops(n);

    return 0;
}
