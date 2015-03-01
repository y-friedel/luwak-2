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
		HISTORY(cv::Mat& ori_img) :last_computed_image(ori_img) { };
		~HISTORY() { };

		IO_ERROR AddNextStep(LUW::PROCESS& process)
		{
			LUW::STEP next_step(last_computed_image, process);
			history.push_back(next_step);
			IO_ERROR err = ComputeHistory();
			return err;
		}

		IO_ERROR ComputeHistory()
		{

			//Find the first modified step
			unsigned int ith_step = 0;
			while (ith_step < history.size() && history[ith_step].has_changed == false)
				ith_step++;

			cv::Mat result;

			//Then recompute all the next steps
			for (ith_step; ith_step < history.size(); ++ith_step)
			{
				IO_ERROR err = history[ith_step].Result(result);

				if (err != IO_OK)
					return err;

				history[ith_step].has_changed = false;

				//Link it with the next step
				if (ith_step + 1 < history.size())
				{
					history[ith_step + 1].image_to_process = result;
				}
			}
			last_computed_image = result;

			return IO_OK;
		}

		std::vector<LUW::STEP> history;
		cv::Mat last_computed_image;

	private:



	};
}
#endif