#include "customColorPicker.h"

customColorPicker::customColorPicker(PNG & writeImg, PNG & readImg)
{
/* Your code here! */
    reIm = readImg;
    wrim = writeimg;
}

HSLAPixel customColorPicker::operator()(int x, int y)
{
    unsigned int x0;
    unsigned int y0;

    x0 = (unsigned int) x % reIm.width();
    y0 = (unsigned int) y % reIm.height();

    HSLAPixel * writePixel = getPixel((unsigned)x,(unsigned)y);
    HSLAPixel * readPixel = getPixel(x0,y0);

    *writePixel = *readPixel;

}
