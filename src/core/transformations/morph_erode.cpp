#include "morph_erode.h"

MorphErode::MorphErode(PNM* img) :
    MorphologicalOperator(img)
{
}

MorphErode::MorphErode(PNM* img, ImageViewer* iv) :
    MorphologicalOperator(img, iv)
{
}

const int MorphErode::morph(math::matrix<double> window, math::matrix<bool> se)
{
    double max=0.0;

    qDebug() << Q_FUNC_INFO << "Not implemented yet!";

    return 0;
}
