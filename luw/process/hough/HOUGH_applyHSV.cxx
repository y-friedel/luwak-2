#include "luw/process/hough/hough.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/core.hpp> //Mat

#define _USE_MATH_DEFINES
#include <math.h>
#include <limits>
#include <set>

IO_ERROR LUW::HOUGH::ApplyHSV(const cv::Mat& image_in, cv::Mat& image_out)
{
	double theta_accuracy = M_PI / 256.;
	double r_accuracy = 5;
	double tolerance_angle = M_PI * 60. / 180.;

	if (!image_in.data)
		return IO_NOT_FOUND;

	int margin = 50; //px
	int width = 1000;
	int height = 600;


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
				//[h]sv in opencv : [0,180]
				double gradient_orientation_rad = M_PI * (2*hsv_pixel[0]) / 180;
				double perfect_orientation = gradient_orientation_rad /*+ M_PI / 2.*/;

				//The code is actually in non-optmized version
				//Compute line samples
				for (unsigned int i = 0; i < m_nb_samples; ++i)
				{
					double theta = (i*M_PI) / m_nb_samples;

					//double theta = perfect_orientation - (tolerance_angle / 2) + ((tolerance_angle * i) / (m_nb_samples));
					//if (theta > M_PI) theta -= M_PI;
					//if (theta < 0)    theta += M_PI;

					//The sample are around the perfect value
					double r = cos(theta)*ith_col + sin(theta)*ith_row;
					samples.push_back(cv::Point2d(r, theta));

					//Put the value into our grid using int result of the division
					int theta_grid = (int)(theta / theta_accuracy);
					int r_grid = (int)(r / r_accuracy);

					auto point_on_grid = std::pair<int, int>(r_grid, theta_grid);

					if (m_grid.count(point_on_grid))
					{
						m_grid.at(point_on_grid) += 1;
					}
					else
					{
						m_grid.insert(std::pair<std::pair<int, int>, int>(point_on_grid, 1));
					}


					
					if (r < min_r) min_r = r;
					if (r > max_r) max_r = r;
				}
			}
		}
	}

	// Apply count filter on the grid
	int grid_intensity_threshold = 0;
	int sum_intensities = 0;
	int max_intensity = 0;
	int min_intensity = std::numeric_limits<int>::max();

	for (auto it = m_grid.begin(); it != m_grid.end(); ++it)
	{
		int current_value = (*it).second;
		//Compute the mean, min and max
		sum_intensities += current_value;
		if (current_value > max_intensity) max_intensity = current_value;
		if (current_value < min_intensity) min_intensity = current_value;
	}
	grid_intensity_threshold = (double)sum_intensities / m_grid.size() + max_intensity / 8; //BASIC
	//grid_intensity_threshold = (double)sum_intensities / m_grid.size() + max_intensity / 4; //FOR LENA
	//grid_intensity_threshold = sum_intensities / m_grid.size();
	//grid_intensity_threshold = 0.5 * max_intensity;

	std::set<std::pair<int, int > > keeped_lines;
	for (auto it = m_grid.begin(); it != m_grid.end(); ++it)
	{
		if ((*it).second >= grid_intensity_threshold)
			keeped_lines.insert((*it).first);
	}

	std::cout << keeped_lines.size() << std::endl;
	//cv::Mat lines_result = cv::Mat::zeros(image_in.rows, image_in.cols, CV_8UC3);
	cv::Mat lines_result;
	image_in.copyTo(lines_result);
	cv::cvtColor(lines_result, lines_result, CV_HSV2RGB);

	for (auto it = keeped_lines.begin(); it != keeped_lines.end(); ++it)
	{
		double line_r = r_accuracy * (*it).first;
		//double line_theta = (theta_accuracy * (*it).second) / M_PI * 180;
		double line_theta = theta_accuracy * (*it).second;

		double x_min = 0.;
		double y_min = line_r / sin(line_theta);

		double x_max = image_in.cols - 1;
		double y_max = (line_r - cos(line_theta)*(image_in.cols - 1)) / sin(line_theta);

		if (y_min < 0 || y_min > image_in.rows - 1)
		{
			y_min = 0.;
			x_min = line_r / cos(line_theta);
		}

		if (y_max < 0 || y_max > image_in.rows - 1)
		{
			y_max = image_in.rows - 1;
			x_max = (line_r - sin(line_theta)*(image_in.rows - 1)) / cos(line_theta);
		}

		//Compute min/max pts
		cv::Point2d pt_start(x_min, y_min);
		cv::Point2d pt_end(x_max, y_max);

		//std::cout << "(" << pt_start.x << ", " << pt_start.y << ") & (" << pt_end.x << ", " << pt_end.y << ")" << std::endl;

		//draw the line
		cv::line(lines_result, pt_start, pt_end, cv::Scalar(255, 0, 0));

	}

	image_out = lines_result;

	cv::Mat image_temp = cv::Mat::zeros(height, width, CV_32SC1);
	double min_theta = 0.;
	double max_theta = M_PI;

	//Get the max value (for render only)
	int max_value = 0;
	for (unsigned int i = 0; i < samples.size(); ++i)
	{
		double r = samples[i].x;
		double theta = samples[i].y;

		unsigned int x = static_cast<unsigned int>(100 + (r - min_r) / (max_r - min_r) * (image_temp.rows - 201));
		unsigned int y = static_cast<unsigned int>(100 + (theta - min_theta) / (max_theta - min_theta) * (image_temp.cols - 201));

		image_temp.at<int>(x, y) += 1;
		if (image_temp.at<int>(x, y) > max_value)
			max_value = image_temp.at<int>(x, y);
	}


	cv::Mat graph = cv::Mat::zeros(height, width, CV_8UC1);
	for (int ith_row = 0; ith_row < graph.rows; ++ith_row)
	{
		for (int ith_col = 0; ith_col < graph.cols; ++ith_col)
		{
			graph.at<uchar>(ith_row, ith_col) = static_cast<uchar>(((double)image_temp.at<int>(ith_row, ith_col) / max_value) * 255);
		}
	}

	LogImage(graph);



	return IO_OK;
}