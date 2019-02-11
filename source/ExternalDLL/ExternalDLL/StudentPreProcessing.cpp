#include "StudentPreProcessing.h"
#include "edge_detection.h"
#include <iostream>
#include "thresholding.h"


//TEMPORARY
#include "ImageIO.h"
#include "GrayscaleAlgorithm.h"
#include "ImageFactory.h"
#include "HereBeDragons.h"

IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const { // aanpassen
	ed::matrix<260,260> m(image);
	ed::matrix<9, 9> kernel({ {
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
	//ed::matrix<3,3> kernel({
	//	{
	//		{0,1,0},
	//		{1,-4,1},
	//		{0,1,0}
	//	} });

	auto convulutioned = ed::convolution(m, kernel);

	std::cout << convulutioned[0][0] << '\n';

	//This is thresholding
	for (int i = 0; i < convulutioned.org_height; i++) {
		for (int ii = 0; ii < convulutioned.org_width; ii++) {
			if(convulutioned[i][ii] <= 185 || convulutioned[i][ii] > 2500){
				convulutioned[i][ii] = 0;
			}else{
				convulutioned[i][ii] = 255;
			}
		}
	}


	//for (unsigned int y = 0; y < image.getHeight(); y++) {
	//	for (unsigned int x = 0; x < image.getWidth(); x++) {
	//		auto c = convulutioned[y][x];
	//		uint8_t number = 0;
	//		for (unsigned int i = 0; i < 8; i++) {
	//			((c >> i) & 0b1) ? number += pow(2, i) : number += 0;
	//		}
	//		std::cout << ((int)number < 220)?1:0 ;
	//	}
	//	std::cout << '\n';
	//}
	//return nullptr;
	return convulutioned.get_intensity_image_ptr();
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const { // aanpassen
	
	// TODO: Image container. DONE
	//cv::Mat temp_image;
	ed::matrix<260, 260> m(image);


	//TODO: 5x5 gaussian kernel to remove the noise, then apply Otsu thresholding.

	// TODO: Basic Threshold filter then Otsu threshold for better result
	//cv::threshold(temp_image, temp_image, 127, 200, cv::THRESH_BINARY_INV);
	//tr::basic_threshold(m, 185, 255);
	tr::auto_threshold(m, 120, 255);

	// TODO: Make pointer image to return. DONE
	//IntensityImage * ThoroughBushThoroughBrier = ImageFactory::newIntensityImage();
	//HereBeDragons::NoWantOfConscienceHoldItThatICall(temp_image, *ThoroughBushThoroughBrier);
	//return ThoroughBushThoroughBrier;
	return m.get_intensity_image_ptr();
}