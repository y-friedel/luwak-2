#ifndef __LUW_MATH_H_
#define __LUW_MATH_H_

#include "compat\lmath\lmath.h"
#include <opencv2/core/core.hpp> //Point

namespace LUW_MATH
{
	double DistBetween(const cv::Point2d& p1, const cv::Point2d& p2)
	{
		return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
	}
}


#endif