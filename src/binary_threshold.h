#ifndef BINARY_THRESHOLD_H
#define BINARY_THRESHOLD_H
#include "cbmp.h"

#define THRESHOLD 90

void binaryThreshold(unsigned char (*in_image_buffer)[BMP_HEIGTH],
                     unsigned char (*out_image_buffer)[BMP_HEIGTH]);
#endif