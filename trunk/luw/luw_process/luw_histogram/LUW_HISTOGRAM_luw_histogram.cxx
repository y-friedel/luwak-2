#include "luw/luw_process/luw_histogram/luw_histogram.h"
#include <opencv2/core/core.hpp> //Mat

LUW_HISTOGRAM::LUW_HISTOGRAM()
{
	m_histogram = std::vector<int>(256, 0);
}

LUW_HISTOGRAM::~LUW_HISTOGRAM()
{

}