#ifndef __LUW_MATRIXFILTER_H_
#define __LUW_MATRIXFILTER_H_

#include <opencv2/core/core.hpp> //Mat
#include "luw/process/process.h"
#include "compat/compat.h"

namespace LUW
{
	class MATRIXFILTER : public PROCESS
	{
	public:

		//Constructor/Destructor
		MATRIXFILTER(cv::Mat& filter);
		~MATRIXFILTER();

		virtual IO_ERROR Apply(const cv::Mat& image_in, cv::Mat& image_out);

	private:
		cv::Mat filter_matrix;



	};
}
#endif