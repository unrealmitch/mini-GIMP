#include "histogram_equalization.h"

#include "../histogram.h"

/**
 * @brief HistogramEqualization::HistogramEqualization
 * @author Miguel Caballero
 * @param img
 */

HistogramEqualization::HistogramEqualization(PNM* img) :
    Transformation(img)
{
}

HistogramEqualization::HistogramEqualization(PNM* img, ImageViewer* iv) :
    Transformation(img, iv)
{
}

PNM* HistogramEqualization::transform()
{
    int width = image->width();
    int height = image->height();

    PNM* newImage = new PNM(width, height, image->format());

    double rBand[256];
    double gBand[256];
    double bBand[256];
    double rAccumulative = 0;
    double gAccumulative = 0;
    double bAccumulative = 0;
    unsigned int *ret = (unsigned int *)malloc(sizeof(unsigned int)*256);
    if(!ret)
        qErrnoWarning("Error: Couldn't reserve memory for ret variable");

    memset(rBand,0,sizeof(double)*256);
    memset(gBand,0,sizeof(double)*256);
    memset(bBand,0,sizeof(double)*256);

    //We add one for each color band for post normalization
    for(int x=0 ; x < width ; x++)
        for(int y=0 ; y < height ; y++)
        {
            int v = image->pixel(x,y);

            rBand[qRed(v)] += 1;
            gBand[qGreen(v)] += 1;
            bBand[qBlue(v)] += 1;
        }

    //We normalize the histogram in each band
    for(int i=0 ; i < 256 ; i++)
    {
        rBand[i] /= width * height;
        gBand[i] /= width * height;
        bBand[i] /= width * height;
    }

    //Then, we compute the Cumulative Distribution Function (CDF)
    for(int i=0; i < 256; i++)
    {
        rAccumulative += rBand[i];
        gAccumulative += gBand[i];
        bAccumulative += bBand[i];
        ret[i] = qRgb((int)(rAccumulative*255+0.5),(int)(gAccumulative*255+0.5),(int)(bAccumulative*255+0.5));
    }

    //Finally, we apply equalized histogram to newImage
    for(int x=0 ; x < width ; x++)
        for(int y=0 ; y < height ; y++)
        {
            int v = image->pixel(x,y);

            newImage->setPixel(x,y, qRgb(qRed(ret[qRed(v)]),qGreen(ret[qGreen(v)]),qBlue(ret[qBlue(v)])));
        }

    return newImage;
}
