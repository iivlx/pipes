#pragma once

#include <string>

#include "curses.h"

#include "directions.h"

class PipeWindow {
 public:
  Point cursor;
  WINDOW* window;
  PipeWindow(int nlines, int ncols, int begin_y, int begin_x);
};