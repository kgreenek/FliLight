//------------------------------------------------------------------------------
#include "strobeanimation.h"

//------------------------------------------------------------------------------
StrobeAnimation::StrobeAnimation(QObject *parent) :
    FlAnimation(parent)
{
    memset(&cubeFrame, 0, sizeof(CubeFrame));  // This doesn't need to be done.
    sem.release();
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

        // Send our local CubeFrame to the cube to be drawn.
        render(&cubeFrame);
    }

    clockCounter++;

    sem.acquire();
    clockCounter %= (int) (NUM_CLOCKS_PER_BEAT / strobeSpeed);
    sem.release();
}

//------------------------------------------------------------------------------
// Position is the position of the slider, ranging from -1 to 3.
void StrobeAnimation::setStrobeSpeed(float position) {
    sem.acquire();
    strobeSpeed = pow(2, position);
    sem.release();
}

//------------------------------------------------------------------------------
void StrobeAnimation::toggleCube() {
    if (cubeFrame[0][0][0] != 0)
        memset(&cubeFrame, 0, sizeof(CubeFrame));
    else
        memset(&cubeFrame, 0xff, sizeof(CubeFrame));
}

//------------------------------------------------------------------------------
void StrobeAnimation::run() {
    qDebug() << "Starting StrobeAnimation";
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
