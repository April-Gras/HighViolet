#include "hv.h"

int get_row_size(int r) { return (2 * MAP_SIZE) + 1 - abs(MAP_SIZE - r); }

TILE new_map_tile(int q, int r) {
  int s = -q - r;
  SDL_assert(q + r + s == 0);
  return (TILE){false, false, (AXIAL_COORD){q, r}, (CUBE_COORD){q, r, s}};
}

TILE **new_map() {
  int totalMembers = MAP_SIZE * 2;
  TILE **map = (TILE **)malloc(sizeof(TILE *) * (totalMembers + 1));
  int r = 0;

  while (r <= totalMembers) {
    int q = 0;
    int row_size = get_row_size(r);

    map[r] = (TILE *)malloc(sizeof(TILE) * row_size);
    while (q < row_size) {
      map[r][q] = new_map_tile(q + imax(0, MAP_SIZE - r), r);
      q++;
    }
    r++;
  }
  return map;
}

void destroy_tile_map(TILE **map) {
  int totalMembers = MAP_SIZE * 2;
  int r = 0;

  while (r <= totalMembers) {
    free(map[r]);
    r++;
  }
  free(map);
}