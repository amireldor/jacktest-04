#ifndef JACKAUDIOBUFFER_H
#define JACKAUDIOBUFFER_H

#include <jack/jack.h>

class JackAudioBuffer /*: public AudioBuffer*/
{
	public:
		JackAudioBuffer();
		virtual ~JackAudioBuffer();

		jack_nframes_t get_total_frames() { return total_frames; }
		jack_default_audio_sample_t* get_buffer() { return buffer; }
		jack_default_audio_sample_t* operator[] (jack_nframes_t);

		jack_default_audio_sample_t* allocate_new(jack_nframes_t size);

		// called automatically on `~JackAudioBuffer()`
		void safe_delete_buffer();

	private:
		jack_nframes_t total_frames;
		jack_default_audio_sample_t* buffer;
};

#endif
