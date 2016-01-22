#include "histogram_stretching.h"

#include "../histogram.h"

HistogramStretching::HistogramStretching(PNM* img) :
    Transformation(img)
{
}

HistogramStretching::HistogramStretching(PNM* img, ImageViewer* iv) :
    Transformation(img, iv)
{
}

PNM* HistogramStretching::transform()
{
    int width  = image->width();
    int height = image->height();

    PNM* newImage = new PNM(width, height, image->format());

    if (image->format() == QImage::Format_Mono)
        qDebug() << Q_FUNC_INFO << "Not implemented yet!";
    else if(image->format() == QImage::Format_Indexed8)
    {
        //First we obtain an histogram for grayscale
        double histogram[256];
        memset(histogram,0,sizeof(double)*256);
        for(int x=0 ; x < width ; x++)
            for(int y=0 ; y < height ; y++)
                histogram[qGray(image->pixel(x,y))] += 1;

        //Then we look for min and max
        bool minFounded = false;
        int temp = 0, min = 0, max = 0;

        for(int i = 0 ; i < 256 ; i++)
        {
            if(!minFounded && histogram[i] > 0)
            {
                minFounded = true;
                min = i;
            }

            if(histogram[i] > temp)
            {
                temp = histogram[i];
                max = i;
            }
        }

        qDebug() << "Min Value: " << min;
        qDebug() << "Max Value: " << max;

        //Finally, we stretch the histogram
        for(int x = 0 ; x < width  ; x++)
            for(int y = 0 ; y < height ; y++)
                newImage->setPixel(x, y, (255/(max-min))*(qGray(image->pixel(x,y))-min) );
    }
    else
    {
        double rBand[256];
        double gBand[256];
        double bBand[256];
        memset(rBand,0,sizeof(double)*256);
        memset(gBand,0,sizeof(double)*256);
        memset(bBand,0,sizeof(double)*256);

        int v = 0;
        //First we obtain an histogram for each channel
        for(int x=0 ; x < width ; x++)
            for(int y=0 ; y < height ; y++)
            {
                v = image->pixel(x,y);

                rBand[qRed(v)] += 1;
                gBand[qGreen(v)] += 1;
                bBand[qBlue(v)] += 1;
            }

        //Then we look for min and max for each band
        int edges[3][2];
        memset(edges,0,sizeof(int)*3);

        bool minFounded = false;
        int temp = 0;

        //rBand
        for(int j = 0 ; j < 256 ; j++)
        {
            if(!minFounded && rBand[j] > 0)
            {
                minFounded = true;
                edges[0][0] = j;
            }

            if(rBand[j] > temp)
            {
                temp = rBand[j];
                edges[0][1] = j;
            }
        }
        minFounded = false;
        temp = 0;

        //gBand
        for(int j = 0 ; j < 256 ; j++)
        {
            if(!minFounded && gBand[j] > 0)
            {
                minFounded = true;
                edges[1][0] = j;
            }

            if(gBand[j] > temp)
            {
                temp = gBand[j];
                edges[1][1] = j;
            }
        }
        minFounded = false;
        temp = 0;

        //bBand
        for(int j = 0 ; j < 256 ; j++)
        {
            if(!minFounded && bBand[j] > 0)
            {
                minFounded = true;
                edges[2][0] = j;
            }

            if(bBand[j] > temp)
            {
                temp = bBand[j];
                edges[2][1] = j;
            }
        }

        //Finally, we stretch the histogram
        int rNewPixel=0;
        int gNewPixel=0;
        int bNewPixel=0;

        for(int x = 0 ; x < width  ; x++)
            for(int y = 0 ; y < height ; y++)
            {
                rNewPixel = (int)((255/(edges[0][1]-edges[0][0]))*(qRed(image->pixel(x,y))-edges[0][0]));
                gNewPixel = (int)((255/(edges[1][1]-edges[1][0]))*(qGreen(image->pixel(x,y))-edges[1][0]));
                bNewPixel = (int)((255/(edges[2][1]-edges[2][0]))*(qBlue(image->pixel(x,y))-edges[2][0]));

                newImage->setPixel(x, y, qRgb(rNewPixel,gNewPixel,bNewPixel) );
            }
    }

    return newImage;
}


