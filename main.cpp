//------------------------------------------------------------------------------
#include <QtGui/QApplication>
#include <QAudioInput>
#include <QtMultimedia>
#include <QThread>

#include "mainwindow.h"
#include "midibeatdetector.h"
#include "beatdispenser.h"

#include "windows.h"

#if 0
    #define AUDIO_SAMPLE_RATE   44100
    #define AUDIO_NUM_CHANNELS  1
    #define AUDIO_SAMPLE_SIZE   16
    #define AUDIO_CODEC         "audio/pcm"
    #define AUDIO_BYTE_ORDER    QAudioFormat::LittleEndian
    #define AUDIO_SAMPLE_TYPE   QAudioFormat::SignedInt
#endif

//------------------------------------------------------------------------------
// This needs to be global, unfortunately.
MidiBeatDetector midiBeatDetector;

//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    // SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);

    QApplication application(argc, argv);

    BeatDispenser beatDispenser;
    CubeController cubeController;
    AnimationController animationController(&beatDispenser, &cubeController);

    MainWindow mainWindow(&beatDispenser, &animationController);
    mainWindow.show();

    midiBeatDetector.start();

#if 0
    // Initialize audio stuff.
    QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
    QAudioFormat format;
    format.setSampleRate(AUDIO_SAMPLE_RATE);
    format.setChannels(AUDIO_NUM_CHANNELS);
    format.setSampleSize(AUDIO_SAMPLE_SIZE);
    format.setCodec(AUDIO_CODEC);
    format.setByteOrder(AUDIO_BYTE_ORDER);
    format.setSampleType(AUDIO_SAMPLE_TYPE);

    AudioManager audioMgr(&format, &info, &application);
    audioMgr.startRecording();
    QTimer::singleShot(3000, &audioMgr, SLOT(stopRecording()));
#endif

    return application.exec();
}

//------------------------------------------------------------------------------
