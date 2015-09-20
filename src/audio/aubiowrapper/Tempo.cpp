#include "Tempo.h"

namespace stormrider
{
namespace aubio
{

Tempo::Tempo(const std::string& method, uint_t buffer_size, uint_t hop_size, uint_t samplerate)
{
	tempo_ = new_aubio_tempo(const_cast<char*>(method.c_str()), buffer_size, hop_size, samplerate);
}

Tempo::~Tempo()
{
	del_aubio_tempo(tempo_);
}

void Tempo::SetThereshold(smpl_t thereshold)
{
	aubio_tempo_set_threshold(tempo_, thereshold);
}

void Tempo::Do(FVec& input, FVec& tempo)
{
	aubio_tempo_do (tempo_, input.GetFvec(), tempo.GetFvec());
}

smpl_t Tempo::GetLastDetectedBeatTime()
{
	return aubio_tempo_get_last_s(tempo_);
}

} // namespace aubio
} // namespace stormrider

