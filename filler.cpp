/**
 * @file filler.cpp
 * Implementation of functions in the filler namespace. 
 *
 */
//#include "filler.h"

animation filler::fillStripeDFS(PNG& img, int x, int y, HSLAPixel fillColor,
                                int stripeSpacing, double tolerance, int frameFreq)
{ 
    /**
     * @todo Your code here! 
     */
    stripeColorPicker a(fillColor, stripeSpacing);
    return fill<Stack>(img, x, y, a, tolerance, frameFreq);
}

animation filler::fillBorderDFS(PNG& img, int x, int y,
                                    HSLAPixel borderColor, double tolerance, int frameFreq)
{ 
    /**
     * @todo Your code here! 
     */
    HSLAPixel *center = img.getPixel(x,y);

    borderColorPicker a(borderColor, img, tolerance, *center);
    return fill<Stack>(img, x, y, a, tolerance, frameFreq);
}

/* Given implementation of a DFS rainbow fill. */
animation filler::fillRainDFS(PNG& img, int x, int y,
                                    long double freq, double tolerance, int frameFreq)
{
    rainbowColorPicker a(freq);
    return fill<Stack>(img, x, y, a, tolerance, frameFreq);
}

animation filler::fillStripeBFS(PNG& img, int x, int y, HSLAPixel fillColor,
                                int stripeSpacing, double tolerance, int frameFreq)
{
    /**
     * @todo Your code here! 
     */
    stripeColorPicker a(fillColor, stripeSpacing);
    return fill<Queue>(img, x, y, a, tolerance, frameFreq);
}

animation filler::fillBorderBFS(PNG& img, int x, int y,
                                    HSLAPixel borderColor, double tolerance, int frameFreq)
{
    /**
     * @todo Your code here! You should replace the following line with a
     */
    HSLAPixel *center = img.getPixel(x,y);

    borderColorPicker a(borderColor, img, tolerance, *center);
    return fill<Queue>(img, x, y, a, tolerance, frameFreq);
}

/* Given implementation of a BFS rainbow fill. */
animation filler::fillRainBFS(PNG& img, int x, int y,
                                    long double freq, double tolerance, int frameFreq)
{
    rainbowColorPicker a(freq);
    return fill<Queue>(img, x, y, a, tolerance, frameFreq);
}

animation filler::fillCustomDFS(PNG& writeImg, PNG& readImg, int x, int y, double tolerance, int frameFreq)
{
    customColorPicker a(writeImg,readImg);
    return fill<Stack>(writeImg, x, y, a, tolerance, frameFreq);
}

animation filler::fillCustomBFS(PNG& writeImg, PNG& readImg, int x, int y, double tolerance, int frameFreq)
{
    customColorPicker a(writeImg,readImg);
    return fill<Queue>(writeImg, x, y, a, tolerance, frameFreq);

}

