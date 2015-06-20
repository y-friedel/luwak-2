#include "luw/history/history.h"

IO_ERROR LUW::HISTORY::ComputeHistory()
{
	////Find the first modified step
	//auto it_step = m_history.begin();
	//while (it_step != m_history.end() && (*it_step).HasChanged() == false)
	//	++it_step;

	//cv::Mat image;

	////Then recompute all the next steps
	//for (it_step; it_step != m_history.end(); ++it_step)
	//{
	//	IO_ERROR err = (*it_step).Result(image);

	//	if (err != IO_OK) return err;

	//	//Link it with the next step
	//	if (it_step + 1 != m_history.end())
	//	{
	//		(*it_step).SetImageToProcess(image);
	//	}
	//}
	//m_last_computed_image = image;

	return IO_ERR;
}