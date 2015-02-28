#include "luw_histogram.h"
#include <opencv2/core/core.hpp> //Mat

IO_ERROR LUW_HISTOGRAM::ComputeHistogram(const cv::Mat& image_in)
{
	if (!image_in.data)
		return IO_NOT_FOUND;

#pragma omp parrallel
	for (int ith_row = 0; ith_row < image_in.rows; ++ith_row)
	{
#pragma omp parrallel
		for (int ith_col = 0; ith_col < image_in.cols; ++ith_col)
		{
			uchar intensity = image_in.at<uchar>(ith_row, ith_col);
			m_histogram[intensity] += 1;
		}
	}

	return IO_OK;
}
