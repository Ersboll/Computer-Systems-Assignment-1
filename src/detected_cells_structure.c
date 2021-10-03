#include "detected_cells_structure.h"

cell_list_t *initialize_cell_list() {
  cell_list_t *cell_list = malloc(sizeof *cell_list);
  if (!cell_list)
    return 0;

  cell_list->capacity = START_CELL_COUNT;
  cell_list->count = 0;
  cell_list->list = calloc(START_CELL_COUNT, sizeof(cell_list->list));
  if (!cell_list->list) {
    free(cell_list);
    return 0;
  }

  return cell_list;
}

int add_cell_to_list(cell_list_t *cell_list, unsigned short x,
                     unsigned short y) {
  if (cell_list->count == cell_list->capacity) {
    unsigned short new_capacity = cell_list->capacity + CELL_COUNT_STEP;
    unsigned short(*new_list)[2] =
        realloc(cell_list->list, new_capacity * sizeof(*new_list));
    if (!new_list)
      return 0;
    cell_list->capacity = new_capacity;
    cell_list->list = new_list;
  }

  cell_list->list[cell_list->count][0] = x;
  cell_list->list[cell_list->count][1] = y;
  cell_list->count++;

  return 1;
}

void destroy_cell_list(cell_list_t *cell_list) {
  if (!cell_list)
    return;
  free(cell_list->list);
  free(cell_list);
}