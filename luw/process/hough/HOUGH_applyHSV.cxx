#include "luw/process/hough/hough.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/core/core.hpp> //Mat

#define _USE_MATH_DEFINES
#include <math.h>
#include <limits>

IO_ERROR LUW::HOUGH::ApplyHSV(const cv::Mat& image_in, cv::Mat& image_out)
{
	if (!image_in.data)
		return IO_NOT_FOUND;

	int margin = 50; //px
	int width = 1000;
	int height = 600;

	cv::Mat image_temp = cv::Mat::zeros(height, width, CV_32SC1);
	image_out = cv::Mat::zeros(height, width, CV_8UC1);

	std::vector<cv::Point2d> samples;

	//For render only
	double min_r = std::numeric_limits<double>::max();
	double max_r = std::numeric_limits<double>::min();

	for (int ith_row = 0; ith_row < image_in.rows; ++ith_row)
	{
		for (int ith_col = 0; ith_col < image_in.cols; ++ith_col)
		{
			cv::Vec3b hsv_pixel = image_in.at<cv::Vec3b>(ith_row, ith_col);
			if (hsv_pixel[2] == 255)
			{
				double gradient_orientation_rad = M_PI * hsv_pixel[0] / 180;
				double perfect_orientation = gradient_orientation_rad + M_PI / 2.;
				double tolerance_angle = M_PI * 90. / 180.;

				//Compute line samples
				for (unsigned int i = 0; i < m_nb_samples; ++i)
				{
					double theta = perfect_orientation - tolerance_angle / 2 + (tolerance_angle*i) / m_nb_samples;
					if (theta > M_PI) theta -= M_PI;
					if (theta < 0)    theta += M_PI;

					//The sample are around the perfect value
					//double theta = (i*M_PI) / nb_samples;
					double r = cos(theta)*ith_col + sin(theta)*ith_row;
					samples.push_back(cv::Point2d(r, theta));

					if (r < min_r) min_r = r;
					if (r > max_r) max_r = r;
				}
			}
		}
	}

	double min_theta = 0.;
	double max_theta = M_PI;

	//Get the max value (for render only)
	int max_value = 0;
	for (unsigned int i = 0; i < samples.size(); ++i)
	{
		double r = samples[i].x;
		double theta = samples[i].y;

		unsigned int x = 100 + (r - min_r) / (max_r - min_r) * (image_temp.rows - 201);
		unsigned int y = 100 + (theta - min_theta) / (max_theta - min_theta) * (image_temp.cols - 201);

		image_temp.at<int>(x, y) += 1;
		if (image_temp.at<int>(x, y) > max_value)
			max_value = image_temp.at<int>(x, y);
	}

	for (int ith_row = 0; ith_row < image_out.rows; ++ith_row)
	{
		for (int ith_col = 0; ith_col < image_out.cols; ++ith_col)
		{
			image_out.at<uchar>(ith_row, ith_col) = ((double)image_temp.at<int>(ith_row, ith_col) / max_value) * 255;
		}
	}




	return IO_OK;
}