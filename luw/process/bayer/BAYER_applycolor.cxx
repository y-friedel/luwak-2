#include "luw/process/bayer/bayer.h"
#include <opencv2/core.hpp> //Mat

void LUW::BAYER::ApplyColor(const cv::Mat& image_in, cv::Mat& image_out)
{
	if (!image_in.data)
		throw std::exception("Bayer Filter : Image not found", IO_NOT_FOUND);

	if (image_in.type() != CV_8UC3)
		throw std::exception("Bayer Filter : Image type not supported", IO_INCOMPATIBLE);

	image_in.copyTo(image_out);

#pragma omp parrallel
	for (int ith_row = 0; ith_row < image_out.rows; ++ith_row)
	{
#pragma omp parrallel
		for (int ith_col = 0; ith_col < image_out.cols; ++ith_col)
		{
			cv::Vec3b rgb_pixel = image_in.at<cv::Vec3b>(ith_row, ith_col);
			if (ith_row % 2 == ith_col % 2)
			{
				rgb_pixel[0] = 0;
				rgb_pixel[2] = 0;
				image_out.at<cv::Vec3b>(ith_row, ith_col) = rgb_pixel;
			}
			else if (ith_row % 2)
			{
				//rgb_pixel[0] = 0;
				rgb_pixel[1] = 0;
				rgb_pixel[2] = 0;
				image_out.at<cv::Vec3b>(ith_row, ith_col) = rgb_pixel;
			}
			else
			{
				rgb_pixel[0] = 0;
				rgb_pixel[1] = 0;
				//rgb_pixel[2] = 0;
				image_out.at<cv::Vec3b>(ith_row, ith_col) = rgb_pixel;
			}

		}
	}
}
