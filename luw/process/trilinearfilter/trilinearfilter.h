#ifndef __LUW_TRILINEARFILTER_H_
#define __LUW_TRILINEARFILTER_H_

#include <opencv2/core.hpp> //Mat
#include "luw/process/process.h"
#include "compat/compat.h"

namespace LUW
{
	class TRILINEARFILTER : public LUW::PROCESS
	{
	public:

		//Constructor/Destructor
		TRILINEARFILTER();
		TRILINEARFILTER(TRILINEARFILTER& revert);
		~TRILINEARFILTER();

		virtual std::vector<cv::Mat> Apply(const cv::Mat& image_in);

	private:



	};
}
#endif