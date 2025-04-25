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
    fprintf(stderr, "arrival_probability simulation_duration local_doctor_count specialist_count local_doctor_salary specialist_salary local_doctor_decision_min local_doctor_decision_max specialist_decision_min specialist_decision_max prob_cured_directly prob_referred\n");
}

void runDefaultTest(unsigned randomNumber) {
    SimulationParams params;
    SimulationStats stats;
    initParams(&params);
    initStats(&stats);
    runSimulation(&params, &stats, stdout, randomNumber);
    fprintf(stdout, "\n");
    freeStats(&stats);
}

void runCustomTest(float arrival_probability, int simulation_duration, int local_doctor_count, int specialist_count, int local_doctor_salary, int specialist_salary, int local_doctor_decision_min, int local_doctor_decision_max, int specialist_decision_min, int specialist_decision_max, float prob_cured_directly, float prob_referred, unsigned randomNumber) {
    SimulationParams params;
    SimulationStats stats;
    initParams(&params);
    initStats(&stats);

    params.arrival_probability = arrival_probability;
    params.simulation_duration = simulation_duration;
    params.local_doctor_count = local_doctor_count;
    params.specialist_count = specialist_count;
    params.local_doctor_salary = local_doctor_salary;
    params.specialist_salary = specialist_salary;
    params.local_doctor_decision_min = local_doctor_decision_min;
    params.local_doctor_decision_max = local_doctor_decision_max;
    params.specialist_decision_min = specialist_decision_min;
    params.specialist_decision_max = specialist_decision_max;
    params.prob_cured_directly = prob_cured_directly;
    params.prob_referred = prob_referred;

    runSimulation(&params, &stats, stdout, randomNumber);
    fprintf(stdout, "\n");
    freeStats(&stats);
}

int main(int argc, char *argv[]) {
    unsigned randomNumber = 0;  // Default value if -rnd is not provided
    char configFileName[256] = {0};
    FILE *input = stdin;

    // Parse arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-rnd") == 0 && i + 1 < argc) {
            randomNumber = atoi(argv[i + 1]);
            i++;  // Skip next argument
        } 
        else if (strcmp(argv[i], "-h") == 0) {
            printUsage(argv[0]);
            return EXIT_FAILURE;
        }
        else if (strcmp(argv[i], "-test") == 0) {
            runDefaultTest(1);
            runCustomTest(0.3, 1000, 1, 3, 5, 20, 5, 10, 15, 25, 0.4, 0.4, 2);
            runCustomTest(0.3, 1000, 1, 8, 5, 20, 5, 10, 15, 25, 0.4, 0.4, 3);
            runCustomTest(0.3, 1000, 2, 5, 5, 20, 5, 10, 15, 25, 0.4, 0.4, 4);
            runCustomTest(0.3, 1000, 2, 3, 5, 20, 5, 10, 15, 25, 0.4, 0.4, 5);
            return EXIT_SUCCESS;
        }
        else if (strcmp(argv[i], "-") != 0) {
            input = fopen(argv[i], "r");
            if (input == NULL) {
                fprintf(stderr, "Error: Could not open file %s\n", argv[i]);
                return EXIT_FAILURE;
            }
        }
    }

    // If no file was provided explicitly, use default configuration file
    if (input == stdin) {
        char *programPath = argv[0];
        char *programName = programPath;

        for (char *p = programPath; *p != '\0'; p++) {
            if (*p == '/' || *p == '\\') {  // handle both Unix and Windows
                programName = p + 1;
            }
        }

        strncpy(configFileName, programName, sizeof(configFileName) - 1);
        configFileName[sizeof(configFileName) - 1] = '\0';

        char *extension = NULL;
        for (char *p = configFileName; *p != '\0'; p++) {
            if (*p == '.') {
                extension = p;
            }
        }

        if (extension != NULL) {
            strncpy(extension, ".cfg", sizeof(configFileName) - (extension - configFileName));
        } else {
            strncat(configFileName, ".cfg", sizeof(configFileName) - strlen(configFileName) - 1);
        }

        input = fopen(configFileName, "r");
        if (input == NULL) {
            fprintf(stderr, "Error: Could not open file %s\n", configFileName);
            return EXIT_FAILURE;
        }
    }

    SimulationParams params;
    SimulationStats stats;

    initParams(&params);
    initStats(&stats);

    readParams(&params, input); // Override with input values
    if (input != stdin) {
        fclose(input);
    }

    runSimulation(&params, &stats, stdout, randomNumber);

    freeStats(&stats);

    return EXIT_SUCCESS;
}