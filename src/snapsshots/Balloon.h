#ifndef BALLOON_H
#define	BALLOON_H
#include <string>
#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp> //for: VideoCapture
#include <opencv2/imgproc/imgproc.hpp> //for: getStructuringElement & findContours & cvtColorv

using namespace std;
using namespace cv;

class Balloon {
public:
    Balloon(); 
    virtual ~Balloon();
    
    Balloon(string name);

    int getXPos() { return xPos; }
    void setXPos(int x) { xPos = x; }

    int getYPos() { return yPos; }
    void setYPos(int y) { yPos = y; }
    
    string getType() { return type; }
    void setType(string t) { type = t; }
    
    Scalar getHSVmin() { return HSVmin; }
    void setHSVmin(Scalar min) { HSVmin = min; } 
    
    Scalar getHSVmax() {return HSVmax; }
    void setHSVmax(Scalar max) { HSVmax = max; } 
    
    Scalar getColour() { return colour; }
    void setColour(Scalar c) { colour = c;}
    
private:

    int xPos, yPos;
    // Decipher wich colour of balloon.
    string type;
    Scalar HSVmin, HSVmax;
    
    // displays wich balloon is the target.
    Scalar colour;
};

#endif	/* BALLOON_H */

