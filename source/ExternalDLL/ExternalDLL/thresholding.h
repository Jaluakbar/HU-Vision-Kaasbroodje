#pragma once


#include "IntensityImage.h"
#include "ImageFactory.h"
#include <array>
#include "edge_detection.h"

namespace tr {
	void basic_threshold(ed::matrix<x_src, y_src> &src, int threshold, int maxval) {
		for (int i = 0; i < x_src; i++) {
			for (int j = 0; j < y_src; j++) {
				if (src[i][j] < threshold) {
					src[i][j] = 0;
				}else{
					src[i][j] = 255;
		}
	}

}