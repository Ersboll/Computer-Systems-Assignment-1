#ifndef COMPRESSION_H
#define COMPRESSION_H

#include "cbmp.h"

void compressBinaryImage(
    unsigned char (*in_image_buffer)[BMP_HEIGTH],
    unsigned char (*out_image_buffer)[BMP_HEIGTH / 8]);

unsigned char getValue(
    unsigned char (*compressedImage)[BMP_HEIGTH / 8],
    unsigned char index1,
    unsigned char index2);

void setValue(
    unsigned char (*compressedImage)[BMP_HEIGTH / 8],
    unsigned char index1,
    unsigned char index2,
    unsigned char value);

#endif