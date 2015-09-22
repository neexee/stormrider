#include <string>
#include <vector>

#include "audio/vamp/FeatureSet.h"
#include "audio/vamp/PluginExecutor.h"

void run_console_test(const std::string filename)
{

	const std::string soname = "vamp-aubio";
	const std::string id = "aubiotempo";
	stormrider::vamp::PluginExecutor ex(soname, id, filename);
	std::vector<stormrider::vamp::FeatureSet> results = ex.run();

	int channel = 1;
	for(auto& feature: results)
	{
		if (feature.HasOutput(channel))
		{
			feature.print(std::cout, channel);
		}
	}
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cout << "Input waveform file is required" << std::endl;
		return 1;
	}
	run_console_test(argv[1]);
	return 0;
}
