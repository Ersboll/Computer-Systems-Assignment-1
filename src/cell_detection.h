#ifndef CELL_DETECTION_H
#include "cbmp.h"
#include "image_processing.h"

int detectCells(unsigned char (*in_image_buffer)[BMP_HEIGTH/8],
                unsigned char (*out_image_buffer)[BMP_HEIGTH/8],
                unsigned short int (*list_buffer)[2]);

#endif