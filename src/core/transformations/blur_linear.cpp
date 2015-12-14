#include "blur_linear.h"

BlurLinear::BlurLinear(PNM* img) :
    Convolution(img)
{
}

BlurLinear::BlurLinear(PNM* img, ImageViewer* iv) :
    Convolution(img, iv)
{
}

PNM* BlurLinear::transform()
{
	
    int maskSize = getParameter("size").toInt();
	int radius = (maskSize/2)+1;
    QList<QVariant> tmpMask = getParameter("mask").toList();
    bool normalize = getParameter("normalize").toBool();

    math::matrix<double> mask(maskSize, maskSize);
	int licznik=0;
    
   for (int i=0;i<radius;i++){
	   for (int j=0;j<radius;j++){
			 mask(i,j)=tmpMask.at(licznik).toDouble();
			licznik++;
			if (normalize==1){
				mask(i,j)=mask(i,j)/sum(mask);
			}
		 }
   }
   //convolute(mask, RepeatEdge);

    return convolute(mask, RepeatEdge);
}
