
#ifndef __IO_H_
#define __IO_H_

#include <string>
#include "compat/compat.h"

namespace cv
{
	class Mat;
};

namespace LIO
{
	IO_ERROR LoadImage(const std::string& filename, cv::Mat& image, int type = 0); //CV_LOAD_IMAGE_GRAYSCALE
	IO_ERROR SaveImage(const std::string& filename, const cv::Mat& image);

	std::string Type2Str(int type);
};

#endif