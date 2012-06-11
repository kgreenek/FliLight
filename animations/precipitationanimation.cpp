//------------------------------------------------------------------------------
#include "precipitationanimation.h"

//------------------------------------------------------------------------------
PrecipitationAnimation::PrecipitationAnimation(QObject *parent) :
    FlAnimation(parent)
{
    memset(&cubeFrame, 0, sizeof(CubeFrame));  // This doesn't need to be done.
    srand(time(NULL));
    addRainDropDelayCount = 0;
    randDelay = 0;
}

//------------------------------------------------------------------------------
void PrecipitationAnimation::beatDetected() {
    // NOP
}

//------------------------------------------------------------------------------
// 24 clock signals are sent per beat.
void PrecipitationAnimation::clockDetected() {
    addRainDropDelayCount++;
    if (addRainDropDelayCount > randDelay) {
        addRainDropDelayCount = 0;
        randDelay = rand() % 20 + 5;
        addRandomRainDrop();
    }

    updateRainDropPositions();
    renderRainDrops();
}

//------------------------------------------------------------------------------
void PrecipitationAnimation::initSlowRainAnimation() {
    randDelay = rand() % 20 + 5;

    // Initialize all the raindrops as not visible with pos [0, 0, 0].
    for (int i = 0; i < MAX_NUM_RAIN_DROPS; i++) {
        rainDropPts[i].isVisible = 0;
        rainDropPts[i].drawCount = 0;
        rainDropPts[i].pos.x = 0;
        rainDropPts[i].pos.y = 0;
        rainDropPts[i].pos.z = 0;
    }
}

//------------------------------------------------------------------------------
void PrecipitationAnimation::addRandomRainDrop() {
    for (int i = 0; i < MAX_NUM_RAIN_DROPS; i++) {
        // Find a rain drop that is not yet visible.
        if (rainDropPts[i].isVisible)
            continue;

        rainDropPts[i].isVisible = 1;
        rainDropPts[i].drawCount = 0;
        rainDropPts[i].pos.x = rand() % 8;
        rainDropPts[i].pos.y = rand() % 4;
        rainDropPts[i].pos.z = rand() % 8;
        break;
    }
}

//------------------------------------------------------------------------------
void PrecipitationAnimation::updateRainDropPositions() {
    for (int i = 0; i < MAX_NUM_RAIN_DROPS; i++) {
        if (!rainDropPts[i].isVisible)
                continue;

        rainDropPts[i].drawCount++;
        if (rainDropPts[i].drawCount > 200 &&
            rainDropPts[i].drawCount % 2) {
            rainDropPts[i].pos.y++;
            if (rainDropPts[i].pos.y >= CUBE_NUM_LEVELS)
                rainDropPts[i].isVisible = 0;
        }
    }
}

//------------------------------------------------------------------------------
void PrecipitationAnimation::renderRainDrops() {
    // Update the displayFrame based on the rainDropPts.
    memset(&cubeFrame, 0, sizeof(CubeFrame));
    for (int i = 0; i < MAX_NUM_RAIN_DROPS; i++) {
        if (!rainDropPts[i].isVisible)
            continue;

        int level = rainDropPts[i].pos.y;
        int row = rainDropPts[i].pos.z;
        cubeFrame[level][row][0] |= 1 << rainDropPts[i].pos.x;
    }

    // Send our local CubeFrame to the cube to be drawn.
    render(&cubeFrame);
}

//------------------------------------------------------------------------------
void PrecipitationAnimation::run() {
    qDebug() << "Starting PrecipitationAnimation";
    cubeManager.registerAnimation((FlAnimation *) this);

    initSlowRainAnimation();

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
