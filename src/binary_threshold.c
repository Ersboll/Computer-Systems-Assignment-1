#include "binary_threshold.h"

void binaryThreshold(unsigned char (*in_image_buffer)[BMP_HEIGTH],
                     unsigned char (*out_image_buffer)[BMP_HEIGTH]) {
  for (int i = 0; i < BMP_WIDTH; i++) {
    for (int j = 0; j < BMP_HEIGTH; j++) {
      out_image_buffer[i][j] = in_image_buffer[i][j] > THRESHOLD ? 255 : 0;
    }
  }
}