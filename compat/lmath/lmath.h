#ifndef __LUW_MATH_H_
#define __LUW_MATH_H_

#include "compat.h"
namespace cv
{
	class Point2d;
}

namespace LMATH
{
	double DistBetween(const cv::Point2d& p1, const cv::Point2d& p2);
	double DistToOrigin(const cv::Point2d& p1);
}


#endif