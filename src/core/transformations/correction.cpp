#include "correction.h"

Correction::Correction(PNM* img) :
    Transformation(img)
{
}

Correction::Correction(PNM* img, ImageViewer* iv) :
    Transformation(img, iv)
{
}

PNM* Correction::transform()
{
    qDebug() << Q_FUNC_INFO << "Not implemented yet!";

    double shift  = getParameter("shift").toDouble();
    double factor = getParameter("factor").toDouble();
    double gamma  = getParameter("gamma").toDouble();

    int width  = image->width();
    int height = image->height();

    PNM* newImage = new PNM(width, height, image->format());

    if (image->format() == QImage::Format_Indexed8)
    {

    }
    else //if (image->format() == QImage::Format_RGB32)
    {

    }

    return newImage;
}

const int Correction::add(int value, double shift)
{
    qDebug() << Q_FUNC_INFO << "Not implemented yet!";

    return 0;
}

const  double Correction::mult(int value, double factor)
{
    qDebug() << Q_FUNC_INFO << "Not implemented yet!";

    return 0;
}

const int Correction::power(int value, double power)
{
    qDebug() << Q_FUNC_INFO << "Not implemented yet!";

    return 0;
}
