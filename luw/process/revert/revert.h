#ifndef __LUW_REVERT_H_
#define __LUW_REVERT_H_

#include <opencv2/core.hpp> //Mat
#include "luw/process/process.h"
#include "compat/compat.h"

namespace LUW
{
	class REVERT : public LUW::PROCESS
	{
	public:

		//Constructor/Destructor
		REVERT();
		REVERT(REVERT& revert);
		~REVERT();

		virtual std::vector<cv::Mat> Apply(const cv::Mat& image_in);

	private:



	};
}
#endif