#ifndef CLINIC_H
#define CLINIC_H

#include "queue.h"
#include <stdio.h>

typedef struct {
    float arrival_probability;  // Pacientų atvykimo tikimybė per laiko vienetą
    int simulation_duration;    // Simuliacijos trukmė (laiko vienetai)
    int local_doctor_count;     // Apylinkės gydytojų skaičius
    int specialist_count;       // Specialistų skaičius
    int local_doctor_salary;    // Apylinkės gydytojo atlyginimas
    int specialist_salary;      // Specialisto atlyginimas
    int local_doctor_decision_min; // Apylinkės gyd. sprendimo laiko ribos
    int local_doctor_decision_max;
    int specialist_decision_min;   // Specialisto sprendimo laiko ribos
    int specialist_decision_max;
    float prob_cured_directly;  // Tikimybė, kad pacientas pagydomas iškart
    float prob_referred;        // Tikimybė, kad pacientas siunčiamas pas kitą specialistą
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
void runSimulation(SimulationParams *params, SimulationStats *stats, FILE *output);
void runDefaultTest();
void runCustomTest(int plates, int eat_min, int eat_max, float prob, int wash, int duration);
void readParams(SimulationParams *params, FILE *input);

#endif
