#include "noise_bilateral.h"

NoiseBilateral::NoiseBilateral(PNM* img) :
    Convolution(img)
{
}

NoiseBilateral::NoiseBilateral(PNM* img, ImageViewer* iv) :
    Convolution(img, iv)
{
}

PNM* NoiseBilateral::transform()
{
    int width  = image->width();
    int height = image->height();

    PNM* newImage = new PNM(width, height, image->format());

    qDebug() << Q_FUNC_INFO << "Not implemented yet!";

    return newImage;
}

int NoiseBilateral::getNeighbours(int x, int y, Channel channel)
{
    int sigma_d = getParameter("sigma_d").toInt();
    int sigma_r = getParameter("sigma_r").toInt();
    int radius = sigma_d;

    qDebug() << Q_FUNC_INFO << "Not implemented yet!";

    return 0;
}

double NoiseBilateral::g(int x, int y, int sigma_d)
{
    qDebug() << Q_FUNC_INFO << "Not implemented yet!";

    return 0;
}

double NoiseBilateral::r(int v, int v_ij, int sigma_r)
{
    qDebug() << Q_FUNC_INFO << "Not implemented yet!";

    return 0;
}
