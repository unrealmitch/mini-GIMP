#include "bin_niblack.h"

/**
 * @brief BinarizationNiblack::BinarizationNiblack
 * @author Miguel Caballero
 * @param img
 */

BinarizationNiblack::BinarizationNiblack(PNM* img) :
    Transformation(img)
{
}

BinarizationNiblack::BinarizationNiblack(PNM* img, ImageViewer* iv) :
    Transformation(img, iv)
{
}

PNM* BinarizationNiblack::transform()
{
    int width = image->width();
    int height = image->height();

    int    r = getParameter("r").toInt();
    int half_r= ceil(r/2);
    double a = getParameter("a").toDouble();
    int threshold = 0;
    int u;
    int sigma;

    PNM* newImage = new PNM(width, height, QImage::Format_Mono);

    //For each pixel in the original image we crop a window of size r
    for (int x=0; x<width; x++)
    {
        emit progress(100*x/double(image->width()));

        for (int y=0; y<height; y++)
        {
            int sumVal = 0;

            //We crop a rectangle on the original image
            QRect rect(x-half_r,y-half_r,r,r);
            QImage cropped = image->copy(rect);

            //We calculate u
            for (int i=0; i< cropped.width(); i++)
                for (int j=0; j< cropped.height(); j++)
                {
                    if(qGray(cropped.pixel(i,j)) >= 0 || qGray(cropped.pixel(i,j)) <= 255)
                        sumVal += qGray(cropped.pixel(i,j));
                    else
                        sumVal += 0;
                }

            u = sumVal/pow(r,2);

            //Then, we calculate sigma
            sumVal = 0;
            for (int i=0; i< cropped.width(); i++)
                for (int j=0; j< cropped.height(); j++)
                {
                    if(qGray(cropped.pixel(i,j)) >= 0 || qGray(cropped.pixel(i,j)) <= 255)
                        sumVal += pow(cropped.pixel(i,j) - u,2)/pow(r,2);
                    else
                        sumVal += pow(u,2)/pow(r,2);
                }

            sigma = sqrt(sumVal);

            //Then, we let threshold for original image's pixel(x,y)
            threshold = u + a * sigma;

            //Finally, we write the pixel in the new image
            int v = qGray(image->pixel(x,y));    // Get the 0-255 value of the L channel
            QRgb black = 0;
            QRgb white = 1;

            newImage->setPixel(x,y, v < threshold ? black : white);
        }
    }

    return newImage;
}
