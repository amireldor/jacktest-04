#ifndef JACKENGINE_H
#define JACKENGINE_H

#include <jack/jack.h>

#include "audioengine.h"

class JackEngine : public AudioEngine
{
	public:
		JackEngine();
		//JackEngine(... some options ...)

		~JackEngine();

		bool Start();
		bool Stop();

	private:
		jack_client_t *jack_client;
		jack_status_t jack_status;

		// TODO: be smarter than fixed number of outs
		jack_port_t *left;
		//jack_port_t *right;
};

class JackException : public AudioEngineException
{
public:
	JackException(const std::string& m) : AudioEngineException(m) {}
};

#endif
