#ifndef __LUW_HISTOGRAM_H_
#define __LUW_HISTOGRAM_H_

#include <opencv2/core/core.hpp> //Mat
#include "luw/process/process.h"
#include "compat/compat.h"

namespace LUW
{
	class HISTOGRAM : public PROCESS
	{
	public:

		//Constructor/Destructor
		HISTOGRAM();
		~HISTOGRAM();


		//Return a picture of the histogram - not useful in the process, it shoud just be used for debug
		virtual IO_ERROR Apply(const cv::Mat& image_in, cv::Mat& image_out);

	protected:
		IO_ERROR ComputeHistogram(const cv::Mat& image_in);

	protected:
		std::vector<int> m_histogram;


	};
}
#endif