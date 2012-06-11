//------------------------------------------------------------------------------
#ifndef FLANIMATION_H
#define FLANIMATION_H

//------------------------------------------------------------------------------
#include <QObject>
#include <QThread>
#include <QDebug>

#include "cubeframe.h"

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
class FlAnimation : public QThread
{
    Q_OBJECT
public:
    explicit FlAnimation(QObject *parent = 0);
    void render(CubeFrame *cubeFrame);
    void run();
    void stop();

private:
    bool running;

public slots:
    void beatDetected();
    void clockDetected();
};

//------------------------------------------------------------------------------
#endif // ANIMATION_H

//------------------------------------------------------------------------------
