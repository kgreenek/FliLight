//------------------------------------------------------------------------------
#ifndef UPDOWNSWEEPANIMATION_H
#define UPDOWNSWEEPANIMATION_H

//------------------------------------------------------------------------------
#include "flanimation.h"
#include "beatdispenser.h"

//------------------------------------------------------------------------------
class UpDownSweepAnimation : public FlAnimation
{
public:
    explicit UpDownSweepAnimation();
    void beatDetected();
    void clockDetected();
    void setSweepSpeed(float newSweepSpeed) { sweepSpeed = newSweepSpeed; }

private:
    int clockCounter;
    int beatCounter;
    int currentLevel;

    enum SweepDirEnum {
        SWEEP_DIR_UP,
        SWEEP_DIR_DOWN
    };
    SweepDirEnum sweepDir;
    float sweepSpeed;

    void switchSweepDir();
    void renderCurrentLevel();
};

//------------------------------------------------------------------------------
#endif // UPDOWNSWEEPANIMATION_H

//------------------------------------------------------------------------------
