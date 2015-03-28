#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include "opencv/cv.h"


//LIO
#include "lio/lio.h"

//LUW
#include "luw/history/history.h"
#include "luw/process/revert/revert.h"
#include "luw/process/threshold/threshold.h"
#include "luw/process/blur/blur.h"
#include "luw/process/matrixfilter/matrixfilter.h"
#include "luw/process/histogram/histogram.h"
#include "luw/process/histogram/equalizer/equalizer.h"
#include "luw/process/bayer/bayer.h"

#include "luw/process/hough/hough.h"


int main(int argc, char* argv[])
{

	if (argc != 2)
	{
		std::cout << " Usage: display_image ImageToLoadAndDisplay" << std::endl;
		return -1;
	}

	cv::Mat image;

	//std::string input = "resources/green-bird-chillis.jpg";
	//std::string input = "resources/eye.JPG";
	//std::string input = "resources/lena.bmp";
	std::string input = "resources/Bikesgray.jpg";
	//std::string input = "resources/unequalized.jpg";
	//std::string input = "resources/hough_unit.png";

	//IO_ERROR err = LIO::LoadImage(input, image, CV_LOAD_IMAGE_COLOR);
	IO_ERROR err = LIO::LoadImage(input, image);

	//int err = LIOinput::LoadImage(argv[1], image);

	if (err != IO_OK) // Check for invalid input
	{
		std::cout << "Could not open or find the image : " << input << std::endl;
		system("pause");
		return err;
	}

	cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE);// Create a window for display.
	imshow("Display window", image);                   // Show our image inside it.

	LUW::HISTORY main_history(image);
	LUW::REVERT revert;

	char filter_prewitt[9] = { -1, 0, 1, -1, 0, 1, -1, 0, 1 };
	char filter_sobel[9]   = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
	cv::Mat mat_filter = cv::Mat(3, 3, CV_8SC1, &filter_sobel);
	LUW::MATRIXFILTER matrix_filter = LUW::MATRIXFILTER(mat_filter, LUW::MATRIXFILTER::GRADIENT);

	//err = main_history.AddNextStep(matrix_filter);
	//err = main_history.AddNextStep(blur);

	//HISTOGRAM DEMO
	//LUW::HISTOGRAM histo;
	//LUW::EQUALIZER equalizer;
	//err = main_history.AddNextStep(equalizer);
	//err = main_history.AddNextStep(histo);

	//BAYER DEMO
	//LUW::BAYER bayer(LUW::BAYER::BLACK_WHITE);
	//LUW::BAYER bayer_revert(LUW::BAYER::REVERT);
	//err = main_history.AddNextStep(bayer);
	//err = main_history.AddNextStep(bayer_revert);

	//HOUGH DEMO
	LUW::BLUR blur(3);
	LUW::THRESHOLD thresold(75);
	LUW::HOUGH     hough;
	main_history.AddNextStep(blur);
	main_history.AddNextStep(matrix_filter);
	main_history.AddNextStep(thresold);
	main_history.AddNextStep(hough);

	//cv::cvtColor(main_history.m_last_computed_image, main_history.m_last_computed_image, CV_HSV2RGB);
	if (err != IO_OK) // Check for invalid compute
	{
		std::cout << "error in process " << input << std::endl;
		system("pause");
		return err;
	}

	cv::namedWindow("Result", cv::WINDOW_AUTOSIZE);// Create a window for display.
	cv::imshow("Result", main_history.m_last_computed_image);                   // Show our image inside it.

	cvWaitKey(0);

	LIO::SaveImage("output/last_output.png", main_history.m_last_computed_image);
}