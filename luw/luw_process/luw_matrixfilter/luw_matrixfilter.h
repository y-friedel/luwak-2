#ifndef __LUW_MATRIXFILTER_H_
#define __LUW_MATRIXFILTER_H_

#include <opencv2/core/core.hpp> //Mat
#include "luw/luw_process/luw_process.h"
#include "compat/compat.h"

class LUW_MATRIXFILTER : public LUW_PROCESS
{
public:

	//Constructor/Destructor
	LUW_MATRIXFILTER(cv::Mat& filter);
	~LUW_MATRIXFILTER();
	
	virtual IO_ERROR Apply(const cv::Mat& image_in, cv::Mat& image_out);

private:
	cv::Mat filter_matrix;



};

#endif