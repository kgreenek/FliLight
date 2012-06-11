#ifndef ONANIMATION_H
#define ONANIMATION_H

#include "flanimation.h"
#include "cubeframe.h"
#include "cubemanager.h"

class OnAnimation : public FlAnimation
{
    Q_OBJECT
public:
    explicit OnAnimation(QObject *parent = 0);
    void run();

private:
    CubeFrame cubeFrame;

public slots:
    void beatDetected();
    void clockDetected();
};

#endif // ONANIMATION_H
