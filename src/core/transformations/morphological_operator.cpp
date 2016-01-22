#include "morphological_operator.h"

MorphologicalOperator::MorphologicalOperator(PNM* img) :
    Transformation(img)
{
}

MorphologicalOperator::MorphologicalOperator(PNM* img, ImageViewer* iv) :
    Transformation(img, iv)
{
}

const int MorphologicalOperator::morph(math::matrix<double>, math::matrix<bool>)
{
    return 0;
}

math::matrix<bool> MorphologicalOperator::getSE(int size, SE shape)
{
    switch (shape)
    {
    case Square:    return seSquare(size);
    case Cross:     return seCross(size);
    case XCross:    return seXCross(size);
    case VLine:     return seVLine(size);
    case HLine:     return seHLine(size);
    default:        return seSquare(size);
    }
}


math::matrix<bool> MorphologicalOperator::seSquare(int size)
{
    math::matrix<bool> ret(size, size);

    for (int i=0; i<size;i++){
		for (int j=0;j<size;j++){
			ret(i,j)=true;
		}
	}

    return ret;
}

math::matrix<bool> MorphologicalOperator::seCross(int size)
{
    math::matrix<bool> ret(size, size);

      for (int i=0; i<size;i++){
		for (int j=0;j<size;j++){
			if(i==size/2  || j==size/2){
				ret(i,j)=true;
			}
			else{
		
			ret(i,j)=false;
			}
			}
	}

    return ret;
}

math::matrix<bool> MorphologicalOperator::seXCross(int size)
{
    math::matrix<bool> ret(size, size);

        for (int i=0; i<size;i++){
		for (int j=0;j<size;j++){
			if(i==j  || i==size-j){
				ret(i,j)=true;
			}
			else{
		
			ret(i,j)=false;
			}
			}
	}

    return ret;
}

math::matrix<bool> MorphologicalOperator::seVLine(int size)
{
    math::matrix<bool> ret(size, size);

    for (int i=0; i<size;i++){
		for (int j=0;j<size;j++){
			if(i==size/2){
				ret(i,j)=true;
			}
			else{
		
			ret(i,j)=false;
			}
			}
	}

    return ret;
}

math::matrix<bool> MorphologicalOperator::seHLine(int size)
{
    math::matrix<bool> ret(size, size);

       for (int i=0; i<size;i++){
		for (int j=0;j<size;j++){
			if(j==size/2){
				ret(i,j)=true;
			}
			else{
		
			ret(i,j)=false;
			}
			}
	}


    return ret;
}

PNM* MorphologicalOperator::transform()
{  
    int width  = image->width();
    int height = image->height();
    int size  = getParameter("size").toInt();
    SE  shape = (MorphologicalOperator::SE) getParameter("shape").toInt();
    math::matrix<bool> shape2=getSE(size,shape);
    PNM* newImage = new PNM(image->width(), image->height(), image->format());
    if (image->format() == QImage::Format_RGB32){
    for (int x=0; x<width; x++){
           for (int y=0; y<height; y++){
                math::matrix<double> cR = getWindow(x,y,size,RChannel,RepeatEdge);
                math::matrix<double> cG = getWindow(x,y,size,GChannel,RepeatEdge);
                math::matrix<double> cB = getWindow(x,y,size,BChannel,RepeatEdge);

    double r=morph(cR,shape2);
    double g=morph(cG,shape2);
    double b=morph(cB,shape2);
	 QColor newPixel = QColor(r,g,b);
			  newImage->setPixel(x,y, newPixel.rgb());
			   }
			  
		   }
   }
	  
     if (image->format() == QImage::Format_Mono)
    {      
		for (int x=0; x<width; x++)
           for (int y=0; y<height; y++)
		
          {
            math::matrix<double> cL=getWindow(x,y,size,LChannel,RepeatEdge);
            double v=morph(cL,shape2);
			newImage->setPixel(x,y, v);
		   }
	 }

    return newImage;
}
