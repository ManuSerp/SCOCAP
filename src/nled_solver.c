#include "../header/nled_solver.h"

// Function: nled_solver

float cal_thetap(float at, float* tp, float* r, float* rp, int i, float h) {
    float tpp = (at - 2 * rp[i] * tp[i]) / r[i];
    float next_thetap = tpp * h + tp[i];
    return next_thetap;
}

float cal_rp(float ar, float* tp, float* r, float* rp, int i, float h) {
    return h * (ar + r[i] * pow(tp[i], 2)) + rp[i];
}
float cal_r(float* r, float* rp, int i, float h) { return h * rp[i] + r[i]; }

float cal_t(float* tp, float* t, int i, float h) { return h * tp[i] + t[i]; }

void print_array(float* array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%f ", array[i]);
    }
    printf("\n");
}

void nled_solver_init(Nled_solver_arg_init* arg, float h) {
    float* thetap = (float*)malloc(sizeof(float) * GROUP_SIZE);
    float* theta = (float*)malloc(sizeof(float) * GROUP_SIZE);
    float* r = (float*)malloc(sizeof(float) * GROUP_SIZE);
    float* rp = (float*)malloc(sizeof(float) * GROUP_SIZE);
    r[0] = arg->r1;
    rp[0] = arg->rp1;
    thetap[0] = arg->tp1;
    theta[0] = arg->t1;

    for (int i = 0; i < GROUP_SIZE; i++) {
        thetap[i + 1] = cal_thetap(arg->at, thetap, r, rp, i, h);
        rp[i + 1] = cal_rp(arg->ar, thetap, r, rp, i, h);
        r[i + 1] = cal_r(r, rp, i, h);
        theta[i + 1] = cal_t(thetap, theta, i, h);
    }

    arg->r = r;
    arg->rp = rp;
    arg->thetap = thetap;
    arg->theta = theta;

    // printf("thetap: ");
    // print_array(thetap, GROUP_SIZE);
    // printf("r: ");
    // print_array(r, GROUP_SIZE);
    // printf("rp: ");
    // print_array(rp, GROUP_SIZE);
}