#include "luw_matrixfilter.h"
#include <opencv2/core/core.hpp> //Mat

LUW_MATRIXFILTER::LUW_MATRIXFILTER(cv::Mat& filter)
{
	filter_matrix = filter;
}

LUW_MATRIXFILTER::~LUW_MATRIXFILTER()
{

}