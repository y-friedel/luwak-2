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

		//PROCESS& operator=(PROCESS&&);

		virtual std::vector<cv::Mat> Apply(const cv::Mat& image_in);

		IO_ERROR LogImage(const cv::Mat& image);

	private:
	};
}

#endif