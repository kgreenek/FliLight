//------------------------------------------------------------------------------
#include "beatsnakeanimation.h"

//------------------------------------------------------------------------------
BeatSnakeAnimation::BeatSnakeAnimation(QObject *parent) :
    FlAnimation(parent)
{
    sem.release();
    memset(&cubeFrame, 0, sizeof(CubeFrame));  // This doesn't need to be done.
    srand(time(NULL));
    coolMode = false;
    clockCounter = 0;
    snakeLen = DEFAULT_SNAKE_LEN;
    for (int i = 0; i < MAX_NUM_SNAKE_PTS; ++i)
        snakePts.append(new Point3D(0, 0, 0));
    recalcDirVec();
}

//------------------------------------------------------------------------------
void BeatSnakeAnimation::beatDetected() {
    recalcDirVec();
}

//------------------------------------------------------------------------------
// 24 clock signals are sent per beat.
void BeatSnakeAnimation::clockDetected() {
    clockCounter++;
    if (clockCounter == NUM_CLOCKS_PER_BEAT / 4) {
        clockCounter = 0;
        if (coolMode)
            recalcDirVec();
        moveSnake();
        renderSnake();
    }
}

//------------------------------------------------------------------------------
// Move the snake one LED forward, as defined by dirVec.
void BeatSnakeAnimation::moveSnake() {
    sem.acquire();
    for (int i = snakeLen - 1; i > 0; i--) {
        snakePts[i]->x = snakePts[i - 1]->x;
        snakePts[i]->y = snakePts[i - 1]->y;
        snakePts[i]->z = snakePts[i - 1]->z;
    }

    for (int i = snakeLen; i < MAX_NUM_SNAKE_PTS; ++i) {
        snakePts[i]->x = snakePts[snakeLen - 1]->x;
        snakePts[i]->y = snakePts[snakeLen - 1]->y;
        snakePts[i]->z = snakePts[snakeLen - 1]->z;
    }
    sem.release();

#if 0
    snakePts[0]->x += dirVec.x;
    snakePts[0]->y += dirVec.y;
    snakePts[0]->z += dirVec.z;

    // If we have hit a wall, "wrap around" to the opposite side of the cube.
    if (snakePts[0]->x < 0)
        snakePts[0]->x = NUM_LEDS_PER_ROW - 1;
    if (snakePts[0]->x >= NUM_LEDS_PER_ROW)
        snakePts[0]->x = 0;

    if (snakePts[0]->y < 0)
        snakePts[0]->y = NUM_LEVELS - 1;
    if (snakePts[0]->y >= NUM_LEVELS)
        snakePts[0]->y = 0;

    if (snakePts[0]->z < 0)
        snakePts[0]->z = NUM_ROWS - 1;
    if (snakePts[0]->z >= NUM_ROWS)
        snakePts[0]->z = 0;
#else
    // If we hit a wall 'bounce' off of it.
    if (snakePts[0]->x + dirVec.x < 0)
        dirVec.x = -dirVec.x;
    if (snakePts[0]->x + dirVec.x >= CUBE_NUM_LEDS_PER_ROW)
        dirVec.x = -dirVec.x;

    if (snakePts[0]->y + dirVec.y < 0)
        dirVec.y = -dirVec.y;
    if (snakePts[0]->y + dirVec.y >= CUBE_NUM_LEVELS)
        dirVec.y = -dirVec.y;

    if (snakePts[0]->z + dirVec.z < 0)
        dirVec.z = -dirVec.z;
    if (snakePts[0]->z + dirVec.z >= CUBE_NUM_ROWS_PER_LEVEL)
        dirVec.z = -dirVec.z;

    snakePts[0]->x += dirVec.x;
    snakePts[0]->y += dirVec.y;
    snakePts[0]->z += dirVec.z;
#endif
}

//------------------------------------------------------------------------------
void BeatSnakeAnimation::recalcDirVec() {
    Point3D oldDirVec;
    oldDirVec.x = dirVec.x;
    oldDirVec.y = dirVec.y;
    oldDirVec.z = dirVec.z;

    // Keep getting a new random dirVec until we have one that is valid.
    // Invalid dirVecs:
    //   - New dirVec is the same as oldDirVec
    //   - New dirVec will cause the snake to 'double back' on itself
    //   - New dirVec is (0, 0, 0). I.e. not moving.
    do {
        // Get a random int from 0 to 2 and subtract 1 to get a random int from -1 to 1.
        // srand(time(NULL));
        dirVec.x = rand() % 3 - 1;
        // srand(time(NULL));
        dirVec.y = rand() % 3 - 1;
        // srand(time(NULL));
        dirVec.z = rand() % 3 - 1;
    }
    while ((dirVec.x == oldDirVec.x && dirVec.y == oldDirVec.y && dirVec.z == oldDirVec.z) ||
           (dirVec.x == -oldDirVec.x && dirVec.y == -oldDirVec.y && dirVec.z == -oldDirVec.z) ||
           (dirVec.x == 0 && dirVec.y == 0 && dirVec.z == 0));
}

//------------------------------------------------------------------------------
// Update our local CubeFrame based on the snake points.
void BeatSnakeAnimation::renderSnake() {
    memset(&cubeFrame, 0, sizeof(CubeFrame));

    sem.acquire();
    for (int i = 0; i < snakeLen; ++i) {
        int level = snakePts[i]->y;
        int row = snakePts[i]->z;
        cubeFrame[level][row][0] |= 1 << snakePts[i]->x;
    }
    sem.release();

    // Send our CubeFrame to the cube to be drawn.
    render(&cubeFrame);
}

//------------------------------------------------------------------------------
void BeatSnakeAnimation::setSnakeLen(int value) {
    if (value < 3 || value > MAX_NUM_SNAKE_PTS)
        return;

    sem.acquire();
    snakeLen = value;
    sem.release();
}

//------------------------------------------------------------------------------
void BeatSnakeAnimation::initSnakeAnimation() {
    // Initialize the snakePts.
    snakePts[0]->x = 0;
    snakePts[0]->y = 0;
    snakePts[0]->z = 0;
    for (int i = 1; i < MAX_NUM_SNAKE_PTS; i++) {
        snakePts[i]->x = 1;
        snakePts[i]->y = 0;
        snakePts[i]->z = 0;
    }

    // Initialize dirVec.
    dirVec.x = 0;
    dirVec.y = 1;
    dirVec.z = 1;
    recalcDirVec();

    moveSnake();
    renderSnake();
}

//------------------------------------------------------------------------------
void BeatSnakeAnimation::run() {
    qDebug() << "Starting BeatSnakeAnimation";
    cubeManager.registerAnimation((FlAnimation *) this);

    initSnakeAnimation();

    QObject::connect(&beatDetector, SIGNAL(beatDetected()),
                     this, SLOT(beatDetected()));
    QObject::connect(&beatDetector, SIGNAL(clockDetected()),
                     this, SLOT(clockDetected()));

    exec();

    QObject::disconnect(&beatDetector, SIGNAL(beatDetected()),
                        this, SLOT(beatDetected()));
    QObject::disconnect(&beatDetector, SIGNAL(clockDetected()),
                        this, SLOT(clockDetected()));

    cubeManager.unRegisterAnimation((FlAnimation *) this);
}

//------------------------------------------------------------------------------
