#ifndef MARK_CELLS_H
#include "cbmp.h"
#include "image_processing.h"

void markCells(unsigned short (*detected_cells)[2],
               unsigned short number_of_cells,
               unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS],
               unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS]);

#endif