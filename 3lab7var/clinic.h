#ifndef CLINIC_H
#define CLINIC_H

#include "queue.h"
#include <stdio.h>

typedef struct {
    float arrival_probability;
    int simulation_duration;
    int specialist_count;
    int local_doctor_salary;
    int specialist_salary;
    int local_doctor_decision_time_from;
    int local_doctor_decision_time_to;
    int specialist_decision_time_from;
    int specialist_decision_time_to;
} SimulationParams;

typedef struct {
    int total_customers;
    int cured_customers;
    int average_waiting_time;
    int total_local_doctor_visits;
    int total_specialist_visits;
    int average_decision_time;
    int money_spent;
} SimulationStats;

void initParams(SimulationParams *params);
void initStats(SimulationStats *stats);
void freeStats(SimulationStats *stats);
void runSimulation(SimulationParams *params, SimulationStats *stats, FILE *output);
void runDefaultTest();
void runCustomTest(int plates, int eat_min, int eat_max, float prob, int wash, int duration);
void readParams(SimulationParams *params, FILE *input);

#endif
