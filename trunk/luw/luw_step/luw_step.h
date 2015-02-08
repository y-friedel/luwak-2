
#ifndef __LUW_STEP_H_
#define __LUW_STEP_H_

#include "compat/compat.h"
#include <opencv2/core/core.hpp> //Mat
#include "luw/luw_process/luw_process.h"

class LUW_STEP
{
public:

	//Constructor/Destructor
	LUW_STEP(cv::Mat& image_in, LUW_PROCESS& _process) : image_to_process(image_in), process(_process), has_changed(true) { }
	~LUW_STEP();

	IO_ERROR Result(cv::Mat& result)
	{
		return process.Apply(image_to_process, result);
		has_changed = true;
	}

	//Attributes
	cv::Mat image_to_process;
	LUW_PROCESS& process;
	bool has_changed;
private:



};

#endif