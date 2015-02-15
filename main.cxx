#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "lio/lio.h"
#include "luw/luw_history/luw_history.h"
#include <string>

#include "luw/luw_process/luw_revert/luw_revert.h"
#include "luw/luw_process/luw_blur/luw_blur.h"
#include "luw/luw_process/luw_matrixfilter/luw_matrixfilter.h"


int main(int argc, char* argv[])
{

	if (argc != 2)
	{
		std::cout << " Usage: display_image ImageToLoadAndDisplay" << std::endl;
		return -1;
	}

	cv::Mat image;

	std::string input = "resources/Bikesgray.jpg";
	int err = LIO::LoadImage(input, image);

	//int err = LIOinput::LoadImage(argv[1], image);

	if (err != IO_OK) // Check for invalid input
	{
		std::cout << "Could not open or find the image : " << input << std::endl;
		//std::cout << "Could not open or find the image : " << argv[1] << std::endl;
		system("pause");
		return -1;
	}

	cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE);// Create a window for display.
	imshow("Display window", image);                   // Show our image inside it.

	LUW_HISTORY main_history(image);
	LUW_REVERT revert;
	LUW_BLUR blur(1);

	char filter_prewitt[9] = { -1, 0, 1, -1, 0, 1, -1, 0, 1 };
	char filter_sobel[9]   = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
	cv::Mat mat_filter = cv::Mat(3, 3, CV_8SC1, &filter_sobel);
	LUW_MATRIXFILTER matrix_filter = LUW_MATRIXFILTER(mat_filter);

	//main_history.AddNextStep(revert);
	main_history.AddNextStep(blur);
	main_history.AddNextStep(matrix_filter);

	cv::namedWindow("Result", cv::WINDOW_AUTOSIZE);// Create a window for display.
	imshow("Result", main_history.last_computed_image);                   // Show our image inside it.

	cvWaitKey(0);

	LIO::SaveImage("output/bike_sobel.png", main_history.last_computed_image);
}