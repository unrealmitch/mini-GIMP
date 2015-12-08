#include "edge_canny.h"

#include "blur_gaussian.h"
#include "conversion_grayscale.h"
#include "edge_sobel.h"

EdgeCanny::EdgeCanny(PNM* img) :
    Convolution(img)
{
    initMembers();
}

EdgeCanny::EdgeCanny(PNM* img, ImageViewer* iv) :
    Convolution(img, iv)
{
    initMembers();
}

void EdgeCanny::initMembers()
{
    m_orientation = math::matrix<double>(image->width(), image->height());
    m_magnitude   = math::matrix<double>(image->width(), image->height());

    qDebug() << Q_FUNC_INFO << "Not implemented yet!";
}

PNM* EdgeCanny::transform()
{
    int width  = image->width(),
        height = image->height();

    int upper_thresh = getParameter("upper_threshold").toInt(),
        lower_thresh = getParameter("lower_threshold").toInt();

    PNM* newImage = new PNM(width, height, QImage::Format_Indexed8);

    qDebug() << Q_FUNC_INFO << "Not implemented yet!";

    return newImage;
}

void EdgeCanny::checkHysterysis(int i, int j, int di, int dj, int direction, int lower_thresh, PNM* newImage)
{
    qDebug() << Q_FUNC_INFO << "Not implemented yet!";
}
