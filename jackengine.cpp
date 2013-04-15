#include "jackengine.h"

JackEngine::JackEngine() : jack_client(NULL)
{
	// TODO: fix hardcoded client name
	jack_client = jack_client_open("JackTest-04", JackNullOption, &jack_status);

	if (jack_client == NULL) throw JackException("Couldn't open client");

	// TODO: make and move stuff to a `Restart()` function or smt that gets options such as number of inputs and such
	left = jack_port_register(jack_client, "left", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);

	Start();
}

JackEngine::~JackEngine()
{
	Stop();

	if (jack_client)
	{
		jack_client_close(jack_client);
		jack_client = NULL;
	}
}

bool JackEngine::Start()
{
	jack_activate(jack_client);
	return true;
}

bool JackEngine::Stop()
{
	jack_deactivate(jack_client);
	return true;
}
