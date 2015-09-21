#include <utility>
#include "FVec.h"

namespace stormrider
{
namespace aubio
{

FVec::FVec(uint_t size)
: size_(size)
{
	fvec_ = new_fvec(size);
}

FVec::FVec(const FVec& other)
: size_(other.size_)
{
	fvec_ = new_fvec(size_);
	fvec_copy(other.fvec_, fvec_);
}

FVec::FVec(FVec&& other)
: size_(0)
, fvec_(nullptr)
{
	swap(*this, other);
}

FVec& FVec::operator=(FVec other)
{
	swap(*this, other);
	return *this;
}

FVec& FVec::operator=(FVec&& other)
{
	swap(*this, other);
	return *this;
}

FVec::~FVec()
{
	del_fvec(fvec_);
}

smpl_t FVec::GetSample(uint_t offset)
{
	return fvec_get_sample(fvec_, 0);
}

fvec_t* FVec::GetFvec()
{
	return fvec_;
}

uint_t FVec::IsSilence(smpl_t thereshold)
{
	return aubio_silence_detection(fvec_, thereshold);
}

void swap(FVec& first, FVec& second)
{
	std::swap(first.fvec_, second.fvec_);
}

} // namespace aubio
} // namespace stormrider


