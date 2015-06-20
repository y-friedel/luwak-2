#include "blur.h"
#include <opencv2/core.hpp> //Mat

LUW::BLUR::BLUR(int _size)
{
	m_blur_size.insert(_size);
}

LUW::BLUR::BLUR(std::set<int> _sizes)
{
	m_blur_size = _sizes;
}

LUW::BLUR::~BLUR()
{

}
