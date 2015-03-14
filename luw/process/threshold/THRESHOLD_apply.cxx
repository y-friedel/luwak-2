#include "luw/process/threshold/threshold.h"
#include <opencv2/core/core.hpp> //Mat

IO_ERROR LUW::THRESHOLD::Apply(const cv::Mat& image_in, cv::Mat& image_out)
{
	if (!image_in.data)
		return IO_NOT_FOUND;

	if (image_in.type() != CV_8UC1)
		return IO_INCOMPATIBLE;

	image_out = cv::Mat::zeros(image_in.rows, image_in.cols, CV_8UC1);

#pragma omp parrallel
	for (int ith_row = 0; ith_row < image_out.rows; ++ith_row)
	{
#pragma omp parrallel
		for (int ith_col = 0; ith_col < image_out.cols; ++ith_col)
		{
			if (image_in.at<uchar>(ith_row, ith_col) > m_threshold)
				image_out.at<uchar>(ith_row, ith_col) = 255;
		}
	}

	return IO_OK;
}
