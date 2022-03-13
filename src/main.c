#include "hv.h"

void handle_SDL_event(SDL_Event *event, STATE *state) {
  switch (event->type) {
  case SDL_WINDOWEVENT:
    switch (event->window.event) {
    case SDL_WINDOWEVENT_CLOSE:
      state->is_still_running = false;
      break;
    }
    break;
  case SDL_MOUSEMOTION:
    handle_mouse_motion_event(state->mouse, event->motion);
    break;
  case SDL_MOUSEBUTTONDOWN:
    handle_mouse_button_event(state->mouse, event->button);
    break;
  case SDL_MOUSEBUTTONUP:
    handle_mouse_button_event(state->mouse, event->button);
    break;
  }
}

void game_loop(STATE *state) {
  state->timers->last_frame_time_stamp = SDL_GetTicks();
  state->is_still_running = true;

  while (state->is_still_running) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) { // poll until all events are handled!
      handle_SDL_event(&event, state);
    }
    SDL_FillRect(state->surface, NULL,
                 SDL_MapRGB(state->surface->format, 0x00, 0x00, 0x00));
    SDL_Rect rect;
    rect.w = 64;
    rect.h = 64;
    rect.x = state->mouse->x;
    rect.y = state->mouse->y;
    SDL_FillRect(state->surface, &rect,
                 SDL_MapRGB(state->surface->format,
                            state->mouse->left_click ? 0xFF : 0x25,
                            state->mouse->middle_click ? 0xFF : 0x25,
                            state->mouse->right_click ? 0xFF : 0x25));
    SDL_UpdateWindowSurface(state->window);
  }
}

int main(int argc, char **argv) {
  STATE *state = init_state();
  game_loop(state);
  destroy_state(state);
  return 0;
}