#include "luw/process/histogram/histogram.h"
#include <opencv2/core.hpp> //Mat

LUW::HISTOGRAM::HISTOGRAM()
{
	m_histogram = std::vector<int>(256, 0);
	m_cumulated_histogram = std::vector<int>(256, 0);
}

LUW::HISTOGRAM::~HISTOGRAM()
{

}