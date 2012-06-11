//------------------------------------------------------------------------------
#ifndef BEATSNAKEANIMATION_H
#define BEATSNAKEANIMATION_H

//------------------------------------------------------------------------------
#include <QThread>
#include <QDebug>
#include <QSemaphore>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "beatdispenser.h"
#include "flanimation.h"
#include "cubemanager.h"

#define DEFAULT_SNAKE_LEN 6
#define MAX_NUM_SNAKE_PTS 64

//------------------------------------------------------------------------------
class BeatSnakeAnimation : public FlAnimation
{
    Q_OBJECT
public:
    explicit BeatSnakeAnimation(QObject *parent = 0);    
    void run();
    void setSnakeLen(int value);

    bool coolMode;

private:
    void initSnakeAnimation();
    void moveSnake();
    void recalcDirVec();
    void renderSnake();

    CubeFrame cubeFrame;
    Point3D dirVec;
    QList<Point3D *> snakePts;
    int snakeLen;
    int clockCounter;
    QSemaphore sem;

signals:

public slots:
    void beatDetected();
    void clockDetected();
};

//------------------------------------------------------------------------------
#endif // BEATSNAKEANIMATION_H

//------------------------------------------------------------------------------
