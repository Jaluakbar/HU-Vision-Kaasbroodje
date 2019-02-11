#include "StudentPreProcessing.h"
#include "edge_detection.h"
#include <iostream>

IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const { // aanpassen
	ed::matrix<int> m(image);

	//ed::matrix<double, 5, 5> gaussian_kernel({ {
	//		{static_cast<double>(0.031827), 	static_cast<double>(0.037541), static_cast<double>(0.039665), static_cast<double>(0.037541), static_cast<double>(0.031827)},
	//		{static_cast<double>(0.037541), static_cast<double>(0.044281), static_cast<double>(0.046787), static_cast<double>(0.044281), static_cast<double>(0.037541)},
	//		{static_cast<double>(0.039665), static_cast<double>(0.046787), static_cast<double>(0.049434), static_cast<double>(0.046787), 	static_cast<double>(0.039665)},
	//		{static_cast<double>(0.037541), static_cast<double>(0.044281), static_cast<double>(0.046787), static_cast<double>(0.044281), 	static_cast<double>(0.037541)},
	//		{static_cast<double>(0.031827), 	static_cast<double>(0.037541), static_cast<double>(0.039665), static_cast<double>(0.037541), static_cast<double>(0.031827)},
	//	} });
	//auto convulutioned = ed::convolution<int, 5, 5, double>(m, gaussian_kernel);

	ed::matrix<int, 9,9> kernel({ {
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


	auto convulutioned = ed::convolution<int, 9, 9>(m, kernel);

	for (int i = 0; i < convulutioned.height; i++) {
		for (int ii = 0; ii < convulutioned.width; ii++) {
			if(convulutioned(i,ii) <= 150 || convulutioned(i,ii) > 2500){
				convulutioned(i,ii) = 0;
			}else{
				convulutioned(i,ii) = 255;
			}
		}
	}


	return convulutioned.get_intensity_image_ptr();
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const { // aanpassen
	return nullptr;
}