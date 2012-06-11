#include <QSemaphore>
#include <QFile>

class AudioFile : QIODevice
{
public:
	AudioFile();
	
	char *audioData;
	char *beats;
	int audioStartIndex;
	int playIndex;
	QAudioFormat format;
	int avgSamplesPerBeat;
	QIODevice *playbackDevice;
	QSemaphore audioLock;
	
	bool open(string fileName)
	{
		if (audioData)
			close();

		QFile file(fileName);
		if (!file.open(QIODevice::ReadOnly))
			return false;
			
		audioLock.acquire();
			audioData = (char *) malloc(file.size());
			if (audioData == NULL) {
				audioLock.release();
				return false;
			}
			
			int bytesRead = 0;
			while (bytesRead < file.size() && bytesRead != -1)
				file.readData(audio, file.size()));
			if (bytesRead < 0) {
				audioLock.release();
				return false;
			}
			
			file.close();
			
			parseFormat();
			calculateBeats();
			
			// Open playbackDevice.
			startPlayback(playbackDevice);
		audioLock.release();
		
		return true;
	}
	
	void close()
	{
		audioLock.acquire();
			// Stop playback.
			audioOutput.reset();
			audioOutput.close();
			emit playbackStopped();
			delete audioData;
			audioData = NULL;
		audioLock.release();
	}

	startPlayback(playIndex = 0)
	{
		audioLock.acquire();
			this->playIndex = playIndex;
			audioOutput.start(this);
		audioLock.release();
	}
	
	// Called from audioOutput. Reads audioData to audio playback device.
	readData(char *data, qint64 maxSize)
	{
		audioLock.acquire();
			int bytesToRead = 0;
			if (maxSize > audioSize - playIndex)
				bytesToRead = audioSize - playIndex;
			else
				bytesToRead = maxSize;
			
			memcpy(audioData + playIndex, data, bytesToRead);
		audioLock.release();
	}
	
private:
	void parseFormat()
	{
	
	}

	void calculateBeats()
	{
	
	}
};