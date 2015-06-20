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
		HISTORY(cv::Mat& ori_img); // : m_last_computed_image(ori_img) { };
		~HISTORY() { };

		IO_ERROR AddNextStep(LUW::PROCESS& process);
		IO_ERROR ComputeHistory();

		LUW::HISTORY& operator+(LUW::PROCESS& process)
		{
			IO_ERROR msg = AddNextStep(process);
			return (*this);
		}

		const std::vector<cv::Mat>& GetLastResults() { return m_steps.back(); }

		std::vector<LUW::PROCESS> m_process;
		std::vector< std::vector<cv::Mat> > m_steps;

	private:



	};
}
#endif