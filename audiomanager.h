#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <QDebug>
#include <QThread>
#include <QAudio>
#include <QAudioInput>
#include <QTimer>
#include <QFile>
#include <QApplication>

#include "audiobuffer.h"

class AudioManager : public QThread
{
    Q_OBJECT
public:
    explicit AudioManager(const QAudioFormat *format, const QAudioDeviceInfo *info,
                          QObject *parent);
    void run();

private:
    QObject *parent;
    QAudioInput *audioInput;
    QAudioFormat audioFormat;
    QAudioDeviceInfo audioDevInfo;
    AudioBuffer *audioBuf;
    // QFile outputFile;   // For Testing.

signals:

public slots:
    void startRecording();
    void stopRecording();

};

#endif // AUDIOMANAGER_H
