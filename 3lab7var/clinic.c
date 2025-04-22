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
    stats->total_customers = createLongNum("0");
    stats->average_waiting_time = createLongNum("0");
    stats->total_local_doctor_visits = createLongNum("0");
    stats->total_specialist_visits = createLongNum("0");
    stats->max_waiting_time = createLongNum("0");
    stats->min_waiting_time = createLongNum("0");
}

void freeStats(SimulationStats *stats) {
    destroyLongNum(&stats->total_customers);
    destroyLongNum(&stats->average_waiting_time);
    destroyLongNum(&stats->total_local_doctor_visits);
    destroyLongNum(&stats->total_specialist_visits);
    destroyLongNum(&stats->max_waiting_time);
    destroyLongNum(&stats->min_waiting_time);
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
    
    if (params->arrival_probability < 0 || params->arrival_probability > 1) {
        fprintf(stderr, "Error: Arrival probability must be between 0 and 1.\n");
        exit(EXIT_FAILURE);
    }

    if (params->simulation_duration <= 0) {
        fprintf(stderr, "Error: Simulation duration must be greater than 0.\n");
        exit(EXIT_FAILURE);
    }

    if (params->specialist_count <= 0) {
        fprintf(stderr, "Error: Specialist count must be greater than 0.\n");
        exit(EXIT_FAILURE);
    }

    if (params->local_doctor_salary <= 0) {
        fprintf(stderr, "Error: Local doctor salary must be greater than 0.\n");
        exit(EXIT_FAILURE);
    }

    if (params->specialist_salary <= 0) {
        fprintf(stderr, "Error: Specialist salary must be greater than 0.\n");
        exit(EXIT_FAILURE);
    }

    if (params->local_doctor_decision_time_from <= 0 || params->local_doctor_decision_time_to <= 0) {
        fprintf(stderr, "Error: Local doctor decision time must be greater than 0.\n");
        exit(EXIT_FAILURE);
    }

    if (params->specialist_decision_time_from <= 0 || params->specialist_decision_time_to <= 0) {
        fprintf(stderr, "Error: Specialist decision time must be greater than 0.\n");
        exit(EXIT_FAILURE);
    }

    if (params->local_doctor_decision_time_from > params->local_doctor_decision_time_to) {
        fprintf(stderr, "Error: Local doctor decision time from must be less than or equal to to.\n");
        exit(EXIT_FAILURE);
    }

    if (params->specialist_decision_time_from > params->specialist_decision_time_to) {
        fprintf(stderr, "Error: Specialist decision time from must be less than or equal to to.\n");
        exit(EXIT_FAILURE);
    }
}

void runSimulation(SimulationParams *params, SimulationStats *stats, FILE *output) {
    srand(time(NULL));

    Queue *localDoctorQueue = create();  // Eilė pas apylinkės gydytoją
    Queue *specialistQueue = create();   // Eilė pas specialistą
    LongNum *total_waiting_time = createLongNum("0");
    LongNum *total_customers = createLongNum("0");
    LongNum *max_waiting_time = createLongNum("0");
    LongNum *min_waiting_time = createLongNum("999999999");  // Didelė reikšmė kaip pradinis minimumas
    LongNum *localDoctorPatients = createLongNum("0");
    LongNum *specialistDirectPatients = createLongNum("0");

    for (LongNum *time = createLongNum("0"); lessThan(&time, createLongNumFromInt(params->simulation_duration)); increment(&time)) {
        if ((float)rand() / RAND_MAX < params->arrival_probability) {
            enqueue(localDoctorQueue, time);
            total_customers = add(&total_customers, createLongNum("1"));
            
            if ((float)rand() / RAND_MAX < 0.5) {
                localDoctorPatients = add(&localDoctorPatients, createLongNum("1"));
            } else {
                enqueue(specialistQueue, time);
                specialistDirectPatients = add(&specialistDirectPatients, createLongNum("1"));
            }
        }

        if (!is_empty(localDoctorQueue)) {
            LongNum *arrivalTime = dequeue(localDoctorQueue, NULL);
            LongNum *waiting_time = subtract(&time, &arrivalTime);
            total_waiting_time = add(&total_waiting_time, &waiting_time);
            max_waiting_time = greaterThan(&waiting_time, &max_waiting_time) ? waiting_time : max_waiting_time;
            min_waiting_time = lessThan(&waiting_time, &min_waiting_time) ? waiting_time : min_waiting_time;

            if ((float)rand() / RAND_MAX < 0.7) {
                enqueue(specialistQueue, time);
            }
        }

        if (!is_empty(specialistQueue)) {
            LongNum *arrivalTime = dequeue(specialistQueue, NULL);
            LongNum *waiting_time = subtract(&time, &arrivalTime);
            total_waiting_time = add(&total_waiting_time, &waiting_time);
            max_waiting_time = greaterThan(&waiting_time, &max_waiting_time) ? waiting_time : max_waiting_time;
            min_waiting_time = lessThan(&waiting_time, &min_waiting_time) ? waiting_time : min_waiting_time;
        }
    }

    stats->total_customers = total_customers;
    stats->average_waiting_time = divide(&total_waiting_time, &total_customers);
    stats->max_waiting_time = max_waiting_time;
    stats->min_waiting_time = min_waiting_time;
    
    fprintf(output, "Total customers: ");
    printLongNum(&stats->total_customers);
    fprintf(output, "Average waiting time: ");
    printLongNum(&stats->average_waiting_time);
    fprintf(output, "Max waiting time: ");
    printLongNum(&stats->max_waiting_time);
    fprintf(output, "Min waiting time: ");
    printLongNum(&stats->min_waiting_time);
    fprintf(output, "Local doctor patients: ");
    printLongNum(&localDoctorPatients);
    fprintf(output, "Direct specialist patients: ");
    printLongNum(&specialistDirectPatients);

    done(localDoctorQueue);
    done(specialistQueue);
}