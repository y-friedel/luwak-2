#ifndef __LUW_BLUR_H_
#define __LUW_BLUR_H_

#include <opencv2/core/core.hpp> //Mat
#include "luw/luw_process/luw_process.h"
#include "compat/compat.h"

class LUW_BLUR : public LUW_PROCESS
{
public:

	//Constructor/Destructor
	LUW_BLUR(int _size);
	~LUW_BLUR();
	
	virtual IO_ERROR Apply(const cv::Mat& image_in, cv::Mat& image_out);

private:
	int blur_size;


};

#endif