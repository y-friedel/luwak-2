#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include "opencv/cv.h"


//LIO
#include "lio/lio.h"

//LUW
#include "luw/history/history.h"
#include "luw/process/revert/revert.h"
#include "luw/node/node.h"

//Workdir
#include "compat/session/session.h"


int main(int argc, char* argv[])
{
	cv::Mat image;

	std::string input = "resources/green-bird-chillis.jpg";
	//std::string input = "resources/eye.JPG";
	//std::string input = "resources/lena.bmp";
	//std::string input = "resources/Bikesgray.jpg";
	//std::string input = "resources/unequalized.jpg";
	//std::string input = "resources/hough_unit.png";

	//IO_ERROR err = LIO::LoadImage(input, image, CV_LOAD_IMAGE_COLOR);
	IO_ERROR err = LIO::LoadCvImage(input, image);

	if (err != IO_OK) // Check for invalid input
	{
		std::cout << "Could not open or find the image : " << input << std::endl;
		system("pause");
		return err;
	}

	cv::namedWindow("Input", cv::WINDOW_AUTOSIZE);// Create a window for display.
	imshow("Input", image);                   // Show our image inside it.

	LUW::REVERT revert;

	LUW::NODE revert_node(LUW::NODE::EmptyNode(), image, revert);

	//cv::cvtColor(main_history.m_last_computed_image, main_history.m_last_computed_image, CV_HSV2RGB);
	if (err != IO_OK) // Check for invalid compute
	{
		std::cout << "error in process " << input << std::endl;
		system("pause");
		return err;
	}

	cv::namedWindow("Result", cv::WINDOW_AUTOSIZE);// Create a window for display.
	//cv::imshow("Result", main_history.m_last_computed_image);                   // Show our image inside it.

	cvWaitKey(0);

	//LIO::SaveImage("output/last_output.png", main_history.m_last_computed_image);

	//S_INT test(3);
}