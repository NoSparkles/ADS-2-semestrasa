#include "clinic.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void printUsage(char *programName) {
    fprintf(stderr, "Usage: %s [-|filename] [-test]\n", programName);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "  filename: Read from specified file\n");
    fprintf(stderr, "  -test   : Run built-in test cases\n");
    fprintf(stderr, "Input format:\n");
    fprintf(stderr, "arrival_probability simulation_duration specialist_count local_doctor_salary specialist_salary local_doctor_decision_time_from  local_doctor_decision_time_to specialist_decision_time_from specialist_decision_time_to\n");
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printUsage(argv[0]);
        return EXIT_FAILURE;
    }

    // if (strcmp(argv[1], "-test") == 0) {
    //     runDefaultTest();
    //     runCustomTest(15, 5, 15, 0.3, 10, 100);
    //     runCustomTest(20, 5, 15, 0.5, 10, 100);
    //     runCustomTest(20, 5, 15, 0.3, 15, 100);
    //     runCustomTest(20, 5, 15, 0.3, 10, 200);
    //     return EXIT_SUCCESS;
    // }

    FILE *input = stdin;
    if (strcmp(argv[1], "-") != 0) {
        input = fopen(argv[1], "r");
        if (input == NULL) {
            fprintf(stderr, "Error: Could not open file %s\n", argv[1]);
            return EXIT_FAILURE;
        }
    }

    SimulationParams params;
    SimulationStats stats;

    initParams(&params); // Set defaults
    initStats(&stats);

    printf("444444444444444444444444\n");

    readParams(&params, input); // Override with input values
    if (input != stdin) {
        fclose(input);
    }

    printf("3333333333333333333333\n");

    runSimulation(&params, &stats, stdout);

    printf("111111111111111111111111\n");

    freeStats(&stats);

    printf("22222222222222222222222222\n");
    return EXIT_SUCCESS;
}