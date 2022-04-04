#include "hv.h"

int imax(int a, int b) { return a > b ? a : b; }

int imin(int a, int b) { return a < b ? a : b; }

double lerp(double a, double b, double t) { return a + (b - a) * t; }