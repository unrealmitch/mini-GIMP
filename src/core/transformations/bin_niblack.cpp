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
        emit progress(100*x/double(image->width()));//Displays a loading image

        for (int y=0; y<height; y++)
        {
            int sumVal = 0;

            /*//We crop a rectangle on the original image
            QRect rect(x-half_r,y-half_r,r,r);
            QImage cropped = image->copy(rect);*/

            math::matrix<double> windowR(r,r);
            math::matrix<double> windowG(r,r);
            math::matrix<double> windowB(r,r);
            windowR = Transformation::getWindow(x,y,r,RChannel,RepeatEdge);
            windowG = Transformation::getWindow(x,y,r,GChannel,RepeatEdge);
            windowB = Transformation::getWindow(x,y,r,BChannel,RepeatEdge);

            //1--
            math::matrix<double> window(r,r);
            for (int i=0; i< window.RowNo(); i++)
                for (int j=0; j< window.ColNo(); j++)
                    window(i,j) = qRgb(windowR(i,j),windowG(i,j),windowB(i,j));


            //We calculate u
            for (int i=0; i< window.RowNo(); i++)
                for (int j=0; j< window.ColNo(); j++)
                    sumVal += qGray(window(i,j));

            u = sumVal/pow(r,2);

            //Then, we calculate sigma
            sumVal = 0;
            for (int i=0; i< window.RowNo(); i++)
                for (int j=0; j< window.ColNo(); j++)
                    pow(window(i,j) - u,2)/pow(r,2);

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
