#ifndef __LUW_PROCESS_H_
#define __LUW_PROCESS_H_

#include <opencv2/core.hpp> //Mat
#include "compat/compat.h"

namespace LUW
{
	class PROCESS
	{
	public:
		//Constructor/Destructor
		PROCESS(){}
		~PROCESS(){}

		virtual std::vector<cv::Mat> Apply(const cv::Mat& image_in);

		void LogImage(const cv::Mat& image);

	private:
	};
}

#endif