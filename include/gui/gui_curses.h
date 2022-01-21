#pragma once

#include <string>

#include "PipeGrid.h"
#include "PipeWindow.h"

#define COLOR_NORMAL 1
#define COLOR_SOLVED 2
#define COLOR_SOURCE 3
#define COLOR_SOURCEL 4
#define COLOR_SS 5
#define COLOR_SSL 6
#define COLOR_A 7

using std::string;

struct ColorAttributes {
  bool bold;
  bool reverse;
  int color;
};

void initColors();
void initCurses();
void display(PipeWindow* window, PipeGrid* g);
void displayGrid(PipeWindow* window, PipeGrid* g);
PipeWindow* createWindow();
void deleteWindow();
int getWindowHeight();
int getWindowWidth();
void moveCursor(PipeWindow* window, PipeGrid* g, int c);
void setAttributes(ColorAttributes& attributes, bool source, bool sourceLoops, bool solved, bool reverse);
void applyAttributes(ColorAttributes attributes);
void removeAttributes(ColorAttributes& attributes);
void clearAttributes(ColorAttributes& attributes);
string getCommand(int x, int y, int maxLength = 60, char prompt = ':');
bool handleCommand(PipeWindow* window, PipeGrid* g);
void handleKeyPress(PipeWindow* window, PipeGrid* g, char c);

void rotateCellAtCursor(PipeWindow* window, PipeGrid* g);

void gui(PipeGrid* g);