#include "luw/process/matrixfilter/matrixfilter.h"
#include <opencv2/core/core.hpp> //Mat
#include "opencv/cv.h"

#define _USE_MATH_DEFINES
#include <math.h>

IO_ERROR LUW::MATRIXFILTER::Apply(const cv::Mat& image_in, cv::Mat& image_out)
{
	if (!image_in.data)
		return IO_NOT_FOUND;

	if (image_in.type() != CV_8UC1)
		return IO_INCOMPATIBLE;

	double max_intensity = 0.;
	double min_intensity = 255.;
	double mean_intensity = 0.;

	// Opti/Better result (balanced matrix only) :
	// Compute the worst case of your input matrix, then divide all your final intensities by this
	int max_matrix = 0;
	for (int ith_mat_row = -0; ith_mat_row < m_filter_matrix.rows; ++ith_mat_row)
	{
		for (int ith_mat_col = 0; ith_mat_col < m_filter_matrix.cols; ++ith_mat_col)
		{
			if (m_filter_matrix.at<char>(ith_mat_row, ith_mat_col) > 0)
				max_matrix = m_filter_matrix.at<char>(ith_mat_row, ith_mat_col) * 255;
		}
	}

	cv::Mat gradients = cv::Mat::zeros(image_in.rows, image_in.cols, CV_64FC2);

	for (int ith_row = 0; ith_row < image_in.rows; ++ith_row)
	{
		for (int ith_col = 0; ith_col < image_in.cols; ++ith_col)
		{
			int pixel_value_horizontal = 0;
			int pixel_value_vertical   = 0;

			//Apply the matrix on each pixel
			for (int ith_mat_row = - 0; ith_mat_row < m_filter_matrix.rows; ++ith_mat_row)
			{
				for (int ith_mat_col = 0; ith_mat_col < m_filter_matrix.cols; ++ith_mat_col)
				{
					int ith_target_row = ith_row + (ith_mat_row - 1 / 2 * (m_filter_matrix.rows));
					int ith_target_col = ith_col + (ith_mat_col - 1 / 2 * (m_filter_matrix.cols));

					if (ith_target_row < 0)
						ith_target_row = abs(ith_target_row);

					if (ith_target_col < 0)
						ith_target_col = abs(ith_target_col);

					if (ith_target_row >= image_in.rows)
						ith_target_row = ith_row - (ith_mat_row - 1 / 2 * (m_filter_matrix.rows));

					if (ith_target_col >= image_in.cols)
						ith_target_col = ith_col - (ith_mat_col - 1 / 2 * (m_filter_matrix.cols));

					int yfl_val_mal = m_filter_matrix.at<char>(ith_mat_row, ith_mat_col);
					int target_pixel = image_in.at<uchar>(ith_target_row, ith_target_col);
					pixel_value_horizontal += target_pixel * m_filter_matrix.at<char>(ith_mat_row, ith_mat_col);
					pixel_value_vertical   += target_pixel * m_filter_matrix.at<char>(ith_mat_col, ith_mat_row);
				}
			}

			double gradient_magnitude = sqrt(pixel_value_horizontal*pixel_value_horizontal + pixel_value_vertical*pixel_value_vertical)/2;
			double gradient_direction = atan2(pixel_value_horizontal, pixel_value_vertical);

			cv::Vec2d gradient;
			gradient[0] = gradient_magnitude;
			gradient[1] = gradient_direction;

			gradients.at<cv::Vec2d>(ith_row, ith_col) = gradient;

			mean_intensity += gradient_magnitude;
			if (gradient_magnitude > max_intensity) max_intensity = gradient_magnitude;
			if (gradient_magnitude < min_intensity) min_intensity = gradient_magnitude;
		}
	}


	mean_intensity /= image_in.rows * image_in.cols;


	//Create the output image
	if (m_output_level == INTENSITY)
	{
		image_out = cv::Mat::zeros(image_in.rows, image_in.cols, CV_8UC1);
		for (int ith_row = 0; ith_row < image_in.rows; ++ith_row)
		{
			for (int ith_col = 0; ith_col < image_in.cols; ++ith_col)
			{
				double original_result = gradients.at<cv::Vec2d>(ith_row, ith_col)[0];
				double d_result = ((original_result - min_intensity) / max_intensity) * 255.;
				uchar u_result = uchar(d_result);

				//if (u_result < mean_intensity)
				//	u_result = 0;
				//else u_result = 255;

				image_out.at<uchar>(ith_row, ith_col) = u_result;
				//image_out = ((gradients - min_intensity) / 30.) * 255;
			}
		}
	}
	else if (m_output_level == GRADIENT)
	{
		//Note : For HSV, Hue range is[0, 179], Saturation range is[0, 255] and Value range is[0, 255].1
		//softwares use different scales.So if you are comparing OpenCV values with them, you need to normalize these ranges.
		image_out = cv::Mat::zeros(image_in.rows, image_in.cols, CV_8UC3);

		for (int ith_row = 0; ith_row < image_in.rows; ++ith_row)
		{
			for (int ith_col = 0; ith_col < image_in.cols; ++ith_col)
			{
				double gradient_magnitude = gradients.at<cv::Vec2d>(ith_row, ith_col)[0];
				double gradient_direction = gradients.at<cv::Vec2d>(ith_row, ith_col)[1];

				uchar image_value = uchar(((gradient_magnitude - min_intensity) / max_intensity) * 255.);

				cv::Vec3b hsv_pixel;

				hsv_pixel[0] = (gradient_direction+M_PI) * 90 / M_PI;
				hsv_pixel[1] = 255;
				hsv_pixel[2] = image_value;
				image_out.at<cv::Vec3b>(ith_row, ith_col) = hsv_pixel;
			}
		}

		cv::cvtColor(image_out, image_out, CV_HSV2RGB);

	}

	return IO_OK;
}
