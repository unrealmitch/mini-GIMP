#include "blur_uniform.h"

BlurUniform::BlurUniform(PNM* img) :
    Convolution(img)
{
}

BlurUniform::BlurUniform(PNM* img, ImageViewer* iv) :
    Convolution(img, iv)
{
}

math::matrix<double> BlurUniform::getMask(int size, Mode)
{
    math::matrix<double> mask(size, size);

    qDebug() << Q_FUNC_INFO << "Not implemented yet!";

    return mask;
}
