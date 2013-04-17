#include "soundfile.h"
#include <cstring>

SoundFile::SoundFile()
{
}

SoundFile::SoundFile(const std::string& filename)
{
	open(filename);
}

SoundFile::~SoundFile()
{
}

bool SoundFile::open(const std::string& filename)
{
	SF_INFO tmp_info;

	file = sf_open(filename.c_str(), SFM_READ, &tmp_info);
	std::memcpy(&info, &tmp_info, sizeof(tmp_info));

	if (file == NULL)
	{
		return false;
	}

	return true;
}

sf_count_t SoundFile::read_float(float *ptr, sf_count_t items)
{
	return sf_read_float(file, ptr, items);
}
