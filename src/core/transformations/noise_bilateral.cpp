#include "noise_bilateral.h"

NoiseBilateral::NoiseBilateral(PNM* img) :
    Convolution(img)
{
}

NoiseBilateral::NoiseBilateral(PNM* img, ImageViewer* iv) :
    Convolution(img, iv)
{
}

PNM* NoiseBilateral::transform()
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
			int r=getNeighbours(x,y,RChannel);

		int 	g=getNeighbours(x,y,GChannel);
		int b=getNeighbours(x,y,BChannel);
		
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
				v=getNeighbours(x,y,LChannel);
				newImage->setPixel(x,y, v);
		   }
	 }
    return newImage;
}

int NoiseBilateral::getNeighbours(int x, int y, Channel channel)
{
    int sigma_d = getParameter("sigma_d").toInt();
    int sigma_r = getParameter("sigma_r").toInt();
    int radius = sigma_d;
		Mode mode=	RepeatEdge;
	 math::matrix<double> okno = getWindow(x,y,radius*2+1,channel,mode);
	 int val=0;
	 int k=0;
	 int kernels;
	 for (int i=0; i<okno.RowNo();i++){
		 for (int j=0; j<okno.ColNo();j++){
			 kernels=g(i,j,sigma_d)*r(i,j,sigma_r);
			 val+=okno(i,j)*kernels;
			 k+=kernels;
		 }
	 }

  
	 if(k==0){
		 return val;
	 }
	 else{
    return val/k;
	 }
}

double NoiseBilateral::g(int x, int y, int sigma_d)
{
	double Pi=3.14;
	double e= 2.718281828459;
	double g=(pow(e,-(pow(x,2)+pow(y,2)))/2*pow(sigma_d,2));
   
    return g;



	
   
}

double NoiseBilateral::r(int v, int v_ij, int sigma_r)
{
    double Pi=3.14;
	double e= 2.718281828459;
	double g=pow(e,-(pow((v_ij-v),2)/2*pow(sigma_r,2)));
    return g;
}
