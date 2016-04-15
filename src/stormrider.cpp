#include <string>
#include <vector>
#include <thread>

#include "audio/vamp/FeatureSet.h"
#include "audio/vamp/PluginExecutor.h"
#include "graphics/Application.h"

typedef std::vector<stormrider::vamp::FeatureSet::TimeGraphPoint> TimeGraph;

const TimeGraph make_time_graph(std::vector<stormrider::vamp::FeatureSet>& feature_sets, int channel)
{
	TimeGraph graph;
	for(auto& feature_set: feature_sets)
	{
		if (feature_set.HasOutput(channel))
		{
			auto point = feature_set.GetTimeGraphPoint(channel);
			graph.push_back(point);
		}
	}
	return graph;
}

void sound_analyzer(const std::string& filename, Application& app)
{
	using namespace std::chrono_literals;
	const std::string soname = "vamp-aubio";
	const std::string id = "aubiotempo";
	stormrider::vamp::PluginExecutor ex(soname, id, filename);
	std::vector<stormrider::vamp::FeatureSet> results = ex.run();

	int channel = 1;

	auto time_graph = make_time_graph(results, channel);

	auto max_point = std::max_element(time_graph.begin(), time_graph.end(), [](const auto& a, const auto& b) {
		return a.second < b.second;
	});
	float max_value = (*max_point).second;
	std::chrono::microseconds time = std::chrono::microseconds::zero();
	for (const auto& point: time_graph)
	{
		int useconds = point.first;
		float value = point.second;
		std::chrono::microseconds start_at(useconds);
		std::this_thread::sleep_for(start_at - time);
		time = start_at;
		std::cout << value/max_value << std::endl;
		app.setScale(value/max_value);

	}
}


int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cout << "Input waveform file is required" << std::endl;
		return 1;
	}
	const std::string filename = argv[1];
	Application app;
	std::thread sound_thread(sound_analyzer, std::ref(filename), std::ref(app));
	try {
		app.go();
	} catch( Ogre::Exception& e ) {
		std::cerr << "An exception has occured: " <<
					 e.getFullDescription().c_str() << std::endl;
	}
	sound_thread.join();
	return 0;
}
