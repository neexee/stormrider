#include <memory>
#include <boost/format.hpp>
#include <boost/shared_array.hpp>
#include <vamp-hostsdk/PluginHostAdapter.h>
#include <vamp-hostsdk/PluginInputDomainAdapter.h>
#include <vamp-hostsdk/PluginLoader.h>
#include "../../utils/stormlogger.h"
#include "FeatureSet.h"
#include "PluginExecutor.h"

namespace stormrider
{
namespace vamp
{

PluginExecutor::PluginExecutor(const std::string& soname, const std::string& id,
		const std::string& wavname)
		: sndfile_(wavname)
{
	if (!sndfile_)
	{
		ERROR<< boost::format("ERROR: Failed to open input file \"%1\": %2") %wavname, sndfile_.error();
	}
	LoadPlugin(soname, id);
	InitSoundFileSizes();

	//cerr << "Running plugin: \"" << plugin->getIdentifier() << "\"..." << endl
	Vamp::Plugin::OutputList outputs = plugin_->getOutputDescriptors();
	if (outputs.empty())
	{
		ERROR << boost::format("ERROR: Plugin \'%1%:%2%\' has no outputs!") % soname % id;
	}

	if (!plugin_->initialise(sndfile_.channels(), step_size_, block_size_))
	{
		ERROR << boost::format("Plugin initialise (channels=%1%, stepSize=%2%, blockSize=%3%) failed")
		% sndfile_.channels() % step_size_ % block_size_;
	}
}

PluginExecutor::~PluginExecutor()
{
}

void PluginExecutor::LoadPlugin(const std::string& soname, const std::string& id)
{
	using Vamp::HostExt::PluginLoader;
	PluginLoader* loader = PluginLoader::getInstance();
	PluginLoader::PluginKey key = loader->composePluginKey(soname, id);
	plugin_ = std::shared_ptr<Vamp::Plugin>(
			loader->loadPlugin(key, sndfile_.samplerate(), PluginLoader::ADAPT_ALL_SAFE));

	if (!plugin_)
	{
		ERROR<< boost::format("ERROR: Failed to load plugin %1% from library \"%2%\"") % id % soname;
	}
}

void PluginExecutor::InitSoundFileSizes()
{
	block_size_ = plugin_->getPreferredBlockSize();
	step_size_ = plugin_->getPreferredStepSize();

	if (block_size_ == 0)
	{
		block_size_ = 1024;
	}

	if (step_size_ == 0)
	{
		step_size_ = block_size_;
		if (plugin_->getInputDomain() == Vamp::Plugin::FrequencyDomain)
		{
			step_size_ /= 2;
		}
	}
	else if (step_size_ > block_size_)
	{
		block_size_ = step_size_;
		if (plugin_->getInputDomain() == Vamp::Plugin::FrequencyDomain)
		{
			block_size_ *= 2;
		}
	}
}

// Here we iterate over the frames, avoiding asking the numframes in case it's streaming input.
const std::vector<FeatureSet> PluginExecutor::run()
{
	std::vector<FeatureSet> results;
	const int channels = sndfile_.channels();

	boost::shared_array<float> filebuf(new float[block_size_ * channels]);
	PluginInputBuffer plugin_buf(channels, block_size_);

	sf_count_t current_step = 0;
	std::cout << "Stepsize = " << step_size_ << ", block size = " << block_size_ << std::endl;
	int steps_remaining = std::max(1, (block_size_ / step_size_) - 1);
	do
	{
		sf_count_t count = readSndFile(current_step, filebuf.get());
		if (count != block_size_)
		{
			--steps_remaining;
		}

		for (int channel = 0; channel < channels; ++channel)
		{
			for (int j = 0; j < count; ++j)
			{
				plugin_buf.SetValue(channel, j, filebuf[j * channels + channel]);
			}
			float* position = plugin_buf.GetPointer(channel, count);
			std::fill(position, position + block_size_ - count, 0.0f);
		}

		results.push_back(Process(current_step, plugin_buf));
		++current_step;
	} while (steps_remaining > 0);

	std::cout << "Current step " << current_step << std::endl;
	INFO<< boost::format("PluginExecutor: done in %1% steps") % current_step;
	results.push_back(Process(current_step, PluginInputBuffer()));

	return results;
}

const FeatureSet PluginExecutor::Process(int current_step, const PluginInputBuffer& buffer)
{
	using rt = Vamp::RealTime;
	int samplerate = sndfile_.samplerate();
	Vamp::RealTime time = rt::RealTime::frame2RealTime(current_step * step_size_, samplerate);

	Vamp::Plugin::FeatureSet raw_results;
	if(buffer.GetBuffer() != nullptr)
	{
		raw_results = plugin_->process(buffer.GetBuffer(), time);
	}
	else
	{
		raw_results = plugin_->getRemainingFeatures();
	}

	int frame = rt::RealTime::realTime2Frame(time + Adjustment(), samplerate);

	return FeatureSet(frame, samplerate, raw_results);
}

Vamp::RealTime PluginExecutor::Adjustment() const
{
	namespace vhost = Vamp::HostExt;
	auto wrapper = std::dynamic_pointer_cast<vhost::PluginWrapper>(plugin_);
	Vamp::RealTime adjustment = Vamp::RealTime::zeroTime;
	if (wrapper)
	{
		vhost::PluginInputDomainAdapter* ida =
				wrapper->getWrapper<vhost::PluginInputDomainAdapter>();
		if (ida)
		{
			adjustment = ida->getTimestampAdjustment();
		}
	}
	return adjustment;
}

sf_count_t PluginExecutor::readSndFile(int currentStep, float* filebuf)
{
	sf_count_t count = 0;
	int overlap_size = block_size_ - step_size_;

	if (overlap_size == 0 || currentStep == 0)
	{
		if ((count = sndfile_.readf(filebuf, block_size_)) < 0)
		{
			ERROR<< boost::format("sf_readf_float failed: %1%") % sndfile_.error();
		}
	}
	else
	{
		int bufSize = overlap_size * sndfile_.channels();
		memmove(filebuf, filebuf + step_size_ * sndfile_.channels(), bufSize* sizeof(float));
		if ((count = sndfile_.readf(filebuf + bufSize, step_size_)) < 0)
		{
			ERROR << boost::format("sf_readf_float failed: %1%") % sndfile_.error();
		}
		count += overlap_size;
	}
	return count;
}

} // namespace vamp
} // namespace stormrider
