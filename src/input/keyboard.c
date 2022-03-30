#include "hv.h"

void handle_keydown_event(STATE *state, SDL_KeyboardEvent event) {
  if (event.keysym.scancode == SDL_SCANCODE_GRAVE)
    state->display_debug_values = !state->display_debug_values;
}