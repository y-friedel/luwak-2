#include "luw/process/revert/revert.h"
#include <opencv2/core.hpp> //Mat

std::vector<cv::Mat> LUW::REVERT::Apply(const cv::Mat& image_in)
{

	std::vector<cv::Mat> images_out(0);
	if (!image_in.data)
		return std::move(images_out);

	if (image_in.type() != CV_8UC1)
		return std::move(images_out);

	//if (images_out.size() == 0)
	//	return IO_ERR;

	cv::Mat image_out;
	image_in.copyTo(image_out);

#pragma omp parrallel
	for (int ith_row = 0; ith_row < image_out.rows; ++ith_row)
	{
#pragma omp parrallel
		for (int ith_col = 0; ith_col < image_out.cols; ++ith_col)
		{
			//image_out.row(ith_row).col(ith_col) = 255 - image_out.row(ith_row).col(ith_col);
			image_out.at<uchar>(ith_row, ith_col) = 255 - image_in.at<uchar>(ith_row, ith_col);
		}
	}

	LogImage(image_out);
	images_out.emplace_back(image_out);
	return std::move(images_out);

}
