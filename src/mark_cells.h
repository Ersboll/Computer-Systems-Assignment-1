#ifndef MARK_CELLS_H
#include "cbmp.h"
#include "detected_cells_structure.h"
#include "image_processing.h"

void markCells(cell_list_t *cell_list,
               unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS],
               unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS]);

#endif