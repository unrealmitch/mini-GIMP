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

	int n=size/2;
	
	for(int i=0; i<=n; i++){
		for(int j=0; j<=n; j++){
			mask(i,j)=0.0;
		}
	}

	mask(size/2, size/2) = 1;

    return mask;
}

/** Does the convolution process for all pixels using the given mask. */
PNM* Convolution::convolute(math::matrix<double> mask, Mode mode = RepeatEdge)
{
	int width  = image->width(),
		height = image->height();

	PNM* newImage = new PNM(width, height, image->format());

	double weight = sum(mask);
	vector<Channel> channels;

	if(image->format() == QImage::Format_Indexed8)
	{
		channels.push_back(LChannel);
	}
	else 
	{
		channels.push_back(RChannel);
		channels.push_back(GChannel);
		channels.push_back(BChannel);
	}
	double result[3];

	for(int x=0; x<width; x++)
	{
		for(int y=0; y<height; y++)
		{
			for(int z=0; z<channels.size(); z++)
			{				
				math::matrix<double> accum = join(mask, getWindow(x, y, mask.RowNo(), channels[c], mode));

				result[c] = sum(accum);
				if(weight != 0) result[z]  /= weight;
				if(result[z]  > 255) result[c]  = 255;
				else if(result[z]  < 0) result[c]  = 0;
			}

			if(image->format() == QImage::Format_Indexed8) newImage->setPixel(x, y, result[0]);
			else newImage->setPixel(x, y, qRgb(result[0], result[1], result[2]));
		}
	}

	return newImage;
}

/** Joins to matrices by multiplying the A[i,j] with B[i,j].
  * Warning! Both Matrices must be squares with the same size!
  */
const math::matrix<double> Convolution::join(math::matrix<double> A, math::matrix<double> B)
{
	int size = A.RowNo();
	math::matrix<double> C(size, size);
	for(int x=0; x<size; x++)
	{
		for(int y=0; y<size; y++)
		{
			C(x, y) = A(x, y) * B(x, y);
		}
	}

	return C;
}

/** Sums all of the matrixes elements */
const double Convolution::sum(const math::matrix<double> A)
{
    double sum = 0.0;

    qDebug() << Q_FUNC_INFO << "Not implemented yet!";

    return sum;

}
