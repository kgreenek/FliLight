//------------------------------------------------------------------------------
#include "animationcontroller.h"

//------------------------------------------------------------------------------
AnimationController::AnimationController(BeatDispenser *beatDispenser,
                                         CubeController *cubeController)
{
    this->beatDispenser = beatDispenser;
    this->cubeController = cubeController;

    // Initialize our list of animations.
    // Make sure to initialize in the same order as declared in ANIMATIONS_ENUM.
    animations.append(new StrobeAnimation());
    animations.append(new UpDownSweepAnimation());
    animations.append(new BeatSnakeAnimation());
    animations.append(new PrecipitationAnimation());
    animations.append(new OnAnimation());
    animations.append(new PlaneAnimation());

    // Start listening for beats and clocks. Make sure to do this after initializing animations.
    connect(beatDispenser, SIGNAL(clockDetected()), this, SLOT(clockDetected()));
    connect(beatDispenser, SIGNAL(beatDetected()), this, SLOT(beatDetected()));
}

//------------------------------------------------------------------------------
void AnimationController::beatDetected() {
    bool dirty = false;

    // Send beatDetected signal to all running animations.
    foreach (FlAnimation *animation, animations) {
        if (!animation->isRunning())
            continue;

        animation->beatDetected();
        if (animation->isDirty()) {
            animation->setDirty(false);
            dirty = true;
        }
    }

    // If any animations have changed, send a new CubeFrame to the cube.
    if (dirty)
        renderAnimationsToCube();
}

//------------------------------------------------------------------------------
void AnimationController::clockDetected() {
    bool dirty = false;

    // Send clockDetected signal to all running animations.
    foreach (FlAnimation *animation, animations) {
        if (!animation->isRunning())
            continue;

        animation->clockDetected();
        if (animation->isDirty()) {
            animation->setDirty(false);
            dirty = true;
        }
    }

    // If any animations have changed, send a new CubeFrame to the cube.
    if (dirty)
        renderAnimationsToCube();
}

//------------------------------------------------------------------------------
void AnimationController::renderAnimationsToCube() {
    memset(&cubeFrame, 0, sizeof(CubeFrame));
    foreach (FlAnimation *animation, animations) {
        if (!animation->isRunning())
            continue;
        for (int level = 0; level < CUBE_NUM_LEVELS; ++level) {
            for (int row = 0; row < CUBE_NUM_ROWS_PER_LEVEL; ++row) {
                for (int rowByte = 0; rowByte < CUBE_NUM_BYTES_PER_ROW; ++rowByte) {
                    const CubeFrame *animCubeFrame = animation->getCubeFrame();
                    cubeFrame[level][row][rowByte] |= (*animCubeFrame)[level][row][rowByte];
                }
            }
        }
    }
    cubeController->render(&cubeFrame);
}

//------------------------------------------------------------------------------
void AnimationController::setAnimationRunning(AnimationEnum animation, bool running) {
    animations[animation]->setRunning(running);
    renderAnimationsToCube();
}

//------------------------------------------------------------------------------
void AnimationController::setUpDownSweepSpeed(float sweepSpeed) {
    UpDownSweepAnimation *upDownAnim = (UpDownSweepAnimation *)animations[UP_DOWN_SWEEP_ANIMATION];
    upDownAnim->setSweepSpeed(sweepSpeed);
}

//------------------------------------------------------------------------------
void AnimationController::setSnakeLen(int snakeLen) {
    BeatSnakeAnimation *snakeAnim = (BeatSnakeAnimation *)animations[BEAT_SNAKE_ANIMATION];
    snakeAnim->setSnakeLen(snakeLen);
}

//------------------------------------------------------------------------------
void AnimationController::setSnakeCoolMode(bool coolMode) {
    BeatSnakeAnimation *snakeAnim = (BeatSnakeAnimation *)animations[BEAT_SNAKE_ANIMATION];
    snakeAnim->setCoolMode(coolMode);
}

//------------------------------------------------------------------------------
void AnimationController::setStrobeSpeed(int strobeSpeed) {
    StrobeAnimation *strobeAnim = (StrobeAnimation *)animations[STROBE_ANIMATION];
    strobeAnim->setStrobeSpeed(strobeSpeed);
}

//------------------------------------------------------------------------------
