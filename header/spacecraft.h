#ifndef SPACECRAFT_H
#define SPACECRAFT_H

#include <iostream>

class Spacecraft {
   public:
    Spacecraft(float rayon, float theta, float mass, float speed_theta,
               float speed_rayon);

    Spacecraft(int rayon, int theta, int mass, int speed_theta,
               int speed_rayon);

    Spacecraft();

    float getRayon();
    float getTheta();
    float getSpeed_theta();
    float getSpeed_rayon();
    float getMass();

   private:
    float s_rayon;
    float s_theta;
    float s_speed_theta;
    float s_speed_rayon;
    float s_mass;
};

#endif