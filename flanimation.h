//------------------------------------------------------------------------------
#ifndef FLANIMATION_H
#define FLANIMATION_H

//------------------------------------------------------------------------------
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
class FlAnimation
{
public:
    explicit FlAnimation();
    void start();
    void stop();

    // Override these if you want to make changes when a beat or clock is received.
    virtual void beatDetected();
    virtual void clockDetected();

    // Getters/setters
    const CubeFrame *getCubeFrame() { return &cubeFrame; }
    bool isDirty() { return dirty; }
    void setDirty(bool newDirty) { dirty = newDirty; }
    bool isRunning() { return running; }
    void setRunning(bool newRunning);

private:
    // Called whenever the animation goes from being not-running to running.
    virtual void init() {}

    bool running; // Keeps track of whether the animation is enabled or not.
    bool dirty;

protected:
    CubeFrame cubeFrame;
};

//------------------------------------------------------------------------------
#endif // ANIMATION_H

//------------------------------------------------------------------------------
