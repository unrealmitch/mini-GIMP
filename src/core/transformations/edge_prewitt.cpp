#include "edge_prewitt.h"

EdgePrewitt::EdgePrewitt(PNM*img) :
    EdgeGradient(img)
{
    prepareMatrices();
}

EdgePrewitt::EdgePrewitt(PNM*img, ImageViewer* iv) :
    EdgeGradient(img, iv)
{
    prepareMatrices();
}

void EdgePrewitt::prepareMatrices()
{
    math::matrix<double> gx(3,3);
    math::matrix<double> gy(3,3);

    gx(0,0) = -1;
    gx(0,1) = 0;
    gx(0,2) = 1;
    gx(1,0) = -1;
    gx(1,1) = 0;
    gx(1,2) = 1;
    gx(2,0) = -1;
    gx(2,1) = 0;
    gx(2,2) = 1;

    gy(0,0) = -1;
    gy(0,1) = -1;
    gy(0,2) = -1;
    gy(1,0) = 0;
    gy(1,1) = 0;
    gy(1,2) = 0;
    gy(2,0) = 1;
    gy(2,1) = 1;
    gy(2,2) = 1;

    g_x = gx;
    g_y = gy;
}
