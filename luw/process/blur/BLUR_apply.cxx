#include "blur.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/core/core.hpp> //Mat

IO_ERROR LUW::BLUR::Apply(const cv::Mat& image_in, cv::Mat& image_out)
{
	if (!image_in.data)
		return IO_NOT_FOUND;

	image_in.copyTo(image_out);

	cv::blur(image_in, image_out, cv::Size(blur_size, blur_size));

	return IO_OK;
}