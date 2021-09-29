#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include "cbmp.h"
#define DETECTION_FRAME 14

int _exclusion(short x, short y,
               unsigned char (*in_image_buffer)[BMP_HEIGTH / 8 + 1]);
int _detection(short x, short y,
               unsigned char (*in_image_buffer)[BMP_HEIGTH / 8 + 1]);
void _whipeCell(short x, short y,
                unsigned char (*out_image_buffer)[BMP_HEIGTH / 8 + 1]);
void _getXandYmaxmin(short x, short y, short *xmin, short *xmax,
                     short *ymin, short *ymax);

#endif