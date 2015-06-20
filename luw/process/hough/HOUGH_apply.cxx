#include "luw/process/hough/hough.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/core.hpp> //Mat

#define _USE_MATH_DEFINES
#include <math.h>
#include <limits>

std::vector<cv::Mat> LUW::HOUGH::Apply(const cv::Mat& image_in)
{
	std::vector<cv::Mat> results;
	results.emplace_back();
	cv::Mat& image_out = results[0];

	switch (image_in.type())
	{
	case CV_8UC1:
		ApplyGS(image_in, image_out);
		break;
	case CV_8UC3:
		ApplyHSV(image_in, image_out);
		break;
	}

	LogImage(image_out);

	return results;

}