//------------------------------------------------------------------------------
#ifndef UPDOWNSWEEPANIMATION_H
#define UPDOWNSWEEPANIMATION_H

//------------------------------------------------------------------------------
#include <QSemaphore>

#include "beatdispenser.h"
#include "flanimation.h"
#include "cubemanager.h"

//------------------------------------------------------------------------------
class UpDownSweepAnimation : public FlAnimation
{
    Q_OBJECT
public:
    explicit UpDownSweepAnimation(QObject *parent = 0);
    void run();
    QSemaphore sem;
    float sweepSpeed;

private:
    CubeFrame cubeFrame;
    int clockCounter;
    int beatCounter;
    int currentLevel;

    enum SweepDirEnum {
        SWEEP_DIR_UP,
        SWEEP_DIR_DOWN
    };
    SweepDirEnum sweepDir;

    void switchSweepDir();
    void renderCurrentLevel();

public slots:
    void beatDetected();
    void clockDetected();
};

//------------------------------------------------------------------------------
#endif // UPDOWNSWEEPANIMATION_H

//------------------------------------------------------------------------------
