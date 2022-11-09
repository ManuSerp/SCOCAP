#include <cmath>
#include <iostream>

#include "../header/celestial_body.h"
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

    float force = (G * sp.getMass() * cb.getMass()) / pow(distance, 3);

    // projection sur les axes
    f->force_theta = force * (-cb.getRayon() * (angle_intra));
    f->force_rayon = force * (sp.getRayon() - cb.getRayon() * cos(angle_intra));
}

void compute(Spacecraft* sp, Celestial_body cb, float t) {
    Force* f = new Force;
    compute_force(*sp, cb, f);
    cout << "Force rayon : " << f->force_rayon << endl;
    cout << "Force theta : " << f->force_theta << endl;
    float ardt = t * f->force_rayon / sp->getMass();
    cout << "ardt = " << ardt << endl;
    float athetadt = t * f->force_theta / (sp->getMass() * sp->getRayon());
    cout << "athetadt = " << athetadt << endl;

    sp->setSpeed_rayon(sp->getSpeed_rayon() + ardt);
    sp->setSpeed_theta(sp->getSpeed_theta() + athetadt);
}

int main() {
    Celestial_body Lune(1737.4, 0.0123 * MASSE_TERRE);
    Celestial_body Terre(6371, MASSE_TERRE);

    Spacecraft Apollo(10000, 0, 50, 0, 0);

    Celestial_body centre = Terre;
    Force* f = new Force;

    compute(&Apollo, centre, 1);
    cout << "Speed rayon : " << Apollo.getSpeed_rayon() << endl;
    cout << "Speed theta : " << Apollo.getSpeed_theta() << endl;

    return 0;
}
