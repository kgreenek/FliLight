//------------------------------------------------------------------------------
#include "strobeanimation.h"

//------------------------------------------------------------------------------
StrobeAnimation::StrobeAnimation()
{
    memset(&cubeFrame, 0, sizeof(CubeFrame));  // This doesn't need to be done.
    clockCounter = 0;
}

//------------------------------------------------------------------------------
void StrobeAnimation::beatDetected() {
    clockCounter = 0;
}

//------------------------------------------------------------------------------
// 24 clock signals are sent per beat.
void StrobeAnimation::clockDetected() {
    if (clockCounter == 0) {
        // Invert the cube (if its on, turn it off).
        toggleCube();
        setDirty(true);
    }
    clockCounter++;
    clockCounter %= (int) (NUM_CLOCKS_PER_BEAT / strobeSpeed);
}

//------------------------------------------------------------------------------
// Position is the position of the slider, ranging from -1 to 3.
void StrobeAnimation::setStrobeSpeed(float position) {
    strobeSpeed = pow(2, position);
}

//------------------------------------------------------------------------------
void StrobeAnimation::toggleCube() {
    if (cubeFrame[0][0][0] != 0)
        memset(&cubeFrame, 0, sizeof(CubeFrame));
    else
        memset(&cubeFrame, 0xff, sizeof(CubeFrame));
}

//------------------------------------------------------------------------------
