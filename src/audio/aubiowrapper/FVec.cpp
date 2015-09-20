#include "FVec.h"

namespace stormrider
{
namespace aubio
{

FVec::FVec(uint_t size)
{
	fvec_ = new_fvec(size);

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

} // namespace aubio
} // namespace stormrider


