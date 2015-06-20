#include "luw/process/process.h"
#include <opencv2/core.hpp> //Mat

#ifdef LUW_DEBUG
#include "compat/session/session.h"
#endif

IO_ERROR LUW::PROCESS::LogImage(const cv::Mat& image)
{
#ifdef LUW_DEBUG
	SESSION::Instance().SaveImage(image);
#endif
	return IO_OK;
}

std::vector<cv::Mat> LUW::PROCESS::Apply(const cv::Mat& image_in)
{
	std::vector<cv::Mat> output(0);
	return std::move(output);

}
