#include "edge_roberts.h"

EdgeRoberts::EdgeRoberts(PNM* img) :
    EdgeGradient(img)
{
    prepareMatrices();
}

EdgeRoberts::EdgeRoberts(PNM* img, ImageViewer* iv) :
    EdgeGradient(img, iv)
{
    prepareMatrices();
}

void EdgeRoberts::prepareMatrices()
{
	math::matrix<double> gx(2,2);
	math::matrix<double> gy(2,2);

	gx(0,0) = 1;
	gx(0,1) = 0;
	gx(1,0) = 0;
	gx(1,1) = -1;

	gy(0,0) = 0;
	gy(0,1) = 1;
	gy(1,0) = -1;
	gy(1,1) = 0;

	g_x = gx;
	g_y = gy;
}
