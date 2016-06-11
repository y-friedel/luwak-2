#include "matrixfilter.h"
#include <opencv2/core.hpp> //Mat

LUW::MATRIXFILTER::MATRIXFILTER(cv::Mat& filter, OUTPUT_TYPE output_level)
{
	m_filter_matrix = filter;
	m_output_level = output_level;
}

LUW::MATRIXFILTER::~MATRIXFILTER()
{

}