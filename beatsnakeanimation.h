//------------------------------------------------------------------------------
#ifndef BEATSNAKEANIMATION_H
#define BEATSNAKEANIMATION_H

//------------------------------------------------------------------------------
#include <QThread>
#include <QDebug>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "midibeatdetector.h"
#include "flanimation.h"
#include "cubemanager.h"

#define DEFAULT_SNAKE_LEN 6

//------------------------------------------------------------------------------
class Point3D {
public:
    Point3D();
    Point3D(int x, int y, int z);
    int x;
    int y;
    int z;
};

//------------------------------------------------------------------------------
class BeatSnakeAnimation : public FlAnimation
{
    Q_OBJECT
public:
    explicit BeatSnakeAnimation(QObject *parent = 0);    
    void run();

private:
    void moveSnake();
    void recalcDirVec();
    void renderSnake();

    CubeFrame cubeFrame;
    Point3D dirVec;
    QList<Point3D *> snakePts;
    int snakeLen;
    int clockCounter;

signals:

public slots:
    void beatDetected();
    void clockDetected();
};

//------------------------------------------------------------------------------
#endif // BEATSNAKEANIMATION_H

//------------------------------------------------------------------------------
