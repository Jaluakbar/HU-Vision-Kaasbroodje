#pragma once


#include "IntensityImage.h"
#include "ImageFactory.h"
#include <array>
#include "edge_detection.h"

namespace tr {

	template <int x_src, int y_src>
	void basic_threshold(ed::matrix<x_src, y_src> &src, int threshold, int maxval) {
		for (int i = 0; i < x_src; i++) {
			for (int j = 0; j < y_src; j++) {
				if (src[i][j] <= threshold || src[i][j] > 2500) {
					src[i][j] = maxval;
				}
				else {
					src[i][j] = 0;
				}
			}
		}
	}

	template <int x_src, int y_src>
	void auto_threshold(ed::matrix<x_src, y_src> &src, int init_threshold, int maxval) {
		int background = 0;
		int background_pixels = 0;
		int foreground = 0;
		int foreground_pixels = 0;
		for (int i = 0; i < x_src; i++) {
			for (int j = 0; j < y_src; j++) {
				if (src[i][j] <= init_threshold /*|| src[i][j] > 2500*/) {
					background += src[i][j];
					background_pixels += 1;
				}
				else {
					foreground += src[i][j];
					foreground_pixels += 1;
				}
			}
		}
		int average_threshold = ((background/background_pixels)+(foreground/ foreground_pixels)) / 2;

		if (average_threshold - init_threshold > 2){
			basic_threshold(src, average_threshold, maxval);
		}

	}


}