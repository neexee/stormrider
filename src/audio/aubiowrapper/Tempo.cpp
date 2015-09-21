#include <utility>
#include "Tempo.h"

namespace stormrider
{
namespace aubio
{

Tempo::Tempo(const std::string& method, uint_t buffer_size, uint_t hop_size, uint_t samplerate)
{
	tempo_ = new_aubio_tempo(const_cast<char*>(method.c_str()), buffer_size, hop_size, samplerate);
}

Tempo::Tempo(Tempo&& other)
: tempo_(nullptr)
{
	swap(*this, other);
}

Tempo& Tempo::operator=(Tempo&& other)
{
	swap(*this, other);
	return *this;
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

void swap(Tempo& first, Tempo& second)
{
	std::swap(first.tempo_, second.tempo_);
}

} // namespace aubio
} // namespace stormrider

