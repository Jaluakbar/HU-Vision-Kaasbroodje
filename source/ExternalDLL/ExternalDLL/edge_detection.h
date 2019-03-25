#pragma once

#include "IntensityImage.h"
#include "ImageFactory.h"
#include <array>
#include <iostream>
#include <map>

/**
 * \brief This namespace contains every function related to the used Canny edge detection
 */
namespace ed{

	/**
	 * The matrix class can be used for 2D matrixes.
	 * The matrix contains some functions that are handy for working with
	 * the HU-Vision code structure.
	 */
	template <class T, int Height = 0, int Width = 0>
	class matrix {
	public:
		int width = -1;
		int height = -1;

		T* m;

		/**
		 * The constructor for creating an empty matrix by giving the height and width.
		 * 
		 * \param height The height of the matrix
		 * \param width The width of the matrix
		 */
		matrix(const int height, const int width) :
			width(width),
			height(height) 
		{
			m = new T[height*width];
		}


		/**
		 * The constructor for creating a matrix from an IntensityImage.
		 * 
		 * \param image An IntensityImage
		 */
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

		/**
		 * The constructor for creating a copy of another matrix.
		 * 
		 * \param matrix The matrix which going to be copied.
		 */
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


		/**
		 * \brief This function creates and returns an new IntensityImage pointer.
		 * This function creates a IntensityImage pointer from the matrix and returns the pointer afterwards.
		 * 
		 * \return The IntensityImage pointer.
		 */
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

		/**
		 * \brief Non-lineair equalization.
		 * 
		 * This equalization function makes use of the non-lineair way of equalization with
		 * the result of distributing a pixel value according to the frequency of the original 
		 * pixel value. This function scales the values <=0 to 0 with as maximum the spread_size value.
		 * 
		 * \param spread_size The equialized values are in a range from 0 and spread_size.
		 */
		template <typename NT = unsigned int>
		void equalization(int spread_size) {
			static std::map<int, unsigned int> cdf = cdf_map();
			// an equalized value map is an map with the old value as key and the new value as value in a map.
			static std::map<unsigned int, NT> equalized_value_map;

			// we need the lowest non-neg cdf value to calibrate every value between 0 and spread_size.
			int lowest_non_neg_cdf_key = 0;
			int lowest_non_neg_cdf_value = 0;

			std::map<int, unsigned int>::iterator it;
			for(int i = 0;; i++){
				if(cdf[i]){
					it = cdf.find(i);
					lowest_non_neg_cdf_value = cdf[i];
					lowest_non_neg_cdf_key = i;
					std::cout << "found lowest CDF key: " << lowest_non_neg_cdf_key << '\n';
					std::cout << "found lowest CDF value: " << lowest_non_neg_cdf_value << '\n';
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
				std::cout << i << " = " << equalized_value_map[i] << '\n';
				it = std::next(it, 1);
			}

			// give the picture the new equalized values of the pixels.
			for (int i = 0; i < MxN; i++) {
				(m[i] < 0) ? (m[i] = 0) : (m[i] = equalized_value_map[m[i]]);
			}
		}

		/**
		 * \brief Thresholding for Canny edge detection
		 * This function is a static implementation of a thresholding function which
		 * means that the values that are going to be MinValue and MaxValue are allready known.
		 */
		template <unsigned MinValue = 0, unsigned MaxValue = 255>
		void thresholding_static() {
			for (int i = 0; i < height; i++) {
				for (int ii = 0; ii < width; ii++) {
					if (this->operator()(i, ii) <= 155 || this->operator()(i, ii) > 2500) {
						this->operator()(i, ii) = MaxValue;
					} else {
						this->operator()(i, ii) = MinValue;
					}
				}
			}
		}

		/**
		 * Operator for using the 1D array as an 2D array.
		 * 
		 * \param y The height value (y).
		 * \param x The width value (x).
		 * 
		 * \return The reference to the value of (y, x).
		 */
		T & operator()(const int y, const int x) {
			return m[(y*width) + x];
		}

		/**
		 * Operator for using the 1D array with a direct index.
		 * 
		 * \param n The index of the array.
		 * 
		 * \return The reference to the value of (n).
		 */
		T & operator()(int n) {
			return m[n];
		}

	protected:

		// the CDF map is used for simplify the non-lineair equalization function and 
		// making the rest of the equalization function faster.
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


	/**
	 * @brief This function convolutes a matrix with another matrix.
	 * This function multiplies the first parameter matrix(image) with the second parameter matrix(kernel).
	 * 
	 * @param image Is the matrix which is going to be convoluted by the second matrix (kernel).
	 * @param kernel Is the matrix which is the kernel which the image is going to be multiplied with.
	 * 
	 * @return A new matrix as result from the convoluted picture with the kernel. 
	 */
	template <typename T, int Height, int Width, typename TT = T>
	matrix<T> convolution(matrix<T> & image, matrix<TT, Height, Width> & kernel) {
		// find center position of kernel (half of kernel size)
		unsigned int kernel_width = kernel.width;
		unsigned int kernel_height = kernel.height;

		int kernel_center_X = kernel_width / 2 + 1;
		int kernel_center_Y = kernel_height / 2 + 1;

		matrix<T> new_image(image.height, image.width);

		for (int y = 0; y < image.height; ++y) {
			for (int x = 0; x < image.width; ++x) {
				for (int yy = kernel_height - 1; yy >= 0; --yy) {
					for (int xx = kernel_width - 1; xx >= 0; --xx) {

						// index of input signal, used for checking boundary
						int image_index_Y = y + (kernel_center_Y - yy);
						int image_index_X = x + (kernel_center_X - xx);

						// ignore input samples which are out of bound
						if (image_index_Y >= 0 && image_index_Y <= image.height && image_index_X >= 0 && image_index_X <= image.width) {
							new_image(y, x) += image(image_index_Y, image_index_X) * kernel(yy, xx);
						}
					}
				}
			}
		}
		return new_image;
	}
}
