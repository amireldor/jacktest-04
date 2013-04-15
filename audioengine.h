#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include <stdexcept>
#include <string>

#include <jack/jack.h>

class AudioEngine
{
	public:
		AudioEngine();
		virtual ~AudioEngine();

		virtual bool Start() = 0;
		virtual bool Stop() = 0;

	private:
};

class AudioEngineException : public std::runtime_error
{
public:
	AudioEngineException(const std::string& m) : std::runtime_error(m) {}
};

#endif
