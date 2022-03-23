#include "hv.h"

void handle_input_mouse_tick(STATE *state) {
  AXIAL_COORD potencial_hex_hover =
      mouse_to_hexa_axial_coord(state->mouse, (double)state->camera->z);

  for (int r = 0; r <= R_LENGTH; r++) {
    int row_size = get_map_row_size(r);
    for (int q = 0; q < row_size; q++)
      if (axial_coord_equals(state->map[r][q].axial_coord, potencial_hex_hover))
        state->map[r][q].is_hovered = true;
  }
}