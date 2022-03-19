#include "hv.h"

void generate_tile_list_map(TILE_LIST **start, int width, int height) {
  int totalMembers = width * height;

  for (int i = 0; i < totalMembers; i++)
    tile_list_push(start);
  // TODO correctly link that shit
}

void destroy_tile_list_map() {}
