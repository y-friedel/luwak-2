#include "luw/process/integral/integral.h"
#include <opencv2/core.hpp> //Mat
#include <iostream>
#include "opencv2/imgproc.hpp"

std::vector<cv::Mat> LUW::INTEGRAL::Apply(const cv::Mat& image_in)
{
	assert(image_in.data);

	std::vector<cv::Mat> results;
	results.emplace_back();
	cv::Mat& image_out = results[0];

	switch (image_in.type())
	{
	case CV_8UC1:
		ApplyGS(image_in, image_out);
		break;
	//case CV_8UC3:
	//	return ApplyHSV(image_in);
	//	break;
	default:
		throw;
	}

	LogImage(image_out);
	return std::move(results);
	
}

IO_ERROR LUW::INTEGRAL::ApplyGS(const cv::Mat& image_in, cv::Mat& image_out)
{
	if (!image_in.data)
		return IO_NOT_FOUND;

	if (image_in.type() != CV_8UC1)
		return IO_INCOMPATIBLE;

	image_out = cv::Mat::zeros(image_in.rows, image_in.cols, CV_16UC1);

	for (int ith_row = 0; ith_row < image_out.rows; ++ith_row)
	{
		for (int ith_col = 0; ith_col < image_out.cols; ++ith_col)
		{
			unsigned int integral_value = image_in.at<uchar>(ith_row, ith_col);

			bool not_first_row = (ith_row - 1 >= 0);
			bool not_first_col = (ith_col - 1 >= 0);

			if (not_first_row)
				integral_value += image_out.at<unsigned int>(ith_row - 1, ith_col);

			if (not_first_col)
				integral_value += image_out.at<unsigned int>(ith_row, ith_col - 1);

			if (not_first_row & not_first_col)
				integral_value -= image_out.at<unsigned int>(ith_row - 1, ith_col - 1);

			image_out.at<unsigned int>(ith_row, ith_col) = integral_value;
		}
	}
	
	return IO_OK;
}
