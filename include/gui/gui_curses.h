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
  bool bold = false;
  bool reverse = false;
  int color = 0;
};

void initColors();
void initCurses();
void display(PipeWindow* window, PipeGrid* g);
void displayGrid(PipeWindow* window, PipeGrid* g);
PipeWindow* createWindow();
void deleteWindow();
int getWindowHeight();
int getWindowWidth();
void drawPipe(PipeCell* c);
void drawPipeEnd(Connections c);
void drawPipeElbowOrStraight(Connections c);
void drawPipeT(Connections c);
void drawPipeConnector(Connections c);
void setAttributes(ColorAttributes& attributes, bool source, bool sourceLoops, bool solved, bool reverse);
void applyAttributes(ColorAttributes attributes);
void removeAttributes(ColorAttributes& attributes);
void clearAttributes(ColorAttributes& attributes);
void eraseCharacter(int x, int y);
void setCursorBlink(bool value);
string getCommand(int x, int y, int maxLength = 60, char prompt = ':');
bool handleKeyPress(PipeWindow* window, PipeGrid* g, char c);
bool longCommand(PipeWindow* window, PipeGrid* g);
bool handleCommand(PipeWindow* window, PipeGrid* g, string command);

void gui(PipeGrid* g);