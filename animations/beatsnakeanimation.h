//------------------------------------------------------------------------------
#ifndef BEATSNAKEANIMATION_H
#define BEATSNAKEANIMATION_H

//------------------------------------------------------------------------------
#include <QDebug>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "flanimation.h"
#include "beatdispenser.h"

#define DEFAULT_SNAKE_LEN 6
#define MAX_NUM_SNAKE_PTS 64

//------------------------------------------------------------------------------
class BeatSnakeAnimation : public FlAnimation
{
public:
    explicit BeatSnakeAnimation();
    void setSnakeLen(int value);
    void setCoolMode(bool newCoolMode) { coolMode = newCoolMode; }
    void beatDetected();
    void clockDetected();

private:
    void init();
    void moveSnake();
    void recalcDirVec();
    void renderSnake();

    Point3D dirVec;
    QList<Point3D *> snakePts;
    int snakeLen;
    bool coolMode;
    int clockCounter;
};

//------------------------------------------------------------------------------
#endif // BEATSNAKEANIMATION_H

//------------------------------------------------------------------------------
