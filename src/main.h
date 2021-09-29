#ifndef MAIN_H
#define MAIN_H

#include "cbmp.h"
#include "cell_detection.h"
#include "env.h"
#include "erosion.h"
#include "image_processing.h"
#include "mark_cells.h"
#include "rgb_gray_conversion.h"
#include "threshold.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "compression.h"

#define MAX_CELL_COUNT 500

void print_results(unsigned short (*list)[2], short size);
void convert_to_binary(unsigned char (*out_image_buffer)[BMP_HEIGTH / 8 + 1]);

#endif