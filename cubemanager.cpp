//------------------------------------------------------------------------------
#include "cubemanager.h"

//------------------------------------------------------------------------------
CubeManager::CubeManager(QObject *parent)
{}

//------------------------------------------------------------------------------
// Returns reference to CubeManagerAnim in cubeMgrAnims if flAnim is found.
// Else returns NULL.
//
// NOTE: Assumes cubeMgrAnimsSem is already acquired by calling function!
CubeManagerAnim* CubeManager::getCubeMgrAnim(const FlAnimation *flAnim) {
    for (int i = 0; i < cubeMgrAnims.size(); ++i) {
        if (cubeMgrAnims[i]->flAnim == flAnim)
            return cubeMgrAnims[i];
    }
    return NULL;
}

//------------------------------------------------------------------------------
void CubeManager::registerAnimation(const FlAnimation *flAnim) {
    if (!flAnim)
        return;

    cubeMgrAnimsSem.acquire();
    // Make sure the animation isn't already registered.
    if (getCubeMgrAnim(flAnim)) {
        qDebug() << "WARNING (register) Animation already registered";
        return;
    }

    // Add flAnim to the list of cubeMgrAnims.
    CubeManagerAnim *cubeMgrAnim = new CubeManagerAnim();
    cubeMgrAnim->flAnim = flAnim;
    memset(&cubeMgrAnim->cubeFrame, 0, sizeof(CubeFrame));

    cubeMgrAnims.append(cubeMgrAnim);
    cubeMgrAnimsSem.release();
}

//------------------------------------------------------------------------------
void CubeManager::unRegisterAnimation(const FlAnimation *flAnim) {
    if (!flAnim)
        return;

    cubeMgrAnimsSem.acquire();
    CubeManagerAnim *cubeMgrAnim = getCubeMgrAnim(flAnim);
    if (cubeMgrAnim) {
        cubeMgrAnims.removeOne(cubeMgrAnim);
        delete cubeMgrAnim;
    }
    cubeMgrAnimsSem.release();
}

//------------------------------------------------------------------------------
void CubeManager::render(const FlAnimation* flAnim, const CubeFrame *cubeFrame) {
    if (!flAnim || !cubeFrame)
        return;

    cubeMgrAnimsSem.acquire();
    CubeManagerAnim *cubeMgrAnim = getCubeMgrAnim(flAnim);
    if (!cubeMgrAnim) {
        qDebug() << "ERROR (render) Animation not found. Did you register it first?";
        return;
    }

    memcpy(&cubeMgrAnim->cubeFrame, cubeFrame, sizeof(CubeFrame));

    CubeFrame outCubeFrame;
    renderOutCubeFrame(&outCubeFrame);

    // Send outCubeFrame to the cube uC to be physically displayed.
    // TODO

    cubeMgrAnimsSem.release();
}

//------------------------------------------------------------------------------
// ORs all the cubeFrames together into outCubeFrame.
//
// NOTE: Assumes cubeMgrAnimsSem is already acquired by calling function!
void CubeManager::renderOutCubeFrame(CubeFrame *outCubeFrame) {
    memset(outCubeFrame, 0, sizeof(CubeFrame));
    for (int i = 0; i < cubeMgrAnims.size(); ++i) {
        for (int level = 0; level < CUBE_NUM_LEVELS; ++level) {
            for (int row = 0; row < CUBE_NUM_ROWS_PER_LEVEL; ++row) {
                for (int rowByte = 0; rowByte < CUBE_NUM_BYTES_PER_ROW; ++rowByte) {
                    (*outCubeFrame)[level][row][rowByte] |= cubeMgrAnims[i]->cubeFrame[level][row][rowByte];
                }
            }
        }
    }
}

//------------------------------------------------------------------------------
