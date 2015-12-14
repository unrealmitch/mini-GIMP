#include "correction.h"

Correction::Correction(PNM* img) :
    Transformation(img)
{
}

Correction::Correction(PNM* img, ImageViewer* iv) :
    Transformation(img, iv)
{
}

PNM* Correction::transform()
{
    qDebug() << Q_FUNC_INFO << "Not implemented yet!";

    double shift  = getParameter("shift").toDouble();
    double factor = getParameter("factor").toDouble();
    double gamma  = getParameter("gamma").toDouble();

    int width  = image->width();
    int height = image->height();

    PNM* newImage = new PNM(width, height, image->format());

    if (image->format() == QImage::Format_Indexed8)
    {       for (int x=0; x<width; x++)
           for (int y=0; y<height; y++)
		
          {
				QRgb pixel = image->pixel(x,y); // Getting the pixel(x,y) value

                int v = qGray(pixel);    // Get the 0-255 value of the L channel
               v = add(v,shift);
				v = mult(v,factor);
			   v= power(v,gamma);

                newImage->setPixel(x,y, v);

   }
	}

	    else //if (image->format() == QImage::Format_RGB32)
    {
        // Iterate over image space
        for (int x=0; x<width; x++)
            for (int y=0; y<height; y++)
            {
           QRgb pixel = image->pixel(x,y); // Getting the pixel(x,y) value
		      
                int r = qRed(pixel);    // Get the 0-255 value of the R channel
                int g = qGreen(pixel);  // Get the 0-255 value of the G channel
                int b = qBlue(pixel);   // Get the 0-255 value of the B channel
				
           
			r = add(r,shift);
			r = mult(r,factor);
			r = power(r,gamma);
			g = add(r,shift);
			g = mult(r,factor);
			g = power(r,gamma);
            b = add(r,shift);
			b = mult(r,factor);
			b = power(r,gamma);
                QColor newPixel = QColor(r,g,b);
                newImage->setPixel(x,y, newPixel.rgb()); 
            }
    }
   
    				
			

    return newImage;
}

const int Correction::add(double value, double shift)
{
//    qDebug() << Q_FUNC_INFO << "Not implemented yet!";
	shift=shift+value;
if (shift>PIXEL_VAL_MAX){
		return PIXEL_VAL_MAX;
	}
	if (shift<PIXEL_VAL_MIN){
		return PIXEL_VAL_MIN;
	}
	
   
    return shift;
}

const  double Correction::mult(int value, double factor)
{
  //  qDebug() << Q_FUNC_INFO << "Not implemented yet!";
	factor = factor*value;
	if (factor>PIXEL_VAL_MAX){
		return PIXEL_VAL_MAX;
	}
	if (factor<PIXEL_VAL_MIN){
		return PIXEL_VAL_MIN;
	}
	else
 
    return factor;
}

const int Correction::power(int value, double power)
{
 //   qDebug() << Q_FUNC_INFO << "Not implemented yet!";
	power = pow(value,power);
	if (power>PIXEL_VAL_MAX){
		return PIXEL_VAL_MAX;
	}
	if (power<PIXEL_VAL_MIN){
		return PIXEL_VAL_MIN;
	}
	else
   return power;
}
