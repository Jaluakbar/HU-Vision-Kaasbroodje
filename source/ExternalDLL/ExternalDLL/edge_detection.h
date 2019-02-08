#pragma once

#include "IntensityImage.h"
#include "ImageFactory.h"
#include <array>

namespace ed{

	template <int W, int H>
	class matrix {
	public:
		int width = W;
		int height = H;

		int org_width=-1;
		int org_height=-1;

		std::array<std::array<int, W>, H> m;

		matrix() = default;

		matrix(const IntensityImage& image):
			org_width(image.getWidth()),
			org_height(image.getHeight())
		{
			for (int y = 0; y < image.getHeight(); y++) {
				for (int x = 0; x < image.getWidth(); x++) {
					m[y][x] = image.getPixel(x, y);
				}
			}
		}

		matrix(const std::array<std::array<int, W>, H> & matrix) {
			for (int y = 0; y < H; y++) {
				for (int x = 0; x < W; x++) {
					m[y][x] = matrix[y][x];
				}
			}
		}

		IntensityImage * get_intensity_image_ptr() {
			IntensityImage * img_ptr = ImageFactory::newIntensityImage();
			img_ptr->set(org_width, org_height);
			for (int y = 0; y < org_height; y++) {
				for (int x = 0; x < org_width; x++) {
					img_ptr->setPixel(x, y, (char)m[x][y]);
					std::cout << m[x][y];
				}
			}
			return img_ptr;
		}

		std::array<int, W> & operator[](const int & i) {
			return m[i];
		}
	};

	template <int iH, int iW, int kH, int kW>
	matrix<iH, iW> convolution(matrix<iH,iW> & image, matrix<kH, kW> & kernel){
		// find center position of kernel (half of kernel size)
		int kernel_width = kernel.width;
		int kernel_height = kernel.height;

		int kernel_center_X =  kernel_width / 2 + 1;
		int kernel_center_Y =  kernel_height / 2 + 1;

		matrix<iH, iW> new_image{};
		new_image.org_height = image.org_height;
		new_image.org_width = image.org_width;

		for (int i = 0; i < image.height; ++i){              // rows
			for (int j = 0; j < image.width; ++j){          // columns
				for (int m = 0; m < kernel_height; ++m){     // kernel rows
					int mm = kernel_height - 1 - m;      // row index of flipped kernel
					for (int n = 0; n < kernel_width; ++n){ // kernel columns
						int nn = kernel_width - 1 - n;  // column index of flipped kernel

						// index of input signal, used for checking boundary
						int ii = i + (kernel_center_Y - mm);
						int jj = j + (kernel_center_X - nn);

						// ignore input samples which are out of bound
						if (ii >= 0 && ii < image.height && jj >= 0 && jj < image.width){
							new_image[i][j] += image[ii][jj] * kernel[mm][nn];
						}
					}
				}
			}
		}
		return new_image;
	}

}




