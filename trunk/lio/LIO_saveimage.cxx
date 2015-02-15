#include "lio/lio.h"
#include <opencv2/core/core.hpp> //Mat
#include <opencv2/highgui/highgui.hpp> //imwrite

IO_ERROR LIO::SaveImage(const std::string& filename, const cv::Mat& image)
{

	if (filename.size() == 0)
	{
		return IO_ERR;
	}

	std::vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(9);

	bool result = cv::imwrite(filename, image, compression_params);   // write the file

	if (!result)                              // Check for invalid input
	{
		return IO_ERR;
	}

	return IO_OK;
}