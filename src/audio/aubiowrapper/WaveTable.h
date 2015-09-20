#pragma once
#include <aubio/aubio.h>
namespace stormrider
{
namespace aubio
{

class WaveTable
{
public:
	WaveTable(uint_t samplerate, uint_t hop_size);
	~WaveTable();

	void SetFreq(smpl_t freq);
	uint_t Play();
	uint_t Stop();

private:
	aubio_wavetable_t* wavetable_;
};

} //namespace aubio
} //namespace stormrider
