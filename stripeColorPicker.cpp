#include "stripeColorPicker.h"

stripeColorPicker::stripeColorPicker(HSLAPixel fillColor, int stripeSpacing)
{
	color = fillColor;
	spacing = stripeSpacing;
/* your code here! */
}

HSLAPixel stripeColorPicker::operator()(int x, int y)
{
	if(x/spacing==0 || y/spacing==0)
		return color;
	else{
		HSLAPixel white;
		white.h = 0;
		white.s = 0;
		white.l = 1;
		return white;
	}
/* your code here! */
}
