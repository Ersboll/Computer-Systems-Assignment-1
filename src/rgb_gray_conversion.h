#include "cbmp.h"

void rgb2gray(unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS],
              unsigned char (*out_image_buffer)[BMP_HEIGTH]);
void gray2rgb(unsigned char (*in_image_buffer)[BMP_HEIGTH],
              unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS]);