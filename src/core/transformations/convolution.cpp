#include "convolution.h"

/** Overloaded constructor */
Convolution::Convolution(PNM* img) :
    Transformation(img)
{
}

Convolution::Convolution(PNM* img, ImageViewer* iv) :
    Transformation(img, iv)
{
}

/** Returns a convoluted form of the image */
PNM* Convolution::transform()
{
    return convolute(getMask(3, Normalize), RepeatEdge);
}

/** Returns a sizeXsize matrix with the center point equal 1.0 */
math::matrix<double> Convolution::getMask(int size, Mode mode = Normalize)
{
    math::matrix<double> mask(size, size);

    qDebug() << Q_FUNC_INFO << "Not implemented yet!";

    return mask;
}

/** Does the convolution process for all pixels using the given mask. */
PNM* Convolution::convolute(math::matrix<double> mask, Mode mode = RepeatEdge)
{
    int width  = image->width(),
        height = image->height();

    PNM* newImage = new PNM(width, height, image->format());

    qDebug() << Q_FUNC_INFO << "Not implemented yet!";

    return newImage;
}

/** Joins to matrices by multiplying the A[i,j] with B[i,j].
  * Warning! Both Matrices must be squares with the same size!
  */
const math::matrix<double> Convolution::join(math::matrix<double> A, math::matrix<double> B)
{
    int size = A.RowNo();
    math::matrix<double> C(size, size);

    qDebug() << Q_FUNC_INFO << "Not implemented yet!";

    return C;
}

/** Sums all of the matrixes elements */
const double Convolution::sum(const math::matrix<double> A)
{
    double sum = 0.0;

    qDebug() << Q_FUNC_INFO << "Not implemented yet!";

    return sum;

}
