
#ifndef __IO_H_
#define __IO_H_

#include <string>
#include "compat/compat.h"

namespace cv
{
	class Mat;
};

class LIO
{
public:
	static IO_ERROR LoadImage(const std::string& filename, cv::Mat& image);
	static IO_ERROR SaveImage(const std::string& filename, const cv::Mat& image);
};

#endif