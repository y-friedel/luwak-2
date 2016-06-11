#include "luw/process/threshold/threshold.h"
#include <opencv2/core.hpp> //Mat
#include <iostream>
#include "opencv2/imgproc.hpp"

std::vector<cv::Mat> LUW::THRESHOLD::Apply(const cv::Mat& image_in)
{
	assert(image_in.data);

	std::vector<cv::Mat> results;
	results.emplace_back();
	cv::Mat& image_out = results[0];

	switch (image_in.type())
	{
	case CV_8UC1:
		ApplyGS(image_in, image_out);
		break;
	case CV_8UC3:
		return ApplyHSV(image_in);
		break;
	}

	LogImage(image_out);
	return std::move(results);
	
}

IO_ERROR LUW::THRESHOLD::ApplyGS(const cv::Mat& image_in, cv::Mat& image_out)
{
	if (!image_in.data)
		return IO_NOT_FOUND;

	if (image_in.type() != CV_8UC1)
		return IO_INCOMPATIBLE;

	image_out = cv::Mat::zeros(image_in.rows, image_in.cols, CV_8UC1);
	/*
#pragma omp parrallel
	for (int ith_row = 0; ith_row < image_out.rows; ++ith_row)
	{
#pragma omp parrallel
		for (int ith_col = 0; ith_col < image_out.cols; ++ith_col)
		{
			if (image_in.at<uchar>(ith_row, ith_col) > m_threshold)
				image_out.at<uchar>(ith_row, ith_col) = 255;
		}
	}
	*/
	return IO_OK;
}


std::vector<cv::Mat> LUW::THRESHOLD::ApplyHSV(const cv::Mat& image_in)
{

	std::vector<cv::Mat> images_out;
	std::vector<cv::MatIterator_<cv::Vec3b > > vec_it_out;
	for (auto i = 0u; i < m_threshold.size(); ++i)
	{
		images_out.push_back(cv::Mat::zeros(image_in.rows, image_in.cols, CV_8UC3));
		vec_it_out.push_back(images_out.back().begin<cv::Vec3b>());
	}

	#pragma omp parrallel
	for (auto& it_in = image_in.begin<cv::Vec3b>(); it_in != image_in.end<cv::Vec3b>(); ++it_in)
	{
		std::set<unsigned int>::iterator threshold_value = m_threshold.begin();

		#pragma omp parrallel
		for (unsigned int i = 0; i < m_threshold.size(); ++i)
		{
			auto it_out = vec_it_out[i];
			if ((*it_in)[2] > (*threshold_value))
			{
				(*it_out) = (*it_in);
				(*it_out)[2] = 255;
			}

			++threshold_value;
			if (it_in + 1 != image_in.end<cv::Vec3b>()) 
				vec_it_out[i]++;
		}
	}

	for (auto& image_out = images_out.begin(); image_out != images_out.end(); ++image_out)
	{
		cv::Mat hsv_result;
		cv::cvtColor((*image_out), hsv_result, CV_HSV2RGB);
		LogImage(hsv_result);
	}

	return images_out;
}
