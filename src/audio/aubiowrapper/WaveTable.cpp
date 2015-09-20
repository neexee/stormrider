#include "WaveTable.h"
namespace stormrider
{
namespace aubio
{

WaveTable::WaveTable(uint_t samplerate, uint_t hop_size)
{
	wavetable_ = new_aubio_wavetable(samplerate, hop_size);
}

WaveTable::~WaveTable()
{
	del_aubio_wavetable(wavetable_);
}
void WaveTable::SetFreq(smpl_t freq)
{
	aubio_wavetable_set_freq(wavetable_, freq);
}

uint_t WaveTable::Play()
{
	return aubio_wavetable_play(wavetable_);
}

uint_t WaveTable::Stop()
{
	return aubio_wavetable_stop(wavetable_);
}

} //namespace aubio
} //namespace stormrider

