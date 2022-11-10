#ifndef NLED_SOLVER_H
#define NLED_SOLVER_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    float ar;
    float at;
    float r0;
    float r1;
    float rp1;
    float tp1;
    float* sol;
} Nled_solver_arg;

#endif