#ifndef __LUW_BLUR_H_
#define __LUW_BLUR_H_

#include <opencv2/core/core.hpp> //Mat
#include "luw/process/process.h"
#include "compat/compat.h"


namespace LUW
{

	class BLUR : public PROCESS
	{
	public:

		//Constructor/Destructor
		BLUR(int _size);
		~BLUR();

		virtual IO_ERROR Apply(const cv::Mat& image_in, cv::Mat& image_out);

	private:
		int blur_size;


	};

}
#endif