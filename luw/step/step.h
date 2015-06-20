
#ifndef __LUW_STEP_H_
#define __LUW_STEP_H_

#include "compat/compat.h"
#include <opencv2/core.hpp> //Mat
#include "luw/process/process.h"

namespace LUW
{

	class STEP
	{
	public:

		//Constructor/Destructor
		STEP(const cv::Mat images_in, LUW::PROCESS& _process) : m_image_to_process(images_in), m_process(_process), m_has_changed(true) { }
		~STEP();

		inline std::vector<cv::Mat>&& Result()
		{
			std::vector<cv::Mat> result = m_process.Apply(m_image_to_process);
			m_has_changed = false;

			return std::move(result);
		}

		inline void SetImageToProcess(cv::Mat& image_to_process)
		{
			m_image_to_process = image_to_process;
			m_has_changed = true;
		}

		inline bool HasChanged() { return m_has_changed; }

		inline const LUW::PROCESS& GetProcess() { return m_process; }
		IO_ERROR SetProcess(LUW::PROCESS& process)
		{
			m_process = process;
			m_has_changed = true;
		}

		//Attributes
	private:
		cv::Mat m_image_to_process;
		LUW::PROCESS& m_process;
		bool m_has_changed;

	};

}
#endif