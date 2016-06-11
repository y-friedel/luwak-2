#include "luw/process/bayer/bayer.h"
#include <opencv2/core.hpp> //Mat

void LUW::BAYER::ApplyBlackWhite(const cv::Mat& image_in, cv::Mat& image_out)
{
	if (!image_in.data)
		throw std::exception("Bayer Filter : Image not found", IO_NOT_FOUND);

	if (image_in.type() != CV_8UC3)
		throw std::exception("Bayer Filter : Image type not supported", IO_INCOMPATIBLE);

	image_out = cv::Mat::zeros(image_in.rows, image_in.cols, CV_8UC1);

#pragma omp parrallel
	for (int ith_row = 0; ith_row < image_out.rows; ++ith_row)
	{
#pragma omp parrallel
		for (int ith_col = 0; ith_col < image_out.cols; ++ith_col)
		{
			cv::Vec3b rgb_pixel = image_in.at<cv::Vec3b>(ith_row, ith_col);
			if (ith_row % 2 == ith_col % 2)
			{
				image_out.at<uchar>(ith_row, ith_col) = rgb_pixel[1];
			}
			else if (ith_row % 2)
			{
				image_out.at<uchar>(ith_row, ith_col) = rgb_pixel[0];
			}
			else
			{
				image_out.at<uchar>(ith_row, ith_col) = rgb_pixel[2];
			}

		}
	}
}
