#include "hv.h"

void destroy_state(STATE *state) {
  if (state->map)
    destroy_tile_map(state->map);
  if (state->mouse)
    destroy_mouse(state->mouse);
  if (state->timers)
    destroy_engine_timers(state->timers);
  if (state->renderer)
    SDL_DestroyRenderer(state->renderer);
  if (state->window)
    SDL_DestroyWindow(state->window);
  if (state->camera)
    destroy_camera(state->camera);
  SDL_Quit();
  free(state);
}

void gracefully_exit_and_destroy_state(STATE *state, int error_number) {
  destroy_state(state);
  exit(error_number);
}

void init_SDL_systems(STATE *s) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
    gracefully_exit_and_destroy_state(s, HV_SDL_sytems_init_failure);
  }
  if (SDL_SetRelativeMouseMode(SDL_TRUE)) {
    fprintf(stderr, "mouse trap failed :< %s\n", SDL_GetError());
    gracefully_exit_and_destroy_state(s, HV_SDL_mouse_trap_failed);
  }
}

SDL_Window *new_SDL_window(STATE *s) {
  SDL_Window *window = SDL_CreateWindow("hight_violet", SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                        SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    fprintf(stderr, "could not create window: %s\n", SDL_GetError());
    gracefully_exit_and_destroy_state(s, HV_SDL_window_init_failure);
  }
  return window;
}

SDL_Renderer *new_SDL_renderer(STATE *s) {
  SDL_Renderer *renderer =
      SDL_CreateRenderer(s->window, -1, SDL_RENDERER_ACCELERATED);

  if (renderer == NULL) {
    fprintf(stderr, "could not create SDL renderer: %s\n", SDL_GetError());
    gracefully_exit_and_destroy_state(s, HV_SDL_rendererr_init_failure);
  }
  return renderer;
}

STATE *new_state() {
  STATE *state = (STATE *)malloc(sizeof(STATE));

  state->window = NULL;
  state->map = NULL;
  state->mouse = NULL;
  state->timers = NULL;
  state->renderer = NULL;
  state->is_still_running = false;
  state->camera = NULL;
  return state;
}

STATE *init_state() {
  STATE *state = new_state();

  // Initialize internal systems
  state->map = new_map();
  state->timers = new_engine_timers();
  state->camera = new_camera();
  state->mouse = new_mouse();

  // Initialize SDL systems
  state->window = new_SDL_window(state);
  state->renderer = new_SDL_renderer(state);
  return state;
}