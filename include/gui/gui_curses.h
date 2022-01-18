#pragma once

#include "PipeGrid.h"

#define COLOR_NORMAL 1
#define COLOR_SOLVED 2
#define COLOR_SOURCE 3
#define COLOR_SOURCEL 4
#define COLOR_SS 5
#define COLOR_SSL 6
#define COLOR_A 7

struct ColorAttributes {
  bool bold;
  bool reverse;
  int color;
};

void initColors();
void initCurses();
void display(PipeGrid* g);
void displayGrid(PipeGrid* g, int sx, int sy, int cx, int cy);
void setAttributes(ColorAttributes attributes, PipeGrid* g, PipeCell* c, bool sourceLoops, bool reverse);
void applyAttributes(ColorAttributes attributes);
void removeAttributes(ColorAttributes attributes);
void clearAttributes(ColorAttributes& attributes);
void handleCommand();
void handleKeyPress(char c);

void gui(PipeGrid* g);