#include <cmath>
#include <iostream>

#include "../header/celestial_body.h"
#include "../header/image.h"
#include "../header/nled_solver.h"
#include "../header/spacecraft.h"

#define MASSE_TERRE 5.972 * pow(10, 24)
#define G 6.674 * pow(10, -11)
using namespace std;

typedef struct force {
    float force_rayon;
    float force_theta;
} Force;

void compute_force(Spacecraft sp, Celestial_body cb, Force* f) {
    float angle_intra = sp.getTheta() - cb.getTheta();
    float distance =
        sqrt(pow(sp.getRayon() - cb.getRayon() * cos(angle_intra), 2) +
             pow(cb.getRayon() * sin(angle_intra), 2));

    float force = -(G * sp.getMass() * cb.getMass()) / pow(distance, 3);

    // projection sur les axes
    f->force_theta = force * (-cb.getRayon() * sin(angle_intra));
    f->force_rayon = force * (sp.getRayon() - cb.getRayon() * cos(angle_intra));
}

Nled_solver_arg_init* init(Spacecraft* sp, Celestial_body cb) {
    Nled_solver_arg_init* args =
        (Nled_solver_arg_init*)malloc(sizeof(Nled_solver_arg_init));

    Force* f = new Force;

    compute_force(*sp, cb, f);

    args->ar = f->force_rayon / sp->getMass();
    args->at = f->force_theta / (sp->getMass());
    args->r1 = sp->getRayon();
    args->rp1 = sp->getSpeed_rayon();
    args->tp1 = sp->getSpeed_theta() / sp->getRayon();

    return args;
}

void pas(Spacecraft* sp, Celestial_body cb, float t, Grid* g) {
    Force* f = new Force;

    Nled_solver_arg_init* args = init(sp, cb);
    nled_solver_init(args, t);
    sp->update_parameters(args);
    free(args);

    // tableau image
    g->r[g->n] = sp->getRayon();
    g->t[g->n] = sp->getTheta();
    g->n++;
}

int main() {
    Celestial_body Lune(1737.4, 0.0123 * MASSE_TERRE);
    Celestial_body Terre(6371000, MASSE_TERRE);

    Spacecraft Apollo(6771000, 0, 50, 8000, 0);

    Celestial_body centre = Terre;
    // image grid
    Grid* g = new Grid;
    g->r = new float[100];
    g->t = new float[100];
    g->n = 0;
    g->width = 512;
    g->height = 512;
    // image grid

    for (int i = 0; i < 100; i++) {
        pas(&Apollo, centre, 100, g);
        cout << Apollo.getRayon() / 1000 << endl;
        cout << Apollo.getTheta() << endl;
    }

    build_traj_image(g);

    // cout << "Speed rayon : " << Apollo.getSpeed_rayon() << endl;
    // cout << "Speed theta : " << Apollo.getSpeed_theta() << endl;
    // cout << "altitude : " << Apollo.getRayon() / 1000 << endl;

    return 0;
}
