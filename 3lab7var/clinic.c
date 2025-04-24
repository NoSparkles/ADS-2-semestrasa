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
    params->specialist_count = 4;
    params->local_doctor_salary = 5;
    params->specialist_salary = 15;
    params->local_doctor_decision_time_from = 3;
    params->local_doctor_decision_time_to = 5;
    params->specialist_decision_time_from = 5;
    params->specialist_decision_time_to = 10;
}

void initStats(SimulationStats *stats) {
    stats->total_customers = 0;
    stats->cured_customers = 0;
    stats->average_waiting_time = 0;
    stats->total_local_doctor_visits = 0;
    stats->total_specialist_visits = 0;
    stats->average_decision_time = 0;
    stats->money_spent = 0;
}

void freeStats(SimulationStats *stats) {
    // No dynamic memory allocations in SimulationStats, so we just reset values.
    stats->total_customers = 0;
    stats->cured_customers = 0;
    stats->average_waiting_time = 0;
    stats->total_local_doctor_visits = 0;
    stats->total_specialist_visits = 0;
    stats->average_decision_time = 0;
    stats->money_spent = 0;
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

    Queue *localDoctorQueue = create();     // Patients waiting for the doctor
    Queue *specialistQueue = create();      // Patients waiting for specialists
    Queue *decisionQueue = create();        // Patients waiting for decision resolution

    int total_waiting_time = 0;
    int total_decision_time = 0;
    int total_customers = 0;
    int cured_customers = 0;
    int money_spent = 0;
    int total_local_doctor_visits = 0;
    int total_specialist_visits = 0;
    int total_decision_events = 0;

    for (int time = 0; time < params->simulation_duration; time++) {
        // New patient arrival
        if ((float)rand() / RAND_MAX < params->arrival_probability) {
            enqueue(localDoctorQueue, time);
            total_customers++;
        }

        // Process the decision queue - Patients whose decision time has expired
        while (!is_empty(decisionQueue)) {
            int decisionTime = peek(decisionQueue, NULL);
            if (decisionTime > time) break; // Stop processing if the time has not yet come

            dequeue(decisionQueue, NULL); // Remove patient from decision queue

            // Determine if the patient is cured or redirected
            if ((float)rand() / RAND_MAX < 0.7) {
                enqueue(specialistQueue, time);
            } else {
                cured_customers++;
            }
        }

        // Local doctor decision phase
        if (!is_empty(localDoctorQueue)) {
            bool status = false;
            int arrivalTime = dequeue(localDoctorQueue, &status);

            // Local doctor's decision time
            int decision_time = params->local_doctor_decision_time_from + rand() % 
                                (params->local_doctor_decision_time_to - params->local_doctor_decision_time_from + 1);
            
            total_decision_time += decision_time;
            total_decision_events++;

            money_spent += params->local_doctor_salary;
            total_local_doctor_visits++;

            // Enqueue into decision queue to be processed later
            enqueue(decisionQueue, time + decision_time);
        }

        // Specialist decision phase - Process multiple patients at once
        int specialists_available = params->specialist_count;
        while (!is_empty(specialistQueue) && specialists_available > 0) {
            int arrivalTime = dequeue(specialistQueue, NULL);
            specialists_available--;

            // Specialist's decision time
            int specialist_decision_time = params->specialist_decision_time_from + rand() % 
                                           (params->specialist_decision_time_to - params->specialist_decision_time_from + 1);
            
            total_decision_time += specialist_decision_time;
            total_decision_events++;

            total_waiting_time += time - arrivalTime + specialist_decision_time;

            money_spent += params->specialist_salary;
            total_specialist_visits++;
        }
    }

    // Store stats
    stats->total_customers = total_customers;
    stats->cured_customers = cured_customers;
    stats->average_waiting_time = total_customers > 0 ? total_waiting_time / total_customers : 0;
    stats->total_local_doctor_visits = total_local_doctor_visits;
    stats->total_specialist_visits = total_specialist_visits;
    stats->average_decision_time = total_decision_events > 0 ? total_decision_time / total_decision_events : 0;
    stats->money_spent = money_spent;

    // Print results
    fprintf(output, "Total customers: %d\n", stats->total_customers);
    fprintf(output, "Cured customers: %d\n", stats->cured_customers);
    fprintf(output, "Average waiting time: %d\n", stats->average_waiting_time);
    fprintf(output, "Total local doctor visits: %d\n", stats->total_local_doctor_visits);
    fprintf(output, "Total specialist visits: %d\n", stats->total_specialist_visits);
    fprintf(output, "Average decision time: %d\n", stats->average_decision_time);
    fprintf(output, "Money spent: %d\n", stats->money_spent);

    done(localDoctorQueue);
    done(specialistQueue);
    done(decisionQueue);
}