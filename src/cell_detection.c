#include "cell_detection.h"

int detectCells(unsigned char (*in_image_buffer)[BMP_HEIGTH],
                unsigned char (*out_image_buffer)[BMP_HEIGTH],
                unsigned short int (*list_buffer)[2]) {
  int detection_count = 0;
  for (short int i = 0; i < BMP_WIDTH; i++) {
    for (short int j = 0; j < BMP_HEIGTH; j++) {
      out_image_buffer[i][j] = in_image_buffer[i][j];
    }
  }
  for (short int i = 0; i < BMP_WIDTH; i++) {
    for (short int j = 0; j < BMP_HEIGTH; j++) {
      if (_exclusion(i, j, out_image_buffer)) {
        continue;
      } else if (_detection(i, j, out_image_buffer)) {
        list_buffer[detection_count][0] = i;
        list_buffer[detection_count][1] = j;
        detection_count++;

        _whipeCell(i, j, out_image_buffer);
      }
    }
  }
  return detection_count;
}