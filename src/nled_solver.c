#include "../header/nled_solver.h"

// Function: nled_solver

float cal_thetap(float at, float* t, float* r, float* rp, int i, float h) {
    float tpp = (at - 2 * rp[i] * t[i]) / r[i];
    float next_thetap = tpp * h + t[i];
    return next_thetap;
}

float cal_rp(float ar, float* t, float* r, float* rp, int i, float h) {
    return h * (ar + r[i] * pow(t[i], 2)) + rp[i];
}
float cal_r(float* t, float* r, float* rp, int i, float h) {
    return h * rp[i] + r[i];
}

void print_array(float* array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%f ", array[i]);
    }
    printf("\n");
}

void nled_solver_init(Nled_solver_arg_init* arg, float h) {
    float* thetap = (float*)malloc(sizeof(float) * 12);
    float* r = (float*)malloc(sizeof(float) * 12);
    float* rp = (float*)malloc(sizeof(float) * 12);
    r[1] = arg->r1;
    rp[1] = arg->rp1;
    thetap[1] = arg->tp1;

    for (int i = 1; i < 12; i++) {
        thetap[i + 1] = cal_thetap(arg->at, thetap, r, rp, i, h);
        rp[i + 1] = cal_rp(arg->ar, thetap, r, rp, i, h);
        r[i + 1] = cal_r(thetap, r, rp, i, h);
    }

    arg->r = r;
    arg->rp = rp;
    arg->thetap = thetap;

    printf("thetap: ");
    print_array(thetap, 12);
    printf("r: ");
    print_array(r, 12);
    printf("rp: ");
    print_array(rp, 12);
}