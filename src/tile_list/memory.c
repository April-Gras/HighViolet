#include "hv.h"

TILE_LIST *new_tile_list() {
  TILE_LIST *new_tile_list = (TILE_LIST *)malloc(sizeof(TILE_LIST));

  new_tile_list->prev = NULL;
  new_tile_list->next = NULL;

  new_tile_list->top = NULL;
  new_tile_list->top_right = NULL;
  new_tile_list->bottom_right = NULL;
  new_tile_list->bottom = NULL;
  new_tile_list->bottom_left = NULL;
  new_tile_list->top_left = NULL;
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