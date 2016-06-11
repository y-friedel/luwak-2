#include "lio/lio.h"
#include <opencv2/core.hpp> //Mat
#include <opencv2/highgui.hpp> //imread

cv::Mat LIO::LoadCvImage(const std::string& filename, int type)
{

	if (filename.size() == 0)
		throw std::exception("filename empty", IO_ERR);

	cv::Mat image = cv::imread(filename, type);   // Read the file

	if (!image.data)
		throw std::exception("File not Found", IO_NOT_FOUND); // Check for invalid input

	return std::move(image);
}

std::vector<cv::Mat> LoadCvImagesFromDirectory(const std::string& directory)
{
	std::vector<cv::Mat> images;


	return std::move(images);
}