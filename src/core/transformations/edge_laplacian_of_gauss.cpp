#include "edge_laplacian_of_gauss.h"

#include "blur_gaussian.h"

EdgeLaplaceOfGauss::EdgeLaplaceOfGauss(PNM* img) :
    Convolution(img)
{
}

EdgeLaplaceOfGauss::EdgeLaplaceOfGauss(PNM* img, ImageViewer* iv) :
    Convolution(img, iv)
{
}

math::matrix<double> EdgeLaplaceOfGauss::getMask(int, Mode)
{
    size = getParameter("size").toInt();
    double sigma = getParameter("sigma").toDouble();

    math::matrix<double> mask(size, size);

    qDebug() << Q_FUNC_INFO << "Not implemented yet!";

    return mask;
}

double EdgeLaplaceOfGauss::getLoG(int x, int y, double s)
{
    qDebug() << Q_FUNC_INFO << "Not implemented yet!";

    return 0;
}

int EdgeLaplaceOfGauss::getSize()
{
    return size;
}
