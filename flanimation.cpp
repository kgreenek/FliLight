//------------------------------------------------------------------------------
#include "flanimation.h"

//------------------------------------------------------------------------------
Point3D::Point3D() {
    x = 0; y = 0; z = 0;
}

//------------------------------------------------------------------------------
Point3D::Point3D(int x, int y, int z) {
    this->x = x; this->y = y; this->z = z;
}

//------------------------------------------------------------------------------
FlAnimation::FlAnimation()
{
    setRunning(false);
    setDirty(false);
}

//------------------------------------------------------------------------------
// Override this if desired.
void FlAnimation::clockDetected() {
    qDebug() << "FlAnimation clock";
}

//------------------------------------------------------------------------------
// Override this if desired.
void FlAnimation::beatDetected() {
    qDebug() << "FlAnimation beat";
}

//------------------------------------------------------------------------------
void FlAnimation::setRunning(bool newRunning) {
    running = newRunning;
    if (running)
        init();
}

//------------------------------------------------------------------------------
