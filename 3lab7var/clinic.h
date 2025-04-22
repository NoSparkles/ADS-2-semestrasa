#ifndef CAFETERIA_H
#define CAFETERIA_H

#include "longNum.h"
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
    LongNum *total_customers;
    LongNum *average_waiting_time;
    LongNum *total_local_doctor_visits;
    LongNum *total_specialist_visits;
    LongNum *max_waiting_time;
    LongNum *min_waiting_time;
} SimulationStats;

void initParams(SimulationParams *params);
void initStats(SimulationStats *stats);
void freeStats(SimulationStats *stats);
void runSimulation(SimulationParams *params, SimulationStats *stats, FILE *output);
void runDefaultTest();
void runCustomTest(int plates, int eat_min, int eat_max, float prob, int wash, int duration);
void readParams(SimulationParams *params, FILE *input);

#endif
