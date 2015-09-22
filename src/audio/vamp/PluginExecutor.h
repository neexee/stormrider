#pragma once
#include <memory>
#include <string>
#include <vamp-hostsdk/Plugin.h>
#include <sndfile.hh>
#include "PluginInputBuffer.h"

namespace stormrider
{
namespace vamp
{

class PluginExecutor
{
public:
	PluginExecutor(const std::string& soname, const std::string& id, const std::string& wavname);
	const std::vector<FeatureSet> run();
	virtual ~PluginExecutor();

private:
	void InitSoundFileSizes();
	void LoadPlugin(const std::string& soname, const std::string& id);
	sf_count_t readSndFile(int currentStep, float* filebuf);
	Vamp::RealTime Adjustment() const;

	const FeatureSet Process(int current_step, const PluginInputBuffer& buffer);

	std::shared_ptr<Vamp::Plugin> plugin_;
	int step_size_;
	int block_size_;
	SndfileHandle sndfile_;
};

} // namespace vamp
} // namespace stormrider
