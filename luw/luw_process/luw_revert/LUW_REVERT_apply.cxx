#include "luw_revert.h"
#include <opencv2/core/core.hpp> //Mat

IO_ERROR LUW_REVERT::Apply(const cv::Mat& image_in, cv::Mat& image_out)
{
	if (!image_in.data)
		return IO_NOT_FOUND;

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

	return IO_OK;
}
