#include "luw/luw_process/luw_matrixfilter/luw_matrixfilter.h"
#include <opencv2/core/core.hpp> //Mat

IO_ERROR LUW_MATRIXFILTER::Apply(const cv::Mat& image_in, cv::Mat& image_out)
{
	if (!image_in.data)
		return IO_NOT_FOUND;

	image_in.copyTo(image_out);

	cv::Mat mat_temp = cv::Mat(image_in.rows, image_in.cols, CV_64FC1);

	double max_intensity = 0;
	double min_intensity = 255;
	double mean_intensity = 0;

	// Opti/Better result (balanced matrix only) :
	// Compute the worst case of your input matrix, then divide all your final intensities by this
	int max_matrix = 0;
	for (int ith_mat_row = -0; ith_mat_row < filter_matrix.rows; ++ith_mat_row)
	{
		for (int ith_mat_col = 0; ith_mat_col < filter_matrix.cols; ++ith_mat_col)
		{
			if (filter_matrix.at<char>(ith_mat_row, ith_mat_col) > 0)
				max_matrix = filter_matrix.at<char>(ith_mat_row, ith_mat_col) * 255;
		}
	}
	

	for (int ith_row = 0; ith_row < image_in.rows; ++ith_row)
	{
		for (int ith_col = 0; ith_col < image_in.cols; ++ith_col)
		{
			int pixel_value_horizontal = 0;
			int pixel_value_vertical   = 0;

			//Apply the matrix on each pixel
			for (int ith_mat_row = - 0; ith_mat_row < filter_matrix.rows; ++ith_mat_row)
			{
				for (int ith_mat_col = 0; ith_mat_col < filter_matrix.cols; ++ith_mat_col)
				{
					int ith_target_row = ith_row + (ith_mat_row - 1 / 2 * (filter_matrix.rows));
					int ith_target_col = ith_col + (ith_mat_col - 1 / 2 * (filter_matrix.cols));

					if (ith_target_row < 0)
						ith_target_row = abs(ith_target_row);

					if (ith_target_col < 0)
						ith_target_col = abs(ith_target_col);

					if (ith_target_row >= image_in.rows)
						ith_target_row = ith_row - (ith_mat_row - 1 / 2 * (filter_matrix.rows));

					if (ith_target_col >= image_in.cols)
						ith_target_col = ith_col - (ith_mat_col - 1 / 2 * (filter_matrix.cols));

					int yfl_val_mal = filter_matrix.at<char>(ith_mat_row, ith_mat_col);
					int target_pixel = image_in.at<uchar>(ith_target_row, ith_target_col);
					pixel_value_horizontal += target_pixel * filter_matrix.at<char>(ith_mat_row, ith_mat_col);
					pixel_value_vertical   += target_pixel * filter_matrix.at<char>(ith_mat_col, ith_mat_row);
				}
			}

			double pixel_value = sqrt(pixel_value_horizontal*pixel_value_horizontal + pixel_value_vertical*pixel_value_vertical)/2;
			mat_temp.at<double>(ith_row, ith_col) = pixel_value;

			mean_intensity += pixel_value;
			if (pixel_value > max_intensity) max_intensity = pixel_value;
			if (pixel_value < min_intensity) min_intensity = pixel_value;
		}
	}


	mean_intensity /= image_in.rows * image_in.cols;


	for (int ith_row = 0; ith_row < image_in.rows; ++ith_row)
	{
		for (int ith_col = 0; ith_col < image_in.cols; ++ith_col)
		{
			double original_result = mat_temp.at<double>(ith_row, ith_col);
			double d_result = ((mat_temp.at<double>(ith_row, ith_col) - min_intensity) / max_intensity) * 255.;
			uchar u_result = uchar(d_result);

			if (u_result < mean_intensity)
				u_result = 0;
			else u_result = 255;

			image_out.at<uchar>(ith_row, ith_col) = u_result;
			//image_out = ((mat_temp - min_intensity) / 30.) * 255;
		}
	}

	return IO_OK;
}
