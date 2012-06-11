//------------------------------------------------------------------------------
#ifndef STROBEANIMATION_H
#define STROBEANIMATION_H

//------------------------------------------------------------------------------
#include <QSemaphore>

#include <math.h>

#include "flanimation.h"
#include "cubeframe.h"
#include "beatdispenser.h"
#include "cubemanager.h"

//------------------------------------------------------------------------------
class StrobeAnimation : public FlAnimation
{
    Q_OBJECT
public:
    StrobeAnimation(QObject *parent = 0);
    void run();
    void setStrobeSpeed(float speed);

private:
    void toggleCube();

    int clockCounter;
    CubeFrame cubeFrame;
    QSemaphore sem;
    float strobeSpeed;

public slots:
    void beatDetected();
    void clockDetected();
};

//------------------------------------------------------------------------------
#endif // STROBEANIMATION_H

//------------------------------------------------------------------------------
