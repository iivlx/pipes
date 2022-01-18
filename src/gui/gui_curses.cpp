#include "curses.h"

#include "gui_curses.h"
#include "PipeGrid.h"
#include "PipeCell.h"
#include "pipe_characters.h"

void initColors() {
  start_color();
  init_pair(COLOR_SOLVED, COLOR_GREEN, COLOR_BLACK);
  init_pair(COLOR_SOURCE, COLOR_BLUE, COLOR_BLACK);
  init_pair(COLOR_SOURCEL, COLOR_RED, COLOR_BLACK);
  init_pair(COLOR_SS, COLOR_CYAN, COLOR_BLACK);
  init_pair(COLOR_SSL, COLOR_MAGENTA, COLOR_BLACK);
}

void initCurses() {
  initscr();
  noecho();
  cbreak();
  curs_set(0);
}

WINDOW* createWindow() {
  int windowHeight;
  int windowWidth;
  int winBorder = 2;
  getmaxyx(stdscr, windowHeight, windowWidth);
  WINDOW* window = newwin(windowHeight, windowWidth, 0, 0);
  return window;
}

void display(PipeGrid* g, int cx, int cy) {
  clear();
  displayGrid(g, 0, 0, cx, cy);
  refresh();
}

void drawPipeEnd(Connections c) {
  if (c.up) addch(END_U);
  else if (c.right) addch(END_R);
  else if (c.down) addch(END_D);
  else if (c.left) addch(END_L);
}

void drawPipeElbowOrStraight(Connections c) {
  if (c.up && c.right) addch(ELBOW_UR);
  else if (c.up && c.left) addch(ELBOW_UL);
  else if (c.right && c.down) addch(ELBOW_DR);
  else if (c.down && c.left) addch(ELBOW_DL);
  else if (c.right && c.left) addch(STRAIGHT_H);
  else if (c.up && c.down) addch(STRAIGHT_V);
}

void drawPipeT(Connections c) {
  if (c.up == 0) addch(T_U);
  else if (c.right == 0) addch(T_R);
  else if (c.down == 0) addch(T_D);
  else if (c.left == 0) addch(T_L);
}

void drawPipeConnector(Connections c) {
  int numberConnections = countConnections(c);
  if (numberConnections == 1)
    drawPipeEnd(c);
  else if (numberConnections == 2)
    drawPipeElbowOrStraight(c);
  else if (numberConnections == 3)
    drawPipeT(c);
}

void setAttributes(ColorAttributes attributes, PipeGrid* g, PipeCell* c, bool sourceLoops, bool reverse) {
  if (g->isConnectedToSource(c)) {
    if (c->solved)
      if (sourceLoops)
        attributes.color = COLOR_SSL;
      else
        attributes.color = COLOR_SS;
    else
      if (sourceLoops)
        attributes.color = COLOR_SOURCEL;
      else
        attributes.color = COLOR_SOURCE;
  }
  else if (c->solved) {
    attributes.color = COLOR_SOLVED;
    attributes.bold = true;
  }
  if (reverse)
    attributes.reverse = true;
}

void applyAttributes(ColorAttributes attributes) {
  if (attributes.reverse) attron(A_REVERSE);
  if (attributes.bold) attron(A_BOLD);
  attron(COLOR_PAIR(attributes.color));
}

void removeAttributes(ColorAttributes attributes) {
  clearAttributes(attributes);
  applyAttributes(attributes);
}

void clearAttributes(ColorAttributes& attributes) {
  attributes.bold = false;
  attributes.reverse = false;
  attributes.color = 0;
}

void displayGrid(PipeGrid* g, int sx, int sy, int cx, int cy) {
  ColorAttributes colorAttributes;
  clearAttributes(colorAttributes);

  bool cursor;
  bool sourceLoops = g->doesSourceLoop();

  for (int y = 0; y < g->height; y++) {
    for (int x = 0; x < g->width; x++) {
      PipeCell* c = g->getCell(x, y);
      move(sy + y, sx + x);
      cursor = (x == cx && y == cy);
      setAttributes(colorAttributes, g, c, sourceLoops, cursor);

      applyAttributes(colorAttributes);

      if (c->type == PIPE_END)
        drawPipeEnd(c->connections);
      else if (c->type == PIPE_CONNECTOR || c->type == PIPE_SOURCE)
        drawPipeConnector(c->connections);

      removeAttributes(colorAttributes);
    }
  }
  return;
}

void handleCommand() {
  return;
}

void handleKeyPress(char c) {
  return;
}


void gui(PipeGrid* g) {
  initCurses();
  initColors();
  WINDOW* mainWindow = createWindow();

  int cursorX = 0;
  int cursorY = 0;

  int c = 0;
  do {
    if (c == ':')
      handleCommand();
    else
      handleKeyPress(c);
    display(g, cursorX, cursorY);

    c = getch();
  } while (c != 'q');
}