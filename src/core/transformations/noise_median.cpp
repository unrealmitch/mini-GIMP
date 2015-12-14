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
	Mode mode = RepeatEdge;
    for (int x=0; x<width; x++){
           for (int y=0; y<height; y++){
		if (image->format() == QImage::Format_RGB32){
				QRgb pixel = getPixel(x,y,mode);
				// int r = qRed(pixel);    // Get the 0-255 value of the R channel
             //   int g = qGreen(pixel);  // Get the 0-255 value of the G channel
            //    int b = qBlue(pixel);
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

				//int average = 0.3 * r + 0.6 * g + 0.1 * b;
			
			//	newImage->setPixel(x,y, average);
			 QColor newPixel = QColor(r,g,b);
			  newImage->setPixel(x,y, newPixel.rgb()); 
}
	}
	}
	     if (image->format() == QImage::Format_Mono)
    {       for (int x=0; x<width; x++)
           for (int y=0; y<height; y++)
		
          {
				QRgb pixel = image->pixel(x,y); // Getting the pixel(x,y) value

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
	int pom=radius*2+1;
	double tablica[100];
	int licznik=0;
   	   math::matrix<double> okno = getWindow(x,y,pom,channel,mode);
	   //double u=okno(0,0);
	//  x=(okno.ColNo()-1)*(okno.RowNo()-1); 
	   
	   for (int i=0; i<okno.ColNo();i++){
		   for (int j=0; j<okno.RowNo();j++){
			   tablica[licznik]=okno(i,j);
			   licznik++;
		   }
	   }
	  
	std::sort(&tablica[0],&tablica[licznik]);

	//return 7;
return tablica[licznik/2];
}
