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
        for (int x = 0; x<width; x++)
            for (int y = 0; y<height; y++)
            {
            QColor color = QColor::fromRgb(image->pixel(x, y)); // Getting the pixel(x,y) value

            newImage->setPixel(x, y, color == Qt::white ? PIXEL_VAL_MAX : PIXEL_VAL_MIN);
            }
    }
    else
    {
        for (int x = 0; x<width; x++)
            for (int y = 0; y<height; y++)
            {
            QRgb pixel = image->pixel(x, y);

            int r = qRed(pixel);
            int g = qGreen(pixel);
            int b = qBlue(pixel);
            int new_color = (int)((0.6*r) + (0.3*g) + (0.1*b));
            newImage->setPixel(x, y, new_color);
            }
    }

    return newImage;
}
