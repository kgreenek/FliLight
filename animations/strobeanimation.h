//------------------------------------------------------------------------------
#ifndef STROBEANIMATION_H
#define STROBEANIMATION_H

//------------------------------------------------------------------------------
#include <math.h>
#include "flanimation.h"
#include "beatdispenser.h"

//------------------------------------------------------------------------------
class StrobeAnimation : public FlAnimation
{
public:
    StrobeAnimation();
    void beatDetected();
    void clockDetected();
    void setStrobeSpeed(float speed);

private:
    void toggleCube();

    int clockCounter;
    float strobeSpeed;
};

//------------------------------------------------------------------------------
#endif // STROBEANIMATION_H

//------------------------------------------------------------------------------
