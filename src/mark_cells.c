#include "mark_cells.h"

void markCells(
    cell_list_t *cell_list,
    unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS],
    unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS]) {

  short xmin, xmax, ymin, ymax, x, y;

  for (short i = 0; i < BMP_WIDTH; i++) {
    for (short j = 0; j < BMP_HEIGTH; j++) {
      output_image[i][j][0] = input_image[i][j][0];
      output_image[i][j][1] = input_image[i][j][1];
      output_image[i][j][2] = input_image[i][j][2];
    }
  }

  for (unsigned short i = 0; i < cell_list->count; i++) {
    x = cell_list->list[i][0];
    y = cell_list->list[i][1];
    _getXandYmaxmin(x, y, &xmin, &xmax, &ymin, &ymax);

    for (short a = xmin; a <= xmax; a++) {
      output_image[x + a][y][0] = 255;
      output_image[x + a][y][1] = 0;
      output_image[x + a][y][2] = 0;
    }

    for (short a = ymin; a <= ymax; a++) {
      output_image[x][y + a][0] = 255;
      output_image[x][y + a][1] = 0;
      output_image[x][y + a][2] = 0;
    }
  }
}