#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <vector>

#include "../src/lib/EasyBMP.hpp"

typedef struct {
    float* r;
    float* t;
    int n;
    int width;
    int height;
} Grid;

int build_traj_image(Grid* g);

#endif