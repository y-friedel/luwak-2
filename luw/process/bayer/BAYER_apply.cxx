#include "luw/process/bayer/bayer.h"
#include <opencv2/core/core.hpp> //Mat

IO_ERROR LUW::BAYER::Apply(const cv::Mat& image_in, cv::Mat& image_out)
{
	if (!image_in.data)
		return IO_NOT_FOUND;

	switch (m_result_type)
	{
	case COLOR:
		ApplyColor(image_in, image_out);
		break;

	case BLACK_WHITE:
		ApplyBlackWhite(image_in, image_out);
		break;

	case REVERT:
		ApplyRevert(image_in, image_out);
		break;
	}

	return IO_OK;
}
