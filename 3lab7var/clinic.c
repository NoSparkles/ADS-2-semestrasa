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

    Queue *localDoctorQueue = create();
    Queue *specialistQueue = create();
    Queue *decisionQueue = create();

    int availableSpecialists = params->specialist_count;

    int totalWaitingTime = 0;
    int totalDecisionTime = 0;
    int decisionEvents = 0;

    stats->total_customers = 0;
    stats->cured_customers = 0;
    stats->money_spent = 0;
    stats->total_local_doctor_visits = 0;
    stats->total_specialist_visits = 0;

    for (int time = 0; time < params->simulation_duration; time++) {
        // 1. New patient arrival
        if ((float)rand() / RAND_MAX < params->arrival_probability) {
            enqueue(localDoctorQueue, time);
            stats->total_customers++;
        }

        // 2. Handle patients in decision queue
        while (!is_empty(decisionQueue)) {
            int decisionTime = peek(decisionQueue, NULL);
            if (decisionTime > time) break;

            dequeue(decisionQueue, NULL);
            if ((float)rand() / RAND_MAX < 0.7f) {
                enqueue(specialistQueue, time);
            } else {
                stats->cured_customers++;
            }
        }

        // 3. Local doctor processes one patient
        if (!is_empty(localDoctorQueue)) {
            int arrivalTime = dequeue(localDoctorQueue, NULL);
            int decisionTime = params->local_doctor_decision_time_from +
                               rand() % (params->local_doctor_decision_time_to - params->local_doctor_decision_time_from + 1);

            enqueue(decisionQueue, time + decisionTime);

            stats->total_local_doctor_visits++;
            stats->money_spent += params->local_doctor_salary;

            totalDecisionTime += decisionTime;
            decisionEvents++;
        }

        // 4. Specialists process multiple patients (up to available count)
        int specialistsWorking = 0;
        while (!is_empty(specialistQueue) && specialistsWorking < availableSpecialists) {
            int arrivalTime = dequeue(specialistQueue, NULL);
            int decisionTime = params->specialist_decision_time_from +
                               rand() % (params->specialist_decision_time_to - params->specialist_decision_time_from + 1);

            totalWaitingTime += (time - arrivalTime + decisionTime);

            stats->total_specialist_visits++;
            stats->money_spent += params->specialist_salary;

            totalDecisionTime += decisionTime;
            decisionEvents++;
            specialistsWorking++;
        }
    }

    stats->average_waiting_time = stats->total_customers > 0 ? totalWaitingTime / stats->total_customers : 0;
    stats->average_decision_time = decisionEvents > 0 ? totalDecisionTime / decisionEvents : 0;

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
