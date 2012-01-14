//------------------------------------------------------------------------------
#include "beatsnakeanimation.h"

//------------------------------------------------------------------------------
Point3D::Point3D() {
    x = 0; y = 0; z = 0;
}

//------------------------------------------------------------------------------
Point3D::Point3D(int x, int y, int z) {
    this->x = x; this->y = y; this->z = z;
}

//------------------------------------------------------------------------------
BeatSnakeAnimation::BeatSnakeAnimation(QObject *parent) :
    FlAnimation(parent)
{
    memset(cubeFrame, 0, sizeof(CubeFrame));  // This doesn't need to be done.
    clockCounter = 0;
    snakeLen = DEFAULT_SNAKE_LEN;
    for (int i = 0; i < snakeLen; ++i)
        snakePts.append(new Point3D(i, 0, 0));
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
    if (clockCounter == MIDI_CLOCKS_PER_BEAT / 4) {
        clockCounter = 0;
        moveSnake();
        renderSnake();
    }
}

//------------------------------------------------------------------------------
// Move the snake one LED forward, as defined by dirVec.
void BeatSnakeAnimation::moveSnake() {
    for (int i = 1; i < snakePts.size(); ++i) {
        snakePts[i]->x = snakePts[i - 1]->x;
        snakePts[i]->y = snakePts[i - 1]->y;
        snakePts[i]->z = snakePts[i - 1]->z;
    }

    snakePts[0]->x = dirVec.x;
    snakePts[0]->y = dirVec.y;
    snakePts[0]->z = dirVec.z;

    // If we have hit a wall, "wrap around" to the opposite side of the cube.
    if (snakePts[0]->x < 0)
        snakePts[0]->x = CUBE_NUM_LEDS_PER_ROW - 1;
    if (snakePts[0]->x >= CUBE_NUM_LEDS_PER_ROW)
        snakePts[0]->x = 0;

    if (snakePts[0]->y < 0)
        snakePts[0]->y = CUBE_NUM_LEVELS - 1;
    if (snakePts[0]->y >= CUBE_NUM_LEVELS)
        snakePts[0]->y = 0;

    if (snakePts[0]->z < 0)
        snakePts[0]->z = CUBE_NUM_ROWS_PER_LEVEL - 1;
    if (snakePts[0]->z >= CUBE_NUM_ROWS_PER_LEVEL)
        snakePts[0]->z = 0;
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
        srand(time(NULL));
        dirVec.x = rand() % 3 - 1;
        srand(time(NULL));
        dirVec.y = rand() % 3 - 1;
        srand(time(NULL));
        dirVec.z = rand() % 3 - 1;
    }
    while ((dirVec.x == oldDirVec.x && dirVec.y == oldDirVec.y && dirVec.z == oldDirVec.z) ||
           (dirVec.x == -oldDirVec.x && dirVec.y == -oldDirVec.y && dirVec.z == -oldDirVec.z) ||
           (dirVec.x == 0 && dirVec.y == 0 && dirVec.z == 0));
}

//------------------------------------------------------------------------------
void BeatSnakeAnimation::renderSnake() {
    // Update our local CubeFrame based on the snake points.
    memset(cubeFrame, 0, sizeof(CubeFrame));
    for (int i = 0; i < snakePts.size(); ++i) {
        int level = snakePts[i]->y;
        int row = snakePts[i]->z;
        cubeFrame[level][row][0] |= 1 << snakePts[i]->x;
    }

    // Send our CubeFrame to the cube to be drawn.
    render(&cubeFrame);
}

//------------------------------------------------------------------------------
void BeatSnakeAnimation::run() {
    cubeManager.registerAnimation((FlAnimation *) this);
    renderSnake();

    QObject::connect(&beatDetector, SIGNAL(beatDetected()),
                     this, SLOT(beatDetected()));
    QObject::connect(&beatDetector, SIGNAL(clockDetected()),
                     this, SLOT(clockDetected()));

    return exec();
}

//------------------------------------------------------------------------------
