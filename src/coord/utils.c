#include "hv.h"

CUBE_COORD cube_round(double fract_q, double fract_r, double fract_s) {
  double q = round(fract_q);
  double r = round(fract_r);
  double s = round(fract_s);

  double q_diff = fabs(q - fract_q);
  double r_diff = fabs(r - fract_r);
  double s_diff = fabs(s - fract_s);

  if (q_diff > r_diff && q_diff > s_diff)
    q = -r - s;
  else if (r_diff > s_diff)
    r = -q - s;
  else
    s = -q - r;
  return (CUBE_COORD){q, r, s};
}

AXIAL_COORD cube_to_axial(CUBE_COORD coord) {
  return (AXIAL_COORD){coord.q, coord.r};
}

CUBE_COORD axial_to_cube(AXIAL_COORD coord) {
  return (CUBE_COORD){coord.q, coord.r, -coord.q - coord.r};
}

AXIAL_COORD axial_round(double q, double r) {
  cube_to_axial(cube_round(q, r, -q - r));
}

bool axial_coord_equals(AXIAL_COORD a, AXIAL_COORD b) {
  return a.q == b.q && a.r == b.r;
}