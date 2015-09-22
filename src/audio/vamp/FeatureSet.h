#pragma once
#include <fstream>
#include <vamp-hostsdk/Plugin.h>

namespace stormrider
{
namespace vamp
{

class FeatureSet
{
public:
	FeatureSet(int frame, int samplerate, Vamp::Plugin::FeatureSet& feature_set);
	~FeatureSet();

	int GetFrame() const;
	int GetSamplerate() const;
	const Vamp::Plugin::FeatureSet& GetFeatureSet() const;
	bool HasOutput(int output);

	void print(std::ostream& stream, int output, bool use_frames=false);

private:
	int frame_;
	int samplerate_;
	Vamp::Plugin::FeatureSet feature_set_;
};

} // namespace vamp
} // namespace stormrider
