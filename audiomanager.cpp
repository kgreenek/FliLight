#include "audiomanager.h"

AudioManager::AudioManager(const QAudioFormat *format, const QAudioDeviceInfo *info,
                           QObject *parent = 0) : QThread(parent)
{
    this->parent = parent;
    audioFormat = *format;  // Deep copy
    audioDevInfo = *info;   // Deep copy

    if (!audioDevInfo.isFormatSupported(audioFormat)) {
        qWarning() << "Default format not supported try to use nearest";
        audioFormat = audioDevInfo.nearestFormat(audioFormat);
    }

    audioInput = new QAudioInput(audioFormat, this);
    // audioBuf = new AudioBuffer(&audioFormat, this);
}

void AudioManager::startRecording()
{
    qDebug() << "AudioManager Start Recording";
    // audioBuf->open(QIODevice::WriteOnly | QIODevice::Truncate);
    // audioInput->start((QIODevice *) audioBuf);

    QIODevice *ioDevice = audioInput->start();
}

void AudioManager::stopRecording()
{
    qDebug() << "AudioManager Stop Recording";
    audioInput->stop();
    audioBuf->close();
}

/*
 *  Main run loop. Inhereted from QThread.
 */
void AudioManager::run()
{
    // Not used yet.
    exec();
}
