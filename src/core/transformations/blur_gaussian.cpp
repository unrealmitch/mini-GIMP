#include "blur_gaussian.h"

BlurGaussian::BlurGaussian(PNM* img) :
    Convolution(img)
{
}

BlurGaussian::BlurGaussian(PNM* img, ImageViewer* iv) :
    Convolution(img, iv)
{
}

PNM* BlurGaussian::transform()
{
    emit message("Blurring...");

    int size = getParameter("size").toInt();
    radius = (size/2)+1;
    sigma = getParameter("sigma").toDouble();

    return convolute(getMask(size, Normalize), RepeatEdge);
}

math::matrix<double> BlurGaussian::getMask(int size, Mode)
{
    math::matrix<double> mask(size, size);

    qDebug() << Q_FUNC_INFO << "Not implemented yet!";

    return mask;
}

double BlurGaussian::getGauss(int x, int y, double sigma)
{    
    qDebug() << Q_FUNC_INFO << "Not implemented yet!";

    return 0;
}

