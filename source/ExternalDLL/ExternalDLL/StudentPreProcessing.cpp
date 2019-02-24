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






	ed::matrix<double, 5, 5> gaussian_kernel({ {
		{0.015026,0.015026,0.035391,0.028569,0.015026},
		{ 0.028569,0.054318,0.067288,0.054318,0.028569},
		{0.035391,0.067288,0.083355,0.067288,0.035391},
		{0.028569,0.054318,0.067288,0.054318,0.028569},
		{0.015026,0.015026,0.035391,0.028569,0.015026}}
	});

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

//	ed::matrix<int, 3, 3> edge_kernel({ {
//		{0,1,0},
//		{1,-4,1},
//		{0,1,0}
//} });

	ed::matrix<unsigned char, 3, 3> dilation({{
		{0,1,0},
		{1,1,1},
		{0,1,0}
		} });

	ed::matrix<unsigned char, 9, 9> dilation_great({ {
		{0,0,0,1,1,1,0,0,0},
		{0,0,0,1,1,1,0,0,0},
		{0,0,0,1,1,1,0,0,0},
		{1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1},
		{0,0,0,1,1,1,0,0,0},
		{0,0,0,1,1,1,0,0,0},
		{0,0,0,1,1,1,0,0,0},
		} });


	ed::matrix<unsigned char,3 , 3> sobel_edge({{
		{1,2,2},
		{1,1,0},
		{2,4,1}
	} });

	ed::matrix<int, 5, 5> lap_from_gaus({ {
		{0,0,-1,0,0},
		{0,-1,-2,-1,0},
		{-1,-2,16, -2, -1},
		{0,-1,-2,-1,0},
		{0,0,-1,0,0}
} });

	ed::matrix<int> m(image);

	//auto convulutioned = ed::convolution<unsigned char, 5, 5, double>(m, gaussian_kernel);
	//convulutioned = ed::convolution<unsigned char, 5, 5, int>(convulutioned, lap_from_gaus);

	m = ed::convolution<int, 9,9>(m, edge_kernel);
	//m = ed::convolution<int, 3, 3>(m, dilation);

	//auto convulutioned = ed::convolution<unsigned char, 5, 5, double>(m, gaussian_kernel);
	//convulutioned = ed::convolution<unsigned char, 3, 3>(convulutioned, sobel_edge);

	m.equalization(256);

	//for (int i = 0; i < m.height; i++) {
	//	for (int ii = 0; ii < m.width; ii++) {
	//		if(m(i,ii) <= 155 || m(i,ii) > 2500){
	//			m(i,ii) = 0;
	//		}else{
	//			m(i,ii) = 255;
	//		}
	//	}
	//}


	//m = ed::convolution<int, 3, 3>(m, dilation);

	//for(int i = 0; i < m.height; i++){
	//	for (int ii = 0; ii < m.width; ii++) {
	//		if(m(i,ii) >= 155 && m(i,ii) <= 2500){
	//			m(i, ii) = 255;
	//		}else{
	//			m(i, ii) = 0;
	//		}
	//	}
	//}


	//m = ed::convolution<unsigned char, 9, 9>(m, dilation_great);

	return m.get_intensity_image_ptr();
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const { // aanpassen
	
	// TODO: Image container. DONE
	//cv::Mat temp_image;
	ed::matrix<unsigned char> m(image);


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
	//return nullptr;
}