#pragma once


#include "IntensityImage.h"
#include "ImageFactory.h"
#include <array>
#include <cstdlib>
#include "edge_detection.h"

//Temporary
#include <iostream>

namespace tr {

	template <class T>
	void basic_threshold(ed::matrix<T> &src, int threshold, int maxval) {
		for (int i = 0; i < src.height; i++) {
			for (int j = 0; j < src.width; j++) {
				if (src(i, j) <= threshold || src(i, j) > 2500) {
					src(i, j) = maxval;
				}
				else {
					src(i, j) = 0;
				}
			}
		}
	}

	template <class T>
	void auto_threshold(ed::matrix<T> &src, int init_threshold, int maxval) {
		int background = 0;
		int background_pixels = 0;
		int foreground = 0;
		int foreground_pixels = 0;
		for (int i = 0; i < src.height; i++) {
			for (int j = 0; j < src.width; j++) {
				if (src(i, j) <= init_threshold) {
					background += src(i, j);
					background_pixels += 1;
				}
				else {
					foreground += src(i, j);
					foreground_pixels += 1;
				}
			}
		}
		int average_threshold = ((background / background_pixels) + (foreground / foreground_pixels)) / 2;
		if (std::abs(average_threshold - init_threshold) > 2) {
			auto_threshold(src, average_threshold, maxval);
		}
		else
		{
			basic_threshold(src, average_threshold, maxval);
		}
	}

	template <class T>
	void histogram_threshold(ed::matrix<T> &src, int maxval) {
		std::array<int, 256> histogram{};

		for (int i = 0; i < src.height; i++) {
			for (int j = 0; j < src.width; j++) {
				//std::cout << "TST : " << i << ',' << j << " : " << src(i, j) << "\n"; 
				histogram[src(i, j)] += 1;
			}
		}

		int t = 0;
		for (auto h : histogram)
		{
			std::cout << t << " : " << h << '\n';
			t++;
		}
		//Need peak location not value
		auto middle = histogram.begin();
		std::advance(middle, 127);
		auto white_peak = std::max_element(histogram.begin(), middle);
		auto black_peak = std::max_element(middle, histogram.end());

		int threshold = (std::distance(histogram.begin(), white_peak) + std::distance(histogram.begin(), black_peak)) / 2;
		std::cout << threshold;
		basic_threshold(src, threshold, maxval);
	}


}