template <template <class T> class OrderingStructure>
animation filler::fill(PNG& img, int x, int y, colorPicker& fillColor,
                       double tolerance, int frameFreq)
{
    OrderingStructure<std::pair<int,int>> ordering;
    int x0;
    int y0;
    int fill = 0;
    HSLAPixel *pixelCenter = img.getPixel((unsigned int)x,(unsigned int)y);
    HSLAPixel *center = new HSLAPixel(pixelCenter->h, pixelCenter->s, pixelCenter->l, pixelCenter->a);
    animation anim;

    std::vector<std::vector<int>> marked(img.width(), vector<int> (img.height(), 0));

    Add(img,x,y,tolerance,center,marked,fill,frameFreq, ordering, anim, fillColor);

    if(fill%frameFreq == 0){
        //cout<< "should add frame"<<endl;
        anim.addFrame(img);
    }

    if(!ordering.isEmpty())
        cout<<"not empty now"<<endl;
    pair<int,int> firstElement = ordering.peek();


    while(!ordering.isEmpty()){
        pair<int,int> element = ordering.remove();
        x0 = element.first;
        y0 = element.second;

        Add(img,x0+1,y0-1,tolerance,center,marked,fill,frameFreq, ordering, anim, fillColor);
        Add(img,x0,y0-1,tolerance,center,marked,fill,frameFreq, ordering, anim, fillColor);
        Add(img,x0-1,y0-1,tolerance,center,marked,fill,frameFreq, ordering, anim, fillColor);
        Add(img,x0-1,y0,tolerance,center,marked,fill,frameFreq, ordering, anim, fillColor);
        Add(img,x0-1,y0+1,tolerance,center,marked,fill,frameFreq, ordering, anim, fillColor);
        Add(img,x0,y0+1,tolerance,center,marked,fill,frameFreq, ordering, anim, fillColor);
        Add(img,x0+1,y0+1,tolerance,center,marked,fill,frameFreq, ordering, anim, fillColor);
        Add(img,x0+1,y0,tolerance,center,marked,fill,frameFreq, ordering, anim, fillColor);

    }

    cout << "add last frame" <<endl;
    anim.addFrame(img);

    return anim;
    
}

    bool filler::Add(PNG& img, int x,int y,double tolerance, HSLAPixel *center, std::vector<std::vector<int>> &marked,
                    int &fill, int frameFreq, OrderingStructure<std::pair<int,int>> &ordering, animation &anim, colorPicker &fillColor){

        if((unsigned int)x<img.width() && x>=0 && (unsigned int)y<img.height() && y>=0){

            HSLAPixel *pixel = img.getPixel((unsigned int)x,(unsigned int)y);

            if(marked[x][y] == 0 && (pixel->dist(*center)<= tolerance)){

                ordering.add(pair<int,int>(x,y));
/*                cout<<"x: ";
                cout<<x<<endl;
                cout<<"y: ";
                cout<<y<<endl;*/

                *pixel = fillColor(x,y);
                marked[x][y] = 1;
                fill++;
                if(fill%frameFreq == 0){
                    //cout<< "should add frame"<<endl;
                    anim.addFrame(img);
                }
                return true;

            }
            else{
/*                if(mark.count(pair<int,int>(x,y))!=0){
                cout<<"marked: ";
                cout<<mark.count(pair<int,int>(x,y))<<endl;
}*/
                return false;
            }
    	}

        else{
        	return false;
        }
  }

    /**
     * @todo You need to implement this function!
     *
     * This is the basic description of a flood-fill algorithm: Every fill
     * algorithm requires an ordering structure, which is passed to this
     * function via its template parameter. For a breadth-first-search
     * fill, that structure is a Queue, for a depth-first-search, that
     * structure is a Stack. To begin the algorithm, you simply place the
     * given point in the ordering structure, marking it processed
     * (the way you mark it is a design decision you'll make yourself).
     * We have a choice to either change the color, if appropriate, when we
     * add the point to the OS, or when we take it off. In our test cases,
     * we have assumed that you will change the color when a point is added
     * to the structure. 
     *
     * Until the structure is empty, you do the following:
     *
     * 1.     Remove a point from the ordering structure, and then...
     *
     *        1.    add its unprocessed neighbors whose color values are 
     *              within (or equal to) tolerance distance from the center, 
     *              to the ordering structure.
     *        2.    use the colorPicker to set the new color of the point.
     *        3.    mark the point as processed.
     *        4.    if it is an appropriate frame, send the current PNG to the
     *              animation (as described below).
     *
     * 2.     When implementing your breadth-first-search and
     *        depth-first-search fills, you will need to explore neighboring
     *        pixels in some order.
     *
     *        For this assignment, each pixel p has 8 neighbors, consisting of 
     *        the 8 pixels who share an edge or corner with p. (We leave it to
     *        you to describe those 8 pixel locations, relative to the location
     *        of p.)
     *
     *        While the order in which you examine neighbors does not matter
     *        for a proper fill, you must use the same order as we do for
     *        your animations to come out like ours! 
     *
     *        The order you should put
     *        neighboring pixels **ONTO** the ordering structure (queue or stack) 
     *        is as follows: **UPRIGHT(+x,-y), UP(-y), UPLEFT(-x,-y), LEFT(-x), 
     *        DOWNLEFT(-x,+y), DOWN(+y), DOWNRIGHT(+x,+y), RIGHT(+x)**
     *
     *        If you do them in a different order, your fill may
     *        still work correctly, but your animations will be different
     *        from the grading scripts!
     *
     *        IMPORTANT NOTE: *UP*
     *        here means towards the top of the image, so since an image has
     *        smaller y coordinates at the top, this is in the *negative y*
     *        direction. Similarly, *DOWN* means in the *positive y*
     *        direction.  
     *
     * 3.     For every k pixels filled, **starting at the kth pixel**, you
     *        must add a frame to the animation, where k = frameFreq.
     *
     *        For example, if frameFreq is 4, then after the 4th pixel has
     *        been filled you should add a frame to the animation, then again
     *        after the 8th pixel, etc.  You must only add frames for the
     *        number of pixels that have been filled, not the number that
     *        have been checked. So if frameFreq is set to 1, a pixel should
     *        be filled every frame.
     * 4.     Finally, as you leave the function, send one last frame to the
     *        animation. This frame will be the final result of the fill, and 
     *        it will be the one we test against.
     */


