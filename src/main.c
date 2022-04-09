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
    break;
  case SDL_KEYDOWN:
    handle_keydown_event(state, event->key);
    break;
  }
}

void draw(STATE *state) {
  SDL_SetRenderDrawColor(state->renderer, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderClear(state->renderer);
  SDL_SetRenderDrawColor(state->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  int value = state->camera->z;
  draw_map_from_tile_list(value, state->camera->x, state->camera->y, state);
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

    // Input Logic
    // handle_camera_tick(state);
    handle_input_mouse_tick(state);
    handle_input_keyboard_tick(state);

    // Internal Logic //
    // If we got focuesed and hovered
    if (state->focus_reset_target != NULL &&
        state->hover_reset_target != NULL) {
      TILE_COLLECTION collection = get_tile_line_from_extremities(
          state->focus_reset_target, state->hover_reset_target, state);

      for (int i = 0; i < collection.length; i++) {
        print_cube_coord(collection.array[i].cube_coord);
      }
      if (collection.array)
        free(collection.array);
      putchar('\n');
    }

    // Draw //
    draw(state);
    _print_debug_infos_on_screen(state);
    SDL_RenderPresent(state->renderer);
    engine_timer_update(state->timers);
  }
}

int main(int argc, char **argv) {
  STATE *state = init_state();

  game_loop(state);
  destroy_state(state);
  return 0;
}
