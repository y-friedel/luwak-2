#include "luw/history/history.h"

IO_ERROR LUW::HISTORY::AddNextStep(LUW::PROCESS& process)
{
	LUW::STEP next_step(m_last_computed_image, process);
	m_history.push_back(next_step);
	IO_ERROR err = ComputeHistory();
	return err;
}