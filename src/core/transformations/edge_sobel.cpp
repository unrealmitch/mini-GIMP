#include "edge_sobel.h"

EdgeSobel::EdgeSobel(PNM* img, ImageViewer* iv) :
    EdgeGradient(img, iv)
{
    prepareMatrices();
}

EdgeSobel::EdgeSobel(PNM* img) :
    EdgeGradient(img)
{
    prepareMatrices();
}

void EdgeSobel::prepareMatrices()
{
    qDebug() << Q_FUNC_INFO << "Not implemented yet!";
}

math::matrix<double>* EdgeSobel::rawHorizontalDetection()
{
    math::matrix<double>* x_gradient = new math::matrix<double>(this->image->width(), this->image->height());

    qDebug() << Q_FUNC_INFO << "Not implemented yet!";

    return x_gradient;
}

math::matrix<double>* EdgeSobel::rawVerticalDetection()
{
    math::matrix<double>* y_gradient = new  math::matrix<double>(this->image->width(), this->image->height());

    qDebug() << Q_FUNC_INFO << "Not implemented yet!";

    return y_gradient;
}
