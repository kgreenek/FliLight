//------------------------------------------------------------------------------
#ifndef DIAMONDANIMATION_H
#define DIAMONDANIMATION_H

//------------------------------------------------------------------------------
#include <QDebug>
#include "flanimation.h"

//------------------------------------------------------------------------------
class DiamondAnimation : public FlAnimation
{
public:
    DiamondAnimation();

private:
    CubeFrame cubeFrame;
    int clockCounter;

    void renderDiamond();

};

//------------------------------------------------------------------------------
#endif // DIAMONDANIMATION_H

//------------------------------------------------------------------------------
