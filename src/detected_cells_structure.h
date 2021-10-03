#ifndef DETECTED_CELLS_STRUCTURE_H
#define DETECTED_CELLS_STRUCTURE_H

#include <stdlib.h>

#define MAX_CELL_COUNT 500
#define START_CELL_COUNT 300
#define CELL_COUNT_STEP 10

typedef struct {
  unsigned short (*list)[2];
  unsigned short capacity;
  unsigned short count;
} cell_list_t;

cell_list_t *initialize_cell_list();

void destroy_cell_list(cell_list_t *cell_list);

int add_cell_to_list(cell_list_t *cell_list, unsigned short x,
                     unsigned short y);

#endif