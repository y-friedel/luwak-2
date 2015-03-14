#ifndef __LUW_HOUGH_H_
#define __LUW_HOUGH_H_

#include <opencv2/core/core.hpp> //Mat
#include "luw/process/process.h"
#include "compat/compat.h"


namespace LUW
{

	class HOUGH : public PROCESS
	{
	public:

		//Constructor/Destructor
		HOUGH();
		~HOUGH();

		virtual IO_ERROR Apply(const cv::Mat& image_in, cv::Mat& image_out);

	};

}
#endif