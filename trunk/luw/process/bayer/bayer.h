#ifndef __LUW_BAYER_H_
#define __LUW_BAYER_H_

#include <opencv2/core/core.hpp> //Mat
#include "luw/process/process.h"
#include "compat/compat.h"

namespace LUW
{
	class BAYER : public LUW::PROCESS
	{
	public:
		
		enum RESULT_TYPE
		{
			COLOR,
			BLACK_WHITE,
			REVERT,
		};

		//Constructor/Destructor
		BAYER();
		BAYER(RESULT_TYPE result_type) : m_result_type(result_type) { }
		~BAYER();

		virtual IO_ERROR Apply(const cv::Mat& image_in, cv::Mat& image_out);
		virtual IO_ERROR ApplyColor(const cv::Mat& image_in, cv::Mat& image_out);
		virtual IO_ERROR ApplyBlackWhite(const cv::Mat& image_in, cv::Mat& image_out);
		virtual IO_ERROR ApplyRevert(const cv::Mat& image_in, cv::Mat& image_out);

	private:
		RESULT_TYPE m_result_type;


	};
}
#endif