#ifndef AUDIOBUFFER_H
#define AUDIOBUFFER_H

#include <QIODevice>
#include <QAudio>
#include <QAudioInput>
#include <QDebug>

#include <stdio.h>
#include <string.h>

class AudioBuffer : public QIODevice
{
    Q_OBJECT
public:
    explicit AudioBuffer(const QAudioFormat *format, QObject *parent = 0);
    qint64 writeData(const char *data, qint64 maxSize);
    qint64 readData(char *data, qint64 maxSize);
    bool open(OpenMode mode);
    void close();

private:
    QObject *parent;
    QAudioFormat audioFormat;
    char* audio;
    int audioSize;
    int writeIndex;

signals:
    // void bytesWritten(qint64 bytes);

public slots:

};

#endif // AUDIOBUFFER_H
