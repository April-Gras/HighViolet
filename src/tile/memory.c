#include "hv.h"

int get_map_row_size(int r) { return (2 * MAP_SIZE) + 1 - abs(MAP_SIZE - r); }

TILE new_map_tile(int q, int r) {
  int s = -q - r;
  SDL_assert(q + r + s == 0);
  return (TILE){false, false, (AXIAL_COORD){q, r}, (CUBE_COORD){q, r, s}};
}

TILE **new_map() {
  int total_member_count = R_LENGTH;
  TILE **map = (TILE **)malloc(sizeof(TILE *) * (total_member_count + 1));
  int r = 0;

  while (r <= total_member_count) {
    int q = 0;
    int row_size = get_map_row_size(r);

    map[r] = (TILE *)malloc(sizeof(TILE) * row_size);
    while (q < row_size) {
      // q = -(imax(0, MAP_SIZE) - r) is inverse
      map[r][q] = new_map_tile(q + imax(0, MAP_SIZE - r), r);
      q++;
    }
    r++;
  }
  return map;
}

int get_q_index_from_axial_coord(AXIAL_COORD coord) {
  return -(imax(0, MAP_SIZE) - coord.r);
}

void destroy_tile_map(TILE **map) {
  int total_member_count = MAP_SIZE * 2;
  int r = 0;

  while (r <= total_member_count) {
    free(map[r]);
    r++;
  }
  free(map);
}