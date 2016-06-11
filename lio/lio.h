
#ifndef __LIO_H_
#define __LIO_H_

#include <string>
#include <vector>
#include "compat/compat.h"

namespace cv
{
	class Mat;
};

namespace LIO
{
	cv::Mat LoadCvImage(const std::string& filename, int type = 0); //CV_LOAD_IMAGE_GRAYSCALE
	std::vector<cv::Mat> LoadCvImagesFromDirectory(const std::string& directory); //CV_LOAD_IMAGE_GRAYSCALE
	IO_ERROR SaveImage(const std::string& filename, const cv::Mat& image);

	std::string Type2Str(int type);
};

#endif
