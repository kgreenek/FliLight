#include <QtGui/QApplication>
#include <QAudioInput>
#include <QtMultimedia>

#include "mainwindow.h"
#include "audiomanager.h"

#define AUDIO_SAMPLE_RATE   44100
#define AUDIO_NUM_CHANNELS  1
#define AUDIO_SAMPLE_SIZE   16
#define AUDIO_CODEC         "audio/pcm"
#define AUDIO_BYTE_ORDER    QAudioFormat::LittleEndian
#define AUDIO_SAMPLE_TYPE   QAudioFormat::SignedInt

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();

    // Initialize audio stuff.
    QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
    QAudioFormat format;
    format.setFrequency(AUDIO_SAMPLE_RATE);
    format.setChannels(AUDIO_NUM_CHANNELS);
    format.setSampleSize(AUDIO_SAMPLE_SIZE);
    format.setCodec(AUDIO_CODEC);
    format.setByteOrder(AUDIO_BYTE_ORDER);
    format.setSampleType(AUDIO_SAMPLE_TYPE);

    AudioManager audioMgr(&application, &format, &info);
    audioMgr.startRecording();
    QTimer::singleShot(3000, &audioMgr, SLOT(stopRecording()));

    return application.exec();
}
