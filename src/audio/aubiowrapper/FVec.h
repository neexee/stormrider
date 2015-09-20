#pragma once
#include <aubio/aubio.h>

namespace stormrider
{
namespace aubio
{

class FVec
{
public:
	FVec(uint_t size);
	~FVec();

	smpl_t GetSample(uint_t offset);
	fvec_t* GetFvec();
	uint_t IsSilence(smpl_t thereshold);

private:
	fvec_t* fvec_;
};

} // namespace aubio
} // namespace stormrider
