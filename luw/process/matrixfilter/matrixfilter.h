#ifndef __LUW_MATRIXFILTER_H_
#define __LUW_MATRIXFILTER_H_

#include <opencv2/core.hpp> //Mat
#include "luw/process/process.h"
#include "compat/compat.h"

namespace LUW
{
	class MATRIXFILTER : public PROCESS
	{
	public:
		enum OUTPUT_TYPE
		{
			INTENSITY,
			GRADIENT,
		};

		//Constructor/Destructor
		MATRIXFILTER(cv::Mat& filter, OUTPUT_TYPE output_type = INTENSITY);
		~MATRIXFILTER();

		virtual std::vector<cv::Mat> Apply(const cv::Mat& image_in);

	private:
		cv::Mat m_filter_matrix;
		OUTPUT_TYPE m_output_level;


	};
}
#endif