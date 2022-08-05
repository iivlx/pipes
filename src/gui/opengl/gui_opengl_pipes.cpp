#include <math.h>

#include <glew/glew.h>
#include <GL/GLU.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include "gui_opengl.h"
#include "gui_opengl_pipes.h"

void drawBackground(GLfloat x, GLfloat y, vec3 color) {
  glPushMatrix();
  glTranslatef(x, y, 0);
  glBegin(GL_QUADS);
  glColor3f(color.x, color.y, color.z);
  glVertex2f(-20, -20);
  glVertex2f(20, -20);
  glVertex2f(20, 20);
  glVertex2f(-20, 20);
  glEnd();

  glPopMatrix();
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

  double radius = 10;
  double TWO_PI = 2.0 * M_PI;
  glBegin(GL_TRIANGLE_FAN);
  glColor3f(color.x, color.y, color.z);
  glVertex2f(0, 0); // center of circle
  for (int i = 0; i <= 20; i++) 
    glVertex2f(radius * cos(i * TWO_PI / 20), radius * sin(i * TWO_PI / 20));
  glEnd();

  glBegin(GL_QUADS);
  glColor3f(color.x, color.y, color.z);
  glVertex2f(-20, -5);
  glVertex2f(0, -5);
  glVertex2f(0, 5);
  glVertex2f(-20, 5);
  glEnd();

  glPopMatrix();
}