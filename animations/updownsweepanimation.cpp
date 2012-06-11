//------------------------------------------------------------------------------
#include "updownsweepanimation.h"

//------------------------------------------------------------------------------
UpDownSweepAnimation::UpDownSweepAnimation(QObject *parent) :
    FlAnimation(parent)
{
    sem.release();
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
    // qDebug() << "UpDownSweepAnimation beat";
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

        // Send our local CubeFrame to the cube to be drawn.
        render(&cubeFrame);

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
    sem.acquire();
    clockCounter %= (int) (NUM_CLOCKS_PER_BEAT / CUBE_NUM_LEVELS * sweepSpeed);
    sem.release();
}

//------------------------------------------------------------------------------
// Update our local CubeFrame based on currentLevel.
void UpDownSweepAnimation::renderCurrentLevel() {
    memset(cubeFrame, 0, sizeof(CubeFrame));
    memset(&cubeFrame[currentLevel], 0xFF, sizeof(CubeLevel));
}

//------------------------------------------------------------------------------
void UpDownSweepAnimation::run() {
    qDebug() << "Starting UpDownSweepAnimation";
    cubeManager.registerAnimation((FlAnimation *) this);

    QObject::connect(&beatDetector, SIGNAL(beatDetected()),
                     this, SLOT(beatDetected()));
    QObject::connect(&beatDetector, SIGNAL(clockDetected()),
                     this, SLOT(clockDetected()));

    // Will run until the quit() function is called, and will then return.
    exec();

    QObject::disconnect(&beatDetector, SIGNAL(beatDetected()),
                        this, SLOT(beatDetected()));
    QObject::disconnect(&beatDetector, SIGNAL(clockDetected()),
                        this, SLOT(clockDetected()));

    cubeManager.unRegisterAnimation((FlAnimation *) this);
}

//------------------------------------------------------------------------------
