//------------------------------------------------------------------------------
#ifndef MIDIBEATDETECTOR_H
#define MIDIBEATDETECTOR_H

//------------------------------------------------------------------------------
#include <QThread>
#include <QDebug>
#include <QTime>

#include "portmidi.h"
#include "pmutil.h"
#include "porttime.h"

// If INPUT_BUFFER_SIZE is 0, PortMidi uses a default value.
#define INPUT_BUFFER_SIZE 0
#define DRIVER_INFO NULL
#define TIME_PROC NULL
#define TIME_INFO NULL

// Midi Status that we care about.
#define MIDI_CLOCK 0xF8
#define MIDI_START 0xFA

// We receive 24 midi "clock" messages for every quarter note (i.e. every beat).
#define MIDI_CLOCKS_PER_BEAT 24

//------------------------------------------------------------------------------
// This is needed because you can't pass a pointer to a member function.
// Called on a timer to poll midi data.
void processMidiWrapper(PtTimestamp timestamp, void *userData);

//------------------------------------------------------------------------------
class MidiBeatDetector : public QThread
{
    Q_OBJECT
public:
    explicit MidiBeatDetector(QObject *parent = 0);

    void run();
    void quit();

    // Called on a timer to poll midi data.
    void processMidi(PtTimestamp timestamp, void *userData);
    void midiClockHandler(PtTimestamp timestamp);

private:
    int getNumMidiDevices();

    // Midi I/O device stuff.
    int id;
    const PmDeviceInfo *info;
    PmStream *midiIn;

    // Prevents reading input from midi in processMidi before init is finished.
    bool startMidi;

    // Stores how many clocks we have received for the current beat.
    // When this reaches MIDI_CLOCKS_PER_BEAT, new beat.
    int clockIndex;

    // Used solely to differentiate beats in the console when printing.
    int beatCount;

signals:
    void beatDetected();
    void clockDetected();

public slots:

};

//------------------------------------------------------------------------------
extern MidiBeatDetector beatDetector;

#endif // MIDIBEATDETECTOR_H

//------------------------------------------------------------------------------
