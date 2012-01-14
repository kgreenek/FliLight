#ifndef FLANIMATION_H
#define FLANIMATION_H

#include <QObject>
#include <QThread>
#include <QDebug>

#include "cubeframe.h"

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

};

#endif // ANIMATION_H
