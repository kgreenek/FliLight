#ifndef PLANEANIMATION_H
#define PLANEANIMATION_H

#include <QDebug>

#include "cubemanager.h"
#include "beatdispenser.h"
#include "flanimation.h"
#include "cubeframe.h"

class PlaneAnimation : public FlAnimation
{
    Q_OBJECT
public:
    PlaneAnimation(QObject *parent = 0);
    void run();

private:
    void renderPlane();

    float xCoefficient;
    float yCoefficient;
    CubeFrame cubeFrame;
    int clockCounter;
    bool addingX;
    bool addingY;

public slots:
    void beatDetected();
    void clockDetected();
};

#endif // PLANEANIMATION_H
