#include "luw/process/bayer/bayer.h"
#include <opencv2/core.hpp> //Mat


//NB : this is a way non-optimized (and non official) version of the Bayer revert 
void LUW::BAYER::ApplyRevert(const cv::Mat& image_in, cv::Mat& image_out)
{
	if (!image_in.data)
		throw std::exception("Bayer Filter : Image not found", IO_NOT_FOUND);

	if (image_in.type() != CV_8UC1)
		throw std::exception("Bayer Filter : Image type not supported", IO_INCOMPATIBLE);

	image_out = cv::Mat::zeros(image_in.rows, image_in.cols, CV_8UC3);

#pragma omp parrallel
	for (int ith_row = 0; ith_row < image_out.rows; ++ith_row)
	{
#pragma omp parrallel
		for (int ith_col = 0; ith_col < image_out.cols; ++ith_col)
		{
			cv::Vec3b rgb_pixel;
			if (ith_row % 2 == ith_col % 2) //Green Values is the most tricky color
			{
				int left_right_neigbors = 0;
				int up_down_neighbors = 0;

				for (int i = -1; i <= 1; ++i)
				{
					for (int j = -1; j <= 1; ++j)
					{
						//avoid out of image issues
						int x = abs(ith_row + i);
						if (x >= image_out.rows)
							x = ith_row - i;

						int y = abs(ith_col + j);
						if (y >= image_out.cols)
							y = ith_col - j;

						if (i == 0 && j != 0) // Left/right Neighbors
						{
							left_right_neigbors += image_in.at<uchar>(x, y);
						}
						else if (i!=0 && j==0) // Up/down Neighbors
						{
							up_down_neighbors += image_in.at<uchar>(x, y);
						}
					}
				}

				int red = 0;
				int green = image_in.at<uchar>(ith_row, ith_col);
				int blue = 0;

				if (ith_row % 2) // Left/Right Neigbors are Red
				{
					red = left_right_neigbors / 2;
					blue = up_down_neighbors / 2;
				}
				else // Left/Right Neigbors are blue
				{
					red = up_down_neighbors / 2;
					blue = left_right_neigbors / 2;
				}

				rgb_pixel[0] = red;
				rgb_pixel[1] = green;
				rgb_pixel[2] = blue;

				image_out.at<cv::Vec3b>(ith_row, ith_col) = rgb_pixel;
			}
			else if (ith_row % 2) //Red Values
			{
				int red   = 0;
				int green = 0;
				int blue  = 0;
				for (int i = -1; i <= 1; ++i)
				{
					for (int j = -1; j <= 1; ++j)
					{
						//avoid out of image issues
						int x = abs(ith_row + i);
						if (x >= image_out.rows)
							x = ith_row - i;

						int y = abs(ith_col + j);
						if (y >= image_out.cols)
							y = ith_col - j;

						if (i == 0 && j == 0)
						{
							red = image_in.at<uchar>(x, y);
						}
						else if ((i + j) % 2 != 0) //Green values (OPTI : Corner sum coord == even) 
						{
							green += image_in.at<uchar>(x, y);
						}
						else
						{
							blue += image_in.at<uchar>(x, y);
						}
					}
				}
				
				rgb_pixel[0] = red;
				rgb_pixel[1] = green/4;
				rgb_pixel[2] = blue/4;
				image_out.at<cv::Vec3b>(ith_row, ith_col) = rgb_pixel;
			}
			else //Blue Values
			{
				int red = 0;
				int green = 0;
				int blue = 0;
				for (int i = -1; i <= 1; ++i)
				{
					for (int j = -1; j <= 1; ++j)
					{
						//avoid out of image issues
						int x = abs(ith_row + i);
						if (x >= image_out.rows)
							x = ith_row - i;

						int y = abs(ith_col + j);
						if (y >= image_out.cols)
							y = ith_col - j;

						if (i == 0 && j == 0)
						{
							blue = image_in.at<uchar>(x, y);
						}
						else if ((i + j) % 2 != 0) //Green values (OPTI : Non-Corner sum coord == odds) 
						{
							green += image_in.at<uchar>(x, y);
						}
						else
						{
							red += image_in.at<uchar>(x, y);
						}
					}
				}

				rgb_pixel[0] = red / 4;
				rgb_pixel[1] = green / 4;
				rgb_pixel[2] = blue;
				image_out.at<cv::Vec3b>(ith_row, ith_col) = rgb_pixel;
			}
		}
	}
}
