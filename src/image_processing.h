#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include "cbmp.h"
#include <stdio.h>
#define THRESHOLD 90
#define DETECTION_FRAME 14

void rgb2gray(unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS],
              unsigned char (*out_image_buffer)[BMP_HEIGTH]);
void gray2rgb(unsigned char (*in_image_buffer)[BMP_HEIGTH],
              unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS]);
void binaryThreshold(unsigned char (*in_image_buffer)[BMP_HEIGTH],
                     unsigned char (*out_image_buffer)[BMP_HEIGTH]);
int erosion(unsigned char (*in_image_buffer)[BMP_HEIGTH],
            unsigned char (*out_image_buffer)[BMP_HEIGTH]);
int detectCells(unsigned char (*in_image_buffer)[BMP_HEIGTH],
                unsigned char (*out_image_buffer)[BMP_HEIGTH],
                unsigned short int (*list_buffer)[2]);
void markCells(unsigned short int detected_cells[103][2],
               unsigned short int number_of_cells,
               unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS],
               unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS]);
int _exclusion(short int x, short int y,
               unsigned char (*in_image_buffer)[BMP_HEIGTH]);
int _detection(short int x, short int y,
               unsigned char (*in_image_buffer)[BMP_HEIGTH]);
void _whipeCell(short int x, short int y,
                unsigned char (*out_image_buffer)[BMP_HEIGTH]);
void _getXandYmaxmin(short int x, short int y, short int *xmin, short int *xmax,
                     short int *ymin, short int *ymax);

#endif