#include "luw/process/histogram/histogram.h"
#include <opencv2/core/core.hpp> //Mat

IO_ERROR LUW::HISTOGRAM::Apply(const cv::Mat& image_in, cv::Mat& image_out)
{
	if (!image_in.data)
		return IO_NOT_FOUND;

	if (image_in.type() != CV_8UC1)
		return IO_INCOMPATIBLE;

	ComputeHistogram(image_in);
	ComputeCumulatedHistogram();

	//Check min/max in order to compute the most beautiful histogram
	auto min_intensity = (*image_in.size);
	auto max_intensity = 0;

	for (auto current_intensity : m_histogram)
	{
		if (current_intensity < min_intensity) min_intensity = current_intensity;
		else if (current_intensity > max_intensity) max_intensity = current_intensity;
	}

	int margin = 50; //px
	int width  = 1000;
	int height = 600;
	

	//Draw the histogram
	image_out = cv::Mat::zeros(height, width, CV_8UC1);
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

	return IO_OK;
}
