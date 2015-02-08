#include "lio/lio.h"
#include <opencv2/core/core.hpp> //Mat
#include <opencv2/highgui/highgui.hpp> //imread

IO_ERROR LIO::LoadImage(const std::string& filename, cv::Mat& image)
{

	if (filename.size() == 0)
	{
		return IO_ERR;
	}

	image = cv::imread(filename, CV_LOAD_IMAGE_GRAYSCALE);   // Read the file

	if (!image.data)                              // Check for invalid input
	{
		return IO_NOT_FOUND;
	}

	return IO_OK;
}