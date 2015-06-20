#include "luw/process/histogram/histogram.h"
#include <opencv2/core.hpp> //Mat

std::vector<cv::Mat> LUW::HISTOGRAM::Apply(const cv::Mat& image_in)
{
	assert(image_in.data);
	assert(image_in.type() == CV_8UC1);

	ComputeHistogram(image_in);
	ComputeCumulatedHistogram();

	int margin = 50; //px
	int width = 1000;
	int height = 600;

	std::vector < cv::Mat > results;
	results.emplace_back(cv::Mat::zeros(height, width, CV_8UC1));
	cv::Mat& image_out = results[0];

	//Check min/max in order to compute the most beautiful histogram
	auto min_intensity = (*image_in.size);
	auto max_intensity = 0;

	for (auto current_intensity : m_histogram)
	{
		if (current_intensity < min_intensity) min_intensity = current_intensity;
		else if (current_intensity > max_intensity) max_intensity = current_intensity;
	}
	
	//Draw the histogram
	for (int ith_col = 0 + margin; ith_col < image_out.cols - margin; ++ith_col)
	{
		if (ith_col % 3 == 0 && (ith_col - margin) / 3 < 256)
		{
			for (int ith_row = image_out.rows -1 - margin ; ith_row >= 0 + margin; --ith_row)
			{
				int row_intensity = (ith_col - margin) / 3;
				double current_intensity = 
					(double)(m_histogram[row_intensity]) / max_intensity * (height - 2 * margin);
				double current_cumulated_intensity = 
					(double)(m_cumulated_histogram[row_intensity]) / m_cumulated_histogram[255] * (height - 2 * margin);

				if ((image_out.rows - ith_row)<= current_intensity + margin )
				{
					image_out.at<uchar>(ith_row, ith_col) = 255;
				}

				double cumulated_threshold = fabs((image_out.rows - ith_row) - (current_cumulated_intensity + margin));
				if (cumulated_threshold >= 0 && cumulated_threshold < 1)
				{
					image_out.at<uchar>(ith_row, ith_col) = 50;
				}

			}
		}
	}

	
	image_out.col(50) = 50;
	image_out.row(image_out.rows - 50) = 50;

	LogImage(image_out);

	return std::move(results);
}
