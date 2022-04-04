#include "hv.h"

TILE_LIST *new_raw_tile_list() {
  TILE_LIST *new_tile_list = (TILE_LIST *)malloc(sizeof(TILE_LIST));

  new_tile_list->next = NULL;
  new_tile_list->tile = new_map_tile(0, 0);
}

TILE_LIST *tile_list_push(TILE_LIST **tile_list) {
  if (*tile_list == NULL) {
    *tile_list = new_raw_tile_list();
    return *tile_list;
  } else {
    TILE_LIST *swap = *tile_list;

    while (swap->next)
      swap = swap->next;
    swap->next = new_raw_tile_list();
    return swap->next;
  }
}