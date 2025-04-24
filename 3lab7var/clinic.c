#include "clinic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <limits.h>

void initParams(SimulationParams *params) {
    params->arrival_probability = 0.25;              // 25% chance that a patient arrives per time unit
    params->simulation_duration = 200;               // Simulation runs for 200 time units
    params->local_doctor_count = 2;                  // Initially 2 local doctors
    params->specialist_count = 4;                    // 4 specialists
    params->local_doctor_salary = 5;                 // Salary per visit for local doctor (symbolic)
    params->specialist_salary = 15;                  // Salary per visit for specialist

    params->local_doctor_decision_min = 2;           // Local doctor decision takes 2–4 time units
    params->local_doctor_decision_max = 4;

    params->specialist_decision_min = 5;             // Specialist work takes 5–10 time units
    params->specialist_decision_max = 10;

    params->prob_cured_directly = 0.4;               // 40% of cases cured directly
    params->prob_referred = 0.4;                     // 40% of cases referred to a specialist
    // Remaining 20%: patient is healthy (calculated based on above)
}

void initStats(SimulationStats *stats) {
    stats->total_patients = 0;
    stats->cured_patients = 0;
    stats->total_waiting_time = 0;
    stats->average_waiting_time = 0;
    stats->total_local_doctor_visits = 0;
    stats->total_specialist_visits = 0;
    stats->total_cost = 0;
}

void freeStats(SimulationStats *stats) {
    stats->total_patients = 0;
    stats->cured_patients = 0;
    stats->total_waiting_time = 0;
    stats->average_waiting_time = 0;
    stats->total_local_doctor_visits = 0;
    stats->total_specialist_visits = 0;
    stats->total_cost = 0;
}

void readParams(SimulationParams *params, FILE *input) {
    if (!input) {
        fprintf(stderr, "Error: could not open input file.\n");
        exit(1);
    }

    int read = fscanf(input, "%f %d %d %d %d %d %d %d %d %f %f",
           &params->arrival_probability,
           &params->simulation_duration,
           &params->local_doctor_count,
           &params->specialist_count,
           &params->local_doctor_salary,
           &params->specialist_salary,
           &params->local_doctor_decision_min,
           &params->local_doctor_decision_max,
           &params->specialist_decision_min,
           &params->specialist_decision_max,
           &params->prob_cured_directly,
           &params->prob_referred);

    if (read != 11) {
        fprintf(stderr, "Error: invalid input data format (%d parameters read).\n", read);
        exit(2);
    }
}

void runSimulation(SimulationParams *params, SimulationStats *stats, FILE *output) {
    srand(time(NULL));

    Queue *localDoctorQueue = create();
    Queue *specialistQueue = create();

    int *localDoctorTimers = calloc(params->local_doctor_count, sizeof(int));
    int *specialistTimers = calloc(params->specialist_count, sizeof(int));

    for (int time = 0; time < params->simulation_duration; time++) {
        // 1. New patient arrives
        if ((float)rand() / RAND_MAX < params->arrival_probability) {
            stats->total_patients++;
            if ((float)rand() / RAND_MAX < 0.5) {
                enqueue(localDoctorQueue, time);  // Goes to local doctor
            } else {
                enqueue(specialistQueue, time);   // Goes directly to specialist
            }
        }

        // 2. Process local doctors
        for (int i = 0; i < params->local_doctor_count; i++) {
            if (localDoctorTimers[i] > 0) {
                localDoctorTimers[i]--;
                continue;
            }

            if (!is_empty(localDoctorQueue)) {
                int arrivalTime = dequeue(localDoctorQueue, NULL);
                int decisionTime = params->local_doctor_decision_min +
                                   rand() % (params->local_doctor_decision_max - params->local_doctor_decision_min + 1);
                localDoctorTimers[i] = decisionTime;

                stats->total_local_doctor_visits++;
                stats->total_cost += params->local_doctor_salary;

                float decision = (float)rand() / RAND_MAX;
                if (decision < params->prob_cured_directly) {
                    // Patient is cured directly
                    stats->cured_patients++;
                    int timeInSystem = time + decisionTime - arrivalTime;
                    stats->total_waiting_time += timeInSystem;
                } else if (decision < params->prob_cured_directly + params->prob_referred) {
                    // Referred to specialist
                    enqueue(specialistQueue, arrivalTime);  // Keep original arrival time
                }
                // else: healthy, do nothing
            }
        }

        // 3. Process specialists
        for (int i = 0; i < params->specialist_count; i++) {
            if (specialistTimers[i] > 0) {
                specialistTimers[i]--;
                continue;
            }

            if (!is_empty(specialistQueue)) {
                int arrivalTime = dequeue(specialistQueue, NULL);
                int treatmentTime = params->specialist_decision_min +
                                    rand() % (params->specialist_decision_max - params->specialist_decision_min + 1);
                specialistTimers[i] = treatmentTime;

                int timeInSystem = time + treatmentTime - arrivalTime;
                stats->total_waiting_time += timeInSystem;

                stats->total_specialist_visits++;
                stats->total_cost += params->specialist_salary;
                stats->cured_patients++;
            }
        }
    }

    // Calculate average time in system
    int totalCuredPatients = stats->cured_patients;
    if (totalCuredPatients > 0) {
        stats->average_waiting_time = (float)stats->total_waiting_time / totalCuredPatients;
    } else {
        stats->average_waiting_time = 0;
    }

    // Output results
    fprintf(output, "Total patients: %d\n", stats->total_patients);
    fprintf(output, "Cured patients: %d\n", stats->cured_patients);
    fprintf(output, "Average time in system: %.2f\n", stats->average_waiting_time);
    fprintf(output, "Local doctor visits: %d\n", stats->total_local_doctor_visits);
    fprintf(output, "Specialist visits: %d\n", stats->total_specialist_visits);
    fprintf(output, "Total cost: %d\n", stats->total_cost);
    fprintf(output, "Patients still in queue: %d\n", count(localDoctorQueue) + count(specialistQueue));

    // Free dynamically allocated memory
    free(localDoctorTimers);
    free(specialistTimers);
    done(localDoctorQueue);
    done(specialistQueue);
}
