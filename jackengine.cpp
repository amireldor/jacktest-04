#include "jackengine.h"

JackEngine::JackEngine() :
	jack_client(NULL),
	audio_buffer(NULL),
	audio_buffer_cursor(0)
{
	// TODO: fix hardcoded client name
	jack_client = jack_client_open("JackTest-04", JackNullOption, &jack_status);
	if (jack_client == NULL) throw JackException("Couldn't open client");

	jack_set_process_callback(jack_client, process, static_cast<void*>(this));

	// TODO: make and move stuff to a `Restart()` function or smt that gets options such as number of inputs and such
	left = jack_port_register(jack_client, "left", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
	right = jack_port_register(jack_client, "right", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);

	audio_buffer = new JackAudioBuffer();

	Start();
}

JackEngine::~JackEngine()
{
	Stop();

	if (audio_buffer)
	{
		delete audio_buffer;
		audio_buffer = NULL;
	}

	if (jack_client)
	{
		jack_client_close(jack_client);
		jack_client = NULL;
	}
}

// FIXME: temp remove this
#include "soundfile.h"
bool JackEngine::Start()
{
	jack_activate(jack_client);

	// TODO: this is temp, delete it, we load stam stuff in the buffer so we hear something
	SoundFile file("sound1.wav");

	sf_count_t frames = file.get_info()->get_frames();
	int channels = file.get_info()->get_channels();
	unsigned int buf_size = frames * channels;

	jack_default_audio_sample_t *buf = audio_buffer->allocate_new(buf_size);
	file.read_float(buf, buf_size);

	return true;
}

bool JackEngine::Stop()
{
	jack_deactivate(jack_client);
	return true;
}

JackAudioBuffer* JackEngine::get_current_audio_buffer()
{
	return audio_buffer;
}

int JackEngine::process(jack_nframes_t nframes, void *arg)
{
	// arg is pointer to `this`
	JackEngine *engine = static_cast<JackEngine*>(arg);

	// get buffer
	JackAudioBuffer *buffer = engine->get_current_audio_buffer();
	if (buffer == NULL) return 0;

	jack_nframes_t* cursor = engine->get_audio_buffer_cursor();

	// get ports somehow TODO: be smart if using more ports than just stereo
	jack_default_audio_sample_t *left_buffer = static_cast<jack_default_audio_sample_t*>( jack_port_get_buffer(engine->get_port_left(), nframes) );
	jack_default_audio_sample_t *right_buffer = static_cast<jack_default_audio_sample_t*>( jack_port_get_buffer(engine->get_port_right(), nframes) );

	for (jack_nframes_t i = 0; i < nframes; i++)
	{
		// TODO process multiple ports if nice nice smart programmer
		left_buffer[i] = *(*buffer)[*cursor];
		right_buffer[i] = *(*buffer)[*cursor+1];
		*cursor += 2;

		if (*cursor >= buffer->get_total_frames())
		{
			// TODO: move to next buffer
			// for now: go to beginning of the only buffer
			*cursor = 0;
		}

	}

	return 0;
}
