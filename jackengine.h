#ifndef JACKENGINE_H
#define JACKENGINE_H

#include <jack/jack.h>

#include "audioengine.h"
#include "jackaudiobuffer.h"

class JackEngine : public AudioEngine
{
	public:
		JackEngine();
		//JackEngine(... some options ...)

		~JackEngine();

		bool Start();
		bool Stop();

	protected:
		jack_port_t* get_port_left() { return left; }
		jack_port_t* get_port_right() { return right; }

		// TODO: add more if smart programmer in the future, we can use 4 audio buffers for example;
		JackAudioBuffer *audio_buffer;
		jack_nframes_t audio_buffer_cursor;

		JackAudioBuffer* get_current_audio_buffer();
		jack_nframes_t* get_audio_buffer_cursor() { return &audio_buffer_cursor; }

	private:
		jack_client_t *jack_client;
		jack_status_t jack_status;

		// TODO: be smarter than fixed number of outs
		jack_port_t *left;
		jack_port_t *right;

		static int process(jack_nframes_t nframes, void *arg);
};

class JackException : public AudioEngineException
{
public:
	JackException(const std::string& m) : AudioEngineException(m) {}
};

#endif
