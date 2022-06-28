#pragma once

#include <math.h>

#include <glew/glew.h>
#include <GL/GLU.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include "PipeGrid.h"
#include "PipeCell.h"
#include "PipeGridSolver.h"
#include "pipe_characters.h"
#include "generator.h"
#include "gui_opengl.h"

SDL_Window* init() {
  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_Window* w;
  w = SDL_CreateWindow("Pipes", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

  SDL_GLContext glContext = SDL_GL_CreateContext(w);
   if (glContext == NULL) {
     printf("SDL Error: %s\n", SDL_GetError());
		 return nullptr;
  }
	
  GLenum error = glewInit();
  if (error != GLEW_OK) {
    printf("Glew Error: %s\n", glewGetErrorString(error));
    return nullptr;
  }

  return w;
}

void gui(SDL_Window* w, PipeGrid* g) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0);
  glClearColor(0.f, 0.f, 0.f, 1.f);

  glMatrixMode(GL_MODELVIEW);

  SDL_Event event;
  bool quit = false;
  while (!quit) {
    SDL_WaitEvent(&event);
    SDL_Keycode key = event.key.keysym.sym;
    switch (event.type) {
    case SDL_QUIT:
      quit = true;
      break;
    case SDL_KEYDOWN:
    if (key == SDLK_q)
      quit = true;
    else if (key == SDLK_r)
      g->randomize();
    else if (key == SDLK_s) {
      PipeGridSolver* s = new PipeGridSolver(g);
      s->solve();
      delete s;
    }
      break;
    }
    clear();
    displayGrid(g);
    SDL_GL_SwapWindow(w);
  }
}

void drawT(GLfloat x, GLfloat y, GLfloat r, vec3 color) {
  glPushMatrix();
  glTranslatef(x, y, 0);
  glRotatef(r, 0, 0, 1);

  glBegin(GL_QUADS);
  glColor3f(color.x, color.y, color.z);
  glVertex2f(-20, -5); // 1
  glVertex2f(20, -5);
  glVertex2f(20, 5);
  glVertex2f(-20, 5);
  glVertex2f(-5, 5); // 2
  glVertex2f(5, 5);
  glVertex2f(5, 20);
  glVertex2f(-5, 20);
  glEnd();

  glPopMatrix();
}


void drawStraight(GLfloat x, GLfloat y, GLfloat r, vec3 color) {
  glPushMatrix();
  glTranslatef(x, y, 0);
  glRotatef(r, 0, 0, 1);

  glBegin(GL_QUADS);
  glColor3f(color.x, color.y, color.z);
  glVertex2f(-20, -5);
  glVertex2f(20, -5);
  glVertex2f(20, 5);
  glVertex2f(-20, 5);
  glEnd();

  glPopMatrix();
}

void drawElbow(GLfloat x, GLfloat y, GLfloat r, vec3 color) {
  glPushMatrix();
  glTranslatef(x, y, 0);
  glRotatef(r, 0, 0, 1);

  glBegin(GL_QUADS);
  glColor3f(color.x, color.y, color.z);
  glVertex2f(-5, -5); // 1
  glVertex2f(20, -5);
  glVertex2f(20, 5);
  glVertex2f(5, 5);
  glVertex2f(-5, -5); // 2
  glVertex2f(-5, 20);
  glVertex2f(5, 20);
  glVertex2f(5, 5);
  glEnd();

  glPopMatrix();
}

void drawEnd(GLfloat x, GLfloat y, GLfloat r, vec3 color) {
  glPushMatrix();
  glTranslatef(x, y, 0);
  glRotatef(r, 0, 0, 1);

  glBegin(GL_QUADS);
  glColor3f(color.x, color.y, color.z);
  glVertex2f(-20, -5);
  glVertex2f(0, -5);
  glVertex2f(0, 5);
  glVertex2f(-20, 5);
  glEnd();

  glPopMatrix();
}

void displayCell(PipeGrid* g, int x, int y, bool sourceLoops, bool reverse) {
  PipeCell* c = g->getCell(x, y);
  bool source = g->isConnectedToSource(c);

  x = 20 + x * 40;
  y = 20 + y * 40;
  vec3 color = { 1, 1, 1};
  if (sourceLoops)
    color = { 1, 0, 0 };
  else if (source)
    color = { 0, 0, 1 };


  if (countConnections(c->connections) == 3) {
    if (!c->connections.up)
      drawT(x, y, 0, color);
    else if (!c->connections.right)
      drawT(x, y, 90, color);
    else if (!c->connections.down)
      drawT(x, y, 180, color);
    else if (!c->connections.left)
      drawT(x, y, 270, color);
  }

  if (countConnections(c->connections) == 2) {
  if (c->connections.up && c->connections.down)
    drawStraight(x, y, 90, color);
  else if (c->connections.left && c->connections.right)
    drawStraight(x, y, 0, color);
  else if (c->connections.up && c->connections.right)
    drawElbow(x, y, 270, color);
  else if (c->connections.up && c->connections.left)
    drawElbow(x, y, 180, color);
  else if (c->connections.left && c->connections.down)
    drawElbow(x, y, 90, color);
  else
    drawElbow(x, y, 0, color);
  }

  if (countConnections(c->connections) == 1) {
    if (c->connections.left)
      drawEnd(x, y, 0, color);
    else if (c->connections.up)
      drawEnd(x, y, 90, color);
    else if (c->connections.right)
      drawEnd(x, y, 180, color);
    else if (c->connections.down)
      drawEnd(x, y, 270, color);
  }
}

void displayGrid(PipeGrid* g) {
  bool sourceLoops = g->doesSourceLoop();

  for (int y = 0; y < g->height; y++) {
    for (int x = 0; x < g->width; x++) {
      bool reverse = false;
      displayCell(g, x, y, sourceLoops, reverse);
    }
  }
}

void clear() {
  glClearDepth(1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

int main(int argc, char* argv[]) {
  SDL_Window* window = init();

  PipeGrid grid = createPipes(10, 10);

  if (window == nullptr)
    return 1;
  else
    gui(window, &grid);

  return 0;
}
