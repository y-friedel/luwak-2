#include "compat/compat.h"
#include "compat/session/session.h"
#include <ctime>
#include <windows.h>
#include <sstream>
#include <vector>
#include <opencv2/core.hpp> //Mat
#include <opencv2/highgui.hpp> //imwrite


SESSION SESSION::m_instance = SESSION();

SESSION::SESSION()
{
	time_t my_clock = time(NULL);

	if (!use_workdir)
	{
		m_session_path = "";
		return;
	}


	std::string session_number;
	std::stringstream strstream;
	strstream << my_clock;
	strstream >> session_number;
	m_session_path = "workdir/" + session_number + "/";
	m_ith_image = 0;

	if (use_workdir) CreateDirectory("workdir", NULL);
	if (use_workdir) CreateDirectory(m_session_path.c_str(), NULL);
}

SESSION::~SESSION()
{

}

SESSION& SESSION::Instance()
{
	return m_instance;
}

IO_ERROR SESSION::SaveImage(const cv::Mat& image, const std::string& image_name)
{
	std::string ith;
	std::stringstream strstream;
	strstream << m_ith_image++;
	strstream >> ith;

	std::string filename = m_session_path + ith + image_name + ".PNG";

	if (filename.size() == 0) return IO_ERR;

	auto compression_params = std::vector<int>({ CV_IMWRITE_PNG_COMPRESSION, 9 });
	bool result = cv::imwrite(filename, image, compression_params);

	if (!result) return IO_ERR;

	return IO_OK;
}