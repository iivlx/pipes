#include <string>
#include <sstream>
#include <iostream>

#include "curses.h"

#include "gui_curses.h"
#include "gui_curses_commands.h"
#include "PipeGrid.h"
#include "PipeCell.h"
#include "PipeGridSolver.h"
#include "PipeWindow.h"
#include "pipe_characters.h"
#include "generator.h"

using std::string;
using std::stringstream;

int main(int argc, char** argv) {
  PipeGrid grid = createPipes(10, 10);
  gui(&grid);
}

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

PipeWindow* createWindow() {
  int winBorder = 2;
  return new PipeWindow(getWindowHeight(), getWindowWidth(), 0, 0);
}

void deleteWindow(PipeWindow* window) {
  delete window;
}

void display(PipeWindow* window, PipeGrid* g) {
  clear();
  displayGrid(window, g);
  refresh();
}

int getWindowHeight() {
  int windowHeight;
  int windowWidth;
  getmaxyx(stdscr, windowHeight, windowWidth);
  return windowHeight;
}

int getWindowWidth() {
  int windowHeight;
  int windowWidth;
  getmaxyx(stdscr, windowHeight, windowWidth);
  return windowWidth;
}

void drawPipe(PipeCell* c) {
  if (c->type == PIPE_END)
    drawPipeEnd(c->connections);
  else if (c->type == PIPE_CONNECTOR || c->type == PIPE_SOURCE)
    drawPipeConnector(c->connections);
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

void setAttributes(ColorAttributes& attributes, bool source, bool sourceLoops, bool solved, bool reverse) {
  if (source) {
    if (solved)
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
  else if (solved) {
    attributes.color = COLOR_SOLVED;
    attributes.bold = true;
  }
  if (reverse)
    attributes.reverse = true;
}

void applyAttributes(ColorAttributes attributes) {
  if (attributes.color) attron(COLOR_PAIR(attributes.color));
  if (attributes.bold) attron(A_BOLD);
  if (attributes.reverse) attron(A_REVERSE);
}

void removeAttributes(ColorAttributes& attributes) {
  if (attributes.color) attroff(COLOR_PAIR(attributes.color));
  if (attributes.bold) attroff(A_BOLD);
  if (attributes.reverse) attroff(A_REVERSE);
  clearAttributes(attributes);
}

void clearAttributes(ColorAttributes& attributes) {
  attributes.bold = false;
  attributes.reverse = false;
  attributes.color = 0;
}

void displayCell(PipeGrid* g, PipeCell* c, bool sourceLoops, bool reverse) {
  bool source = g->isConnectedToSource(c);
  ColorAttributes colorAttributes;
  setAttributes(colorAttributes, source, sourceLoops, c->solved, reverse);
  applyAttributes(colorAttributes);
  drawPipe(c);
  removeAttributes(colorAttributes);
}

void displayGrid(PipeWindow* window, PipeGrid* g) {
  bool sourceLoops = g->doesSourceLoop();
  for (int y = 0; y < g->height; y++) {
    for (int x = 0; x < g->width; x++) {
      move(y, x);
      bool reverse = (x == window->cursor.x && y == window->cursor.y);
      displayCell(g, g->getCell(x, y), sourceLoops, reverse);
    }
  }
}

void eraseCharacter(int x, int y) {
  mvaddch(y, x, ' ');
  move(y, x);
}

void setCursorBlink(bool value) {
  curs_set(value);
}

string getCommand(int x, int y, int maxLength, char prompt) {
  string command;
  int cursor = x + 1;
  int cursor_min = cursor;

  mvaddch(y, x, prompt);
  setCursorBlink(true);
  for (int c = getch(); c != '\n'; c = getch()) {
    // Handle specific keys first.
    if (c == '\b') {
      if (cursor <= cursor_min) break;
      command.pop_back();
      eraseCharacter(--cursor, y);
    }
    else if (c == 27) {
      command.clear();
      break;
    }
    // Handle all other keys.
    else if (cursor < maxLength) {
      command.push_back(c);
      mvaddch(y, cursor++, c);
    }
    refresh();
  }
  setCursorBlink(false);
  return command;
}

bool longCommand(PipeWindow* window, PipeGrid* g) {
  string command = getCommand(0, getWindowHeight() - 1);
  return handleCommand(window, g, command);
}

bool handleCommand(PipeWindow* window, PipeGrid* g, string command) {
  string b;
  stringstream ss(command);
  while (ss >> b) {
    if (b == "c") {
      int width, height;
      ss >> width;
      ss >> height;
      createNewPuzzle(window, g, width, height);
    }
    else if (b == "r")
      randomizePuzzle(g);
    else if (b == "s")
      solvePuzzle(g);
    else if (b == "q")
      return true;
  }
  return false;
}

bool handleKeyPress(PipeWindow* window, PipeGrid* g, char c) {
  if (c == KEY_MOUSE) {
   // Handle mouse...
  }
  if (c == 'q') return true;
  if (c == 'h' || c == 'j' || c == 'k' || c == 'l') moveCursor(window, g, c);
  if (c == ' ') rotateCellAtCursor(window, g);
  if (c == 't') markSolvedCellAtCursor(window, g);
  return false;
}

bool handleKeys(PipeWindow* window, PipeGrid* g) {
  bool quit = false;
  int c = getch();
  if (c == ':')
    return longCommand(window, g);
  else
    return handleKeyPress(window, g, c);
}

void mainLoop(PipeWindow* window, PipeGrid* g) {
  bool quit = false;
  while (!quit) {
    display(window, g);
    quit = handleKeys(window, g);
  }
}

void gui(PipeGrid* g) {
  initCurses();
  initColors();
  PipeWindow* mainWindow = createWindow();
  mainLoop(mainWindow, g);
  deleteWindow(mainWindow);
}