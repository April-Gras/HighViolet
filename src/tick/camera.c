#include "hv.h"

#define CAMERA_PADDING 50
void handle_camera_tick(STATE *state) {
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