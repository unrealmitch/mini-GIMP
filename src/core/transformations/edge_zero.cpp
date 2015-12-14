#include "edge_zero.h"

#include "edge_laplacian_of_gauss.h"

EdgeZeroCrossing::EdgeZeroCrossing(PNM* img) :
    Convolution(img)
{
}

EdgeZeroCrossing::EdgeZeroCrossing(PNM* img, ImageViewer* iv) :
    Convolution(img, iv)
{
}

double findMinimum(math::matrix<double> matrix, int size)
{
    double minimum = 255.0;
    for (int x=0; x<size; x++)
    {
        for (int y=0; y<size; y++)
        {
            if(matrix(x,y) < minimum)
            {
                minimum = matrix(x, y);
            }
        }
    }
    return minimum;
}

double findMaximum(math::matrix<double> matrix, int size)
{
    double maximum = 0.0;
    for (int x=0; x<size; x++)
    {
        for (int y=0; y<size; y++)
        {
            if(matrix(x,y) > maximum)
            {
                maximum = matrix(x, y);
            }
        }
    }
    return maximum;
}

PNM* EdgeZeroCrossing::transform()
{
    int width = image->width(),
        height = image->height();

    int    size  = getParameter("size").toInt();
    double sigma = getParameter("sigma").toDouble();
    int    t     = getParameter("threshold").toInt();

    EdgeLaplaceOfGauss edgeLaplaceOfGauss(image);
    edgeLaplaceOfGauss.setParameter("size", size);
    edgeLaplaceOfGauss.setParameter("sigma", sigma);
    PNM* newImage = edgeLaplaceOfGauss.transform();
    Transformation lapl(edgeLaplaceOfGauss.transform());

    int v0 = 128;
    if (image->format() == QImage::Format_Indexed8)
    {
        for (int x=0; x<width; x++)
        {
            for (int y=0; y<height; y++)
            {
                math::matrix<double> mask = lapl.getWindow(x, y, size, LChannel, NullEdge);
                double maximum = findMaximum(mask, size);
                double minimum = findMinimum(mask, size);
                if(minimum < v0 - t && maximum > v0 + t)
                {
                    int q = mask(size/2, size/2);
                    newImage->setPixel(x, y, q);
                }
                else
                {
                    newImage->setPixel(x, y, 0);
                }
            }
        }
    }
    else
    {
        for (int x=0; x<width; x++)
        {
            for (int y=0; y<height; y++)
            {
                math::matrix<double> maskR = lapl.getWindow(x, y, size, RChannel, NullEdge);
                double maximumR = findMaximum(maskR, size);
                double minimumR = findMinimum(maskR, size);
                math::matrix<double> maskG = lapl.getWindow(x, y, size, GChannel, NullEdge);
                double maximumG = findMaximum(maskG, size);
                double minimumG = findMinimum(maskG, size);
                math::matrix<double> maskB = lapl.getWindow(x, y, size, BChannel, NullEdge);
                double maximumB = findMaximum(maskB, size);
                double minimumB = findMinimum(maskB, size);
                int r, g, b;
                if(minimumR < v0 - t && maximumR > v0 + t)
                {
                    r = maskR(size/2, size/2);
                }
                else
                {
                    r = 0;
                }
                if(minimumG < v0 - t && maximumG > v0 + t)
                {
                    g = maskG(size/2, size/2);
                }
                else
                {
                    g = 0;
                }
                if(minimumB < v0 - t && maximumB > v0 + t)
                {
                    b = maskB(size/2, size/2);
                }
                else
                {
                    b = 0;
                }
                newImage->setPixel(x, y, qRgb(r, g, b));
            }
        }
    }

    return newImage;
}
