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
#include "luw/process/trilinearfilter/trilinearfilter.h"
#include "luw/process/histogram/histogram.h"
#include "luw/process/histogram/equalizer/equalizer.h"
#include "luw/process/bayer/bayer.h"
#include "luw/process/hough/hough.h"

//Workdir
#include "compat/session/session.h"

int main(int argc, char* argv[])
{

	try
	{

		if (argc != 2)
		{
			std::cout << " Usage: display_image ImageToLoadAndDisplay" << std::endl;
			return -1;
		}

		//std::string input = "resources/green-bird-chillis.jpg";
		//std::string input = "resources/eye.JPG";
		std::string input = "resources/lena.bmp";
		//std::string input = "resources/Bikesgray.jpg";
		//std::string input = "resources/uk.png";
		//std::string input = "resources/ugly_smiley.png";
		//std::string input = "resources/unequalized.jpg";
		//std::string input = "resources/hough_unit.png";

		//cv::Mat image = LIO::LoadCvImage(argv[1]);
		cv::Mat image = LIO::LoadCvImage(input, CV_LOAD_IMAGE_COLOR);
		//cv::Mat image = LIO::LoadCvImage(input);

		cv::namedWindow("Input", cv::WINDOW_AUTOSIZE);// Create a window for display.
		imshow("Input", image);                   // Show our image inside it.

		LUW::HISTORY main_history(image);
		//LUW::BLUR multi_blur(std::set<int>({ 1, 2, 5, 10 }));

		//char filter_prewitt[9] = { -1, 0, 1, -1, 0, 1, -1, 0, 1 };
		//char filter_sobel[9] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
		//cv::Mat mat_filter = cv::Mat(3, 3, CV_8SC1, &filter_sobel);
		//LUW::MATRIXFILTER matrix_filter = LUW::MATRIXFILTER(mat_filter, LUW::MATRIXFILTER::GRADIENT);

		//main_history + LUW::BLUR(3) + matrix_filter;

		//Filter reuse
		//main_history + multi_blur + multi_blur;

		//main_history + LUW::BLUR(3) + matrix_filter;

		// --- HISTOGRAM DEMO ---
		//main_history + multi_blur + LUW::HISTOGRAM();

		// --- EQUALIZED IMAGE ---
		//main_history + LUW::EQUALIZER();

		// --- BAYER DEMO ---
		//main_history + LUW::BAYER(LUW::BAYER::COLOR); //Colored example
		//main_history + LUW::BAYER(LUW::BAYER::BLACK_WHITE) + LUW::BAYER(LUW::BAYER::REVERT); //Demo bayer process

		// --- HOUGH DEMO ---
		//int blur_values[] = { 1, 3 }; //Init the blur sample set
		//unsigned int threshold_value[] = { 50, 80, 95 }; //Init the threshold sample set
		//auto threshold_set = std::set<unsigned int>(threshold_value, threshold_value + 3);

		//main_history + LUW::BLUR(std::set<int>(blur_values, blur_values + 2));
		//main_history + matrix_filter + LUW::THRESHOLD(threshold_set) + LUW::HOUGH(20);

		//TRILINEAR FILTER DEMO
		main_history + LUW::TRILINEARFILTER();

		// Send results
		const std::vector< cv::Mat > last_results = main_history.GetLastResults();
		int i = 1;
		for (auto it : last_results)
		{
			std::string filename = "output/result_" + std::to_string(i++) + ".png";
			cv::namedWindow(filename, cv::WINDOW_AUTOSIZE);	// Create a window for display.
			cv::imshow(filename, it);						// Show our image inside it.
			LIO::SaveImage(filename, it);
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		system("PAUSE");
	}

	cvWaitKey(0);

	//S_INT test(3);
}


