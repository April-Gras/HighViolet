#include "hv.h"

SDL_Point get_hexagon_point_from_index(int radius, int x, int y, int i) {
  return (SDL_Point){x + radius * cos((double)i * 60.0 * M_PI / 180.00),
                     y + radius * sin((double)i * 60.0 * M_PI / 180.00)};
}

void draw_hexagon(int radius, int x, int y, STATE *state) {
  SDL_Point point_collection[7];

  for (int i = 0; i < 6; i++)
    point_collection[i] = get_hexagon_point_from_index(radius, x, y, i);
  point_collection[6] = get_hexagon_point_from_index(radius, x, y, 6);
  SDL_RenderDrawLines(state->renderer, point_collection, 7);
}

void draw_map_from_tile_list(int radius, int start_x, int start_y,
                             STATE *state) {
  TILE_LIST *swap = state->map;
  int diameter = radius * 2;
  int map_pixel_wdth = MAP_WIDTH * diameter;
  int row = 0;
  int col = 0;
  int row_y = start_y;
  int y = start_y;
  int x = start_x;

  while (swap) {
    draw_hexagon(radius, x, y, state);
    swap = swap->next;
    x += diameter;
    y += col % 2 ? -radius : radius;
    if (x >= map_pixel_wdth) {
      x = start_x;
      row_y += diameter;
      y = row_y;
      col = 0;
      row++;
    }
    col++;
  }
}