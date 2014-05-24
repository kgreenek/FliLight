//------------------------------------------------------------------------------
#include "updownsweepanimation.h"

//------------------------------------------------------------------------------
UpDownSweepAnimation::UpDownSweepAnimation()
{
    memset(&cubeFrame, 0, sizeof(CubeFrame));  // This doesn't need to be done.
    currentLevel = 0;
    clockCounter = 0;
    beatCounter = 0;
    sweepSpeed = 2;
    sweepDir = SWEEP_DIR_UP;
}

//------------------------------------------------------------------------------
void UpDownSweepAnimation::switchSweepDir() {
    switch (sweepDir) {
        case SWEEP_DIR_UP:
            currentLevel = CUBE_NUM_LEVELS - 1;
            sweepDir = SWEEP_DIR_DOWN;
            clockCounter = 0;
            break;
        case SWEEP_DIR_DOWN:
            currentLevel = 0;
            sweepDir = SWEEP_DIR_UP;
            clockCounter = 0;
            break;
    }
}

//------------------------------------------------------------------------------
void UpDownSweepAnimation::beatDetected() {
    if (sweepSpeed >= 1) {
        if (beatCounter % (int) sweepSpeed == 0) {
            beatCounter = 0;
            switchSweepDir();
        }
    }
    else {
        beatCounter = 0;
        switchSweepDir();
    }
    beatCounter++;
}

//------------------------------------------------------------------------------
// 24 clock signals are sent per beat.
void UpDownSweepAnimation::clockDetected() {
    if (clockCounter == 0) {
        // qDebug() << "Drawing level " << currentLevel;

        // Update our local CubeFrame with the new level.
        renderCurrentLevel();

        // Update currentLevel for next time.
        switch (sweepDir) {
            case SWEEP_DIR_UP:
                currentLevel++;
                if (currentLevel >= CUBE_NUM_LEVELS)
                    currentLevel = CUBE_NUM_LEVELS - 1;
                break;
            case SWEEP_DIR_DOWN:
                currentLevel--;
                if (currentLevel < 0)
                    currentLevel = 0;
        }
    }

    // Update clockCounter.
    clockCounter++;
    clockCounter %= (int) (NUM_CLOCKS_PER_BEAT / CUBE_NUM_LEVELS * sweepSpeed);
}

//------------------------------------------------------------------------------
// Update our local CubeFrame based on currentLevel.
void UpDownSweepAnimation::renderCurrentLevel() {
    memset(&cubeFrame, 0, sizeof(CubeFrame));
    memset(&cubeFrame[currentLevel], 0xFF, sizeof(CubeLevel));
    setDirty(true);
}

//------------------------------------------------------------------------------
