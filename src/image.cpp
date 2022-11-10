#include "../header/image.h"

#include "../src/lib/EasyBMP.hpp"

using namespace std;

int build_traj_image(Grid* g) {
    EasyBMP::Image img(g->height, g->width, "sample.bmp",
                       EasyBMP::RGBColor(0, 0, 0));

    for (int k = 0; k < g->n; k++) {
        float rayon = g->r[k] / 100000;
        float theta = g->t[k];

        int j = (int)(g->height / 2 + rayon * sin(theta));
        int i = (int)(g->width / 2 + rayon * cos(theta));

        img.SetPixel(i, j, EasyBMP::RGBColor(255, 255, 255));
    }

    img.SetPixel(g->height / 2, g->width / 2, EasyBMP::RGBColor(255, 0, 0));

    img.Write();

    return 0;
}
