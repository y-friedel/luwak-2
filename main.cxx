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
#include "luw/process/threshold/threshold.h"
#include "luw/process/blur/blur.h"
#include "luw/process/matrixfilter/matrixfilter.h"
#include "luw/process/histogram/histogram.h"
#include "luw/process/histogram/equalizer/equalizer.h"
#include "luw/process/bayer/bayer.h"

#include "luw/process/hough/hough.h"

//Workdir
#include "compat/session/session.h"

int main(int argc, char* argv[])
{

	if (argc != 2)
	{
		std::cout << " Usage: display_image ImageToLoadAndDisplay" << std::endl;
		return -1;
	}

	cv::Mat image;

	std::string input = "resources/green-bird-chillis.jpg";
	//std::string input = "resources/eye.JPG";
	//std::string input = "resources/lena.bmp";
	//std::string input = "resources/Bikesgray.jpg";
	//std::string input = "resources/unequalized.jpg";
	//std::string input = "resources/hough_unit.png";

	//IO_ERROR err = LIO::LoadImage(input, image, CV_LOAD_IMAGE_COLOR);

	IO_ERROR err = LIO::LoadCvImage(input, image);

	//int err = LIOinput::LoadImage(argv[1], image);

	if (err != IO_OK) // Check for invalid input
	{
		std::cout << "Could not open or find the image : " << input << std::endl;
		system("pause");
		return err;
	}

	cv::namedWindow("Input", cv::WINDOW_AUTOSIZE);// Create a window for display.
	imshow("Input", image);                   // Show our image inside it.



	LUW::HISTORY main_history(image);
	LUW::BLUR multi_blur(std::set<int>({ 1, 2, 5, 10 }));
	LUW::REVERT revert;

	char filter_prewitt[9] = { -1, 0, 1, -1, 0, 1, -1, 0, 1 };
	char filter_sobel[9]   = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
	cv::Mat mat_filter = cv::Mat(3, 3, CV_8SC1, &filter_sobel);
	LUW::MATRIXFILTER matrix_filter = LUW::MATRIXFILTER(mat_filter, LUW::MATRIXFILTER::GRADIENT);

	//main_history + LUW::BLUR(3) + matrix_filter;

	////HISTOGRAM DEMO
	//LUW::HISTOGRAM histo;
	//main_history + histo;

	////EQUALIZED IMAGE
	//LUW::EQUALIZER equalizer;
	//main_history + equalizer;

	////BAYER DEMO
	//LUW::BAYER bayer_demo(LUW::BAYER::COLOR);
	//main_history + bayer_demo; //Colored example

	//LUW::BAYER bayer(LUW::BAYER::BLACK_WHITE);
	//LUW::BAYER bayer_revert(LUW::BAYER::REVERT);
	//main_history + bayer + bayer_revert; //Demo bayer process

	//HOUGH DEMO
	LUW::HOUGH     hough(100);
	main_history + LUW::BLUR(3);
	main_history + matrix_filter;
	main_history + LUW::THRESHOLD(50);
	main_history + hough;

	//main_history + multi_blur + revert;

	//cv::cvtColor(main_history.m_last_computed_image, main_history.m_last_computed_image, CV_HSV2RGB);
	if (err != IO_OK) // Check for invalid compute
	{
		std::cout << "error in process " << input << std::endl;
		system("pause");
		return err;
	}




	const std::vector< cv::Mat > last_results = main_history.GetLastResults();
	int i = 1;

	for (auto it : last_results)
	{
		std::string filename = "output/result_" + std::to_string(i++) + ".png";
		//name += ".png";
		cv::namedWindow(filename, cv::WINDOW_AUTOSIZE);// Create a window for display.
		cv::imshow(filename, it);                   // Show our image inside it.
		LIO::SaveImage(filename, it);

	}
	cvWaitKey(0);

	//S_INT test(3);
}