#ifndef CELL_DETECTION_H
#include "cbmp.h"
#include "compression.h"
#include "detected_cells_structure.h"
#include "image_processing.h"

int detectCells(cell_list_t *cell_list,
                unsigned char (*in_image_buffer)[BMP_HEIGTH / 8 + 1],
                unsigned char (*out_image_buffer)[BMP_HEIGTH / 8 + 1]);

#endif