#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <QDebug>
#include <QThread>
#include <QAudio>
#include <QAudioInput>
#include <QTimer>
#include <QFile>
#include <QApplication>

class AudioManager : public QThread
{
    Q_OBJECT
public:
    explicit AudioManager(QObject *parent, QAudioFormat *format,
                          QAudioDeviceInfo *info);
    void run();

private:
    QObject *parent;
    QAudioInput *audioInput;
    QAudioFormat audioFormat;
    QAudioDeviceInfo audioDevInfo;
    QFile outputFile;   // For Testing.

signals:

public slots:
    void startRecording();
    void stopRecording();

};

#endif // AUDIOMANAGER_H
