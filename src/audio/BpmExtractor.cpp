#include <boost/format.hpp>
#include <aubio/aubio.h>
#include "../utils/stormlogger.h"
#include "BpmExtractor.h"

namespace stormrider
{
namespace audio
{

BpmExtractor::BpmExtractor(ExtractorSettings settings)
: settings_(settings)
, source_(settings_.GetSourceUri(), settings_.GetSamplerate(), settings_.GetHopSize())
, ibuf_ (settings_.GetHopSize())
, wavetable_ (settings_.GetSamplerate(), settings_.GetHopSize())
, tempo_(settings_.GetTempoMethod(), settings_.GetBufferSize(), settings_.GetHopSize(), settings_.GetSamplerate())
, tempo_out_(2)
{
	// set silence threshold very low to output beats even during silence
	// aubio_tempo_set_silence(tempo, -1000.);
	if (settings_.GetOnsetThreshold() != 0.)
		tempo_.SetThereshold(settings_.GetOnsetThreshold());

	wavetable_.SetFreq(2450.);
}

BpmExtractor::~BpmExtractor()
{
}

void BpmExtractor::Process()
{
	smpl_t is_beat = 0;
	uint_t is_silence = 0.;

	tempo_.Do(ibuf_, tempo_out_);
	is_beat = tempo_out_.GetSample(0);
	smpl_t silence_threshold = settings_.GetSilenceThreshold();
	if (silence_threshold != -90.)
		is_silence = ibuf_.IsSilence(silence_threshold);

	if (is_beat && !is_silence)
	{
		wavetable_.Play();
	}
	else
	{
		wavetable_.Stop();
	}
	/*
	if (mix_input)
		aubio_wavetable_do(wavetable, ibuf, obuf);
	else
		aubio_wavetable_do(wavetable, obuf, obuf);
	*/
}

void BpmExtractor::Read()
{
	uint_t read = 0;
	uint_t total_read = 0;
	uint_t hop_size = settings_.GetHopSize();

	uint_t blocks = 0;
	do
	{
		source_.Do(ibuf_, &read);
		Process();
		// print to console if verbose or no output given
		INFO << boost::format("Got tempo: %1") % tempo_.GetLastDetectedBeatTime();
/*		if (this_sink)
		{
			aubio_sink_do(this_sink, obuf, hop_size);
		}
*/
		blocks++;
		total_read += read;
	} while (read == hop_size);

	std::string source_uri = settings_.GetSourceUri();
	uint_t samplerate = settings_.GetSamplerate();
	smpl_t total_read_per_sample = total_read*1.0/samplerate;

	INFO << boost::format("read %1fs (%2 samples in %3 blocks of %4) from %5 at %6Hz\n") %
			total_read_per_sample % total_read % blocks% hop_size% source_uri% samplerate;

}

} // namespace audio
} // namespace stormrider
