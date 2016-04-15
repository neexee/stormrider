#include <ostream>
#include <boost/format.hpp>
#include "FeatureSet.h"
#include "../../utils/stormlogger.h"

namespace stormrider
{
namespace vamp
{

FeatureSet::FeatureSet(int frame, int samplerate, Vamp::Plugin::FeatureSet& feature_set)
: frame_(frame)
, samplerate_(samplerate)
, feature_set_(feature_set)
{
}

FeatureSet::~FeatureSet()
{
}

const Vamp::Plugin::FeatureSet& FeatureSet::GetFeatureSet() const
{
	return feature_set_;
}

int FeatureSet::GetFrame() const
{
	return frame_;
}

int FeatureSet::GetSamplerate() const
{
	return samplerate_;
}

bool FeatureSet::HasOutput(int output)
{
	return feature_set_.find(output) != feature_set_.end();
}

const FeatureSet::TimeGraphPoint FeatureSet::GetTimeGraphPoint(int output)
{
	typedef Vamp::RealTime RT;
	auto feature_list_it = feature_set_.find(output);
	TimeGraphPoint point;
	if (feature_list_it != feature_set_.end())
	{
		auto feature_list = (*feature_list_it).second;
		auto feature = feature_list[0];
		auto time = RT::frame2RealTime(frame_, samplerate_).usec();
		point =  std::make_pair(time, feature.values[0]);
	}
	return point;
}

void FeatureSet::print(std::ostream& stream, int output, bool use_frames)
{
	typedef Vamp::RealTime RT;
	auto feature_list = feature_set_.find(output);
	if (feature_list != feature_set_.end())
	{
		for (auto& feature : feature_list->second)
		{
			if (use_frames)
			{
				int display_frame = frame_;

				if (feature.hasTimestamp)
				{
					display_frame = RT::realTime2Frame(feature.timestamp, samplerate_);
				}

				stream << display_frame;

				if (feature.hasDuration)
				{
					display_frame = RT::realTime2Frame(feature.duration, samplerate_);
					stream << "," << display_frame;
				}
				stream << ":";
			}
			else
			{
				RT time = RT::frame2RealTime(frame_, samplerate_);

				if (feature.hasTimestamp)
				{
					time = feature.timestamp;
				}

				stream << time.toString();

				if (feature.hasDuration)
				{
					time = feature.duration;
					stream << "," << time.toString();
				}
				stream << ":";
			}

			auto& values = feature.values;
			std::copy(values.begin(), values.end(), std::ostream_iterator<float>(stream, " "));
			stream << feature.label << std::endl;
		}
	}
	else
	{
		ERROR<<boost::format("Output %1% requested, but plugin missing it") % output;
	}
}

} // namespace vamp
} // namespace stormrider
