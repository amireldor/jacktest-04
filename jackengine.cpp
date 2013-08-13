#include "jackengine.h"

JackEngine::JackEngine() :
	jack_client(NULL)
{
	// TODO: fix hardcoded client name
	jack_client = jack_client_open("JackTest-04", JackNullOption, &jack_status);
	if (jack_client == NULL) throw JackException("Couldn't open client");

	jack_set_process_callback(jack_client, process, static_cast<void*>(this));

	// TODO: make and move stuff to a `Restart()` function or smt that gets options such as number of inputs and such
	left = jack_port_register(jack_client, "left", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
	right = jack_port_register(jack_client, "right", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);

	// reset buffer(s)
	this->audio_vector.reserve(1024);

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

// FIXME: temp remove this
#include "soundfile.h"
#include <iostream>
using std::cout;
using std::endl;
bool
JackEngine::Start()
{
	// TODO: this is temp, delete it, we load stam stuff in the buffer so we hear something
	SoundFile file("sound1.wav");

	sf_count_t frames = file.get_info()->get_frames();
	int channels = file.get_info()->get_channels();
	unsigned int buf_size = frames * channels;

	// Load sample in a crude manner
/*	jack_default_audio_sample_t *buf = audio_buffer->allocate_new(buf_size);
	file.read_float(bu1f, buf_size);*/

	jack_default_audio_sample_t *temp_buf = new jack_default_audio_sample_t[buf_size];
	file.read_float(temp_buf, buf_size);

	audio_vector.clear();
	audio_vector.reserve(buf_size);
	// this is so ugly. use `data()` somehow? memcpy?
	for (unsigned int i = 0; i < buf_size; i++)
	{
		audio_vector.push_back(temp_buf[i]);
	}

	cout << "capc: " << audio_vector.capacity() <<
	endl << "buf_size: " << buf_size <<
	endl;
	for (unsigned int i = 0; i < 10; i++)
	{
		cout << i << '\t' << audio_vector[i] << endl;
	}

	delete[] temp_buf;
	// ...sample loaded

	jack_activate(jack_client);

	return true;
}

bool
JackEngine::Stop()
{
	jack_deactivate(jack_client);
	return true;
}

int
JackEngine::process(jack_nframes_t nframes, void *arg)
{
	// arg is pointer to `this`
	JackEngine *engine = static_cast<JackEngine*>(arg);

	static jack_nframes_t cursor = 0;

	JackAudioVector &buffer = engine->getAudioVector();

	// get ports somehow TODO: be smart if using more ports than just stereo
	jack_default_audio_sample_t *left_buffer = static_cast<jack_default_audio_sample_t*>( jack_port_get_buffer(engine->get_port_left(), nframes) );
	jack_default_audio_sample_t *right_buffer = static_cast<jack_default_audio_sample_t*>( jack_port_get_buffer(engine->get_port_right(), nframes) );

	for (jack_nframes_t i = 0; i < nframes; i++)
	{
		// TODO process multiple ports if nice nice smart programmer
		left_buffer[i] = buffer[cursor];
		right_buffer[i] = buffer[cursor+1];
		cursor += 2;

		if (cursor >= buffer.size())
		{
			// TODO: move to next buffer
			// for now: go to beginning of the only buffer
			cursor = 0;
//8			cout << "mark\t";
		}

	}
	return 0;
}
