#ifndef SPACECRAFT_H
#define SPACECRAFT_H

#include <cmath>
#include <iostream>

#include "../header/nled_solver.h"

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
    int setSpeed_rayon(float speed_rayon);
    int setSpeed_theta(float speed_theta);
    int compute_new_position(float t);
    int update_parameters(Nled_solver_arg_init *arg_init);

   private:
    float s_rayon;
    float s_theta;
    float s_speed_theta;
    float s_speed_rayon;
    float s_mass;
};

#endif