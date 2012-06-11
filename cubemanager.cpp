//------------------------------------------------------------------------------
#include "cubemanager.h"

//------------------------------------------------------------------------------
CubeManager::CubeManager(QObject *parent) {
    // If don't do this, refcount is 0, so the first aquire will hang forever.
    cubeMgrAnimsSem.release();

    // Initialize the serial port.
    serialPort = new QextSerialPort("COM3");
    serialPort->setBaudRate(BAUD57600);
    serialPort->setFlowControl(FLOW_OFF);
    serialPort->setParity(PAR_NONE);
    serialPort->setDataBits(DATA_8);
    serialPort->setStopBits(STOP_1);

    // Open the serial port!
    if (!serialPort->open(QextSerialPort::ReadWrite)) {
        // TODO Show a big error dialog box or something!
        qDebug() << "Serial port connection FAILED";
        return;
    }
    qDebug() << "Serial port connection SUCCESS";
}

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
    qDebug() << "Registering Animation";
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
    memset(cubeMgrAnim->cubeFrame, 0, sizeof(CubeFrame));
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

    renderOutCubeFrame();
}

//------------------------------------------------------------------------------
void CubeManager::render(const FlAnimation* flAnim, const CubeFrame *cubeFrame) {
    if (!flAnim || !cubeFrame || !serialPort)
        return;

    // qDebug() << "Sending cubeframe to cube";

    cubeMgrAnimsSem.acquire();
    CubeManagerAnim *cubeMgrAnim = getCubeMgrAnim(flAnim);
    if (!cubeMgrAnim) {
        qDebug() << "ERROR (render) Animation not found. Did you register it first?";
        cubeMgrAnimsSem.release();
        return;
    }

    memcpy(cubeMgrAnim->cubeFrame, *cubeFrame, sizeof(CubeFrame));

    renderOutCubeFrame();
    cubeMgrAnimsSem.release();
}

//------------------------------------------------------------------------------
// ORs all the cubeFrames together into outCubeFrame.
//
// NOTE: Assumes cubeMgrAnimsSem is already acquired by calling function!
void CubeManager::renderOutCubeFrame() {
    memset(outCubeFrame, 0, sizeof(CubeFrame));
    for (int i = 0; i < cubeMgrAnims.size(); ++i) {
        for (int level = 0; level < CUBE_NUM_LEVELS; ++level) {
            for (int row = 0; row < CUBE_NUM_ROWS_PER_LEVEL; ++row) {
                for (int rowByte = 0; rowByte < CUBE_NUM_BYTES_PER_ROW; ++rowByte) {
                    outCubeFrame[level][row][rowByte] |= cubeMgrAnims[i]->cubeFrame[level][row][rowByte];
                }
            }
        }
    }

    char startByte = SERIAL_START_BYTE;
    char stopByte = SERIAL_STOP_BYTE;
    // char response = 0;
    // int bytesRead = 0;

    // Send the cube uC the start byte (twice) so it knows we're about to start transferring. Wait for response.
    serialPort->write(&startByte, 1);
    serialPort->write(&startByte, 1);

    /*  // The cube sends back a response byte, but there really isn't a reason to read it.
    bytesRead = serialPort->read(&response, 1);
    if (bytesRead == 0) {
        // Fire up a timer and try again later.
        // TODO
        return;
    }
    */

    // Send outCubeFrame to the cube uC to be physically displayed.
    serialPort->write((char *) outCubeFrame, sizeof(outCubeFrame));

    serialPort->write(&stopByte, 1);
    serialPort->write(&stopByte, 1);

    /*  // The cube sends back a response byte, but there really isn't a reason to read it.
    bytesRead = serialPort->read(&response, 1);
    if (bytesRead == 0) {
        // Fire up a timer and try again later.
        // TODO
        return;
    }
    */
}

//------------------------------------------------------------------------------
