#include "map_normal.h"

#include "edge_sobel.h"
#include "map_height.h"

MapNormal::MapNormal(PNM* img) :
    Convolution(img)
{
}

MapNormal::MapNormal(PNM* img, ImageViewer* iv) :
    Convolution(img, iv)
{
}

PNM* MapNormal::transform()
{
    int width  = image->width(),
        height = image->height();

    double strength = getParameter("strength").toDouble();

    PNM* newImage = new PNM(width, height, image->format());

    PNM* tempImage = MapHeight(image).transform();
    EdgeSobel sobel(tempImage);
    math::matrix<double>* Gx = sobel.rawHorizontalDetection();
    math::matrix<double>* Gy = sobel.rawVerticalDetection();

    newImage = new PNM(width, height, QImage::Format_RGB32);
    double dz = 1 / strength;
    for (int x=0; x<width; x++)
	{
        for (int y=0; y<height; y++)
		{
            double dx = (*Gx)(x,y) / PIXEL_VAL_MAX;
            double dy = (*Gy)(x,y) / PIXEL_VAL_MAX;
            double length = sqrt(dx * dx + dy * dy + dz * dz);
            dx /= length;
            dy /= length;
            double dzz = dz / length;
            dx = (dx + 1.0) * (255 / strength);
            dy = (dy + 1.0) * (255 / strength);
            dzz = (dzz + 1.0) * (255 / strength);
            newImage->setPixel(x, y, qRgb(dx, dy, dzz));
        }
    }

    return newImage;
}
