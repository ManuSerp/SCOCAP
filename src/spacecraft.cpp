#include "../header/spacecraft.h"
using namespace std;

Spacecraft::Spacecraft() : s_rayon(0), s_mass(0) {}

Spacecraft::Spacecraft(float rayon, float theta, float mass, float speed_theta,
                       float speed_rayon)
    : s_rayon(rayon),
      s_theta(theta),
      s_mass(mass),
      s_speed_theta(speed_theta),
      s_speed_rayon(speed_rayon) {}

Spacecraft::Spacecraft(int rayon, int theta, int mass, int speed_theta,
                       int speed_rayon)
    : s_rayon((float)rayon),
      s_theta((float)theta),
      s_mass((float)mass),
      s_speed_theta((float)speed_theta),
      s_speed_rayon((float)speed_rayon) {}

float Spacecraft::getRayon() { return (s_rayon); }

float Spacecraft::getTheta() { return (s_theta); }

float Spacecraft::getSpeed_rayon() { return (s_speed_rayon); }

float Spacecraft::getSpeed_theta() { return (s_speed_theta); }

float Spacecraft::getMass() { return (s_mass); }

int Spacecraft::setSpeed_rayon(float speed_rayon) {
    s_speed_rayon = speed_rayon;
    return 0;
}

int Spacecraft::setSpeed_theta(float speed_theta) {
    s_speed_theta = speed_theta;
    return 0;
}

int Spacecraft::compute_new_position() {
    s_theta += s_speed_theta;
    s_rayon += s_speed_rayon;
    return 0;
}
