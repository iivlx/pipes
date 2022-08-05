#pragma once

#include <glew/glew.h>
#include <GL/GLU.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include "PipeGrid.h"

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

struct vec3 {
  float x;
  float y;
  float z;
};

SDL_Window* init();
void gui(SDL_Window* w, PipeGrid* g);
void displayCell(PipeGrid* g, int x, int y, bool sourceLoops, bool reverse);
void displayGrid(PipeGrid* g, Point cursor);
void clear();