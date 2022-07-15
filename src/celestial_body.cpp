#include "../header/celestial_body.h"
using namespace std;

Celestial_body::Celestial_body(float rayon, float mass)
    : s_rayon(rayon), s_mass(mass) {}

float Celestial_body::getRayon() { return (s_rayon); }

float Celestial_body::getAngle() { return s_angle; }

float Celestial_body::getDistance() { return s_distance; }

float Celestial_body::getSpeed() { return s_speed; }

float Celestial_body::getMass() { return s_mass; }