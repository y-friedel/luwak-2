#ifndef __LUW_HOUGH_H_
#define __LUW_HOUGH_H_

#include <opencv2/core.hpp> //Mat
#include "luw/process/process.h"
#include "compat/compat.h"


namespace LUW
{

	class HOUGH : public PROCESS
	{
	public:

		//Constructor/Destructor
		HOUGH(unsigned int nb_samples = 100);
		~HOUGH();

		virtual std::vector<cv::Mat> Apply(const cv::Mat& image_in);
		virtual IO_ERROR ApplyGS(const cv::Mat& image_in, cv::Mat& image_out);
		virtual IO_ERROR ApplyHSV(const cv::Mat& image_in, cv::Mat& image_out);

	protected:
		unsigned int m_nb_samples;

	};

}
#endif