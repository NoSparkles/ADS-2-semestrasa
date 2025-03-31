#ifndef FN_SET_H
#define FN_SET_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

int **solve_n_bishops(int n, int timeout);

unsigned long long factorial(int num);

unsigned long long combination(int n, int k);

void handle_timeout(unsigned long long completed_iterations, unsigned long long total_iterations);

#endif // FN_SET_H