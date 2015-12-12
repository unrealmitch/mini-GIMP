#include "bin_iterbimodal.h"

/**
 * @brief BinarizationIterBimodal::BinarizationIterBimodal
 * @author Miguel Caballero
 * @param img
 */

BinarizationIterBimodal::BinarizationIterBimodal(PNM* img) :
    Transformation(img)
{
}

BinarizationIterBimodal::BinarizationIterBimodal(PNM* img, ImageViewer* iv) :
    Transformation(img, iv)
{
}

PNM* BinarizationIterBimodal::transform()
{
    int width = image->width();
    int height = image->height();
    int pixelCount = 0;
    int tempValue = 0;

    PNM* newImage = new PNM(width, height, QImage::Format_Mono);

    //First we calculate middle value of possible pixel values for threshold
    for (int x=0; x<width; x++)
        for (int y=0; y<height; y++)
        {
            tempValue += qGray(image->pixel(x,y));
            pixelCount++;
        }

    int threshold = ceil(tempValue/pixelCount);

    //Step 2, we continue executing until T_new equals T
    bool goBack = true; //boolean for control of going back to step 2
    while(goBack)
    {
        int Tw = 0;
        int iw = 0;
        int Tb = 0;
        int ib = 0;

        //For each pixel we calculed values for Tw,iw,Tb and ib
        for(int x=0; x<width ; x++)
            for(int y=0 ;y<height ; y++)
            {
                int val = qGray(image->pixel(x,y));
                if(val > threshold)
                {
                    Tw+=val;
                    iw++;
                }
                else
                {
                    Tb+=val;
                    ib++;
                }
            }

        //Then we calculated the new threshold
        int newThreshold = ((Tw/iw) + (Tb/ib)) / 2;

        //If T_new differs from T
        if(newThreshold != threshold)
            threshold = newThreshold;
        else
            goBack = false;
    }

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



