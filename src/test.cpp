#include <cmath>

#include "../header/celestial_body.h"
#include "../header/spacecraft.h"
#define MASSE_TERRE 5.972
#define E_TERRE 24
#define G 6.674 * pow(10, -11)
using namespace std;

typedef struct force {
    float force_rayon;
    float force_theta;
} Force;

void compute_force(Spacecraft sp, Celestial_body cb, Force *f) {
    float distance = sqrt(pow(sp.getRayon() - cb.getRayon(), 2) +
                          pow(sp.getTheta() - cb.getTheta(), 2));
    float force = (G * sp.getMass() * cb.getMass()) / pow(distance, 2);
    f->force_theta = force * (sp.getTheta() - cb.getTheta()) / distance;
    f->force_rayon = force * (sp.getRayon() - cb.getRayon()) / distance;
}

void compute(Spacecraft sp, Celestial_body cb) {
    float force = compute_force(sp, cb);
    float acceleration = force / sp.getMass();
    float speed = sp.getSpeed_rayon() + acceleration;
    float rayon = sp.getRayon() + speed;
    sp.setRayon(rayon);
    sp.setSpeed_rayon(speed);
}

int main() {
    Celestial_body Lune(1737.4, 0.0123);
    Celestial_body Terre(6371, 1);

    Spacecraft Apollo(10000, 0, 50, 50, 50);

    Celestial_body centre = Terre;

    return 0;
}
