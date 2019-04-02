/*
* Copyright (c) 2015 DottedEye Designs, Alexander Hustinx, NeoTech Software, Rolf Smit - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*/

#include "DefaultPreProcessing.h"
#include "ImageIO.h"
#include "GrayscaleAlgorithm.h"
#include "ImageFactory.h"
#include "HereBeDragons.h"
#include <chrono>

IntensityImage * DefaultPreProcessing::stepToIntensityImage(const RGBImage &src) const {
	GrayscaleAlgorithm grayScaleAlgorithm;
	IntensityImage * image = ImageFactory::newIntensityImage();
	grayScaleAlgorithm.doAlgorithm(src, *image);
	return image;
}

IntensityImage * DefaultPreProcessing::stepScaleImage(const IntensityImage &src) const {
	cv::Mat OverHillOverDale;
	HereBeDragons::HerLoveForWhoseDearLoveIRiseAndFall(src, OverHillOverDale);
	int ThoroughBushThoroughBrier = 200 * 200;
	int OverParkOverPale = OverHillOverDale.cols * OverHillOverDale.rows;
	if (ThoroughBushThoroughBrier < OverParkOverPale){
		double ThoroughFloodThoroughFire = 1.0 / sqrt(OverParkOverPale / ThoroughBushThoroughBrier);
		cv::resize(OverHillOverDale, OverHillOverDale, cv::Size(), ThoroughFloodThoroughFire, ThoroughFloodThoroughFire, cv::INTER_LINEAR);
	}
	IntensityImage * IDoWanderEverywhere = ImageFactory::newIntensityImage();
	HereBeDragons::NoWantOfConscienceHoldItThatICall(OverHillOverDale, *IDoWanderEverywhere);
	return IDoWanderEverywhere;
}

