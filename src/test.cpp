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

void compute_force(Spacecraft sp, Celestial_body** cb_list, Force* f) {
    for (int i = 1; i < (int)cb_list[0]; i++) {
        Force* f_temp = new Force;
        float angle_intra = sp.getTheta() - (*cb_list[i]).getTheta();
        float distance = sqrt(
            pow(sp.getRayon() - (*cb_list[i]).getRayon() * cos(angle_intra),
                2) +
            pow((*cb_list[i]).getRayon() * sin(angle_intra), 2));

        float force =
            -(G * sp.getMass() * (*cb_list[i]).getMass()) / pow(distance, 3);

        // projection sur les axes
        f_temp->force_theta =
            force * (-(*cb_list[i]).getRayon() * sin(angle_intra));
        f_temp->force_rayon =
            force *
            (sp.getRayon() - (*cb_list[i]).getRayon() * cos(angle_intra));
        f->force_rayon += f_temp->force_rayon;
        f->force_theta += f_temp->force_theta;
    }
}

Nled_solver_arg_init* init(Spacecraft* sp, Celestial_body** cb_list) {
    Nled_solver_arg_init* args =
        (Nled_solver_arg_init*)malloc(sizeof(Nled_solver_arg_init));

    Force* f = new Force;

    compute_force(*sp, cb_list, f);

    args->ar = f->force_rayon / sp->getMass();
    args->at = f->force_theta / (sp->getMass());
    args->r1 = sp->getRayon();
    args->rp1 = sp->getSpeed_rayon();
    args->tp1 = sp->getSpeed_theta() / sp->getRayon();
    args->t1 = sp->getTheta();

    return args;
}

void pas(Spacecraft* sp, Celestial_body** cb_list, float t,
         Grid* g) {  // a cb list as len on [0]
    Force* f = new Force;

    Nled_solver_arg_init* args = init(sp, cb_list);
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

    Celestial_body** cb_list = init_cb_list(2);
    cb_list[1] = &centre;
    // image grid
    Grid* g = new Grid;
    g->r = new float[100000];
    g->t = new float[100000];
    g->n = 0;
    g->width = 512;
    g->height = 512;
    // image grid

    for (int i = 0; i < 1000; i++) {
        cout << "i = " << i << endl;

        pas(&Apollo, cb_list, 0.1,
            g);  // 0.1 seconde par pas du solveur numérique soit GROUPESIZE*0.1
                 // secondes par pas ici
        cout << "rayon = " << Apollo.getRayon() / 1000 << endl;
        cout << "theta = " << Apollo.getTheta() << endl;
        cout << "speed_rayon = " << Apollo.getSpeed_rayon() << endl;
        cout << "speed_theta = " << Apollo.getSpeed_theta() << endl;
    }

    build_traj_image(g);

    // cout << "Speed rayon : " << Apollo.getSpeed_rayon() << endl;
    // cout << "Speed theta : " << Apollo.getSpeed_theta() << endl;
    // cout << "altitude : " << Apollo.getRayon() / 1000 << endl;

    return 0;
}
