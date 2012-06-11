//------------------------------------------------------------------------------
#include "midibeatdetector.h"

//------------------------------------------------------------------------------
MidiBeatDetector::MidiBeatDetector(QObject *parent) :
    QThread(parent)
{
    info = NULL;
    midiIn = NULL;
    startMidi = FALSE;
    clockIndex = 0;
    beatCount = 0;
}

//------------------------------------------------------------------------------
void processMidiWrapper(PtTimestamp timestamp, void *userData) {
    midiBeatDetector.processMidi(timestamp, userData);
}

//------------------------------------------------------------------------------
int MidiBeatDetector::getNumMidiDevices() {
    const PmDeviceInfo *devInfo = NULL;
    int devCount = 0;
    devInfo = Pm_GetDeviceInfo(devCount);
    while (devInfo) {
        qDebug() << "Device info \n id " << devCount << " interf "
                 << devInfo->interf << " name " << devInfo->name
                 << " input " << devInfo->input;
        devCount++;
        devInfo = Pm_GetDeviceInfo(devCount);
    }
    return devCount;
}

//------------------------------------------------------------------------------
void MidiBeatDetector::run() {
    if (midiIn) {
        qDebug() << "A device is already open";
        return;
    }

    // Always start the timer before you start midi.
    // The timer will call our function, processMidi() every millisecond.
    Pt_Start(1, &processMidiWrapper, 0);

    Pm_Initialize();

    getNumMidiDevices();

    // Will the return the correct device?
    // id = Pm_GetDefaultInputDeviceID();
    id = 1;
    info = Pm_GetDeviceInfo(id);
    if (info == NULL) {
        printf("Could not open default input device (%d).", id);
        return;
    }

    qDebug() << "Opening input device id \n" << id << " "
             << info->interf << " " << info->name;
    Pm_OpenInput(&midiIn, id, DRIVER_INFO, INPUT_BUFFER_SIZE,
                 TIME_PROC, TIME_INFO);

    startMidi = TRUE;
}

//------------------------------------------------------------------------------
// Timer interrupt for processing midi data.
void MidiBeatDetector::processMidi(PtTimestamp timestamp, void *userData) {
    PmError result;
    PmEvent buffer; // Just one message at a time

    if (!startMidi)
        return;

    // See if there is any midi input to process.
    do {
        result = Pm_Poll(midiIn);
        if (result) {
            int status, data1, data2;
            if (Pm_Read(midiIn, &buffer, 1) == pmBufferOverflow)
                continue;

            // Unless there was overflow, we should have a message now.
            status = Pm_MessageStatus(buffer.message);
            data1 = Pm_MessageData1(buffer.message);
            data2 = Pm_MessageData2(buffer.message);

            // qDebug() << "Midi status " << status;

            // If the message is a beat.
            if ((status & 0xFF) == MIDI_CLOCK) {
                midiClockHandler(timestamp);
            }
            // Start msg. Used to sync to the start of the beats.
            else if ((status & 0xFF) == MIDI_START) {
                qDebug() << "Start";
                clockIndex = 0;
                beatCount = 0;
            }
        }
    } while (result);
}

//------------------------------------------------------------------------------
void MidiBeatDetector::midiClockHandler(PtTimestamp timestamp) {
    clockIndex++;
    if (clockIndex >= MIDI_CLOCKS_PER_BEAT) {
        qDebug() << "Beat" << beatCount;
        clockIndex = 0;
        beatCount++;
        emit beatDetected();
    }
    emit clockDetected();
}

//------------------------------------------------------------------------------
void MidiBeatDetector::quit() {
    // Stop the timer that calls processMidi().
    Pt_Stop();

    // Close the midi port and de-allocate stuff.
    Pm_Close(midiIn);
    midiIn = NULL;

    startMidi = FALSE;
}

//------------------------------------------------------------------------------
