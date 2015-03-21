#ifndef __LUW_MATRIXFILTER_H_
#define __LUW_MATRIXFILTER_H_

#include <opencv2/core/core.hpp> //Mat
#include "luw/process/process.h"
#include "compat/compat.h"

namespace LUW
{
	class MATRIXFILTER : public PROCESS
	{
	public:
		enum OUTPUT_LEVEL
		{
			INTENSITY,
			GRADIENT,
		};

		//Constructor/Destructor
		MATRIXFILTER(cv::Mat& filter, OUTPUT_LEVEL output_level = INTENSITY);
		~MATRIXFILTER();

		virtual IO_ERROR Apply(const cv::Mat& image_in, cv::Mat& image_out);

	private:
		cv::Mat m_filter_matrix;
		OUTPUT_LEVEL m_output_level;


	};
}
#endif