#include "StudentPreProcessing.h"
#include "edge_detection.h"
#include "thresholding.h"
#include "ImageIO.h"
#include "ImageFactory.h"

IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {
	// Gaussian blur kernel generator.
	const auto gaussian_kernel_creator = [](double sigma = 0.001) {
		const int W = 5;
		ed::matrix<double, W, W> kernel(W, W);
		double mean = W / 2;
		double sum = 0.0; // For accumulating the kernel values.
		for (int x = 0; x < W; ++x) {
			for (int y = 0; y < W; ++y) {
				kernel(y, x) = exp(-0.5 * (pow((x - mean) / sigma, 2.0) + pow((y - mean) / sigma, 2.0))) / (2 * 3.14159265358979323846264338327950288 * sigma * sigma);
				// Accumulate the kernel values.
				sum += kernel(y, x);
			}
		}
		// Normalize the kernel by the accumulated kernel value.
		for (int x = 0; x < W; ++x) {
			for (int y = 0; y < W; ++y) {
				kernel(y, x) /= sum;
			}
		};
		return kernel;
	};

	// Creating the gaussian kernel with a sigma.
	const auto gaussian_kernel = gaussian_kernel_creator(0.35);

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

	// Create an ed::matrix from the IntensityImage.
	ed::matrix<int> img(image);

	img = ed::convolution<int, 5, 5, double>(img, gaussian_kernel);

	// Use the Canny edge detection kernel to complete the first step in the edge detection.
	img = ed::convolution<int>(img, edge_kernel);

	// The equalization function can be used to shrink or expand the values whitin the given range.
	// img.equalization(255);

	// Use the Canny edge detection thresholding to complete step 2 and also the last step in the edge detection.
	tr::basic_threshold<int>(img, 169);

	// convert the matrix to a IntensityImage type which is required.
	return img.get_intensity_image_ptr();
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	// The next lines of code are required to create a copy of the given IntensityImage parameter and return it.
	// We couldn't just make a pointer of the IntensityImage reference becouse it's a const parameter which is declared in the abstract
	// class so we couldn't change const to non-const.
	IntensityImage * img_ptr = ImageFactory::newIntensityImage();
	img_ptr->set(image.getWidth(), image.getHeight());
	for (int y = 0; y < image.getHeight(); y++) {
		for (int x = 0; x < image.getWidth(); x++) {
			img_ptr->setPixel(x, y, image.getPixel(x, y));
		}
	}
	return img_ptr;
}