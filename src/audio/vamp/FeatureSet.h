#pragma once
#include <fstream>
#include <map>
#include <vector>
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

	typedef std::pair<int, float> TimeGraphPoint;
	const TimeGraphPoint GetTimeGraphPoint(int output);
private:
	int frame_;
	int samplerate_;
	Vamp::Plugin::FeatureSet feature_set_;
};

} // namespace vamp
} // namespace stormrider
