#ifndef NLED_SOLVER_H
#define NLED_SOLVER_H

#define GROUP_SIZE 11

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    float ar;
    float at;
    float r1;
    float rp1;
    float tp1;
    float* r;
    float* rp;
    float* thetap;
} Nled_solver_arg_init;

void nled_solver_init(Nled_solver_arg_init* arg, float h);
void print_array(float* array, int size);

#endif