#include "luw/history/history.h"

LUW::HISTORY::HISTORY(cv::Mat& ori_img)
{
	m_steps.emplace_back();
	std::vector<cv::Mat>& last_mat = m_steps.back();
	last_mat.emplace_back(ori_img);
}