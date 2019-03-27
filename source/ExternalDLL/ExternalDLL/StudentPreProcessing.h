/*
* Copyright (c) 2015 DottedEye Designs, Alexander Hustinx, NeoTech Software, Rolf Smit - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*/

#pragma once

#include "PreProcessing.h"

class StudentPreProcessing : public PreProcessing {
public:
	/// \cond DO_NOT_DOCUMENT
	IntensityImage * stepToIntensityImage(const RGBImage &image) const;
	IntensityImage * stepScaleImage(const IntensityImage &image) const;
	/// \endcond

	/**
	 * \brief biertje
	 */
	IntensityImage * stepEdgeDetection(const IntensityImage &image) const;

	/**
	 * \brief We don't use this function.
	 *
	 * We don't use this function for thresholding becouse we do the thresholding in the edge detection function.
	 * Read the implementation plan & measurement  report for more information.
	 *
	 * \return This function returns an img_ptr copied from the stepEdgeDetection function
	 */
	IntensityImage * stepThresholding(const IntensityImage &image) const;
};