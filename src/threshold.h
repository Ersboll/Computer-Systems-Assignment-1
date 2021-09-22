#ifndef THRESHOLD_H
#define THRESHOLD_H
#include "cbmp.h"
#include "env.h"
#include <string.h>

#if DEBUGGING
#include <stdio.h>
#endif

#define BINARY_THRESHOLD_VALUE 90
#define HISTOGRAM_SIZE 256

void binary_threshold(unsigned char (*in_image_buffer)[BMP_HEIGTH],
                      unsigned char (*out_image_buffer)[BMP_HEIGTH]);

unsigned char _otsu(unsigned char (*in_image_buffer)[BMP_HEIGTH]);
unsigned char _maximum_deviation(unsigned char (*in_image_buffer)[BMP_HEIGTH]);

#endif