
#include "luw/process/trilinearfilter/trilinearfilter.h"
#include <opencv2/core.hpp> //Mat

#include<iostream>

LUW::TRILINEARFILTER::TRILINEARFILTER()
{
	std::cout << "hello, trilinearfilter constructed" << std::endl;
}

LUW::TRILINEARFILTER::~TRILINEARFILTER()
{

}

LUW::TRILINEARFILTER::TRILINEARFILTER(TRILINEARFILTER& revert)
{
	std::cout << "hello, trilinearfilter copied" << std::endl;
}