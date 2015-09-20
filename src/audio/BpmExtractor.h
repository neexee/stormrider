#pragma once
#include <memory>
#include <aubio/types.h>
#include "aubiowrapper/Source.h"
#include "aubiowrapper/WaveTable.h"
#include "aubiowrapper/FVec.h"
#include "aubiowrapper/Tempo.h"
#include "ExtractorSettings.h"

namespace stormrider
{
namespace audio
{

class BpmExtractor
{
public:
	BpmExtractor(ExtractorSettings settings);
	~BpmExtractor();
private:
	using SinkPtr = std::unique_ptr<aubio_sink_t>;
	using FVecPtr = std::unique_ptr<fvec_t, void(*)(fvec_t*)>;

	void Read();
	void Process();

	ExtractorSettings settings_;
	aubio::Source source_;
	aubio::FVec ibuf_;
	aubio::WaveTable wavetable_;
	aubio::Tempo tempo_;
	aubio::FVec tempo_out_;
};

} // namespace audio
} // namespace stormrider
