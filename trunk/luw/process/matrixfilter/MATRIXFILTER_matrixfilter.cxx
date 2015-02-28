#include "matrixfilter.h"
#include <opencv2/core/core.hpp> //Mat

LUW::MATRIXFILTER::MATRIXFILTER(cv::Mat& filter)
{
	filter_matrix = filter;
}

LUW::MATRIXFILTER::~MATRIXFILTER()
{

}