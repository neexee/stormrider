#include "ExtractorSettings.h"
namespace stormrider
{
namespace audio
{

ExtractorSettings::ExtractorSettings()
: source_uri()
, sink_uri()
, samplerate(0)
, buffer_size(1024)
, hop_size(512)
, onset_method("hfc")
, onset_threshold(0.3)
, pitch_method("yinfft")
, pitch_unit("freq")
, pitch_tolerance(0.3)
, tempo_method()
, silence_threshold(-90)
{
}

ExtractorSettings::~ExtractorSettings()
{
}

uint_t ExtractorSettings::GetBufferSize() const
{
	return buffer_size;
}

void ExtractorSettings::SetBufferSize(uint_t buffer_size)
{
	this->buffer_size = buffer_size;
}

uint_t ExtractorSettings::GetHopSize() const
{
	return hop_size;
}

void ExtractorSettings::SetHopSize(uint_t hop_size)
{
	this->hop_size = hop_size;
}

const std::string& ExtractorSettings::GetOnsetMethod() const
{
	return onset_method;
}

void ExtractorSettings::SetOnsetMethod(const std::string& onset_method)
{
	this->onset_method = onset_method;
}

smpl_t ExtractorSettings::GetOnsetThreshold() const
{
	return onset_threshold;
}

void ExtractorSettings::SetOnsetThreshold(smpl_t onset_threshold)
{
	this->onset_threshold = onset_threshold;
}

const std::string& ExtractorSettings::GetPitchMethod() const
{
	return pitch_method;
}

void ExtractorSettings::SetPitchMethod(const std::string& pitch_method)
{
	this->pitch_method = pitch_method;
}

smpl_t ExtractorSettings::GetPitchTolerance() const
{
	return pitch_tolerance;
}

void ExtractorSettings::SetPitchTolerance(smpl_t pitch_tolerance)
{
	this->pitch_tolerance = pitch_tolerance;
}

const std::string& ExtractorSettings::GetPitchUnit() const
{
	return pitch_unit;
}

void ExtractorSettings::SetPitchUnit(const std::string& pitch_unit)
{
	this->pitch_unit = pitch_unit;
}

uint_t ExtractorSettings::GetSamplerate() const
{
	return samplerate;
}

void ExtractorSettings::SetSamplerate(uint_t samplerate)
{
	this->samplerate = samplerate;
}

smpl_t ExtractorSettings::GetSilenceThreshold() const
{
	return silence_threshold;
}

void ExtractorSettings::SetSilenceThreshold(smpl_t silence_threshold)
{
	this->silence_threshold = silence_threshold;
}

const std::string& ExtractorSettings::GetSinkUri() const
{
	return sink_uri;
}

void ExtractorSettings::SetSinkUri(const std::string& sink_uri)
{
	this->sink_uri = sink_uri;
}

const std::string& ExtractorSettings::GetSourceUri() const
{
	return source_uri;
}

void ExtractorSettings::SetSourceUri(const std::string& source_uri)
{
	this->source_uri = source_uri;
}

const std::string& ExtractorSettings::GetTempoMethod() const
{
	return tempo_method;
}

void ExtractorSettings::SetTempoMethod(const std::string& tempo_method)
{
	this->tempo_method = tempo_method;
}

} // namespace audio
} // namespace stormrider

