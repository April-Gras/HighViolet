#include "hv.h"

void change_camera_zoom(int zoom_addition, CAMERA *camera) {
  int result = camera->z + (int)zoom_addition;

  if (result < 0)
    camera->z = 0;
  else
    camera->z = result;
}

void change_camera_position(int x, int y, CAMERA *camera) {
  camera->x += x;
  camera->y += y;
}