#include "Balloon.h"

Balloon::Balloon() {
}

Balloon::~Balloon() {
} 

///Returns the HSV-values of the "color balloon".
Balloon::Balloon(string name){
    setType(name);
    
    if(name == "red"){
        setHSVmin(Scalar(0, 137, 0));
        setHSVmax(Scalar(64, 244, 214));
        setColour(Scalar(0,0,255));
    }
    
    if(name == "blue"){
        setHSVmin(Scalar(0, 137, 0));
        setHSVmax(Scalar(64, 244, 214));     
        setColour(Scalar(0,255,0));
    }
}

