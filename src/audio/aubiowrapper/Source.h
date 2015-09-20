#pragma once
#include <string>
#include <aubio/aubio.h>
#include "FVec.h"

namespace stormrider
{
namespace aubio
{

class Source
{
public:
	Source(const std::string& uri, uint_t samplerate, uint_t hop_size);
	~Source();

	void Do(FVec& read_to, uint_t* read);

private:
	aubio_source_t* source_;
};

} // namespace aubio
} // namespace stormrider

