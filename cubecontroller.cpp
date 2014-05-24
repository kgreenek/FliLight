//------------------------------------------------------------------------------
#include "cubecontroller.h"

//------------------------------------------------------------------------------
CubeController::CubeController() {
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
void CubeController::render(const CubeFrame *cubeFrame) {
    if (!cubeFrame || !serialPort || !serialPort->isOpen())
        return;

    // qDebug() << "Sending cubeframe to cube";

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
    serialPort->write((char *) cubeFrame, sizeof(CubeFrame));

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
