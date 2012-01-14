//------------------------------------------------------------------------------
#include "flanimation.h"
#include "cubemanager.h"

//------------------------------------------------------------------------------
FlAnimation::FlAnimation(QObject *parent) :
    QThread(parent)
{
    running = false;
}

//------------------------------------------------------------------------------
void FlAnimation::run() {
    // Override this.
    qDebug() << "FlAnimation run";
}

//------------------------------------------------------------------------------
void FlAnimation::beatDetected() {
    // Override this.
    qDebug() << "FlAnimation beat";
}

//------------------------------------------------------------------------------
void FlAnimation::render(CubeFrame *cubeFrame) {
    cubeManager.render(this, cubeFrame);
}

//------------------------------------------------------------------------------
