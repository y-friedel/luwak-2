#include "lio/lio.h"
#include <opencv2/core/core.hpp> //Mat
#include <opencv2/highgui/highgui.hpp> //imwrite

IO_ERROR LIO::SaveImage(const std::string& filename, const cv::Mat& image)
{

	if (filename.size() == 0) return IO_ERR;

	auto compression_params = std::vector<int>({ CV_IMWRITE_PNG_COMPRESSION, 9 });
	bool result = cv::imwrite(filename, image, compression_params);

	if (!result) return IO_ERR;

	return IO_OK;
}