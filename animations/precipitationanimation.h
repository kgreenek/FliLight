//------------------------------------------------------------------------------
#ifndef PRECIPITATIONANIMATION_H
#define PRECIPITATIONANIMATION_H

//------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "flanimation.h"

//------------------------------------------------------------------------------
#define MAX_NUM_RAIN_DROPS 16

//------------------------------------------------------------------------------
struct RainDropPoint3D {
    Point3D pos;
    int isVisible;
    int drawCount;
};

//------------------------------------------------------------------------------
class PrecipitationAnimation : public FlAnimation
{
public:
    PrecipitationAnimation();
    void beatDetected();
    void clockDetected();

private:
    void init();
    void addRandomRainDrop();
    void updateRainDropPositions();
    void renderRainDrops();

    int clockCounter;
    struct RainDropPoint3D rainDropPts[MAX_NUM_RAIN_DROPS];
    int randDelay;
    int addRainDropDelayCount;
};

//------------------------------------------------------------------------------
#endif // PRECIPITATIONANIMATION_H

//------------------------------------------------------------------------------
