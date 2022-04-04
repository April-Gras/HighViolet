#pragma once

#include "SDL_stdinc.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 720

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAP_SIZE 3
#define R_LENGTH MAP_SIZE * 2

// Math Utils
int imin(int a, int b);
int imax(int a, int b);
double lerp(double a, double b, double t);
typedef enum E_HIGH_VIOLET_ERROR {
  HV_SDL_surface_init_failure = 0,
  HV_SDL_window_init_failure = 1,
  HV_SDL_sytems_init_failure = 2,
  HV_SDL_rendererr_init_failure = 3,
  HV_SDL_mouse_trap_failed = 4,
  HV_TTF_system_failed_init = 5,
  HV_TTF_sans_font_load_failed = 6,
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
typedef struct S_TILE {
  bool is_hovered;
  bool is_focused;

  AXIAL_COORD axial_coord;
  CUBE_COORD cube_coord;
} TILE;
typedef struct S_TILE_LIST {
  TILE tile;

  struct S_TILE_LIST *next;
} TILE_LIST;
typedef struct S_TILE_COLLECTION {
  TILE *array;
  int length;
} TILE_COLLECTION;

typedef struct S_ENGINE_TIMERS {
  int last_frame_time_stamp;
  int new_frame_time_stamp;
  int ellapsed_milliseconds;
} ENGINE_TIMERS;

typedef struct S_MOUSE {
  Sint32 x;
  Sint32 y;
  Sint32 scroll_y;
  bool left_click;
  bool right_click;
  bool middle_click;
} MOUSE;

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
  TILE **map;
  SDL_Window *window;
  CAMERA *camera;
  SDL_Renderer *renderer;
  ENGINE_TIMERS *timers;
  MOUSE *mouse;
  TILE *hover_reset_target;
  TILE *focus_reset_target;
  bool is_still_running;
  bool display_debug_values;
  TTF_Font *font_sans;
} STATE;

// coord/debug
void print_cube_coord(CUBE_COORD coord);
// coord/utils
CUBE_COORD cube_round(double fract_q, double fract_r, double fract_s);
AXIAL_COORD cube_to_axial(CUBE_COORD coord);
CUBE_COORD axial_to_cube(AXIAL_COORD coord);
AXIAL_COORD axial_round(double r, double q);
bool axial_coord_equals(AXIAL_COORD a, AXIAL_COORD b);
bool cube_coord_equals(CUBE_COORD a, CUBE_COORD b);
CUBE_COORD cube_substract(CUBE_COORD a, CUBE_COORD b);
int cube_distance(CUBE_COORD a, CUBE_COORD b);
CUBE_COORD cube_lerp_and_round(CUBE_COORD a, CUBE_COORD b, double t);

// tile/memory
TILE **new_map();
TILE new_map_tile(int q, int r);
void destroy_tile_map(TILE **map);
int get_map_row_size(int r);
int get_q_index_from_axial_coord(AXIAL_COORD coord);
// tile/generation
TILE **generate_tile_list_map();
// tile/list
TILE_LIST *tile_list_push(TILE_LIST **tile_list);
// tile/line
TILE_COLLECTION get_tile_line_from_extremities(TILE *a, TILE *b, STATE *state);

// engine_timers/memory
ENGINE_TIMERS *new_engine_timers();
void destroy_engine_timers(ENGINE_TIMERS *timers);

// mouse/memory
MOUSE *new_mouse();
void destroy_mouse();
// input/mouse
void handle_mouse_whell_event(MOUSE *mouse, SDL_MouseWheelEvent event);
void handle_mouse_motion_event(MOUSE *mouse, SDL_MouseMotionEvent event);
void handle_mouse_button_event(MOUSE *mouse, SDL_MouseButtonEvent event);
AXIAL_COORD mouse_to_hexa_axial_coord(MOUSE *mouse, double radius);

// state/memory
STATE *init_state();
void destroy_state(STATE *state);

// input/keyboard
void handle_keydown_event(STATE *state, SDL_KeyboardEvent event);

// DRAW CALLS
// hexagons
void draw_hexagon(int radius, int x, int y, STATE *state);
void draw_map_from_tile_list(int radius, int x, int y, STATE *state);

// --- //

// TICK CALLS
// input/mouse
void handle_input_mouse_tick(STATE *state);
// camera
void handle_camera_tick(STATE *state);

// DEBUG
void _print_debug_infos_on_screen(STATE *state);