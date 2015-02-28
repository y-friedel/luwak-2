
#ifndef __LUW_STEP_H_
#define __LUW_STEP_H_

#include "compat/compat.h"
#include <opencv2/core/core.hpp> //Mat
#include "luw/process/process.h"

namespace LUW
{

	class STEP
	{
	public:

		//Constructor/Destructor
		STEP(cv::Mat& image_in, LUW::PROCESS& _process) : image_to_process(image_in), process(_process), has_changed(true) { }
		~STEP();

		inline IO_ERROR Result(cv::Mat& result)
		{
			return process.Apply(image_to_process, result);
			has_changed = true;
		}

		inline int GetColorModel()
		{
			return image_to_process.type();
		}

		//Attributes
		cv::Mat image_to_process;
		LUW::PROCESS& process;
		bool has_changed;
	private:



	};

}
#endif