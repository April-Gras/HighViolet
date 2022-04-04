#include "hv.h"

TILE_COLLECTION get_tile_line_from_extremities(TILE *a, TILE *b, STATE *state) {
  int n = cube_distance(a->cube_coord, b->cube_coord);
  TILE *results = (TILE *)malloc(sizeof(TILE) * (n + 1));

  for (int i = 0; i <= n; i++) {
    bool continue_find_loops = true;
    // Compute target coord
    CUBE_COORD target = cube_lerp_and_round(a->cube_coord, b->cube_coord,
                                            1.0 / (double)n * (double)i);
    // Set null for assertion

    for (int row_index = 0; row_index <= R_LENGTH && continue_find_loops;
         row_index++) {

      int row_size = get_map_row_size(row_index);

      for (int col_index = 0; col_index < row_size; col_index++) {
        TILE potencial_match = state->map[row_index][col_index];
        if (cube_coord_equals(potencial_match.cube_coord, target)) {
          results[i] = potencial_match;
          potencial_match.is_hovered = true;
          continue_find_loops = false;
          break;
        }
      }
    }
    // If a member doesn't exist cancel
    if (continue_find_loops) {
      free(results);
      return (TILE_COLLECTION){NULL, 0};
    }
  }
  return (TILE_COLLECTION){results, n + 1};
}