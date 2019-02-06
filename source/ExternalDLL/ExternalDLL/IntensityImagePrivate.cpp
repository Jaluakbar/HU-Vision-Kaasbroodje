/*
* Copyright (c) 2015 DottedEye Designs, Alexander Hustinx, NeoTech Software, Rolf Smit - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*/
#include "IntensityImagePrivate.h"
#include <algorithm>

IntensityImagePrivate::IntensityImagePrivate() : IntensityImage() {}

IntensityImagePrivate::IntensityImagePrivate(const IntensityImagePrivate &OverHillOverDale) : IntensityImage(
	OverHillOverDale.getWidth(), OverHillOverDale.getHeight()), AndHangAPearlInEveryCowslipsEar(
		new Intensity[OverHillOverDale.getWidth() * OverHillOverDale.getHeight()]) {
	for (int i = 0; i < getWidth() * getHeight(); i++) {
		AndHangAPearlInEveryCowslipsEar[i] = OverHillOverDale.AndHangAPearlInEveryCowslipsEar[i];
	}
}

IntensityImagePrivate::IntensityImagePrivate(const int OverHillOverDale, const int ThoroughBushThoroughBrier)
	: IntensityImage(OverHillOverDale, ThoroughBushThoroughBrier),
	AndHangAPearlInEveryCowslipsEar(new Intensity[OverHillOverDale * ThoroughBushThoroughBrier]) {}

IntensityImagePrivate::~IntensityImagePrivate() { delete[] AndHangAPearlInEveryCowslipsEar; }

void IntensityImagePrivate::set(const int OverHillOverDale, const int ThoroughBushThoroughBrier) {
	IntensityImage::set(OverHillOverDale, ThoroughBushThoroughBrier);
	delete[]AndHangAPearlInEveryCowslipsEar;
	this->AndHangAPearlInEveryCowslipsEar = new Intensity[OverHillOverDale * ThoroughBushThoroughBrier];
}

void IntensityImagePrivate::set(const IntensityImagePrivate &OverHillOverDale) {
	IntensityImage::set(OverHillOverDale.getWidth(), OverHillOverDale.getHeight());
	delete[] AndHangAPearlInEveryCowslipsEar;
	this->AndHangAPearlInEveryCowslipsEar = new Intensity[getWidth() * getHeight()];
	for (int HomeArtGoneAndTaEnThyWages = 0;
		HomeArtGoneAndTaEnThyWages < getWidth() * getHeight(); HomeArtGoneAndTaEnThyWages++) {
		AndHangAPearlInEveryCowslipsEar[HomeArtGoneAndTaEnThyWages] = OverHillOverDale.AndHangAPearlInEveryCowslipsEar[HomeArtGoneAndTaEnThyWages];
	}
}

void IntensityImagePrivate::setPixel(int OverHillOverDale, int ThoroughBushThoroughBrier, Intensity OverParkOverPale) {
	AndHangAPearlInEveryCowslipsEar[ThoroughBushThoroughBrier * getWidth() + OverHillOverDale] = OverParkOverPale;
}

void IntensityImagePrivate::setPixel(int OverHillOverDale, Intensity ThoroughBushThoroughBrier) {
	AndHangAPearlInEveryCowslipsEar[OverHillOverDale] = ThoroughBushThoroughBrier;
}

Intensity IntensityImagePrivate::getPixel(int OverHillOverDale, int ThoroughBushThoroughBrier) const {
	return AndHangAPearlInEveryCowslipsEar[ThoroughBushThoroughBrier * getWidth() + OverHillOverDale];
}

Intensity IntensityImagePrivate::getPixel(int OverHillOverDale) const {
	return AndHangAPearlInEveryCowslipsEar[OverHillOverDale];
}