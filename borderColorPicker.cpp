#include "borderColorPicker.h"

borderColorPicker::borderColorPicker(HSLAPixel fillColor, PNG & img, double tolerance,HSLAPixel center)
{
/* Your code here! */
	color = fillColor;
	im = img;
	tol = tolerance;
	ctr = center;
}

HSLAPixel borderColorPicker::operator()(int x, int y)
{

/* Your code here! */
	HSLAPixel *newColor = im.getPixel((unsigned int)x, (unsigned int)y);
	if((*newColor == ctr && isFillBorder(x,y)) || (*newColor == ctr && isImgBorder(x,y))){
		return color;
	}
	else{
		return *newColor;
	}
    
}

bool borderColorPicker::isFillBorder(int x, int y){
	for(unsigned int x_=0; x_<im.width(); x_++){
		for(unsigned int y_=0; y_<im.height(); y_++){
			HSLAPixel *pixel = im.getPixel(x_,y_);
			double disSquare = ((unsigned int)x-x_)*((unsigned int)x-x_) + ((unsigned int)y-y_)*((unsigned int)y-y_);
			if(disSquare<=9 && (ctr.dist(* pixel) >= tol))
				return true;
		}
	}
	return false;
}

bool borderColorPicker::isImgBorder(int x, int y){
	if((double)x+3 >= im.width() || (double)x-3<0 || (double)y+3 >= im.height() || (double)y-3<0)
		return true;
	else
		return false;
}
