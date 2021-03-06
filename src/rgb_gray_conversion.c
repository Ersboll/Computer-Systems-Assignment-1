#include "rgb_gray_conversion.h"
#include "compression.h"

void rgb2gray(unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS],
              unsigned char (*out_image_buffer)[BMP_HEIGTH]) {
  for (int i = 0; i < BMP_WIDTH; i++) {
    for (int j = 0; j < BMP_HEIGTH; j++) {
      out_image_buffer[i][j] =
          input_image[i][j][0]; // Since the images are greyscaled already we
                                // only need one of the cannels
    }
  }
}

void gray2rgb(unsigned char (*in_image_buffer)[BMP_HEIGTH / 8 + 1],
              unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS]) {
  for (int i = 0; i < BMP_WIDTH; i++) {
    for (int j = 0; j < BMP_HEIGTH; j++) {
      output_image[i][j][0] = getValue(in_image_buffer, i, j) * 255;
      output_image[i][j][1] = getValue(in_image_buffer, i, j) * 255;
      output_image[i][j][2] = getValue(in_image_buffer, i, j) * 255;
    }
  }
}