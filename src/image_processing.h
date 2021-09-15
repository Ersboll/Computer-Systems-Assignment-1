#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include "cbmp.h"
#define DETECTION_FRAME 14

int _exclusion(short int x, short int y,
               unsigned char (*in_image_buffer)[BMP_HEIGTH]);
int _detection(short int x, short int y,
               unsigned char (*in_image_buffer)[BMP_HEIGTH]);
void _whipeCell(short int x, short int y,
                unsigned char (*out_image_buffer)[BMP_HEIGTH]);
void _getXandYmaxmin(short int x, short int y, short int *xmin, short int *xmax,
                     short int *ymin, short int *ymax);

#endif