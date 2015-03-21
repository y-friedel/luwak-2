#include "histogram.h"
#include <opencv2/core/core.hpp> //Mat

IO_ERROR LUW::HISTOGRAM::ComputeCumulatedHistogram()
{

	int intensity = 0;

	for (unsigned int ith_histo = 0; ith_histo < m_histogram.size(); ++ith_histo)
	{
		intensity += m_histogram[ith_histo];
		m_cumulated_histogram[ith_histo] = intensity;
	}

	return IO_OK;
}
