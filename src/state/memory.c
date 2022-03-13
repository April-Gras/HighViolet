#include "hv.h"

#define MAP_WIDTH 8
#define MAP_HEIGHT 8

void destroy_state(STATE *state) {
  if (state->map)
    destroy_tile_list(state->map);
  if (state->mouse)
    destroy_mouse(state->mouse);
  if (state->timers)
    destroy_engine_timers(state->timers);
  free(state);
}

void gracefully_exit_and_destroy_state(STATE *state, int error_number) {
  destroy_state(state);
  exit(error_number);
}

void init_SDL_systems(STATE *s) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
    gracefully_exit_and_destroy_state(s, SDL_sytems_init_failure);
  }
}

SDL_Window *new_SDL_window(STATE *s) {
  SDL_Window *window = SDL_CreateWindow("hight_violet", SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                        SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    fprintf(stderr, "could not create window: %s\n", SDL_GetError());
    gracefully_exit_and_destroy_state(s, SDL_window_init_failure);
  }
  return window;
}

SDL_Surface *new_SDL_surface(STATE *s) {
  SDL_Surface *surface = SDL_GetWindowSurface(s->window);

  if (surface == NULL) {
    fprintf(stderr, "could not create windows surface: %s\n", SDL_GetError());
    gracefully_exit_and_destroy_state(s, SDL_surface_init_failure);
  }
  return surface;
}

STATE *new_state() {
  STATE *state = (STATE *)malloc(sizeof(STATE));

  state->window = NULL;
  state->surface = NULL;
  state->map = NULL;
  state->mouse = NULL;
  state->timers = NULL;
  state->is_still_running = false;
  return state;
}

STATE *init_state() {
  STATE *state = new_state();
  TILE_LIST *map = NULL;

  generate_tile_list_map(&map, MAP_WIDTH, MAP_HEIGHT);
  state->map = map;
  state->window = new_SDL_window(state);
  state->surface = new_SDL_surface(state);
  state->timers = new_engine_timers();
  state->mouse = new_mouse();
  return state;
}