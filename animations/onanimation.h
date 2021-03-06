//------------------------------------------------------------------------------
#ifndef ONANIMATION_H
#define ONANIMATION_H

//------------------------------------------------------------------------------
#include <QDebug>
#include "flanimation.h"

//------------------------------------------------------------------------------
class OnAnimation : public FlAnimation
{
public:
    explicit OnAnimation();
    void beatDetected();
    void clockDetected();
};

//------------------------------------------------------------------------------
#endif // ONANIMATION_H

//------------------------------------------------------------------------------
