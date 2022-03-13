#include "hv.h"

TILE_LIST *get_tile_at_index(int index, TILE_LIST *start) {
  TILE_LIST *swap = start;

  for (int i = 0; i < index; i++) {
    // If it crashes then I'm just a brainlet
    // I should just fix the actual logic the uses this
    swap = swap->next;
  }
  return swap;
}

// Up -2width
// Down 2width
//
// Top-right -width + 1
// Top-left -width
//
// Bottom-right width
// Bottom-left width - 1
void link_cell(int x, int y, int width, int height, TILE_LIST *current_tile,
               TILE_LIST *start) {
  // Bind to top top-left and top-right
  int current_index = x * width;
  if (y != 0) {
    if (y > 1)
      current_tile->top = get_tile_at_index(current_index - 2 * width, start);
    if (x > 0)
      current_tile->top_left = get_tile_at_index(current_index - width, start);
    if (x < width)
      current_tile->top_right =
          get_tile_at_index(current_index - width + 1, start);
  }
  if (y != height) {
    if (y < height - 1)
      current_tile->bottom =
          get_tile_at_index(current_index + 2 * width, start);
    if (y > 0)
      current_tile->bottom_left =
          get_tile_at_index(current_index + width - 1, start);
    if (y < height)
      current_tile->bottom_right =
          get_tile_at_index(current_index + width - 1, start);
  }
}

void generate_tile_list_map(TILE_LIST **start, int width, int height) {
  int totalMembers = width * height;
  int x = 0;
  int y = 0;
  TILE_LIST *swap;

  for (int i = 0; i < totalMembers; i++)
    tile_list_push(start);
  swap = *start;
  while (swap) {
    link_cell(x, y, width, height, swap, *start);
    x++;
    if (x == width - 1) {
      x = 0;
      y++;
    }
    swap = swap->next;
  }
}

void destroy_tile_list_map() {}
