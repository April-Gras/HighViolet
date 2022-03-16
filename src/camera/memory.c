#include "hv.h"

CAMERA *new_camera() {
  CAMERA *camera = (CAMERA *)malloc(sizeof(CAMERA));

  camera->x = 0;
  camera->y = 0;
  camera->z = 60;
  return camera;
}

void destroy_camera(CAMERA *camera) { free(camera); }