//------------------------------------------------------------------------------
#ifndef PLANEANIMATION_H
#define PLANEANIMATION_H

//------------------------------------------------------------------------------
#include <QDebug>
#include "flanimation.h"
#include "beatdispenser.h"

//------------------------------------------------------------------------------
class PlaneAnimation : public FlAnimation
{
public:
    PlaneAnimation();
    void beatDetected();
    void clockDetected();

private:
    void renderPlane();

    float xCoefficient;
    float yCoefficient;
    int clockCounter;
    bool addingX;
    bool addingY;
};

//------------------------------------------------------------------------------
#endif // PLANEANIMATION_H

//------------------------------------------------------------------------------
