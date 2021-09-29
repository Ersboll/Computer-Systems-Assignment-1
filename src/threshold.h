#ifndef THRESHOLD_H
#define THRESHOLD_H
#include "cbmp.h"
#include "env.h"
#include <string.h>

#if DEBUGGING
#include <stdio.h>
#endif

void binary_threshold(unsigned char (*in_image_buffer)[BMP_HEIGTH],
                      unsigned char (*out_image_buffer)[BMP_HEIGTH]);

unsigned char _otsu(unsigned char (*in_image_buffer)[BMP_HEIGTH]);
unsigned char _maximum_deviation(unsigned char (*in_image_buffer)[BMP_HEIGTH]);
void _compute_histogram(unsigned int *histogram,
                        unsigned char (*in_image_buffer)[BMP_HEIGTH]);

#endif