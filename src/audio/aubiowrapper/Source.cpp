#include <utility>
#include "Source.h"

namespace stormrider
{
namespace aubio
{

Source::Source(const std::string& uri, uint_t samplerate, uint_t hop_size)
{
	source_ = new_aubio_source(const_cast<char_t*>(uri.c_str()), samplerate, hop_size);
}

Source::Source()
: source_(nullptr)
{
}

Source::Source(Source&& other)
: Source()
{
	swap(*this, other);
}

Source& Source::operator=(Source&& other)
{
	swap(*this, other);
	return *this;
}

Source::~Source()
{
	del_aubio_source(source_);
}

void Source::Do(FVec& read_to, uint_t* read)
{
	aubio_source_do(source_, read_to.GetFvec(), read);
}

void swap(Source& first, Source& second)
{
	std::swap(first.source_, second.source_);
}

} // namespace aubio
} // namespace stormrider

