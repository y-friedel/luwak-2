#include "lio/lio.h"
#include <opencv2/core.hpp> //Mat
#include <opencv2/highgui.hpp> //imread

IO_ERROR LIO::LoadCvImage(const std::string& filename, cv::Mat& image, int type)
{

	if (filename.size() == 0)
	{
		return IO_ERR;
	}

	image = cv::imread(filename, type);   // Read the file

	if (!image.data)                              // Check for invalid input
	{
		return IO_NOT_FOUND;
	}

	return IO_OK;
}