#include "map_horizon.h"

#include "map_height.h"

MapHorizon::MapHorizon(PNM* img) :
    Transformation(img)
{
}

MapHorizon::MapHorizon(PNM* img, ImageViewer* iv) :
    Transformation(img, iv)
{
}

PNM* MapHorizon::transform()
{
    int width  = image->width(),
        height = image->height();

    double scale     = getParameter("scale").toDouble();
    int    sunAlpha = getParameter("alpha").toInt();
    int dx, dy;

    switch (getParameter("direction").toInt())
    {
    case NORTH: dx = 0; dy = -1; break;
    case SOUTH: dx = 0; dy = 1; break;
    case EAST:  dx = 1; dy = 0; break;
    case WEST:  dx = -1; dy = 0; break;
    default:
        qWarning() << "Unknown direction!";
        dx =  0;
        dy = -1;
    }

    PNM* newImage = new PNM(width, height, QImage::Format_Indexed8);

    PNM* mapHeight = MapHeight(image).transform();
    for (int x=0; x<width; x++)
	{
        for (int y=0; y<height; y++)
		{
            double alpha = 0.0;
            int currH = qRed(mapHeight->pixel(x,y));
            for (int k=x+dx, l=y+dy; k < width && l < height && k >= 0 && l >= 0; k += dx, l += dy)
            {
                int rayH = qRed(mapHeight->pixel(k,l));
                if (currH < rayH)
				{
                    double dist = sqrt(pow(k - x, 2) + pow(l - y, 2)) * scale;
                    double rayAlpha = atan((rayH - currH) / dist) * 180./3.14;
                    if(rayAlpha > alpha)  alpha = rayAlpha;
                }
            }
            double delta = alpha - sunAlpha;
            if (delta <= 0) newImage->setPixel(x, y, 255);
            else newImage->setPixel(x, y, cos(delta * 3.14/180.) * 255);
        }
    }

    return newImage;
}

