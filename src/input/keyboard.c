#include "hv.h"

void handle_keydown_event(STATE *state, SDL_KeyboardEvent event) {
  switch (event.keysym.scancode) {
  case SDL_SCANCODE_GRAVE:
    state->display_debug_values = !state->display_debug_values;
    break;
  case SDL_SCANCODE_ESCAPE:
    gracefully_exit_and_destroy_state(state, 0);
    break;
  }
}