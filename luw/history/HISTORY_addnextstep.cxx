#include "luw/history/history.h"

void LUW::HISTORY::AddNextStep(LUW::PROCESS& process)
{
	m_process.emplace_back(process);

	auto& it_images = m_steps.back().begin();
	auto& it_end    = m_steps.back().end();
	m_steps.emplace_back(0);
	auto& results = m_steps.back();

	for (it_images; it_images != it_end; ++it_images)
	{
		std::vector<cv::Mat> current_results = process.Apply(*it_images);
		results.insert(results.end(), current_results.begin(), current_results.end());
		//auto& image_out = results.back();
		//err = process.Apply((*it_images), image_out);
	}
}