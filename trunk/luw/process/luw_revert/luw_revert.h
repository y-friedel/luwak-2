#ifndef __LUW_REVERT_H_
#define __LUW_REVERT_H_

#include <opencv2/core/core.hpp> //Mat
#include "luw/luw_process/luw_process.h"
#include "compat/compat.h"

class LUW_REVERT : public LUW_PROCESS
{
public:

	//Constructor/Destructor
	LUW_REVERT();
	~LUW_REVERT();
	
	virtual IO_ERROR Apply(const cv::Mat& image_in, cv::Mat& image_out);

private:



};

#endif