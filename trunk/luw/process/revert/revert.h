#ifndef __LUW_REVERT_H_
#define __LUW_REVERT_H_

#include <opencv2/core/core.hpp> //Mat
#include "luw/process/process.h"
#include "compat/compat.h"

namespace LUW
{
	class REVERT : public LUW::PROCESS
	{
	public:

		//Constructor/Destructor
		REVERT();
		~REVERT();

		virtual IO_ERROR Apply(const cv::Mat& image_in, cv::Mat& image_out);

	private:



	};
}
#endif