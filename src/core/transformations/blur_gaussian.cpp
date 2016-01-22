#include "blur_gaussian.h"

BlurGaussian::BlurGaussian(PNM* img) :
    Convolution(img)
{
}

BlurGaussian::BlurGaussian(PNM* img, ImageViewer* iv) :
    Convolution(img, iv)
{
}

PNM* BlurGaussian::transform()
{
    emit message("Blurring...");

    int size = getParameter("size").toInt();
    radius = (size/2)+1;
    sigma = getParameter("sigma").toDouble();

    return convolute(getMask(size, Normalize), RepeatEdge);
}

math::matrix<double> BlurGaussian::getMask(int size, Mode)
{
    math::matrix<double> mask(size, size);
    //Mode mode = RepeatEdge;
   for (int i=0;i<size;i++){
         for (int j=0;j<size;j++){
			 mask(i,j)=getGauss(i,j,sigma);
		 }
   }
   //convolute(mask, mode);
    return mask;
}

double BlurGaussian::getGauss(int x, int y, double sigma)
{    
	double Pi=3.14;
	double e= 2.718281828459;
	double g=(pow(e,-((pow(x,2)+pow(y,2)))/2*pow(sigma,2)))/2*Pi*pow(sigma,2);
   
    return g;
}

