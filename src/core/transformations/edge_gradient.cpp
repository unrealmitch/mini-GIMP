#include "edge_gradient.h"

EdgeGradient::EdgeGradient(PNM* img, ImageViewer* iv) :
    Convolution(img, iv)
{
}

EdgeGradient::EdgeGradient(PNM* img) :
    Convolution(img)
{
}

PNM* EdgeGradient::verticalDetection()
{
    return convolute(g_y, RepeatEdge);
}

PNM* EdgeGradient::horizontalDetection()
{
    return convolute(g_x, RepeatEdge);
}

PNM* EdgeGradient::transform()
{
    PNM* newImage = new PNM(image->width(), image->height(), image->format());
    
	// Getting the dimensions
    int width  = image->width();
    int height = image->height();
	PNM* xImage = horizontalDetection();
	PNM* yImage = verticalDetection();

	if (image->format() == QImage::Format_Indexed8)
	{
		for (int x=0; x<width; x++)
		{	
			for (int y=0; y<height; y++)
			{
				QRgb xPixel = xImage->pixel(x, y);
				QRgb yPixel = yImage->pixel(x, y);
				int qx = qGray(xPixel);
				int qy = qGray(yPixel);
				int q = (int) sqrt(qx * qx + qy * qy);
				newImage->setPixel(x, y, q);
			}
		}
	}
	else
	{
		for (int x=0; x<width; x++)
		{	
			for (int y=0; y<height; y++)
			{
				QRgb xPixel = xImage->pixel(x, y);
				QRgb yPixel = yImage->pixel(x, y);
                int rx = qRed(xPixel);
                int gx = qGreen(xPixel);
                int bx = qBlue(xPixel);
                int ry = qRed(yPixel);
                int gy = qGreen(yPixel);
                int by = qBlue(yPixel);
				int r = (int) sqrt(rx * rx + ry * ry);
				int g = (int) sqrt(gx * gx + gy * gy);
				int b = (int) sqrt(bx * bx + by * by);
				QColor newPixel = QColor(r,g,b);
				newImage->setPixel(x, y, newPixel.rgb());
			}
		}
	}

    return newImage;
}

