#ifndef __LUW_HISTORY_H_
#define __LUW_HISTORY_H_

#include "luw/step/step.h"
#include <vector>

namespace LUW
{

	class HISTORY
	{
	public:

		//Constructor/Destructor
		HISTORY(cv::Mat& ori_img) : m_last_computed_image(ori_img) { };
		~HISTORY() { };

		IO_ERROR AddNextStep(LUW::PROCESS& process);
		IO_ERROR ComputeHistory();

		std::vector<LUW::STEP> m_history;
		cv::Mat m_last_computed_image;

	private:



	};
}
#endif