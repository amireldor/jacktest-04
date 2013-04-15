#include "jackengine.h"

JackEngine::JackEngine() : jack_client(NULL)
{
	// TODO: fix hardcoded client name
	jack_client = jack_client_open("JackTest-04", JackNullOption, &jack_status);
	if (jack_client == NULL) throw JackException("Couldn't open client");

	jack_set_process_callback(jack_client, process, static_cast<void*>(this));

	// TODO: make and move stuff to a `Restart()` function or smt that gets options such as number of inputs and such
	left = jack_port_register(jack_client, "left", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
	right = jack_port_register(jack_client, "right", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);

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

int JackEngine::process(jack_nframes_t nframes, void *arg)
{
	// arg is pointer to `this`
	JackEngine *engine = static_cast<JackEngine*>(arg);

	// get ports somehow TODO: be smart if using more ports than just stereo
	jack_default_audio_sample_t *left_buffer = static_cast<jack_default_audio_sample_t*>( jack_port_get_buffer(engine->get_port_left(), nframes) );
	jack_default_audio_sample_t *right_buffer = static_cast<jack_default_audio_sample_t*>( jack_port_get_buffer(engine->get_port_right(), nframes) );

	for (jack_nframes_t i = 0; i < nframes; i++)
	{
		left_buffer[i] = (i % 10) / 9.0f;
		right_buffer[i] = (i*2 % 10) / 9.0f;
	}

	return 0;
}
