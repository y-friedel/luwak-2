#include "luw/process/histogram/equalizer/equalizer.h"
#include <opencv2/core/core.hpp> //Mat

IO_ERROR LUW::EQUALIZER::Apply(const cv::Mat& image_in, cv::Mat& image_out)
{

	if (!image_in.data)
		return IO_NOT_FOUND;

	if (image_in.type() != CV_8UC1)
		return IO_INCOMPATIBLE;

	ComputeHistogram(image_in);
	ComputeCumulatedHistogram();
	m_matching_intensities.resize(m_histogram.size());

	//Compute the mean Value of wanted pixel for each intensity
	const int mean_pixel = (image_in.rows * image_in.cols) / m_histogram.size();
	int current_pixel_sum = 0;
	int current_matching = 0;

	for (unsigned int ith_histogram = 0; ith_histogram < m_histogram.size(); ++ith_histogram)
	{
		current_pixel_sum = m_cumulated_histogram[ith_histogram];
		if (current_pixel_sum <= (current_matching + 1)*mean_pixel)
		{
			m_matching_intensities[ith_histogram] = current_matching;
		}
		else
		{
			++current_matching;
			--ith_histogram;
		}
	}

	image_in.copyTo(image_out);

	#pragma omp parrallel
	for (int ith_row = 0; ith_row < image_out.rows; ++ith_row)
	{
		#pragma omp parrallel
		for (int ith_col = 0; ith_col < image_out.cols; ++ith_col)
		{
			image_out.at<uchar>(ith_row, ith_col) = m_matching_intensities[image_in.at<uchar>(ith_row, ith_col)];
		}
	}

	return IO_OK;
}