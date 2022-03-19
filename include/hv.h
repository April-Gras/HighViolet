#pragma once

#include "SDL_stdinc.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#include <SDL2/SDL.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAP_WIDTH 8
#define MAP_HEIGHT 8

typedef enum E_HIGH_VIOLET_ERROR {
  HV_SDL_surface_init_failure = 0,
  HV_SDL_window_init_failure = 1,
  HV_SDL_sytems_init_failure = 2,
  HV_SDL_rendererr_init_failure = 3,
  HV_SDL_mouse_trap_failed = 4,
} HIGHT_VIOLET_ERR_NO;

typedef struct S_CUBE_COORD {
  int q;
  int r;
  int s;
} CUBE_COORD;

typedef struct S_AXIAL_COORD {
  int q;
  int r;
} AXIAL_COORD;

typedef struct S_TILE_LIST {
  // state
  bool is_hovered;
  bool is_focused;

  // Classic linking
  struct S_TILE_LIST *prev;
  struct S_TILE_LIST *next;

  // Coord systems
  AXIAL_COORD axial_coord;
  CUBE_COORD cube_coord;

} TILE_LIST;
// Memory
void tile_list_push(TILE_LIST **tile_list);
void destroy_tile_list(TILE_LIST *start);
// Generation
void generate_tile_list_map(TILE_LIST **start, int width, int height);

typedef struct S_ENGINE_TIMERS {
  int last_frame_time_stamp;
  int new_frame_time_stamp;
  int ellapsed_milliseconds;
} ENGINE_TIMERS;
// Memory
ENGINE_TIMERS *new_engine_timers();
void destroy_engine_timers(ENGINE_TIMERS *timers);

typedef struct S_MOUSE {
  Sint32 x;
  Sint32 y;
  Sint32 scroll_y;
  bool left_click;
  bool right_click;
  bool middle_click;
} MOUSE;
// Memory
MOUSE *new_mouse();
void destroy_mouse();
void handle_mouse_whell_event(MOUSE *mouse, SDL_MouseWheelEvent event);
void handle_mouse_motion_event(MOUSE *mouse, SDL_MouseMotionEvent event);
void handle_mouse_button_event(MOUSE *mouse, SDL_MouseButtonEvent event);

typedef struct S_CAMERA {
  int x;
  int y;
  int z;
} CAMERA;
// Memory
CAMERA *new_camera();
void destroy_camera(CAMERA *camera);
// Manipulate
void change_camera_zoom(int zoom_addition, CAMERA *camera);
void change_camera_position(int x, int y, CAMERA *camera);

typedef struct S_STATE {
  TILE_LIST *map;
  SDL_Window *window;
  CAMERA *camera;
  SDL_Renderer *renderer;
  ENGINE_TIMERS *timers;
  MOUSE *mouse;
  bool is_still_running;
} STATE;
// Memory
STATE *init_state();
void destroy_state(STATE *state);

// Draw calls
void draw_hexagon(int radius, int x, int y, STATE *state);
void draw_map_from_tile_list(int radius, int x, int y, STATE *state);