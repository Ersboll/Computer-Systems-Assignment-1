#include "erosion.h"

int erosion(unsigned char (*in_image_buffer)[BMP_HEIGTH],
            unsigned char (*out_image_buffer)[BMP_HEIGTH]) {
  int erosionCount = 0;

  for (int i = 0; i < BMP_WIDTH; i++) {
    for (int j = 0; j < BMP_HEIGTH; j++) {
      if (!in_image_buffer[i][j]) { // == 0
        out_image_buffer[i][j] = 0;
      } else { // != 0
        if (i == 0 || i == BMP_WIDTH - 1 || j == 0 ||
            j == BMP_HEIGTH - 1) { // are we on the edge?
          out_image_buffer[i][j] = 0;
          erosionCount++;
        } else if (in_image_buffer[i - 1][j] && in_image_buffer[i + 1][j] &&
                   in_image_buffer[i][j - 1] && in_image_buffer[i][j + 1]) {
          out_image_buffer[i][j] = 255;
        } else {
          out_image_buffer[i][j] = 0;
          erosionCount++;
        }
      }
    }
  }

  return erosionCount;
}