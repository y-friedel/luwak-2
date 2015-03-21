#include "luw/process/hough/hough.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/core/core.hpp> //Mat

#define _USE_MATH_DEFINES
#include <math.h>
#include <limits>


//Work for filtered image only (TODO : find a way to use it on all the image in the world)
IO_ERROR LUW::HOUGH::Apply(const cv::Mat& image_in, cv::Mat& image_out)
{
	if (!image_in.data)
		return IO_NOT_FOUND;

	int margin = 50; //px
	int width = 1000;
	int height = 600;

	cv::Mat image_temp = cv::Mat::zeros(height, width, CV_32SC1);
	image_out = cv::Mat::zeros(height, width, CV_8UC1);

	//Number of line samples for each point
	unsigned int nb_samples = 800;

	std::vector<cv::Point2d> samples;

	//For the graph render
	double min_r = std::numeric_limits<double>::max();
	double max_r = std::numeric_limits<double>::min();
	double min_theta = std::numeric_limits<double>::max();
	double max_theta = std::numeric_limits<double>::min();

	for (int ith_row = 0; ith_row < image_in.rows; ++ith_row)
	{
		for (int ith_col = 0; ith_col < image_in.cols; ++ith_col)
		{
			if (image_in.at<uchar>(ith_row, ith_col) == 255)
			{
				//Compute line samples
				for (unsigned int i = 0; i < nb_samples; ++i)
				{
					//The sample are between [0 - PI[
					double theta = (i*M_PI) / nb_samples;
					double r = cos(theta)*ith_col + sin(theta)*ith_row;
					samples.push_back(cv::Point2d(r, theta));

					if (r < min_r) min_r = r;
					if (r > max_r) max_r = r;
					if (theta < min_theta) min_theta = theta;
					if (theta > max_theta) max_theta = theta;

					//Draw each points (r, theta) on the output image
					//if (r >= 0. && r < image_out.rows && theta >= 0. && theta < image_out.cols)
					//	image_out.at<uchar>(r, theta) = 255;
				}
			}
		}
	}


	int max_value = 0;
	for (unsigned int i = 0; i < samples.size(); ++i)
	{
		double r     = samples[i].x;
		double theta = samples[i].y;

		unsigned int x = 50 + (r - min_r) / (max_r - min_r) * (image_temp.rows-101);
		unsigned int y = 50 + (theta - min_theta) / (max_theta - min_theta) * (image_temp.cols - 101);

		image_temp.at<int>(x, y) += 1;
		if (image_temp.at<int>(x, y) > max_value)
			max_value = image_temp.at<int>(x, y);
	}

	for (int ith_row = 0; ith_row < image_in.rows; ++ith_row)
	{
		for (int ith_col = 0; ith_col < image_in.cols; ++ith_col)
		{
			image_out.at<uchar>(ith_row, ith_col) = ((double)image_temp.at<int>(ith_row, ith_col) / max_value) * 255;
		}
	}




	return IO_OK;
}