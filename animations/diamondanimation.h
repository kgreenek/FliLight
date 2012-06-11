//------------------------------------------------------------------------------
#ifndef DIAMONDANIMATION_H
#define DIAMONDANIMATION_H

//------------------------------------------------------------------------------
#include <QDebug>

#include "flanimation.h"
#include "beatdispenser.h"
#include "cubeframe.h"

//------------------------------------------------------------------------------
class DiamondAnimation : public FlAnimation
{
public:
    DiamondAnimation(QObject *parent = 0);
    void run();

private:
    CubeFrame cubeFrame;
    int clockCounter;

    void renderDiamond();

public slots:
    void beatDetected();
    void clockDetected();
};

//------------------------------------------------------------------------------
#endif // DIAMONDANIMATION_H

//------------------------------------------------------------------------------
