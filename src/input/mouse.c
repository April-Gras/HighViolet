#include "hv.h"

void handle_mouse_whell_event(MOUSE *mouse, SDL_MouseWheelEvent event) {
  mouse->scroll_y = event.y;
}

void handle_mouse_motion_event(MOUSE *mouse, SDL_MouseMotionEvent event) {
  mouse->x = event.x;
  mouse->y = event.y;
}

void handle_mouse_button_event(MOUSE *mouse, SDL_MouseButtonEvent event) {
  bool assign_value = event.state == SDL_PRESSED;

  switch (event.button) {
  case SDL_BUTTON_RIGHT:
    mouse->right_click = assign_value;
    break;
  case SDL_BUTTON_LEFT:
    mouse->left_click = assign_value;
    break;
  case SDL_BUTTON_MIDDLE:
    mouse->middle_click = assign_value;
    break;
  }
}

MOUSE *new_mouse() {
  MOUSE *mouse = (MOUSE *)malloc(sizeof(MOUSE));

  mouse->left_click = false;
  mouse->middle_click = false;
  mouse->right_click = false;
  mouse->x = 0;
  mouse->y = 0;
  mouse->scroll_y = 0;
  return mouse;
}

AXIAL_COORD mouse_to_hexa_axial_coord(MOUSE *mouse, double radius) {
  double x = mouse->x;
  double y = mouse->y;
  double q = ((sqrt(3.0) / 3.0 * x) - (1.0 / 3.0) * y) / radius;
  double r = ((2.0 / 3.0) * y) / radius;

  return axial_round(q, r);
}

void destroy_mouse(MOUSE *mouse) { free(mouse); }