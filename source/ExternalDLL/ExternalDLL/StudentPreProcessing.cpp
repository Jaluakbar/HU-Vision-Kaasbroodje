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
	// Canny edge detection.
	ed::matrix<int, 9,9> edge_kernel({ {
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

	// Create an ed::matrix from the IntensityImage
	ed::matrix<int> img(image);

	// Use the Canny edge detection kernel to complete the first step in the edge detection.
	img = ed::convolution<int>(img, edge_kernel);

	// The equalization function can be used to shrink or expand the values whitin the given range.
	//img.equalization(255);

	// Use the Canny edge detection thresholding to complete step 2 and also the last step in the edge detection.
	tr::basic_threshold<int>(img, 155);


	// convert the matrix to a IntensityImage type which is required.
	return img.get_intensity_image_ptr();
}

/**
 *\brief We don't use this function.
 *
 * We don't use this function becouse we do the thresholding in the edge detection function.
 * Read the documentation for more information.
 */
IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const { 
	// The next lines of code are required to create a copy of the given IntensityImage parameter and return it.
	// We couldn't just make a pointer of the IntensityImage reference becouse it's a const parameter which is declared in the abstract
	// class so we couldn't change const to non-const.
	IntensityImage * img_ptr = ImageFactory::newIntensityImage();
	img_ptr->set(image.getWidth(), image.getHeight());
	for (int y = 0; y < image.getHeight(); y++) {
		for (int x = 0; x < image.getWidth(); x++) {
			img_ptr->setPixel(x, y, image.getPixel(x,y));
		}
	}
	return img_ptr;
}