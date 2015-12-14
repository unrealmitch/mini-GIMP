#include "bin_gradient.h"

/**
 * @brief BinarizationGradient::BinarizationGradient
 * @author Miguel Caballero
 * @param img
 */

BinarizationGradient::BinarizationGradient(PNM* img) :
    Transformation(img)
{
}

BinarizationGradient::BinarizationGradient(PNM* img, ImageViewer* iv) :
    Transformation(img, iv)
{
}

PNM* BinarizationGradient::transform()
{
    int width = image->width();
    int height = image->height();
    int numerator = 0;
    int denominator = 0;

    PNM* newImage = new PNM(width, height, QImage::Format_Mono);

    // Iterate over image space for calculating threshold
    for (int x=0; x<width; x++)
        for (int y=0; y<height; y++)
        {
            int v = qGray(image->pixel(x,y));    // Get the 0-255 value of the L channel
            int G, Gx, Gy;

            if(x==0 && y!=0)
            {
                Gx = qGray(image->pixel(x+1,y)); // Getting gradient Gx
                Gy = qGray(image->pixel(x,y+1)) - qGray(image->pixel(x,y-1)); // Getting gradient Gy
            }
            else if(x==0 && y==0)
            {
                Gx = qGray(image->pixel(x+1,y)); // Getting gradient Gx
                Gy = qGray(image->pixel(x,y+1)); // Getting gradient Gy
            }
            else if(y==0 && x!=0)
            {
                Gx = qGray(image->pixel(x+1,y)) - qGray(image->pixel(x-1,y)); // Getting gradient Gx
                Gy = qGray(image->pixel(x,y+1)); // Getting gradient Gy
            }
            else if(x==width-1 && y!=height-1)
            {
                Gx = qGray(image->pixel(x-1,y)); // Getting gradient Gx
                Gy = qGray(image->pixel(x,y+1)) - qGray(image->pixel(x,y-1)); // Getting gradient Gy
            }
            else if(x==width-1 && y==height-1)
            {
                Gx = qGray(image->pixel(x-1,y)); // Getting gradient Gx
                Gy = qGray(image->pixel(x,y-1)); // Getting gradient Gy
            }
            else if(y==height-1 && x!=width-1)
            {
                Gx = qGray(image->pixel(x+1,y)) - qGray(image->pixel(x-1,y)); // Getting gradient Gx
                Gy = qGray(image->pixel(x,y-1)); // Getting gradient Gy
            }
            else
            {
                Gx = qGray(image->pixel(x+1,y)) - qGray(image->pixel(x-1,y)); // Getting gradient Gx
                Gy = qGray(image->pixel(x,y+1)) - qGray(image->pixel(x,y-1)); // Getting gradient Gy
            }

            G = Gx >= Gy ? Gx : Gy;

            numerator += v * G;
            denominator += G;
        }

    //Once we ended calculating threshold we create the variable and we aplied for filtering
    int threshold = numerator/denominator;

    // Iterate over image space for aplying filter
    for (int x=0; x<width; x++)
        for (int y=0; y<height; y++)
        {
            QRgb pixel = image->pixel(x,y); // Getting the pixel(x,y) value
            QRgb black = 0;
            QRgb white = 1;

            int v = qGray(pixel);    // Get the 0-255 value of the L channel

            newImage->setPixel(x,y, v < threshold ? black : white);
        }

    return newImage;
}

