#include "audiomanager.h"

AudioManager::AudioManager(QObject *parent, QAudioFormat *format,
                           QAudioDeviceInfo *info) : QThread(parent)
{
    this->parent = parent;
    audioFormat = *format;
    audioDevInfo = *info;

    if (!audioDevInfo.isFormatSupported(audioFormat)) {
        qWarning() << "Default format not supported try to use nearest";
        audioFormat = audioDevInfo.nearestFormat(audioFormat);
    }

    audioInput = new QAudioInput(audioFormat, this);
}

void AudioManager::startRecording()
{
    qDebug() << "AudioManager Start Recording To " << ((QApplication *) parent)->applicationDirPath();
    outputFile.setFileName("test.raw");
    outputFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
    audioInput->start(&outputFile);
}

void AudioManager::stopRecording()
{
    qDebug() << "AudioManager Stop Recording";
    audioInput->stop();
    outputFile.close();
}

/*
 *  Main run loop. Inhereted from QThread.
 */
void AudioManager::run()
{
    // Not used yet.
    exec();
}
