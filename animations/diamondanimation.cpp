//------------------------------------------------------------------------------
#include "diamondanimation.h"

//------------------------------------------------------------------------------
DiamondAnimation::DiamondAnimation(QObject *parent) :
    FlAnimation(parent)
{

}

//------------------------------------------------------------------------------
void DiamondAnimation::renderDiamond() {

}

//------------------------------------------------------------------------------
void DiamondAnimation::beatDetected() {

}

//------------------------------------------------------------------------------
// 24 clock signals are sent per beat.
void DiamondAnimation::clockDetected() {
    if (clockCounter == 0) {

        // Send our local CubeFrame to the cube to be drawn.
        render(&cubeFrame);


    }
}

//------------------------------------------------------------------------------
void DiamondAnimation::run() {
    qDebug() << "Starting DiamondAnimation";

    QObject::connect(&beatDetector, SIGNAL(beatDetected()),
                     this, SLOT(beatDetected()));
    QObject::connect(&beatDetector, SIGNAL(clockDetected()),
                     this, SLOT(clockDetected()));

    exec();
}

//------------------------------------------------------------------------------
