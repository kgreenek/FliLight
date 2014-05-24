//------------------------------------------------------------------------------
#ifndef BEATDISPENSER_H
#define BEATDISPENSER_H

//------------------------------------------------------------------------------
#include <QTimer>
#include <QElapsedTimer>
#include <QDebug>

#include "midibeatdetector.h"

//------------------------------------------------------------------------------
// Defines the slowest tempo that can be tapped in. I.e. the longest time between two beats. In ms.
#define TAP_BUTTON_TIMEOUT 2000
#define NUM_CLOCKS_PER_BEAT 24

//------------------------------------------------------------------------------
class BeatDispenser : public QObject
{
    Q_OBJECT
public:
    BeatDispenser(QObject *parent = 0);
    ~BeatDispenser();
    void tapButtonPressed();
    void setUseMidi(bool newUseMidi) { useMidi = newUseMidi; }

private:
    bool useMidi;
    QElapsedTimer *tapButtonTimer;

    // When the timer expires, reset the TAP button.
    QTimer *tapTimeoutTimer;

    // Will expire 24 times for every beat.
    QTimer *beatTimer;

    int    tapCount;
    float  tapTime;

    // Prevents reading input from midi in processMidi before init is finished.
    bool startMidi;

    // Stores how many clocks we have received for the current beat.
    // When this reaches MIDI_CLOCKS_PER_BEAT, new beat.
    int clockCount;

    // Used solely to differentiate beats in the console when printing.
    int beatCount;

signals:
    void beatDetected();
    void clockDetected();

public slots:
    void beatTimerTimeout();
    void tapTimerTimeout();
    void midiClockDetected();
    void midiBeatDetected();
};

//------------------------------------------------------------------------------
extern BeatDispenser beatDetector;

#endif // BEATDISPENSER_H

//------------------------------------------------------------------------------
