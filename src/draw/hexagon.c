#include "hv.h"

SDL_Point get_hexagon_point_from_index(int radius, int x, int y, int i) {
  double angle_rad = (double)i * 60.0 * M_PI / 180.00;

  return (SDL_Point){x + radius * cos(angle_rad), y + radius * sin(angle_rad)};
}

void draw_hexagon(int radius, int x, int y, STATE *state) {
  SDL_Point point_collection[7];

  for (int i = 0; i < 6; i++)
    point_collection[i] = get_hexagon_point_from_index(radius, x, y, i);
  point_collection[6] = point_collection[0];
  SDL_RenderDrawLines(state->renderer, point_collection, 7);
}

void draw_map_from_tile_list(int radius, int start_x, int start_y,
                             STATE *state) {
  TILE_LIST *swap = state->map;
  int y_jump = sqrt(3) * radius;
  int half_y_jump = y_jump / 2;
  int x_jump = (double)(radius * 2) * (double)(3.0 / 4.0);
  int row = 0;
  int col = 0;
  int row_y = start_y;
  int y = start_y;
  int x = start_x;

  while (swap) {
    draw_hexagon(radius, x, y, state);
    swap = swap->next;
    x += x_jump;
    y += col % 2 ? -half_y_jump : half_y_jump;
    if (col >= MAP_WIDTH - 1) {
      x = start_x;
      row_y += y_jump;
      y = row_y;
      col = 0;
      row++;
    } else
      col++;
  }
}