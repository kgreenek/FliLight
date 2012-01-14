#include "audiobuffer.h"

AudioBuffer::AudioBuffer(const QAudioFormat *format, QObject *parent) :
    QIODevice(parent)
{
    this->parent = parent;
    audioFormat = *format;  // Deep copy
    audio = NULL;

    // Initialize audioSize. For now allocate 4 seconds worth of audio.
    audioSize = format->channels() * format->sampleRate() *
                format->sampleSize() / 8;
}

// This will get called whenever audio is ready from the mic.
qint64 AudioBuffer::writeData(const char *data, qint64 maxSize)
{
    // Make sure we're open.
    if (!audio)
    {
        qDebug() << "ERROR writeData - audio buffer not opened";
        return -1;
    }

    // Make sure we have enough room.
    if (writeIndex >= audioSize)
    {
        qDebug() << "ERROR writeData - audio buffer is full";
        return -1;
    }

    // If trying to write more than we have room for,
    // then fill only what's left in the buffer.
    int bytesToWrite = 0;
    if (maxSize > audioSize - writeIndex)
        bytesToWrite = audioSize - writeIndex;
    else
        bytesToWrite = maxSize;

    memcpy(audio + writeIndex, data, bytesToWrite);

    return bytesToWrite;
}

qint64 AudioBuffer::readData(char *data, qint64 maxSize)
{
    // Do something?
    return -1;
}

bool AudioBuffer::open(OpenMode mode)
{
    // Make sure audio has not already been initialized (i.e. we're already open).
    if (audio)
        return false;

    writeIndex = 0;
    audio = (char *) malloc(audioSize);
    if (!audio)
    {
        qDebug() << "ERROR - failed to allocate memory for audio";
        return false;
    }

    return true;
}


void AudioBuffer::close()
{
    free(audio);
    audio = NULL;
    writeIndex = 0;
}
