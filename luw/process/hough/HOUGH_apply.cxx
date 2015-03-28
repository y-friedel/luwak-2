#include "luw/process/hough/hough.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/core/core.hpp> //Mat

#define _USE_MATH_DEFINES
#include <math.h>
#include <limits>

IO_ERROR LUW::HOUGH::Apply(const cv::Mat& image_in, cv::Mat& image_out)
{
	switch (image_in.type())
	{
	case CV_8UC1:
		return ApplyGS(image_in, image_out);
	case CV_8UC3:
		return ApplyHSV(image_in, image_out);
	default:
		return IO_INCOMPATIBLE;
	}

}