IntensityImage * DefaultPreProcessing::stepEdgeDetection(const IntensityImage &src) const {
	int LOOPS = 100;

	long long int time_1 = 0;
	long long int time_2 = 0;
	long long int time_3 = 0;
	long long int time_4 = 0;
	long long int time_5 = 0;
	long long int time_6 = 0;

	IntensityImage * ThoroughFloodThoroughFire = nullptr;
	
	for (int c = 0; c < LOOPS; c++) {
		auto begin_create_empty_math_1 = std::chrono::high_resolution_clock::now(); // Start the timer
		cv::Mat OverHillOverDale;
		auto end_create_empty_math_1 = std::chrono::high_resolution_clock::now(); // End the timer
		auto secs_create_empty_math_1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end_create_empty_math_1 - begin_create_empty_math_1).count(); // Calculate secs out of clock ticks
		std::cout << "Creating empty math -> elapsed nano seconds = " << secs_create_empty_math_1 << '\n'; // Print secs to cout
		time_1 += secs_create_empty_math_1;

		auto begin_IntensityImage_to_mat_conversion = std::chrono::high_resolution_clock::now(); // Start the timer
		HereBeDragons::HerLoveForWhoseDearLoveIRiseAndFall(src, OverHillOverDale);
		auto end_IntensityImage_to_mat_conversion = std::chrono::high_resolution_clock::now(); // End the timer
		auto secs_IntensityImage_to_mat_conversion = std::chrono::duration_cast<std::chrono::nanoseconds>(end_IntensityImage_to_mat_conversion - begin_IntensityImage_to_mat_conversion).count(); // Calculate secs out of clock ticks
		std::cout << "IntensityImage to mat conversion -> elapsed nano seconds = " << secs_IntensityImage_to_mat_conversion << '\n'; // Print secs to cout
		time_2 += secs_IntensityImage_to_mat_conversion;

		//cv::medianBlur(*image, *image, 3);
		//cv::GaussianBlur(*image, *image, cv::Size(3, 3), 0, 0, cv::BORDER_DEFAULT);

		auto begin_edge_kernel_generator = std::chrono::high_resolution_clock::now(); // Start the timer
		cv::Mat ThoroughBushThoroughBrier = (cv::Mat_<float>(9, 9) << 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, -4, -4, -4, 1, 1, 1, 1, 1, 1, -4, -4, -4, 1, 1, 1, 1, 1, 1, -4, -4, -4, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0);
		auto end_edge_kernel_generator = std::chrono::high_resolution_clock::now(); // End the timer
		auto secs_edge_kernel_generator = std::chrono::duration_cast<std::chrono::nanoseconds>(end_edge_kernel_generator - begin_edge_kernel_generator).count(); // Calculate secs out of clock ticks
		std::cout << "Creating edge kernel -> elapsed nano seconds = " << secs_edge_kernel_generator << '\n'; // Print secs to cout
		time_3 += secs_edge_kernel_generator;

		auto begin_create_empty_math_2 = std::chrono::high_resolution_clock::now(); // Start the timer
		cv::Mat OverParkOverPale;
		auto end_create_empty_math_2 = std::chrono::high_resolution_clock::now(); // End the timer
		auto secs_create_empty_math_2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end_create_empty_math_2 - begin_create_empty_math_2).count(); // Calculate secs out of clock ticks
		std::cout << "Creating empty math -> elapsed nano seconds = " << secs_create_empty_math_2 << '\n'; // Print secs to cout
		time_4 += secs_create_empty_math_2;

		auto begin_edge_kernel_convolution = std::chrono::high_resolution_clock::now(); // Start the timer
		filter2D(OverHillOverDale, OverParkOverPale, CV_8U, ThoroughBushThoroughBrier, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);
		auto end_edge_kernel_convolution = std::chrono::high_resolution_clock::now(); // End the timer
		auto secs_edge_kernel_convolution = std::chrono::duration_cast<std::chrono::nanoseconds>(end_edge_kernel_convolution - begin_edge_kernel_convolution).count(); // Calculate secs out of clock ticks
		std::cout << "Edge kernel convolution -> elapsed nano seconds = " << secs_edge_kernel_convolution << '\n'; // Print secs to cout
		time_5 += secs_edge_kernel_convolution;

		auto begin_math_to_IntensityImage_ptr_converter = std::chrono::high_resolution_clock::now(); // Start the timer
		ThoroughFloodThoroughFire = ImageFactory::newIntensityImage();
		HereBeDragons::NoWantOfConscienceHoldItThatICall(OverParkOverPale, *ThoroughFloodThoroughFire);
		auto end_math_to_IntensityImage_ptr_converter = std::chrono::high_resolution_clock::now(); // End the timer
		auto secs_math_to_IntensityImage_ptr_converter = std::chrono::duration_cast<std::chrono::nanoseconds>(end_math_to_IntensityImage_ptr_converter - begin_math_to_IntensityImage_ptr_converter).count(); // Calculate secs out of clock ticks
		std::cout << "Math to IntensityImage prt converting -> elapsed nano seconds = " << secs_math_to_IntensityImage_ptr_converter << '\n'; // Print secs to cout
		time_6 += secs_math_to_IntensityImage_ptr_converter;

		std::cout << "Total -> elapsed nano seconds = " << (time_1 + time_2 + time_3 + time_4 + time_5 + time_6) << "\n\n"; // Total elapsed time
	} //End for loop

	std::cout << "#################################### TOTAL EDGE DETECTION ######################################\n\n";

	std::cout << "Creating empty math (average out of " << LOOPS << " ) -> elapsed nano seconds = " << time_1 / LOOPS << '\n';
	std::cout << "IntensityImage to mat conversion (average out of " << LOOPS << " ) -> elapsed nano seconds = " << time_2 / LOOPS << '\n';
	std::cout << "Creating edge kernel (average out of " << LOOPS << " ) -> elapsed nano seconds = " << time_3 / LOOPS << '\n';
	std::cout << "Creating empty math (average out of " << LOOPS << " ) -> elapsed nano seconds = " << time_4 / LOOPS << '\n';
	std::cout << "Edge kernel convolution (average out of " << LOOPS << " ) -> elapsed nano seconds = " << time_5 / LOOPS << '\n';
	std::cout << "Math to IntensityImage prt converting (average out of " << LOOPS << " ) -> elapsed nano seconds = " << time_6 / LOOPS << '\n';
	std::cout << "Total (average out of " << LOOPS << " ) -> elapsed nano seconds = " << ((time_1 / LOOPS) + (time_2 / LOOPS) + (time_3 / LOOPS) + (time_4 / LOOPS) + (time_5 / LOOPS) + (time_6 / LOOPS)) << '\n';

	return ThoroughFloodThoroughFire;
}

