//------------------------------------------------------------------------------
#ifndef CUBEMANAGER_H
#define CUBEMANAGER_H

//------------------------------------------------------------------------------
#include <QThread>
#include <QSemaphore>
#include <QList>
#include <QDebug>

#include "qextserialport.h"
#include "cubeframe.h"
#include "flanimation.h"

#define SERIAL_START_BYTE 0x9f
#define SERIAL_STOP_BYTE  0xae

//------------------------------------------------------------------------------
class CubeManagerAnim {
public:
    const FlAnimation *flAnim;
    CubeFrame cubeFrame;
};

//------------------------------------------------------------------------------
class CubeManager
{
public:
    explicit CubeManager(QObject *parent = 0);
    void registerAnimation(const FlAnimation *flAnim);
    void unRegisterAnimation(const FlAnimation *flAnim);
    CubeManagerAnim* getCubeMgrAnim(const FlAnimation *flAnim);
    void render(const FlAnimation* flAnim, const CubeFrame *cubeFrame);

private:
    void renderOutCubeFrame();

    QList<CubeManagerAnim *> cubeMgrAnims;
    QSemaphore cubeMgrAnimsSem;
    QextSerialPort *serialPort;
    CubeFrame outCubeFrame;

signals:

public slots:

};

//------------------------------------------------------------------------------
extern CubeManager cubeManager;

#endif // CUBE_H

//------------------------------------------------------------------------------
