#ifndef EROSION_H
#define EROSION_H
#include "cbmp.h"
#include "compression.h"

int erosion(unsigned char (*in_image_buffer)[BMP_HEIGTH/8+1],
            unsigned char (*out_image_buffer)[BMP_HEIGTH/8+1]);

#endif