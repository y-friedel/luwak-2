#ifndef __LUW_HISTOGRAM_H_
#define __LUW_HISTOGRAM_H_

#include <opencv2/core.hpp> //Mat
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
		virtual std::vector<cv::Mat> Apply(const cv::Mat& image_in);

	protected:
		IO_ERROR ComputeHistogram(const cv::Mat& image_in);
		IO_ERROR ComputeCumulatedHistogram();

	protected:
		std::vector<int> m_histogram;
		std::vector<int> m_cumulated_histogram;


	};
}
#endif