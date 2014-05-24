//------------------------------------------------------------------------------
#ifndef ANIMATIONCONTROLLER_H
#define ANIMATIONCONTROLLER_H

#include <QList>
#include <QDebug>

#include "cubecontroller.h"
#include "cubeframe.h"
#include "flanimation.h"
#include "animations/updownsweepanimation.h"
#include "animations/strobeanimation.h"
#include "animations/beatsnakeanimation.h"
#include "animations/precipitationanimation.h"
#include "animations/onanimation.h"
#include "animations/planeanimation.h"

//------------------------------------------------------------------------------
enum AnimationEnum {
    STROBE_ANIMATION,
    UP_DOWN_SWEEP_ANIMATION,
    BEAT_SNAKE_ANIMATION,
    PRECIPITATION_ANIMATION,
    ON_ANIMATION,
    PLANE_ANIMATION,
    NUM_ANIMATIONS
};

//------------------------------------------------------------------------------
class AnimationController : public QObject
{
    Q_OBJECT

public:
    explicit AnimationController(BeatDispenser *beatDispenser,
                        CubeController *cubeController);

    // MainWindow interface
    void setAnimationRunning(AnimationEnum anim, bool running);
    void setUpDownSweepSpeed(float sweepSpeed);
    void setSnakeLen(int snakeLen);
    void setSnakeCoolMode(bool coolMode);
    void setStrobeSpeed(int strobeSpeed);

private:
    void renderAnimationsToCube();

    CubeFrame cubeFrame;
    QList<FlAnimation *> animations;
    CubeController *cubeController;
    BeatDispenser *beatDispenser;

public slots:
    void beatDetected();
    void clockDetected();
};

//------------------------------------------------------------------------------
#endif // ANIMATIONCONTROLLER_H

//------------------------------------------------------------------------------
