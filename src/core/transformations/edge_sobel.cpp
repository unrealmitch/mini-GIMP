#include "edge_sobel.h"

EdgeSobel::EdgeSobel(PNM* img, ImageViewer* iv) :
    EdgeGradient(img, iv)
{
    prepareMatrices();
}

EdgeSobel::EdgeSobel(PNM* img) :
    EdgeGradient(img)
{
    prepareMatrices();
}

void EdgeSobel::prepareMatrices()
{
	math::matrix<double> gx(3,3);
	math::matrix<double> gy(3,3);

	gx(0,0) = -1;
	gx(0,1) = 0;
	gx(0,2) = 1;
	gx(1,0) = -2;
	gx(1,1) = 0;
	gx(1,2) = 2;
	gx(2,0) = -1;
	gx(2,1) = 0;
	gx(2,2) = 1;

	gy(0,0) = -1;
	gy(0,1) = -2;
	gy(0,2) = -1;
	gy(1,0) = 0;
	gy(1,1) = 0;
	gy(1,2) = 0;
	gy(2,0) = 1;
	gy(2,1) = 2;
	gy(2,2) = 1;

	g_x = gx;
	g_y = gy;
}

math::matrix<double>* EdgeSobel::rawHorizontalDetection()
{
	math::matrix<double>* x_gradient = new math::matrix<double>(this->image->width(), this->image->height());

	int width = x_gradient->RowNo();
	int height = x_gradient->ColNo();

	for (int x=0; x<width; x++)
	{	
		for (int y=0; y<height; y++)
		{
			math::matrix<double> window = getWindow(x, y, 3, LChannel, NullEdge);
			(*x_gradient)(x, y) = sum(join(g_x, window));
		}
    }

    return x_gradient;
}

math::matrix<double>* EdgeSobel::rawVerticalDetection()
{
    math::matrix<double>* y_gradient = new  math::matrix<double>(this->image->width(), this->image->height());

	int width = y_gradient->RowNo();
	int height = y_gradient->ColNo();

	for (int x=0; x<width; x++)
	{	
		for (int y=0; y<height; y++)
		{
			math::matrix<double> window = getWindow(x, y, 3, LChannel, NullEdge);
			(*y_gradient)(x, y) = sum(join(g_y, window));
		}
    }

    return y_gradient;
}

