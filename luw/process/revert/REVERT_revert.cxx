
#include "luw/process/revert/revert.h"
#include <opencv2/core.hpp> //Mat

#include<iostream>

LUW::REVERT::REVERT()
{
	std::cout << "hello, revert constructed" << std::endl;
}

LUW::REVERT::~REVERT()
{

}

LUW::REVERT::REVERT(REVERT& revert)
{
	std::cout << "hello, revert copied" << std::endl;
}