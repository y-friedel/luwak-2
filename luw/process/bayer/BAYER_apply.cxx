#include "luw/process/bayer/bayer.h"
#include <opencv2/core.hpp> //Mat










std::vector<cv::Mat> LUW::BAYER::Apply(const cv::Mat& image_in)
{
	assert(image_in.data);

	std::vector<cv::Mat> results;
	results.emplace_back();
	cv::Mat& image_out = results[0];

	switch (m_result_type)
	{
	case COLOR:
		ApplyColor(image_in, image_out);
		break;

	case BLACK_WHITE:
		ApplyBlackWhite(image_in, image_out);
		break;

	case REVERT:
		ApplyRevert(image_in, image_out);
		break;
	}

	LogImage(image_out);

	return results;
}
