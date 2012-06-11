//------------------------------------------------------------------------------
#ifndef PRECIPITATIONANIMATION_H
#define PRECIPITATIONANIMATION_H

//------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "beatdispenser.h"
#include "flanimation.h"
#include "cubeframe.h"
#include "cubemanager.h"

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
    Q_OBJECT
public:
    PrecipitationAnimation(QObject *parent = 0);
    void run();

private:
    void initSlowRainAnimation();
    void addRandomRainDrop();
    void updateRainDropPositions();
    void renderRainDrops();

    int clockCounter;
    CubeFrame cubeFrame;
    struct RainDropPoint3D rainDropPts[MAX_NUM_RAIN_DROPS];
    int randDelay;
    int addRainDropDelayCount;

public slots:
    void beatDetected();
    void clockDetected();
};

//------------------------------------------------------------------------------
#endif // PRECIPITATIONANIMATION_H

//------------------------------------------------------------------------------
