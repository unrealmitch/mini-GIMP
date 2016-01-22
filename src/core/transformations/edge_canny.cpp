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
    m_magnitude = math::matrix<double>(image->width(), image->height());
    for (int i=0; i<361; i++)
    {
        if ((i>=0 && i<23) || (i>=158 && i<203) || (i>=338 && i<361))
        {
            bucket[i] = 0;
        }
        if ((i>=23 && i<68) || (i>=203 && i<248) )
        {
            bucket[i] = 1;
        }
        if ((i>=68 && i<113) || (i>=248 && i<293))
        {
            bucket[i] = 2;
        }
        if ((i>=113 && i<158) || (i>=293 && i<338))
        {
            bucket[i] = 3;
        }
    }
}

QPoint getNextEdgePoint(int bucket, int pointNumber)
{
    QPoint point;
    if (pointNumber == 1)
    {
        if (bucket == 0)
        {
            point = QPoint(0,-1);
        }
        else if (bucket == 1)
        {
            point = QPoint(1,-1);
        }
        else if (bucket == 2)
        {
            point = QPoint(-1,0);
        }
        else if (bucket == 3)
        {
            point = QPoint(-1,-1);
        }
    }
    else
    {
        if (bucket == 0)
        {
            point = QPoint(0,1);
        }
        else if (bucket == 1)
        {
            point = QPoint(-1,1);
        }
        else if (bucket == 2)
        {
            point = QPoint(1,0);
        }
        else if (bucket == 3)
        {
            point = QPoint(1,1);
        }
    }
    return point;
}

PNM* EdgeCanny::transform()
{
    int width  = image->width(),
        height = image->height();

    int upper_thresh = getParameter("upper_threshold").toInt(),
        lower_thresh = getParameter("lower_threshold").toInt();

    PNM* newImage = new PNM(width, height, QImage::Format_Indexed8);
    PNM* tempImage = new PNM(width, height, QImage::Format_Indexed8);

    tempImage = ConversionGrayscale(image).transform();
    BlurGaussian blurGaussian(tempImage);
    blurGaussian.setParameter("size", 3);
    blurGaussian.setParameter("sigma", 1.6);
    tempImage = blurGaussian.transform();
    EdgeSobel sobel(tempImage);
    math::matrix<double>* Gx = sobel.rawHorizontalDetection();
    math::matrix<double>* Gy = sobel.rawVerticalDetection();
    for (int i=0; i<width; i++)
    {
        for (int j=0; j<height; j++)
        {
            m_magnitude(i, j) = sqrt(pow((*Gx)(i, j), 2) + pow((*Gy)(i, j), 2));
            m_orientation(i, j) = (int) ((atan2((*Gy)(i, j), (*Gx)(i, j)) / (M_PI)) * 180 + 360) % 360;
        }
    }
    double neigh_1, neigh_2;
    std::list<QPoint> initialPoints;
    for (int i=1; i<width-1; i++)
    {
        for (int j=1; j<height-1; j++)
        {
            int theta = m_orientation(i, j);
            double m = m_magnitude(i, j);
            QPoint point1 = getNextEdgePoint(bucket[theta], 1);
            QPoint point2 = getNextEdgePoint(bucket[theta], 2);
            neigh_1 = m_magnitude(i + point1.x(), j + point1.y());
            neigh_2 = m_magnitude(i + point2.x(), j + point2.y());
            if(m > neigh_1 && m > neigh_2 && m > upper_thresh)
            {
                newImage->setPixel(i, j, PIXEL_VAL_MIN);
                initialPoints.push_back(QPoint(i, j));
            }
        }
    }
    while (!initialPoints.empty())
    {
        QPoint point = initialPoints.back();
        initialPoints.pop_back();
        int theta = m_orientation(point.x(), point.y());
        QPoint tempNeighPoints[7] = {
            QPoint(-1,0),
            QPoint(-1,1),
            QPoint(0,-1),
            QPoint(0,1),
            QPoint(1,-1),
            QPoint(1,0),
            QPoint(1,1),
        };
        for (int i=1; i<=2; i++)
        {
            QPoint direction = getNextEdgePoint(bucket[theta], i);
            QPoint currentPoint = point;
            while(true)
            {
                QPoint nextPoint = QPoint(currentPoint.x() + direction.x(), currentPoint.y() + direction.y());
                if (nextPoint.x() == width-1 || nextPoint.x() == 0 || nextPoint.y() == height-1 || nextPoint.y() == 0) break;
                if (newImage->pixel(nextPoint.x(), nextPoint.y()) == PIXEL_VAL_MIN) break;
                if (m_magnitude(nextPoint.x(), nextPoint.y()) < lower_thresh) break;
                if (bucket[(int) m_orientation(nextPoint.x(), nextPoint.y())] != bucket[theta]) break;
                bool maxMagnitude = true;
                double magnitude = m_magnitude(nextPoint.x(), nextPoint.y());
                for (int i=0; i<7; i++)
                {
                    QPoint tempNeigh(nextPoint.x() + tempNeighPoints[i].x(), nextPoint.y() + tempNeighPoints[i].y());
                    if (tempNeigh.x() == currentPoint.x() && tempNeigh.y() == currentPoint.y()) continue;
                    if (bucket[(int)m_orientation(tempNeigh.x(), tempNeigh.y())] != bucket[theta]) continue;
                    if (m_magnitude(tempNeigh.x(), tempNeigh.y()) >= magnitude)
                    {
                        maxMagnitude = false;
                        break;
                    }
                }
                if (!maxMagnitude) break;
                newImage->setPixel(nextPoint.x(), nextPoint.y(), PIXEL_VAL_MIN);
                currentPoint = nextPoint;
            }
        }
    }

    return newImage;
}

void EdgeCanny::checkHysterysis(int i, int j, int di, int dj, int direction, int lower_thresh, PNM* newImage)
{
    qDebug() << Q_FUNC_INFO << "Not implemented yet!";
}
