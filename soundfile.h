/**
 *
 * soundfile.h
 * A class for holding stuff about audio files. Basically it's a wrapper to sndfile.h
 *
 */

#ifndef SOUNDFILE_H
#define SOUNDFILE_H

#include <string>

#include <sndfile.h>

struct SoundFileInfo : public SF_INFO
{
	sf_count_t get_frames() const { return frames; }
	int get_sample_rate() const { return samplerate; }
	int get_channels() const { return channels; }
	int get_format() const { return format; }
	int get_sections() const { return sections; }
	int get_seekable() const { return seekable; }
};

class SoundFile
{
	public:
		SoundFile();
		SoundFile(const std::string& filename);
		virtual ~SoundFile();

		bool open(const std::string& filename);
		int close();

		const SoundFileInfo* get_info() const { return &info; }

		// TODO: add other read's
		sf_count_t read_float(float *ptr, sf_count_t items);

	private:
		SNDFILE *file;
		SoundFileInfo info;
};

#endif
