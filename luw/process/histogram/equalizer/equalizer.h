#ifndef __LUW_EQUALIZER_H_
#define __LUW_EQUALIZER_H_

#include "luw\process\histogram\histogram.h"

namespace LUW
{
	class EQUALIZER : public HISTOGRAM
	{
	public:

		//Constructor/Destructor
		EQUALIZER();
		~EQUALIZER();

		virtual IO_ERROR Apply(const cv::Mat& image_in, cv::Mat& image_out);


	protected:
		std::vector<int> m_matching_intensities;

	};


}

#endif