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


	auto convulutioned = ed::convolution(m, kernel);

	std::cout << convulutioned(0,0) << '\n';

	for (int i = 0; i < convulutioned.org_height; i++) {
		for (int ii = 0; ii < convulutioned.org_width; ii++) {
			if(convulutioned(i,ii) <= 185 || convulutioned(i,ii) > 2500){
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