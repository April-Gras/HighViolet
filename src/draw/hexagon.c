#include "hv.h"

SDL_Point get_hexagon_point_from_index(int radius, int x, int y, int i) {
  double angle_deg = (double)i * 60.0 - 30.0;
  double angle_rad = angle_deg * M_PI / 180.00;

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
  int r = 0;
  int horizontal_spacing = sqrt(3) * radius;
  int vertical_spacing = 2.0 * radius * (3.0 / 4.0);

  while (r <= R_LENGTH) {
    int q = 0;
    int row_size = get_map_row_size(r);
    int x_row_offset = (horizontal_spacing / 2) * r;

    while (q < row_size) {
      TILE hex = state->map[r][q];
      int x = hex.axial_coord.q * horizontal_spacing + start_x + x_row_offset;
      int y = hex.axial_coord.r * vertical_spacing + start_y;
      bool is_hovered = hex.is_hovered;
      bool is_focused = hex.is_focused;

      if (is_hovered && !is_focused)
        SDL_SetRenderDrawColor(state->renderer, 0x00, 0xFF, 0x00, 0xFF);
      if (is_focused)
        SDL_SetRenderDrawColor(state->renderer, 0x00, 0x00, 0xFF, 0xFF);
      draw_hexagon(radius, x, y, state);
      if (is_hovered || is_focused)
        SDL_SetRenderDrawColor(state->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
      q++;
    }
    r++;
  }
}
