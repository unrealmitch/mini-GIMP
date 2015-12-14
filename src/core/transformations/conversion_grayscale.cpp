/**
 * @brief ConversionGrayscale::ConversionGrayscale
 * @author Miguel Caballero
 * @param img
 */

#include "conversion_grayscale.h"

ConversionGrayscale::ConversionGrayscale(PNM* img) :
    Transformation(img)
{
}

ConversionGrayscale::ConversionGrayscale(PNM* img, ImageViewer* iv) :
    Transformation(img, iv)
{
}

PNM* ConversionGrayscale::transform()
{
    int width = image->width();
    int height = image->height();

    PNM* newImage = new PNM(width, height, QImage::Format_Indexed8);

    if (image->format() == QImage::Format_Mono)
    {
        qDebug() << Q_FUNC_INFO << "Not implemented yet!";
    }
    else // if (image->format() == QImage::Format_RGB32)
    {
        // Iterate over image space
        for (int x=0; x<width; x++)
            for (int y=0; y<height; y++)
            {
                QRgb pixel = image->pixel(x,y); // Getting the pixel(x,y) value

                int r = qRed(pixel);    // Get the 0-255 value of the R channel
                int g = qGreen(pixel);  // Get the 0-255 value of the G channel
                int b = qBlue(pixel);   // Get the 0-255 value of the B channel
                //QRgb newPixel = (r+g+b)/3; // RGB to Grayscale average method
                QRgb newPixel = 0.21*r+0.72*g+0.07*b; // RGB to Grayscale luminosity method
                newImage->setPixel(x,y, qGray(newPixel));
            }
    }

    return newImage;
}
