#include "bin_otsu.h"

#include "histogram_equalization.h"
#include "../histogram.h"

/**
 * @brief BinarizationOtsu::BinarizationOtsu
 * @author Miguel Caballero
 * @param img
 */

BinarizationOtsu::BinarizationOtsu(PNM* img) :
    Transformation(img)
{
}

BinarizationOtsu::BinarizationOtsu(PNM* img, ImageViewer* iv) :
    Transformation(img, iv)
{
}

PNM* BinarizationOtsu::transform()
{
    int width = image->width();
    int height = image->height();
    int sum1 = 0;
    int sum2 = 0;

    PNM* newImage = new PNM(width, height, QImage::Format_Mono);

    //First, we equalize histogram using our custom class
    PNM* imgEq = HistogramEqualization(image).transform();

    //Then, we create bcv
    double bcv[256];

    //We create our custom histogram for sum1 (notice that we join the three RGB bands in one total band)
    int histogram[256];

    for(int x=0;x<width;x++)
        for(int y=0;y<height;y++)
        {
            histogram[qRed(imgEq->pixel(x,y))] += 1;
            histogram[qGreen(imgEq->pixel(x,y))] += 1;
            histogram[qBlue(imgEq->pixel(x,y))] += 1;
        }

    //For each possible threashold T
    for(int T=0;T<256;T++)
    {
        //[0;T)------------------------
            //After that, we add sum1 [0;T)
            sum1=0;

            for(int j=0;j<T;j++)
                sum1 += histogram[j];

            //Then, we calculate W_b
            int W_b = sum1 / pow(255,2);

            //We add sum2 [0;T)
            sum2=0;

            for(int j=0;j<T;j++)
                sum2 += histogram[j]*j;

            //We calculate u_b
            int u_b = sum1 != 0 ? sum2 / sum1 : 0;

        //[T;255]------------------------

            //After that, we add sum1 [T;255]
            sum1=0;

            for(int j=T;j<256;j++)
                sum1 += histogram[j];

            //Then, we calculate W_f
            int W_f = sum1 / pow(255,2);

            //We add sum2 [T;255]
            sum2=0;

            for(int j=T;j<256;j++)
                sum2 += histogram[j]*j;

            //We calculate u_f
            int u_f = sum1 != 0 ? sum2 / sum1 : 0;

        //------------------------
            //At the end of iteration we let bcv[T]
            bcv[T] = W_b * W_f * pow(u_b - u_f, 2);
    }

    //We find in bcv an index of the biggest value and we assing it to the threshold
    int maxIndex = 0;
    for(int i=0;i<256;i++)
        if(bcv[i]>bcv[maxIndex])
            maxIndex=i;

    int threshold = maxIndex;

    //Finally, we write the pixel in the new image
    for(int x=0;x<width;x++)
        for(int y=0;y<height;y++)
        {
            int v = qGray(imgEq->pixel(x,y));    // Get the 0-255 value of the L channel
            QRgb black = 0;
            QRgb white = 1;

            newImage->setPixel(x,y, v < threshold ? black : white);
        }

    return newImage;
}
