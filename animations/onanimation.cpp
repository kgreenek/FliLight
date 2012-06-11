//------------------------------------------------------------------------------
#include "onanimation.h"

//------------------------------------------------------------------------------
OnAnimation::OnAnimation(QObject *parent) :
    FlAnimation(parent)
{
    memset(&cubeFrame, 0xff, sizeof(CubeFrame));
}

//------------------------------------------------------------------------------
void OnAnimation::beatDetected() {
    // NOP
}

//------------------------------------------------------------------------------
void OnAnimation::clockDetected() {
    // NOP
}

//------------------------------------------------------------------------------
void OnAnimation::run() {
    qDebug() << "Starting OnAnimation";
    cubeManager.registerAnimation((FlAnimation *) this);

    render(&cubeFrame);

    exec();

    cubeManager.unRegisterAnimation((FlAnimation *) this);
}

//------------------------------------------------------------------------------
