#include "noise_median.h"

NoiseMedian::NoiseMedian(PNM* img) :
    Convolution(img)
{
}

NoiseMedian::NoiseMedian(PNM* img, ImageViewer* iv) :
    Convolution(img, iv)
{
}

PNM* NoiseMedian::transform()
{
    int width  = image->width();
    int height = image->height();

    PNM* newImage = new PNM(width, height, image->format());
    for (int x=0; x<width; x++){
           for (int y=0; y<height; y++){
		if (image->format() == QImage::Format_RGB32){
			int r=getMedian(x,y,RChannel);

		int 	g=getMedian(x,y,GChannel);
		int b=getMedian(x,y,BChannel);
		
			 if (r>255){
				r=255;				   
				
			 }

			if (r<0){
				r=0;
				  
			 }
			if (g>255){
				g=255;				   
				
			 }

			if (g<0){
				g=0;
				  
			 }
			if (b>255){
				b=255;				   
				
			 }

			if (b<0){
				b=0;
				  
			 }

			 QColor newPixel = QColor(r,g,b);
			  newImage->setPixel(x,y, newPixel.rgb()); 
}
	}
	}
	     if (image->format() == QImage::Format_Mono)
    {       for (int x=0; x<width; x++)
           for (int y=0; y<height; y++)
		
          {
                QRgb pixel = image->pixel(x,y);

                int v = qGray(pixel); 
				v=getMedian(x,y,LChannel);
				newImage->setPixel(x,y, v);

		   }
	 }
    return newImage;
}

int NoiseMedian::compare(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}

int NoiseMedian::getMedian(int x, int y, Channel channel)
{
    int radius = getParameter("radius").toInt();
	Mode mode=	RepeatEdge;
    int pod=radius*2+1;
    double table[100];
    int count=0;
       math::matrix<double> matrix = getWindow(x,y,pod,channel,mode);
	   
       for (int i=0; i<matrix.ColNo();i++){
           for (int j=0; j<matrix.RowNo();j++){
               table[count]=matrix(i,j);
               count++;
		   }
	   }
	  
    std::sort(&table[0],&table[count]);

return table[count/2];
}
