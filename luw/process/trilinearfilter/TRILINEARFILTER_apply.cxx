#include "luw/process/trilinearfilter/trilinearfilter.h"
#include <opencv2/core.hpp> //Mat
#include <iostream>

std::vector<cv::Mat> LUW::TRILINEARFILTER::Apply(const cv::Mat& image_in)
{

	try
	{
		std::vector<cv::Mat> images_out(0);
		if (!image_in.data)
			return std::move(images_out);

		if (image_in.type() != CV_8UC3)
			return std::move(images_out);

		cv::Mat image_out;
		image_in.copyTo(image_out);

		int halfkernelsize = 20;
		float id = 5.f;
		float cd = 50.f;

		int kernelDim = 2 * halfkernelsize + 1;

		for (int ith_row = 0; ith_row < image_in.rows; ++ith_row)
		{
			for (int ith_col = 0; ith_col < image_in.cols; ++ith_col)
			{

				float sumWeight = 0;

				//unsigned int ctrIdx = y*width + x;


				cv::Vec3b ctrPix = image_in.at<cv::Vec3b>(ith_row, ith_col);

				//float ctrPix[3];
				//ctrPix[0] = image_in.at(ctrIdx).x;
				//ctrPix[1] = image_in.at(ctrIdx).y;
				//ctrPix[2] = image_in.at(ctrIdx).z;

				// neighborhood of current pixel
				int kernelStartX, kernelEndX, kernelStartY, kernelEndY;
				kernelStartX = ith_col - halfkernelsize;
				kernelEndX = ith_col + halfkernelsize;

				kernelStartY = ith_row - halfkernelsize;
				kernelEndY = ith_row + halfkernelsize;

				cv::Vec3f _sum;

				for (int win_ith_row = kernelStartY; win_ith_row <= kernelEndY; win_ith_row++)
				{

					int in_bound_ith_row = abs(win_ith_row);
					if (in_bound_ith_row >= image_in.rows)
						in_bound_ith_row = 2*image_in.rows- in_bound_ith_row - 1;

					for (int win_ith_col = kernelStartX; win_ith_col <= kernelEndX; win_ith_col++)
					{

						int in_bound_ith_col = abs(win_ith_col);
						if (in_bound_ith_col >= image_in.cols)
							in_bound_ith_col = 2 * image_in.cols - in_bound_ith_col - 1;

						//unsigned int idx = std::max(0, std::min(j, height - 1))*width + std::max(0, std::min(i, width - 1));

						cv::Vec3b curPix = image_in.at<cv::Vec3b>(in_bound_ith_row, in_bound_ith_col);
						//float curPix[3];
						//curPix[0] = image_in[idx].x;
						//curPix[1] = image_in[idx].y;
						//curPix[2] = image_in[idx].z;


						float currWeight;

						// define bilateral filter kernel weights
						float imageDist = sqrt((float)((in_bound_ith_col - ith_col)*(in_bound_ith_col - ith_col) + (in_bound_ith_row - ith_row)*(in_bound_ith_row - ith_row)));

						float colorDist = sqrt((float)((curPix[0] - ctrPix[0])*(curPix[0] - ctrPix[0]) +
							(curPix[1] - ctrPix[1])*(curPix[1] - ctrPix[1]) +
							(curPix[2] - ctrPix[2])*(curPix[2] - ctrPix[2])));

						double inverse_p1 = exp((imageDist / id)*(imageDist / id)*0.5);
						double inverse_p2 = exp((colorDist / cd)*(colorDist / cd)*0.5);
						currWeight = 1.0f / (exp((imageDist / id)*(imageDist / id)*0.5)*exp((colorDist / cd)*(colorDist / cd)*0.5));
						sumWeight += currWeight;

						_sum[0] += currWeight*curPix[0];
						_sum[1] += currWeight*curPix[1];
						_sum[2] += currWeight*curPix[2];
					}
				}

				_sum[0] /= sumWeight;
				_sum[1] /= sumWeight;
				_sum[2] /= sumWeight;


				image_out.at<cv::Vec3b>(ith_row, ith_col) = _sum;

				//image_out[ctrIdx].x = (int)(floor(_sum[0]));
				//image_out[ctrIdx].y = (int)(floor(_sum[1]));
				//image_out[ctrIdx].z = (int)(floor(_sum[2]));
				//image_out[ctrIdx].w = image_in[ctrIdx].w;
			}

		}

		LogImage(image_out);
		images_out.emplace_back(image_out);
		return std::move(images_out);

	}
	catch (std::exception& e)
	{
		std::cout << "error" << std::endl;
	}


}
