#pragma once
#include <aubio/aubio.h>

namespace stormrider
{
namespace aubio
{

class FVec
{
public:
	explicit FVec(uint_t size);
	FVec(const FVec& other);
	FVec(FVec&& other);
	~FVec();

	FVec& operator=(FVec other);
	FVec& operator=(FVec&& other);

	smpl_t GetSample(uint_t offset);
	fvec_t* GetFvec();
	uint_t IsSilence(smpl_t thereshold);

	friend void swap(FVec& first, FVec& second);

private:
	fvec_t* fvec_;
	uint_t size_;
};

} // namespace aubio
} // namespace stormrider
