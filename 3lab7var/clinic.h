#ifndef CLINIC_H
#define CLINIC_H

#include "queue.h"
#include <stdio.h>

typedef struct {
    float arrival_probability;
    int simulation_duration;
    int local_doctor_count;
    int specialist_count;
    int local_doctor_salary;
    int specialist_salary;
    int local_doctor_decision_min;
    int local_doctor_decision_max;
    int specialist_decision_min;
    int specialist_decision_max;
    float prob_cured_directly;
    float prob_referred;
} SimulationParams;

typedef struct {
    int total_patients;
    int cured_patients;
    int total_waiting_time;
    double average_waiting_time;
    int total_local_doctor_visits;
    int total_specialist_visits;
    int total_cost;
} SimulationStats;


void initParams(SimulationParams *params);
void initStats(SimulationStats *stats);
void freeStats(SimulationStats *stats);
void runSimulation(SimulationParams *params, SimulationStats *stats, FILE *output, int randomNumber);
void readParams(SimulationParams *params, FILE *input);

#endif
