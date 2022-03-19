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
  draw_map_from_tile_list(value, value + state->camera->x,
                          value + state->camera->y, state);
  SDL_RenderPresent(state->renderer);
}

#define CAMERA_PADDING 50
void handle_camera(STATE *state) {
  int x = state->mouse->x;
  int y = state->mouse->y;

  if (x < CAMERA_PADDING)
    change_camera_position(1, 0, state->camera);
  if (y < CAMERA_PADDING)
    change_camera_position(0, 1, state->camera);
  if (x > SCREEN_WIDTH - CAMERA_PADDING)
    change_camera_position(-1, 0, state->camera);
  if (y > SCREEN_HEIGHT - CAMERA_PADDING)
    change_camera_position(0, -1, state->camera);
  change_camera_zoom(state->mouse->scroll_y, state->camera);
}

void game_loop(STATE *state) {
  state->timers->last_frame_time_stamp = SDL_GetTicks();
  state->is_still_running = true;

  while (state->is_still_running) {
    SDL_Event event;

    // Reset mouse scroll //
    state->mouse->scroll_y = 0;

    // poll until all events are handled! //
    while (SDL_PollEvent(&event)) {
      handle_SDL_event(&event, state);
    }

    // Logic //
    handle_camera(state);

    // Draw //
    draw(state);
  }
}

int main(int argc, char **argv) {
  STATE *state = init_state();
  game_loop(state);
  destroy_state(state);
  return 0;
}
