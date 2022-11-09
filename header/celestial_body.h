#ifndef CELESTIAL_BODY_H
#define CELESTIAL_BODY_H

#include <iostream>

class Celestial_body {
    // the sun is taken as origin of the repere and the referentiel, all
    // celestial bodies are placed in the solar system plan and refered in
    // circular coordinates
   public:
    Celestial_body(float rayon, float mass);
    float getRayon();
    float getAstre_rayon();
    float getTheta();
    float getDistance();
    float getSpeed();
    float getMass();

   private:
    float s_astre_rayon;
    float s_rayon;
    float s_angle;
    float s_distance;
    float s_speed;
    float s_mass;
};

#endif