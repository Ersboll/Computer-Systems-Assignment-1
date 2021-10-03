#include "mark_cells.h"

void markCells(cell_list_t *cell_list,
               unsigned char color_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS]) {

  short xmin, xmax, ymin, ymax, x, y;

  for (unsigned short i = 0; i < cell_list->count; i++) {
    x = cell_list->list[i][0];
    y = cell_list->list[i][1];
    _getXandYmaxmin(x, y, &xmin, &xmax, &ymin, &ymax);

    for (short a = xmin; a <= xmax; a++) {
      color_image[x + a][y][0] = 255;
      color_image[x + a][y][1] = 0;
      color_image[x + a][y][2] = 0;
    }

    for (short a = ymin; a <= ymax; a++) {
      color_image[x][y + a][0] = 255;
      color_image[x][y + a][1] = 0;
      color_image[x][y + a][2] = 0;
    }
  }
}