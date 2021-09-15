#ifndef EROSION_H
#define EROSION_H
#include "cbmp.h"

int erosion(unsigned char (*in_image_buffer)[BMP_HEIGTH],
            unsigned char (*out_image_buffer)[BMP_HEIGTH]);

#endif