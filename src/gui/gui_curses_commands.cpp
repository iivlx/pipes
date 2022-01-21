#include "gui_curses_commands.h"
#include "PipeWindow.h"
#include "PipeGrid.h"
#include "PipeCell.h"

void moveCursor(PipeWindow* window, PipeGrid* g, int c) {
  if (c == 'h' && window->cursor.x > 0) window->cursor.x--;
  if (c == 'j' && window->cursor.y < g->height - 1) window->cursor.y++;
  if (c == 'k' && window->cursor.y > 0) window->cursor.y--;
  if (c == 'l' && window->cursor.x < g->width - 1) window->cursor.x++;
}

void rotateCellAtCursor(PipeWindow* window, PipeGrid* g) {
  PipeCell* c = g->getCell(window->cursor.x, window->cursor.y);
  if (!c->solved) c->rotate();
}