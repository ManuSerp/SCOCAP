#include "../header/image.h"

using namespace std;

int build_traj_image(Grid* g) {
    EasyBMP::Image img(512, 512, "sample.bmp", EasyBMP::RGBColor(0, 0, 0));

    img.SetPixel(0, 0, EasyBMP::RGBColor(255, 0, 0));

    img.Write();

    return 0;
}
