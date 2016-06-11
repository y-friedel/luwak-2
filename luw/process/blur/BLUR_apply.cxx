#include "blur.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/core.hpp> //Mat

std::vector<cv::Mat> LUW::BLUR::Apply(const cv::Mat& image_in)
{

	if(!image_in.data)
		throw std::exception("Blur Filter : Image not found", IO_NOT_FOUND);

	std::vector<cv::Mat> results;
	for (auto size_value : m_blur_size)
	{
		cv::Mat image_out;
		image_in.copyTo(image_out);
		cv::blur(image_in, image_out, cv::Size(size_value, size_value));
		results.emplace_back(image_out);
	}

	return std::move(results);
}