#pragma once

#include <glew/glew.h>
#include <GL/GLU.h>
#include <SDL.h>
#include <SDL_opengl.h>

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

SDL_Window* initSDL();
void gui(SDL_Window* w, PipeGrid* g);
void drawElbow(GLfloat x, GLfloat y, GLfloat r);
void drawEnd(GLfloat x, GLfloat y, GLfloat r);
void drawT(GLfloat x, GLfloat y, GLfloat r);
void drawStraight(GLfloat x, GLfloat y, GLfloat r);
void displayCell(PipeGrid* g, int x, int y, bool sourceLoops, bool reverse);
void displayGrid(PipeGrid* g);
void clear();