#ifndef __LUW_BLUR_H_
#define __LUW_BLUR_H_

#include <opencv2/core.hpp> //Mat
#include "luw/process/process.h"
#include "compat/compat.h"

#include<set>

namespace LUW
{

	class BLUR : public PROCESS
	{
	public:

		//Constructor/Destructor
		BLUR(int _size);
		BLUR(std::set<int>& _sizes);
		~BLUR();

		virtual std::vector<cv::Mat> Apply(const cv::Mat& image_in);

	private:
		std::set<int> m_blur_size;


	};

}
#endif