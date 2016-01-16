#ifndef __LUW_INTEGRAL_H_
#define __LUW_INTEGRAL_H_

#include <opencv2/core.hpp> //Mat
#include "luw/process/process.h"
#include "compat/compat.h"
#include <set>

namespace LUW
{
	class INTEGRAL : public LUW::PROCESS
	{
	public:

		//Constructor/Destructor
		INTEGRAL(){}
		~INTEGRAL(){}

		virtual std::vector<cv::Mat> Apply(const cv::Mat& image_in);
		virtual IO_ERROR ApplyGS(const cv::Mat& image_in, cv::Mat& image_out);
		//virtual IO_ERROR ApplyHSV(const cv::Mat& image_in, cv::Mat& image_out);
		virtual std::vector<cv::Mat> ApplyHSV(const cv::Mat& image_in);
	};
}
#endif