#ifndef __LUW_PROCESS_H_
#define __LUW_PROCESS_H_

#include <opencv2/core/core.hpp> //Mat
#include "compat/compat.h"

namespace LUW
{
	class PROCESS
	{
	public:
		//Constructor/Destructor
		PROCESS(){}
		~PROCESS(){}

		virtual IO_ERROR Apply(const cv::Mat& image_in, cv::Mat& image_out) = 0;

	private:
	};
}

#endif