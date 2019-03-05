#pragma once

#include "IntensityImage.h"
#include "ImageFactory.h"
#include <array>
#include <iostream>
#include <map>

namespace ed{

	template <class T, int Height = 0, int Width = 0>
	class matrix {
	public:
		int width = -1;
		int height = -1;

		T* m;

		matrix(const int h, const int w) :
			width(w),
			height(h) 
		{
			m = new T[height*width];
		}

		matrix(const IntensityImage& image):
			width(image.getWidth()),
			height(image.getHeight())
		{
			m = new T[height*width];
			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++) {
					m[(y*width) + x] = image.getPixel(x, y);
				}
			}
		}

		template <typename TT = T>
		matrix(const std::array<std::array<TT, Width>, Height> & matrix):
			width(Width),
			height(Height)
		{
			m = new T[height*width];
			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++) {
					m[(y*width) + x] = matrix[y][x];
				}
			}
		}

		IntensityImage * get_intensity_image_ptr() {
			IntensityImage * img_ptr = ImageFactory::newIntensityImage();
			img_ptr->set(width, height);
			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++) {
					img_ptr->setPixel(x, y, this->operator()(y,x));
				}
			}
			return img_ptr;
		}

		template <typename NT = unsigned int>
		void equalization(int spread_size) {
			static std::map<int, unsigned int> cdf = cdf_map();
			// an equalized value map is an map with the old value as key and the new value as value in a map
			static std::map<unsigned int, NT> equalized_value_map;

			// we need the lowest non-neg cdf value to calibrate every value between 0 and spread_size
			int lowest_non_neg_cdf_value;
			std::map<int, unsigned int>::iterator it;
			for(int i = 0; i < cdf.end()->first; i++){
				if(cdf[i]){
					it = cdf.find(i);
					lowest_non_neg_cdf_value = cdf[i];
					break;
				}
			}

			double MxN = width * height;
			double alpha = spread_size / (MxN - lowest_non_neg_cdf_value);

			// calculate the new equalized values of the pixels.
			equalized_value_map[0] = static_cast<unsigned int>(alpha * (it->second - lowest_non_neg_cdf_value));
			std::cout << 0 << " = " << equalized_value_map[0] << '\n';
			for (int i = 1; i < spread_size; i++) {
				equalized_value_map[i] = static_cast<unsigned int>(equalized_value_map[i - 1] + (alpha * (it->second - lowest_non_neg_cdf_value)));
				it = std::next(it, 1);
			}

			// give the picture the new equalized values of the pixels.
			for (int i = 0; i < MxN; i++) {
				m[i] = equalized_value_map[m[i]];
			}
		}

		// Operator for using the 1D array as an 2D array
		T & operator()(const int y, const int x) {
			return m[(y*width) + x];
		}

		// Operator for using the 1D array with a direct index)
		T & operator()(int n) {
			return m[n];
		}

	protected:

		std::map<int, unsigned int> cdf_map() {
			std::map<int, unsigned int> map;
			for (int i = 0; i < (width*height); i++) {
				if (m[i] < 0){
					map[0] += 1;
				} else {
				map[m[i]] += 1;
				}
			}

			for (auto ptr = std::next(map.begin(), 1); ptr != map.end(); ptr++) {
				ptr->second += (std::next(ptr, -1))->second;
			}
			return map;
		}
	};


	template <typename T, T Height, T Width, typename TT = T>
	matrix<T> convolution( matrix<T> & image, matrix<TT, Height, Width> & kernel) {
		// find center position of kernel (half of kernel size)
		unsigned int kernel_width = kernel.width;
		unsigned int kernel_height = kernel.height;

		int kernel_center_X =  kernel_width / 2 + 1;
		int kernel_center_Y =  kernel_height / 2 + 1;

		matrix<T> new_image(image.height, image.width);

		for (int y = 0; y < image.height; ++y){
			for (int x = 0; x < image.width; ++x){  
				for (int yy = kernel_height-1; yy >= 0; --yy){ 
					for (int xx = kernel_width-1; xx >= 0; --xx){ 

						// index of input signal, used for checking boundary
						int image_index_Y = y + (kernel_center_Y - yy);
						int image_index_X = x + (kernel_center_X - xx);

						// ignore input samples which are out of bound
						if (image_index_Y >= 0 && image_index_Y <= image.height && image_index_X >= 0 && image_index_X <= image.width){
							new_image(y,x) += image(image_index_Y,image_index_X) * kernel(yy,xx);
						}
					}
				}
			}
		}
		return new_image;
	}
}
