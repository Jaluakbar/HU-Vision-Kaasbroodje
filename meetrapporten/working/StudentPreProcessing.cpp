#include "StudentPreProcessing.h"
#include "edge_detection.h"
#include "thresholding.h"
#include "ImageIO.h"
#include "ImageFactory.h"

#include <chrono>

IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const { 
	int LOOPS = 100;
	
	long long int time_1 = 0;
	long long int time_2 = 0;
	long long int time_3 = 0;
	long long int time_4 = 0;
	long long int time_5 = 0;
	long long int time_6 = 0;
	long long int time_7 = 0;
	long long int time_8 = 0;

	IntensityImage * img_ptr = nullptr;

	for (int c = 0; c < LOOPS; c++) {
		auto begin = std::chrono::high_resolution_clock::now(); // Start the timer
		// Gaussian blur kernel generator
		const auto gaussian_kernel_creator = [](double sigma = 0.001) {
			const int W = 5;
			ed::matrix<double, W, W> kernel(W, W);
			double mean = W / 2;
			double sum = 0.0; // For accumulating the kernel values
			for (int x = 0; x < W; ++x) {
				for (int y = 0; y < W; ++y) {
					kernel(y, x) = exp(-0.5 * (pow((x - mean) / sigma, 2.0) + pow((y - mean) / sigma, 2.0))) / (2 * 3.14159265358979323846264338327950288 * sigma * sigma);
					// Accumulate the kernel values
					sum += kernel(y, x);
				}
			}
			// Normalize the kernel by the accumulated kernel value
			for (int x = 0; x < W; ++x) {
				for (int y = 0; y < W; ++y) {
					kernel(y, x) /= sum;
				}
			};
			return kernel;
		};
		auto end_gaussian_kernel_generator = std::chrono::high_resolution_clock::now(); // End the timer
		auto secs = std::chrono::duration_cast<std::chrono::nanoseconds>(end_gaussian_kernel_generator - begin).count(); // Calculate secs out of clock ticks
		std::cout << "Gaussian blur lambda creation -> elapsed nano seconds = " << secs << '\n'; // Print secs to cout
		time_1 += secs;


		auto begin_gaus_kernel_creation = std::chrono::high_resolution_clock::now();	// Start the timer
		// Creating the gaussian kernel with a sigma
		const auto gaussian_kernel = gaussian_kernel_creator(0.890);
		auto end_gaus_kernel_creation = std::chrono::high_resolution_clock::now(); // End the timer
		auto secs_gaus_kernel_creation = std::chrono::duration_cast<std::chrono::nanoseconds>(end_gaus_kernel_creation - begin_gaus_kernel_creation).count(); // Calculate secs out of clock ticks
		std::cout << "Gaussian blur kernel generator -> elapsed nano seconds = " << secs_gaus_kernel_creation << '\n'; // Print secs to cout
		time_2 += secs_gaus_kernel_creation;

		auto begin_edge_kernel_creation = std::chrono::high_resolution_clock::now();	// Start the timer
		// Canny edge detection kernel.
		ed::matrix<int, 9, 9> edge_kernel({ {
		{0,0,0,1,1,1,0,0,0},
		{0,0,0,1,1,1,0,0,0},
		{0,0,0,1,1,1,0,0,0},
		{1,1,1,-4,-4,-4,1,1,1},
		{1,1,1,-4,-4,-4,1,1,1},
		{1,1,1,-4,-4,-4,1,1,1},
		{0,0,0,1,1,1,0,0,0},
		{0,0,0,1,1,1,0,0,0},
		{0,0,0,1,1,1,0,0,0}
	} });
		auto end_edge_kernel_creation = std::chrono::high_resolution_clock::now(); // End the timer
		auto secs_edge_kernel_creation = std::chrono::duration_cast<std::chrono::nanoseconds>(end_edge_kernel_creation - begin_edge_kernel_creation).count(); // Calculate secs out of clock ticks
		std::cout << "Edge kernel generator -> elapsed nano seconds = " << secs_edge_kernel_creation << '\n'; // Print secs to cout
		time_3 += secs_edge_kernel_creation;

		auto begin_IntensityImage_to_matrix_convertion = std::chrono::high_resolution_clock::now();	// Start the timer
		// Create an ed::matrix from the IntensityImage
		ed::matrix<int> img(image);
		auto end_IntensityImage_to_matrix_convertion = std::chrono::high_resolution_clock::now(); // End the timer
		auto secs_IntensityImage_to_matrix_convertion = std::chrono::duration_cast<std::chrono::nanoseconds>(end_IntensityImage_to_matrix_convertion - begin_IntensityImage_to_matrix_convertion).count(); // Calculate secs out of clock ticks
		std::cout << "IntensityImage to matrix conversion -> elapsed nano seconds = " << secs_IntensityImage_to_matrix_convertion << '\n'; // Print secs to cout
		time_4 += secs_IntensityImage_to_matrix_convertion;

		auto begin_gaussian_blurring = std::chrono::high_resolution_clock::now();	// Start the timer
		// Use gaussian blur for blurring the image
		img = ed::convolution<int, 5, 5, double>(img, gaussian_kernel);
		auto end_gaussian_blurring = std::chrono::high_resolution_clock::now(); // End the timer
		auto secs_gaussian_blurring = std::chrono::duration_cast<std::chrono::nanoseconds>(end_gaussian_blurring - begin_gaussian_blurring).count(); // Calculate secs out of clock ticks
		std::cout << "Gaussian blur convolution -> elapsed nano seconds = " << secs_gaussian_blurring << '\n'; // Print secs to cout
		time_5 += secs_gaussian_blurring;

		auto begin_edge_kernel_convolution = std::chrono::high_resolution_clock::now();	// Start the timer
		// Use the Canny edge detection kernel to complete the first step in the edge detection.
		img = ed::convolution<int>(img, edge_kernel);
		auto end_edge_kernel_convolution = std::chrono::high_resolution_clock::now(); // End the timer
		auto secs_edge_kernel_convolution = std::chrono::duration_cast<std::chrono::nanoseconds>(end_edge_kernel_convolution - begin_edge_kernel_convolution).count(); // Calculate secs out of clock ticks
		std::cout << "Edge kernel convolution -> elapsed nano seconds = " << secs_edge_kernel_convolution << '\n'; // Print secs to cout
		time_6 += secs_edge_kernel_convolution;

		// The equalization function can be used to shrink or expand the values whitin the given range.
		//img.equalization(255);

		auto begin_thresholding = std::chrono::high_resolution_clock::now();	// Start the timer
		// Use the Canny edge detection thresholding to complete step 2 and also the last step in the edge detection.
		tr::basic_threshold<int>(img, 170);
		auto end_thresholding = std::chrono::high_resolution_clock::now(); // End the timer
		auto secs_thresholding = std::chrono::duration_cast<std::chrono::nanoseconds>(end_thresholding - begin_thresholding).count(); // Calculate secs out of clock ticks
		std::cout << "Thresholding -> elapsed nano seconds = " << secs_thresholding << '\n'; // Print secs to cout
		time_7 += secs_thresholding;

		auto begin_matrix_to_IntensityImage_ptr_converter = std::chrono::high_resolution_clock::now();	// Start the timer
		// convert the matrix to a IntensityImage type which is required.
		img_ptr = img.get_intensity_image_ptr();
		auto end_matrix_to_IntensityImage_ptr_converter = std::chrono::high_resolution_clock::now(); // End the timer
		auto secs_matrix_to_IntensityImage_ptr_converter = std::chrono::duration_cast<std::chrono::nanoseconds>(end_matrix_to_IntensityImage_ptr_converter - begin_matrix_to_IntensityImage_ptr_converter).count(); // Calculate secs out of clock ticks
		std::cout << "Matrix to IntensityImage ptr converting -> elapsed nano seconds = " << secs_matrix_to_IntensityImage_ptr_converter << '\n'; // Print secs to cout
		time_8 += secs_matrix_to_IntensityImage_ptr_converter;

		std::cout << "Total -> elapsed nano seconds = " << (time_1 + time_2 + time_3 + time_4 + time_5 + time_6 + time_7 + time_8) << "\n\n"; // Total elapsed time
	}; // End for loop

	std::cout << "#################################### TOTAL ######################################\n\n";

	std::cout << "Gaussian blur lambda creation (average out of " << LOOPS << " ) -> elapsed nano seconds = " << time_1/LOOPS << '\n';
	std::cout << "Gaussian blur kernel generator (average out of " << LOOPS << " ) -> elapsed nano seconds = " << time_2/LOOPS << '\n';
	std::cout << "Edge kernel generator (average out of " << LOOPS << " ) -> elapsed nano seconds = " << time_3/LOOPS << '\n';
	std::cout << "IntensityImage to matrix conversion (average out of " << LOOPS << " ) -> elapsed nano seconds = " << time_4/LOOPS << '\n';
	std::cout << "Gaussian blur convolution (average out of " << LOOPS << " ) -> elapsed nano seconds = " << time_5/LOOPS << '\n';
	std::cout << "Edge kernel convolution (average out of " << LOOPS << " ) -> elapsed nano seconds = " << time_6/LOOPS << '\n';
	std::cout << "Thresholding (average out of " << LOOPS << " ) -> elapsed nano seconds = " << time_7/LOOPS << '\n';
	std::cout << "Matrix to IntensityImage ptr converting (average out of " << LOOPS << " ) -> elapsed nano seconds = " << time_8 / LOOPS << '\n';
	std::cout << "Total (average out of " << LOOPS << " ) -> elapsed nano seconds = " << ((time_1 / LOOPS) + (time_2 / LOOPS) + (time_3 / LOOPS) + (time_4 / LOOPS) + (time_5 / LOOPS) + (time_6 / LOOPS) + (time_7 / LOOPS) + (time_8 / LOOPS)) << '\n';

	return img_ptr;
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const { 
	// The next lines of code are required to create a copy of the given IntensityImage parameter and return it.
	// We couldn't just make a pointer of the IntensityImage reference becouse it's a const parameter which is declared in the abstract
	// class so we couldn't change const to non-const.
	int LOOPS = 100;

	long long int total = 0;

	IntensityImage * img_ptr = nullptr;
	for(int c = 0; c < LOOPS; c++){
		auto begin = std::chrono::high_resolution_clock::now();	// Start the timer
		img_ptr = ImageFactory::newIntensityImage();
		img_ptr->set(image.getWidth(), image.getHeight());
		for (int y = 0; y < image.getHeight(); y++) {
			for (int x = 0; x < image.getWidth(); x++) {
				img_ptr->setPixel(x, y, image.getPixel(x, y));
			}
		}
		auto end = std::chrono::high_resolution_clock::now(); // End the timer
		total += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count(); // Calculate secs out of clock ticks
	}

	std::cout << "#################################### TOTAL ######################################\n\n";

	std::cout << "Total (average out of " << LOOPS << " ) -> elapsed nano seconds = " << total / LOOPS << '\n';
	return img_ptr;
}