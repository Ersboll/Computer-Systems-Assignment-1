#include "rgb_gray_conversion.h"
#include "compression.h"

void rgb2gray(unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS],
              unsigned char out_image_buffer[BMP_WIDTH][BMP_HEIGTH]) {
  for (int i = 0; i < BMP_WIDTH; i++) {
    for (int j = 0; j < BMP_HEIGTH; j++) {
      out_image_buffer[i][j] =
          (input_image[i][j][0] + input_image[i][j][1] + input_image[i][j][2]) /
          3;
    }
  }
}

void gray2rgb(unsigned char (*in_image_buffer)[BMP_HEIGTH/8+1],
              unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS]) {
  for (int i = 0; i < BMP_WIDTH; i++) {
    for (int j = 0; j < BMP_HEIGTH; j++) {
      output_image[i][j][0] = getValue(in_image_buffer, i, j);
      output_image[i][j][1] = output_image[i][j][0];
      output_image[i][j][2] = output_image[i][j][0];
    }
  }
}