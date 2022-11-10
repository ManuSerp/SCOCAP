#include "../header/nled_solver.h"

// Function: nled_solver

float cal_thetap(float at, float* t, float* r, float* rp, int i, float h) {
    float tpp = (at - 2 * rp[i] * t[i]) / r[i];
    return tpp;
}

void nled_solver(Nled_solver_arg* arg, float h) {
    float* thetap = malloc(sizeof(float) * 12);
    float* r = malloc(sizeof(float) * 12);
    float* rp = malloc(sizeof(float) * 12);
    r[0] = arg->r0;
    r[1] = arg->r1;
    rp[1] = arg->rp1;
    thetap[1] = arg->tp1;

    for (int i = 1; i < 12; i++) {
        thetap[i + 1] = cal_thetap(arg->at, thetap, r, rp, i, h);
        r[i + 1] = cal_r(r, i);
    }
}