#include "image_processing.h"

void rgb2gray(unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS],
              unsigned char (*out_image_buffer)[BMP_HEIGTH]) {
  for (int i = 0; i < BMP_WIDTH; i++) {
    for (int j = 0; j < BMP_HEIGTH; j++) {
      out_image_buffer[i][j] =
          (input_image[i][j][0] + input_image[i][j][1] + input_image[i][j][2]) /
          3;
    }
  }
}

void gray2rgb(unsigned char (*in_image_buffer)[BMP_HEIGTH],
              unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS]) {
  for (int i = 0; i < BMP_WIDTH; i++) {
    for (int j = 0; j < BMP_HEIGTH; j++) {
      output_image[i][j][0] = in_image_buffer[i][j];
      output_image[i][j][1] = in_image_buffer[i][j];
      output_image[i][j][2] = in_image_buffer[i][j];
    }
  }
}

void binaryThreshold(unsigned char (*in_image_buffer)[BMP_HEIGTH],
                     unsigned char (*out_image_buffer)[BMP_HEIGTH]) {
  for (int i = 0; i < BMP_WIDTH; i++) {
    for (int j = 0; j < BMP_HEIGTH; j++) {
      out_image_buffer[i][j] = in_image_buffer[i][j] > THRESHOLD ? 255 : 0;
    }
  }
}

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
    // printf("%d,%d\n", x, y);
    // printf("xmin: %d\n", xmax);

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
    // output_image[x][y][0] = 255;
  }
}

// Returns 1 if white pixel is detected in the exclusion frame else 0
int _exclusion(short int x, short int y,
               unsigned char (*in_image_buffer)[BMP_HEIGTH]) {
  int exclude = 0;
  short int xmin, xmax, ymin, ymax;
  _getXandYmaxmin(x, y, &xmin, &xmax, &ymin, &ymax);

  for (int i = xmin; i <= xmax; i++) {
    if (exclude)
      break;

    exclude = exclude || in_image_buffer[x + i][y + ymax] ||
              in_image_buffer[x + i][y + ymin];
  }

  for (int i = ymin; i <= ymax; i++) {
    if (exclude)
      break;

    exclude = exclude || in_image_buffer[x + xmax][y + i] ||
              in_image_buffer[x + xmin][y + i];
  }

  return exclude;
}

// Returns 1 if a white pixel is found in the detection area else 0
int _detection(short int x, short int y,
               unsigned char (*in_image_buffer)[BMP_HEIGTH]) {
  int detected = 0;

  short int xmin, xmax, ymin, ymax;
  _getXandYmaxmin(x, y, &xmin, &xmax, &ymin, &ymax);

  xmin++;
  ymin++;
  xmax--;
  ymax--;

  for (int i = xmin; i <= xmax; i++) {
    for (int j = ymin; j <= ymax; j++) {
      if (in_image_buffer[i + x][j + y]) {
        detected = 1;
        break;
      }
    }
    if (detected)
      break;
  }

  return detected;
}

void _whipeCell(short int x, short int y,
                unsigned char (*out_image_buffer)[BMP_HEIGTH]) {
  short int xmin, xmax, ymin, ymax;
  _getXandYmaxmin(x, y, &xmin, &xmax, &ymin, &ymax);
  xmin++;
  ymin++;
  xmax--;
  ymax--;

  for (short int i = xmin; i <= xmax; i++) {
    for (short int j = ymin; j <= ymax; j++) {
      out_image_buffer[x + i][y + j] = 0;
    }
  }
}

void _getXandYmaxmin(short int x, short int y, short int *xmin, short int *xmax,
                     short int *ymin, short int *ymax) {
  *xmin = -5;
  *xmax = 6;
  *ymin = -5;
  *ymax = 6;

  if (x < 5) {
    *xmin = -x;
  }
  if (x > BMP_WIDTH - 1 - *xmax) {
    *xmax = BMP_WIDTH - 1 - x;
  }

  if (y < 5) {
    *ymin = -y;
  }
  if (y > BMP_HEIGTH - 1 - *ymax) {
    *ymax = BMP_HEIGTH - 1 - y;
  }
}