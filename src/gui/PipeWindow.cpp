#include "PipeWindow.h"
#include "directions.h"

PipeWindow::PipeWindow(int nlines, int ncols, int begin_y, int begin_x) {
  this->window = newwin(nlines, ncols, begin_y, begin_x);
}
