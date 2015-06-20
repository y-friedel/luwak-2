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

		virtual std::vector<cv::Mat> Apply(const cv::Mat& image_in);


	protected:
		std::vector<int> m_matching_intensities;

	};


}

#endif