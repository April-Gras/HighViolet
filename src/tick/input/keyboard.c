#include "hv.h"

void handle_input_keyboard_tick(STATE *state) {
  const int camera_offset = 5;
  const Uint8 *keyboard_state = SDL_GetKeyboardState(NULL);

  if (keyboard_state[SDL_SCANCODE_A])
    state->camera->x += camera_offset;
  if (keyboard_state[SDL_SCANCODE_D])
    state->camera->x -= camera_offset;
  if (keyboard_state[SDL_SCANCODE_W])
    state->camera->y += camera_offset;
  if (keyboard_state[SDL_SCANCODE_S])
    state->camera->y -= camera_offset;
}