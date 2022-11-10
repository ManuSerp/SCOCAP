#include <cmath>
#include <iostream>

#include "../header/celestial_body.h"
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

int main() {
    Celestial_body Lune(1737.4, 0.0123 * MASSE_TERRE);
    Celestial_body Terre(6371000, MASSE_TERRE);

    Spacecraft Apollo(6771000, 0, 50, 8000, 0);

    Celestial_body centre = Terre;
    Force* f = new Force;

    Nled_solver_arg_init* args = init(&Apollo, centre);
    nled_solver_init(args, 100);
    Apollo.update_parameters(args);

    cout << "Speed rayon : " << Apollo.getSpeed_rayon() << endl;
    cout << "Speed theta : " << Apollo.getSpeed_theta() << endl;
    cout << "altitude : " << Apollo.getRayon() / 1000 << endl;

    printf("thetap: ");
    print_array(args->thetap, GROUP_SIZE);
    printf("r: ");
    print_array(args->r, GROUP_SIZE);
    printf("rp: ");
    print_array(args->rp, GROUP_SIZE);

    return 0;
}
