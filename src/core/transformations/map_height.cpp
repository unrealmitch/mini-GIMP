#include "map_height.h"

MapHeight::MapHeight(PNM* img) :
    Transformation(img)
{
}

MapHeight::MapHeight(PNM* img, ImageViewer* iv) :
    Transformation(img, iv)
{
}

PNM* MapHeight::transform()
{
    int width  = image->width(),
        height = image->height();

    PNM* newImage = new PNM(width, height, QImage::Format_Indexed8);

    if (image->format() == QImage::Format_Mono)
    {

        for (int x = 0; x<width; x++)
            for (int y = 0; y<height; y++)
            {
            QColor color = QColor::fromRgb(image->pixel(x, y));
            newImage->setPixel(x, y, color == Qt::white ? PIXEL_VAL_MAX : PIXEL_VAL_MIN);
            }
    }
    else
    {
        for (int x = 0; x<width; x++)
            for (int y = 0; y<height; y++)
            {
            QRgb pixel = image->pixel(x, y);
            int new_color = (int)((0.6*qRed(pixel)) + (0.3*qGreen(pixel)) + (0.1*qBlue(pixel)));
            newImage->setPixel(x, y, new_color);
            }
    }

    return newImage;
}

