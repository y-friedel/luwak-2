#ifndef __SESSION_H_
#define __SESSION_H_

#include <string>

namespace cv
{
	class Mat;
};

	class SESSION
	{

	public:
		static SESSION& Instance();
		IO_ERROR        SaveImage(const cv::Mat& image, const std::string& image_name = "");

		std::string m_session_path;
		unsigned int m_ith_image;


	private:
		SESSION& operator= (const SESSION&){}
		SESSION(const SESSION&){}

		static SESSION m_instance;
		SESSION();
		~SESSION();



	};

#endif