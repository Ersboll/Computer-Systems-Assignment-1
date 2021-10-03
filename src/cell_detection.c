#include "cell_detection.h"

int detectCells(cell_list_t *cell_list,
                unsigned char (*in_image_buffer)[BMP_HEIGTH / 8 + 1],
                unsigned char (*out_image_buffer)[BMP_HEIGTH / 8 + 1]) {
  for (unsigned short i = 0; i < BMP_WIDTH; i++) {
    for (unsigned short j = 0; j < BMP_HEIGTH; j++) {
      setValue(out_image_buffer, i, j, getValue(in_image_buffer, i, j));
    }
  }

  for (unsigned short i = 0; i < BMP_WIDTH; i++) {
    for (unsigned short j = 0; j < BMP_HEIGTH; j++) {

      if (_exclusion(i, j, out_image_buffer)) {
        continue;
      } else if (_detection(i, j, out_image_buffer)) {
        int res = add_cell_to_list(cell_list, i, j);
        if (!res) {
          return 0;
        }
        _whipeCell(i, j, out_image_buffer);
      }
    }
  }
  return 1;
}