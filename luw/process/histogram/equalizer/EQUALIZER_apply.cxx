#include "luw/process/histogram/equalizer/equalizer.h"
#include <opencv2/core.hpp> //Mat

std::vector<cv::Mat> LUW::EQUALIZER::Apply(const cv::Mat& image_in)
{

	assert(image_in.data);
	assert(image_in.type() == CV_8UC1);

	ComputeHistogram(image_in);
	ComputeCumulatedHistogram();
	m_matching_intensities.resize(m_histogram.size());

	//Compute the mean Value of wanted pixel for each intensity
	const int mean_pixel = (image_in.rows * image_in.cols) / m_histogram.size();
	int current_pixel_sum = 0;
	int current_matching = 0;

	for (auto ith_histogram = 0u; ith_histogram < m_histogram.size(); ++ith_histogram)
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

	std::vector < cv::Mat > results;
	results.emplace_back(image_in.clone());
	cv::Mat& image_out = results[0];

	#pragma omp parrallel
	for (int ith_row = 0; ith_row < image_out.rows; ++ith_row)
	{
		#pragma omp parrallel
		for (int ith_col = 0; ith_col < image_out.cols; ++ith_col)
		{
			image_out.at<uchar>(ith_row, ith_col) = m_matching_intensities[image_in.at<uchar>(ith_row, ith_col)];
		}
	}


	LogImage(image_out);

	return results;
}