#pragma once
#include <string>
#include <utility>
#include <aubio/aubio.h>
#include "FVec.h"

namespace stormrider
{
namespace aubio
{

class Source
{
public:
	Source();
	Source(const std::string& uri, uint_t samplerate, uint_t hop_size);
	Source(const Source& other) = delete;
	Source(Source&& other);

	Source& operator=(Source other) = delete;
	Source& operator=(Source&& other);

	~Source();

	void Do(FVec& read_to, uint_t* read);

	friend void swap(Source& first, Source& second);

private:
	aubio_source_t* source_;
};

} // namespace aubio
} // namespace stormrider

