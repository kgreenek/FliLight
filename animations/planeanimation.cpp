//------------------------------------------------------------------------------
#include "planeanimation.h"

//------------------------------------------------------------------------------
PlaneAnimation::PlaneAnimation(QObject *parent) :
    FlAnimation(parent)
{
    memset(&cubeFrame, 0, sizeof(CubeFrame));  // This doesn't need to be done.
    clockCounter = 0;
    xCoefficient = -0.5;
    yCoefficient = 0.5;
    addingX = true;
}

//------------------------------------------------------------------------------
void PlaneAnimation::beatDetected() {
    // NOP
}

//------------------------------------------------------------------------------
void PlaneAnimation::clockDetected() {
    if (clockCounter == 0) {
        if (addingX) {
            if (xCoefficient >= 0.5)
                addingX = false;
        }
        else {
            if (xCoefficient <= -0.5)
                addingX = true;
        }

        if (addingY) {
            if (yCoefficient >= 0.75)
                addingY = false;
        }
        else {
            if (yCoefficient <= -0.75)
                addingY = true;
        }

        if (addingX) {
            xCoefficient += 0.25;
        }
        else {
            xCoefficient -= 0.25;
        }

        if (addingY) {
            yCoefficient += 0.25;
        }
        else {
            yCoefficient -= 0.25;
        }

        // qDebug() << "xCoeff " << xCoefficient;

        renderPlane();
    }
    clockCounter++;
    clockCounter %= NUM_CLOCKS_PER_BEAT / 6;
}

//------------------------------------------------------------------------------
void PlaneAnimation::renderPlane() {
    memset(&cubeFrame, 0, sizeof(CubeFrame));

    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            float z = (xCoefficient * (x - 3) + yCoefficient * (y - 3) + 3);

            // Round z to nearest int value.
            int zInt = z;
            if (z - zInt >= 0.5)
                zInt++;

            if (zInt >= 0 && zInt < 8)
                cubeFrame[zInt][y][0] |= 1 << x;
        }
    }

    // Send our CubeFrame to the cube to be drawn.
    render(&cubeFrame);
}

//------------------------------------------------------------------------------
void PlaneAnimation::run() {
    qDebug() << "Starting PlaneAnimation";
    cubeManager.registerAnimation((FlAnimation *) this);

    renderPlane();

    QObject::connect(&beatDetector, SIGNAL(beatDetected()),
                     this, SLOT(beatDetected()));
    QObject::connect(&beatDetector, SIGNAL(clockDetected()),
                     this, SLOT(clockDetected()));

    exec();

    QObject::disconnect(&beatDetector, SIGNAL(beatDetected()),
                        this, SLOT(beatDetected()));
    QObject::disconnect(&beatDetector, SIGNAL(clockDetected()),
                        this, SLOT(clockDetected()));

    cubeManager.unRegisterAnimation((FlAnimation *) this);
}

//------------------------------------------------------------------------------
