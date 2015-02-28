#ifndef __LUW_HISTOGRAM_H_
#define __LUW_HISTOGRAM_H_

#include <opencv2/core/core.hpp> //Mat
#include "luw/luw_process/luw_process.h"
#include "compat/compat.h"

class LUW_HISTOGRAM : public LUW_PROCESS
{
public:

	//Constructor/Destructor
	LUW_HISTOGRAM();
	~LUW_HISTOGRAM();
	
	virtual IO_ERROR Apply(const cv::Mat& image_in, cv::Mat& image_out);

protected:
	IO_ERROR ComputeHistogram(const cv::Mat& image_in);

protected:
	std::vector<int> m_histogram;


};

#endif