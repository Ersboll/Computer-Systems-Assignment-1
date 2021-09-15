#include "mark_cells.h"

void markCells(
    unsigned short int (*detected_cells)[2], unsigned short int number_of_cells,
    unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS],
    unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS]) {

  short int xmin, xmax, ymin, ymax, x, y;

  for (short int i = 0; i < BMP_WIDTH; i++) {
    for (short int j = 0; j < BMP_HEIGTH; j++) {
      output_image[i][j][0] = input_image[i][j][0];
      output_image[i][j][1] = input_image[i][j][1];
      output_image[i][j][2] = input_image[i][j][2];
    }
  }

  for (unsigned short int i = 0; i < number_of_cells; i++) {
    x = detected_cells[i][0];
    y = detected_cells[i][1];
    _getXandYmaxmin(x, y, &xmin, &xmax, &ymin, &ymax);

    for (short int a = xmin; a <= xmax; a++) {
      output_image[x + a][y][0] = 255;
      output_image[x + a][y][1] = 0;
      output_image[x + a][y][2] = 0;
    }

    for (short int a = ymin; a <= ymax; a++) {
      output_image[x][y + a][0] = 255;
      output_image[x][y + a][1] = 0;
      output_image[x][y + a][2] = 0;
    }
  }
}