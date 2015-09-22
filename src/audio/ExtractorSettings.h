#pragma once
#include <aubio/types.h>
#include <string>

namespace stormrider
{
namespace audio
{

class ExtractorSettings
{
	typedef unsigned int uint_t;
	typedef float smpl_t;
public:
	ExtractorSettings();
	~ExtractorSettings();

	uint_t GetBufferSize() const;
	void SetBufferSize(uint_t buffer_size);

	uint_t GetHopSize() const;
	void SetHopSize(uint_t hop_size);

	const std::string& GetOnsetMethod() const;
	void SetOnsetMethod(const std::string& onset_method);

	smpl_t GetOnsetThreshold() const;
	void SetOnsetThreshold(smpl_t onset_threshold);

	const std::string& GetPitchMethod() const;
	void SetPitchMethod(const std::string& pitch_method);

	smpl_t GetPitchTolerance() const;
	void SetPitchTolerance(smpl_t pitch_tolerance);

	const std::string& GetPitchUnit() const;
	void SetPitchUnit(const std::string& pitch_unit);

	uint_t GetSamplerate() const;
	void SetSamplerate(uint_t samplerate);

	smpl_t GetSilenceThreshold() const;
	void SetSilenceThreshold(smpl_t silence_threshold);

	const std::string& GetSinkUri() const;
	void SetSinkUri(const std::string& sink_uri);

	const std::string& GetSourceUri() const;
	void SetSourceUri(const std::string& source_uri);

	const std::string& GetTempoMethod() const;
	void SetTempoMethod(const std::string& tempo_method);

private:
	// input / output
	std::string source_uri;
	std::string sink_uri;

	//general settings
	uint_t samplerate; // 0 to use input source samplerate, or 32000 to force 32kHz
	uint_t buffer_size; // number of frames to run the analysis on
	uint_t hop_size; // number of frames to read from source before each analysis

	// onset stuff
	std::string onset_method;  // onset detection algorithm <default|energy|hfc|complex|phase|specdiff|kl|mkl|specflux>; default=hfc"
	smpl_t onset_threshold; // a value between 0.1 (more detections) and 1 (less); default=0.3

	// pitch stuff
	std::string pitch_method; // pitch detection algorithm <default|yinfft|yin|mcomb|fcomb|schmitt>; default=yinfft"
	std::string pitch_unit;  // pitch output unit <default|freq|hertz|Hz|midi|cent|bin>; default=freq"
	smpl_t pitch_tolerance; // pitch tolerance (yin, yinfft only) a value between 0.1 and 0.7; default=0.3"

	// tempo stuff
	std::string tempo_method;

	// more general stuff
	smpl_t silence_threshold; // "silence threshold a value in dB, for instance -70, or -100; default=-90"
};

} // namespace audio
} // namespace stormrider
