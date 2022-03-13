#pragma once

#include "SDL_stdinc.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#include <SDL2/SDL.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum E_HIGH_VIOLET_ERROR {
  SDL_surface_init_failure,
  SDL_window_init_failure,
  SDL_sytems_init_failure,
  SDL_gamepad_submodule_init_failure,
} HIGHT_VIOLET_ERR_NO;

typedef struct S_VECTOR_2D {
  float x;
  float y;
} VECTOR_2D;

typedef struct S_TILE_LIST {
  struct S_TILE_LIST *prev;
  struct S_TILE_LIST *next;

  struct S_TILE_LIST *top;
  struct S_TILE_LIST *top_right;
  struct S_TILE_LIST *bottom_right;
  struct S_TILE_LIST *bottom;
  struct S_TILE_LIST *bottom_left;
  struct S_TILE_LIST *top_left;
} TILE_LIST;

typedef struct S_Input {
  VECTOR_2D direction; // all values should be normalized between -1.0 and 1.0
  bool action;
  SDL_GameController *controller;
} Input;
Input *new_input();
void destroy_input(Input *input);
void update_input(Input *input, SDL_Event *event);
void detect_controlers(Input *input, SDL_Event *event);
void try_and_find_controller(Input *input);

void tile_list_push(TILE_LIST **tile_list);
void destroy_tile_list(TILE_LIST *start);

void generate_tile_list_map(TILE_LIST **start, int width, int height);

typedef struct S_ENGINE_TIMERS {
  int last_frame_time_stamp;
  int new_frame_time_stamp;
  int ellapsed_milliseconds;
} ENGINE_TIMERS;
ENGINE_TIMERS *new_engine_timers();
void destroy_engine_timers(ENGINE_TIMERS *timers);

typedef struct S_MOUSE {
  Sint32 x;
  Sint32 y;
  bool left_click;
  bool right_click;
  bool middle_click;
} MOUSE;
MOUSE *new_mouse();
void destroy_mouse();
void handle_mouse_motion_event(MOUSE *mouse, SDL_MouseMotionEvent event);
void handle_mouse_button_event(MOUSE *mouse, SDL_MouseButtonEvent event);

typedef struct S_STATE {
  TILE_LIST *map;
  SDL_Window *window;
  SDL_Surface *surface;
  ENGINE_TIMERS *timers;
  MOUSE *mouse;
  bool is_still_running;
} STATE;

STATE *init_state();
void destroy_state(STATE *state);