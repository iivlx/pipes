#include "gui_curses_commands.h"
#include "PipeWindow.h"
#include "PipeGrid.h"
#include "PipeGridSolver.h"
#include "PipeCell.h"
#include "generator.h"

void createNewPuzzle(PipeWindow* window, PipeGrid* g, int width, int height) {
  if (width < PIPEGRID_MIN_WIDTH || height < PIPEGRID_MIN_HEIGHT) return;
  *g = createPipes(width, height);
  window->cursor.x = 1;
  window->cursor.y = 1;
}

void randomizePuzzle(PipeGrid* g) {
  g->randomize();
}

void solvePuzzle(PipeGrid* g) {
  PipeGridSolver* s = new PipeGridSolver(g);
  s->solve();
  delete s;
}

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

void markSolvedCellAtCursor(PipeWindow* window, PipeGrid* g) {
  PipeCell* c = g->getCell(window->cursor.x, window->cursor.y);
  c->solved = !c->solved;
}