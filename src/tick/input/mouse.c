#include "hv.h"

void reset_last_hover_target(STATE *state) {
  if (state->hover_reset_target == NULL)
    return;

  state->hover_reset_target->is_hovered = false;
  state->hover_reset_target = NULL;
}

void handle_hover_tick(TILE *target_tile, STATE *state) {
  target_tile->is_hovered = true;
  state->hover_reset_target = target_tile;
}

void reset_last_focus_target(STATE *state) {
  if (state->focus_reset_target == NULL || !state->mouse->left_click)
    return;
  state->focus_reset_target->is_focused = false;
  state->focus_reset_target = NULL;
}

void handle_focus_tick(TILE *target_tile, STATE *state) {
  if (!state->mouse->left_click)
    return;
  reset_last_focus_target(state);
  target_tile->is_focused = true;
  state->focus_reset_target = target_tile;
}

void handle_input_mouse_tick(STATE *state) {
  AXIAL_COORD potencial_hex_hover =
      mouse_to_hexa_axial_coord(state->mouse, (double)state->camera->z);

  reset_last_hover_target(state);

  // Look for matching hex to the current position of the pointer
  for (int r = 0; r <= R_LENGTH; r++) {
    int row_size = get_map_row_size(r);

    for (int q = 0; q < row_size; q++) {
      AXIAL_COORD target_coord = state->map[r][q].axial_coord;
      if (axial_coord_equals(target_coord, potencial_hex_hover)) {
        // Target hex has been found, apply actions
        TILE *pointer = &state->map[r][q];
        handle_hover_tick(pointer, state);
        handle_focus_tick(pointer, state);
        return;
      }
    }
  }

  // If no target hex has been found
  reset_last_focus_target(state);
  return;
}