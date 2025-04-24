#include "clinic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <limits.h>

void initParams(SimulationParams *params) {
    params->arrival_probability = 0.3;
    params->simulation_duration = 100;
    params->specialist_count = 15;
    params->local_doctor_salary = 5;
    params->specialist_salary = 15;
    params->local_doctor_decision_time_from = 3;
    params->local_doctor_decision_time_to = 5;
    params->specialist_decision_time_from = 5;
    params->specialist_decision_time_to = 10;
}

void initStats(SimulationStats *stats) {
    stats->total_customers = 0;
    stats->average_waiting_time = 0;
    stats->total_local_doctor_visits = 0;
    stats->total_specialist_visits = 0;
    stats->max_waiting_time = 0;
    stats->min_waiting_time = INT_MAX; // Ensuring a high initial value for comparison
}

void freeStats(SimulationStats *stats) {
    stats->total_customers = 0;
    stats->average_waiting_time = 0;
    stats->total_local_doctor_visits = 0;
    stats->total_specialist_visits = 0;
    stats->max_waiting_time = 0;
    stats->min_waiting_time = INT_MAX;
}


void readParams(SimulationParams *params, FILE *input) {
    fscanf(input, "%f %d %d %d %d %d %d %d %d",
           &params->arrival_probability,
           &params->simulation_duration,
           &params->specialist_count,
           &params->local_doctor_salary,
           &params->specialist_salary,
           &params->local_doctor_decision_time_from,
           &params->local_doctor_decision_time_to,
           &params->specialist_decision_time_from,
           &params->specialist_decision_time_to);
}

void runSimulation(SimulationParams *params, SimulationStats *stats, FILE *output) {
    srand(time(NULL));

    Queue *localDoctorQueue = create();
    Queue *specialistQueue = create();

    int total_waiting_time = 0;
    int total_customers = 0;
    int max_waiting_time = 0;
    int min_waiting_time = INT_MAX;
    int localDoctorPatients = 0;
    int specialistDirectPatients = 0;

    for (int time = 0; time < params->simulation_duration; time++) {
        if ((float)rand() / RAND_MAX < params->arrival_probability) {
            enqueue(localDoctorQueue, time);
            total_customers++;

            if ((float)rand() / RAND_MAX < 0.5) {
                localDoctorPatients++;
            } else {
                enqueue(specialistQueue, time);
                specialistDirectPatients++;
            }
        }

        if (!is_empty(localDoctorQueue)) {
            bool status = false;
            int arrivalTime = dequeue(localDoctorQueue, &status);
            int waiting_time = time - arrivalTime;
            total_waiting_time += waiting_time;
            if (waiting_time > max_waiting_time) max_waiting_time = waiting_time;
            if (waiting_time < min_waiting_time) min_waiting_time = waiting_time;

            if ((float)rand() / RAND_MAX < 0.7) {
                enqueue(specialistQueue, time);
            }
        }

        if (!is_empty(specialistQueue)) {
            int arrivalTime = dequeue(specialistQueue, NULL);
            int waiting_time = time - arrivalTime;
            total_waiting_time += waiting_time;
            if (waiting_time > max_waiting_time) max_waiting_time = waiting_time;
            if (waiting_time < min_waiting_time) min_waiting_time = waiting_time;
        }
    }

    stats->total_customers = total_customers;
    stats->average_waiting_time = total_customers > 0 ? total_waiting_time / total_customers : 0;
    stats->max_waiting_time = max_waiting_time;
    stats->min_waiting_time = min_waiting_time;

    fprintf(output, "Total customers: %d\n", stats->total_customers);
    fprintf(output, "Average waiting time: %d\n", stats->average_waiting_time);
    fprintf(output, "Max waiting time: %d\n", stats->max_waiting_time);
    fprintf(output, "Min waiting time: %d\n", stats->min_waiting_time);
    fprintf(output, "Local doctor patients: %d\n", localDoctorPatients);
    fprintf(output, "Direct specialist patients: %d\n", specialistDirectPatients);

    done(localDoctorQueue);
    done(specialistQueue);
}