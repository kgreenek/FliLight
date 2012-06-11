//------------------------------------------------------------------------------
#include "beatdispenser.h"

//------------------------------------------------------------------------------
BeatDispenser::BeatDispenser(QObject *parent) :
    QObject(parent)
{
    // Start the timer simply so the first "elapsedMs" value is at least kinda valid.
    tapButtonTimer = new QElapsedTimer();
    tapButtonTimer->start();

    tapTimeoutTimer = new QTimer(this);
    connect(tapTimeoutTimer, SIGNAL(timeout()), this, SLOT(tapTimerTimeout()));

    beatTimer = new QTimer(this);
    connect(beatTimer, SIGNAL(timeout()), this, SLOT(beatTimerTimeout()));

    useMidi = false;

    connect(&midiBeatDetector, SIGNAL(clockDetected()), this, SLOT(midiClockDetected()));
    connect(&midiBeatDetector, SIGNAL(beatDetected()), this, SLOT(midiBeatDetected()));
}

//------------------------------------------------------------------------------
BeatDispenser::~BeatDispenser() {
    // Cleanup allocated memory.
    delete tapButtonTimer;
    delete tapTimeoutTimer;
    delete beatTimer;
}

//------------------------------------------------------------------------------
// Called on the "mouse-down" event of the beat tap-button.
void BeatDispenser::tapButtonPressed() {
    if (useMidi)
        return;

    int elapsedMs = tapButtonTimer->elapsed();
    tapButtonTimer->start();
    tapTimeoutTimer->start(TAP_BUTTON_TIMEOUT);
    tapCount++;

    // Set the button color so the user knows the tap timer is active.
    // TODO
    // MainWindow->button->setStyleSheet("* { background-color: rgb(255,125,100) }");

    // If we don't have at least two taps, we obviously can't determine the beat.
    if (tapCount < 2) {
        return;
    }

    // Calculate the new average time between taps.
    // tapTime = (tapTime * (tapCount - 2) + elapsedMs) / (tapCount - 1);
    tapTime = elapsedMs;

    qDebug() << "tapTime = " << tapTime;

    // Finally, start the beat timer that will notify the listeners.
    clockCount = NUM_CLOCKS_PER_BEAT;
    beatTimer->start(tapTime / NUM_CLOCKS_PER_BEAT);
}

//------------------------------------------------------------------------------
void BeatDispenser::tapTimerTimeout() {
    tapTimeoutTimer->stop();

    if (useMidi)
        return;

    // Set button color back to normal.
    // TODO

    tapCount = 0;
    tapTime = 0.0;
}

//------------------------------------------------------------------------------
void BeatDispenser::beatTimerTimeout() {
    if (useMidi)
        return;

    clockCount++;
    if (clockCount >= NUM_CLOCKS_PER_BEAT) {
        qDebug() << "Beat" << beatCount;
        clockCount = 0;
        beatCount++;
        emit beatDetected();
    }
    emit clockDetected();
}

//------------------------------------------------------------------------------
void BeatDispenser::midiClockDetected() {
    if (useMidi)
        emit clockDetected();
}

//------------------------------------------------------------------------------
void BeatDispenser::midiBeatDetected() {
    if (useMidi)
        emit beatDetected();
}

//------------------------------------------------------------------------------
