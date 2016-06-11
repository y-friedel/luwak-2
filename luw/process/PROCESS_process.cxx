#include "luw/process/process.h"
#include <opencv2/core.hpp> //Mat

//#ifdef LUW_DEBUG
#include "compat/session/session.h"
//#endif

void LUW::PROCESS::LogImage(const cv::Mat& image)
{
	SESSION::Instance().SaveImage(image);
}

std::vector<cv::Mat> LUW::PROCESS::Apply(const cv::Mat& image_in)
{
	std::vector<cv::Mat> output(0);
	return std::move(output);

}