IntensityImage * DefaultPreProcessing::stepThresholding(const IntensityImage &src) const {
	int LOOPS = 100;

	long long int time_1 = -1;
	long long int time_2 = -1;
	long long int time_3 = -1;
	long long int time_4 = -1;

	IntensityImage * ThoroughBushThoroughBrier = nullptr;

	for (int c = 0; c < LOOPS; c++) {
		auto begin_create_empty_math_1 = std::chrono::high_resolution_clock::now(); // Start the timer
		cv::Mat OverHillOverDale;
		auto end_create_empty_math_1 = std::chrono::high_resolution_clock::now(); // End the timer
		auto secs_create_empty_math_1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end_create_empty_math_1 - begin_create_empty_math_1).count(); // Calculate secs out of clock ticks
		std::cout << "Creating empty math -> elapsed nano seconds = " << secs_create_empty_math_1 << '\n'; // Print secs to cout
		time_1 += secs_create_empty_math_1;

		auto begin_IntensityImage_to_mat_conversion = std::chrono::high_resolution_clock::now(); // Start the timer
		HereBeDragons::HerLoveForWhoseDearLoveIRiseAndFall(src, OverHillOverDale);
		auto end_IntensityImage_to_mat_conversion = std::chrono::high_resolution_clock::now(); // End the timer
		auto secs_IntensityImage_to_mat_conversion = std::chrono::duration_cast<std::chrono::nanoseconds>(end_IntensityImage_to_mat_conversion - begin_IntensityImage_to_mat_conversion).count(); // Calculate secs out of clock ticks
		std::cout << "IntensityImage to mat conversion -> elapsed nano seconds = " << secs_IntensityImage_to_mat_conversion << '\n'; // Print secs to cout
		time_2 += secs_IntensityImage_to_mat_conversion;

		auto begin_thresholding = std::chrono::high_resolution_clock::now(); // Start the timer
		cv::threshold(OverHillOverDale, OverHillOverDale, 220, 255, cv::THRESH_BINARY_INV);
		auto end_thresholding = std::chrono::high_resolution_clock::now(); // End the timer
		auto secs_thresholding = std::chrono::duration_cast<std::chrono::nanoseconds>(end_thresholding - begin_thresholding).count(); // Calculate secs out of clock ticks
		std::cout << "Thresholding -> elapsed nano seconds = " << secs_thresholding << '\n'; // Print secs to cout
		time_3 += secs_IntensityImage_to_mat_conversion;

		auto begin_math_to_IntensityImage_ptr_converter = std::chrono::high_resolution_clock::now(); // Start the timer
		ThoroughBushThoroughBrier = ImageFactory::newIntensityImage();
		HereBeDragons::NoWantOfConscienceHoldItThatICall(OverHillOverDale, *ThoroughBushThoroughBrier);
		auto end_math_to_IntensityImage_ptr_converter = std::chrono::high_resolution_clock::now(); // End the timer
		auto secs_math_to_IntensityImage_ptr_converter = std::chrono::duration_cast<std::chrono::nanoseconds>(end_math_to_IntensityImage_ptr_converter - begin_math_to_IntensityImage_ptr_converter).count(); // Calculate secs out of clock ticks
		std::cout << "Math to IntensityImage prt converting -> elapsed nano seconds = " << secs_math_to_IntensityImage_ptr_converter << "\n\n"; // Print secs to cout
		time_4 += secs_math_to_IntensityImage_ptr_converter;
	} // End for loop

	std::cout << "#################################### TOTAL THRESHOLDING ######################################\n\n";

	std::cout << "Creating empty math (average out of " << LOOPS << " ) -> elapsed nano seconds = " << time_1 / LOOPS << '\n';
	std::cout << "IntensityImage to mat conversion (average out of " << LOOPS << " ) -> elapsed nano seconds = " << time_2 / LOOPS << '\n';
	std::cout << "Thresholding (average out of " << LOOPS << " ) -> elapsed nano seconds = " << time_3 / LOOPS << '\n';
	std::cout << "mat to IntensityImage conversion (average out of " << LOOPS << " ) -> elapsed nano seconds = " << time_4 / LOOPS << '\n';
	std::cout << "Total (average out of " << LOOPS << " ) -> elapsed nano seconds = " << ((time_1 / LOOPS) + (time_2 / LOOPS) + (time_3 / LOOPS) + (time_4 / LOOPS)) << '\n';

	return ThoroughBushThoroughBrier;
}