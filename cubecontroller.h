//------------------------------------------------------------------------------
#ifndef CUBEMANAGER_H
#define CUBEMANAGER_H

//------------------------------------------------------------------------------
#include <QDebug>

#include "qextserialport.h"
#include "cubeframe.h"

#define SERIAL_START_BYTE 0x9f
#define SERIAL_STOP_BYTE  0xae

//------------------------------------------------------------------------------
class CubeController
{
public:
    explicit CubeController();
    void render(const CubeFrame *cubeFrame);

private:
    QextSerialPort *serialPort;
};

//------------------------------------------------------------------------------
#endif // CUBE_H

//------------------------------------------------------------------------------
