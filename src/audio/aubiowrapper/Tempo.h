#pragma once
#include <string>
#include <aubio/aubio.h>
#include "FVec.h"

namespace stormrider
{
namespace aubio
{

class Tempo
{
public:
	Tempo(const std::string& method, uint_t buffer_size,uint_t hop_size, uint_t samplerate);
	Tempo(const Tempo& other) = delete;
	Tempo(Tempo&& other);

	Tempo& operator=(Tempo other) = delete;
	Tempo& operator=(Tempo&& other);

	~Tempo();

	void SetThereshold(smpl_t thereshold);
	void Do(FVec& input, FVec& tempo);
	smpl_t GetLastDetectedBeatTime();

	friend void swap(Tempo& first, Tempo& second);
private:
	aubio_tempo_t* tempo_;
};

} // namespace aubio
} // namespace stormrider
