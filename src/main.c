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
  case SDL_MOUSEWHEEL:
    handle_mouse_whell_event(state->mouse, event->wheel);
  }
}

void draw(STATE *state) {
  SDL_SetRenderDrawColor(state->renderer, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderClear(state->renderer);
  SDL_SetRenderDrawColor(state->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  int value = state->camera->z;
  draw_map_from_tile_list(value, 50, 50, state);
  SDL_RenderPresent(state->renderer);
}

void game_loop(STATE *state) {
  state->timers->last_frame_time_stamp = SDL_GetTicks();
  state->is_still_running = true;

  while (state->is_still_running) {
    SDL_Event event;

    // Reset mouse scroll
    state->mouse->scroll_y = 0;
    while (SDL_PollEvent(&event)) { // poll until all events are handled!
      handle_SDL_event(&event, state);
    }
    printf("%i\n", state->mouse->scroll_y);
    change_camera_zoom(state->mouse->scroll_y, state->camera);
    draw(state);
  }
}

int main(int argc, char **argv) {
  STATE *state = init_state();
  game_loop(state);
  destroy_state(state);
  return 0;
}
