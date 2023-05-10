#include "../header/celestial_body.h"
using namespace std;

Celestial_body::Celestial_body(float rayon, float mass)
    : s_astre_rayon(rayon),
      s_mass(mass),
      s_angle(0),
      s_distance(0),
      s_speed(0) {}


Celestial_body::Celestial_body(float rayon, float mass,float theta, float pos_rayon)
    : s_astre_rayon(rayon),
      s_mass(mass),
      s_angle(theta),
      s_rayon(pos_rayon),
      s_speed(0) {}


float Celestial_body::getRayon() { return (s_rayon); }

float Celestial_body::getAstre_rayon() { return (s_astre_rayon); }

float Celestial_body::getTheta() { return s_angle; }

float Celestial_body::getDistance() { return s_distance; }

float Celestial_body::getSpeed() { return s_speed; }

float Celestial_body::getMass() { return s_mass; }

void Celestial_body::update() { s_angle += s_speed; }

Celestial_body** init_cb_list(int len) {
    Celestial_body** cb_list =
        (Celestial_body**)malloc(sizeof(Celestial_body*) * (len + 1));
    cb_list[0] = (Celestial_body*)len;
    return cb_list;
}