//------------------------------------------------------------------------------
#include "flanimation.h"
#include "cubemanager.h"

//------------------------------------------------------------------------------
Point3D::Point3D() {
    x = 0; y = 0; z = 0;
}

//------------------------------------------------------------------------------
Point3D::Point3D(int x, int y, int z) {
    this->x = x; this->y = y; this->z = z;
}

//------------------------------------------------------------------------------
FlAnimation::FlAnimation(QObject *parent) :
    QThread(parent)
{
    running = false;
}

//------------------------------------------------------------------------------
// Override this always.
void FlAnimation::run() {
    qDebug() << "FlAnimation run";
    exec();
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
void FlAnimation::render(CubeFrame *cubeFrame) {
    cubeManager.render(this, cubeFrame);
}

//------------------------------------------------------------------------------
