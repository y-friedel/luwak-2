#ifndef __LUW_THRESHOLD_H_
#define __LUW_THRESHOLD_H_

#include <opencv2/core.hpp> //Mat
#include "luw/process/process.h"
#include "compat/compat.h"

namespace LUW
{
	class THRESHOLD : public LUW::PROCESS
	{
	public:

		//Constructor/Destructor
		THRESHOLD(unsigned int threshold) : m_threshold(threshold){}
		~THRESHOLD(){}

		virtual std::vector<cv::Mat> Apply(const cv::Mat& image_in);
		virtual IO_ERROR ApplyGS(const cv::Mat& image_in, cv::Mat& image_out);
		virtual IO_ERROR ApplyHSV(const cv::Mat& image_in, cv::Mat& image_out);

	private:
		unsigned int m_threshold;


	};
}
#endif