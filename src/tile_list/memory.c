#include "hv.h"

TILE_LIST *new_tile_list() {
  TILE_LIST *new_tile_list = (TILE_LIST *)malloc(sizeof(TILE_LIST));

  new_tile_list->is_focused = false;
  new_tile_list->is_hovered = false;

  new_tile_list->prev = NULL;
  new_tile_list->next = NULL;

  // TODO init coord systems
  new_tile_list->axial_coord = (AXIAL_COORD){0, 0};
  new_tile_list->cube_coord = (CUBE_COORD){0, 0};
  return new_tile_list;
}

void destroy_tile_list(TILE_LIST *start) {
  TILE_LIST *swap;

  while (start != NULL) {
    swap = start->next;
    free(start);
    start = swap;
  }
}

void tile_list_push(TILE_LIST **tile_list) {
  if (*tile_list == NULL) {
    *tile_list = new_tile_list();
  } else {
    TILE_LIST *swap = *tile_list;

    while (swap->next != NULL)
      swap = swap->next;
    swap->next = new_tile_list();
    swap->next->prev = swap;
  }
}