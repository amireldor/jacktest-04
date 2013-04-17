#include "jackaudiobuffer.h"
#include <cassert>

JackAudioBuffer::JackAudioBuffer() :
	buffer(NULL),
	total_frames(0)
{
}

JackAudioBuffer::~JackAudioBuffer()
{
	safe_delete_buffer();
}

jack_default_audio_sample_t* JackAudioBuffer::operator[] (jack_nframes_t pos)
{
	if (pos >= total_frames)
	{
		// TODO: be smart, throw exception
		//throw JackException("
		return NULL;
	}

	return &(buffer[pos]);
}

jack_default_audio_sample_t* JackAudioBuffer::allocate_new(jack_nframes_t size)
{
	// TODO: do i need to delete if buffer not NULL?
	assert(size > 0);
	buffer = new jack_default_audio_sample_t[size];
	total_frames = size;
	return buffer;
}

void JackAudioBuffer::safe_delete_buffer()
{
	if (buffer)
	{
		delete[] buffer;
		buffer = NULL;
		total_frames = 0;
	}
}
