#pragma once

#include "IntensityImage.h"
#include "ImageFactory.h"

/**
 * \brief This namespace contains every function related to the thresholding
 */
namespace tr {
	/**
		 * \brief Thresholding for Canny edge detection
		 * This function is a static implementation of a thresholding function which
		 * means that the values that are going to be 0 if its below the threshold or 255 if above.
		 * \param src The original image to apply threshold to
		 * \param threshold The threshold trigger to split the image
		 */
	template <class T>
	void basic_threshold(ed::matrix<T> &src, const int &threshold) {
		for (int i = 0; i < src.height; i++) {
			for (int j = 0; j < src.width; j++) {
				if (src(i, j) <= threshold || src(i, j) > 2500) {
					src(i, j) = 255;
				}
				else {
					src(i, j) = 0;
				}
			}
		}
	}
}