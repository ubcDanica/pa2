#include "customColorPicker.h"

customColorPicker::customColorPicker(PNG & writeImg, PNG & readImg)
{
/* Your code here! */
    reIm = readImg;
    wrIm = writeImg;
}

HSLAPixel customColorPicker::operator()(int x, int y)
{
    unsigned int x0;
    unsigned int y0;

    x0 = (unsigned int) x % reIm.width();
    y0 = (unsigned int) y % reIm.height();

    HSLAPixel * writePixel = wrIm.getPixel((unsigned)x,(unsigned)y);
    HSLAPixel * readPixel = reIm.getPixel(x0,y0);

    *writePixel = *readPixel;

    return *writePixel;

}
