#include "PipeCell.h"

PipeCell::PipeCell() {
  this->checked = 0;
  this->connections = { 0, 0, 0, 0 };
  this->type = 0;
  this->time = 0;
}

void PipeCell::rotate() {
  int temp;
  temp = this->connections.up;
  this->connections.up = this->connections.left;
  this->connections.left = this->connections.down;
  this->connections.down = this->connections.right;
  this->connections.right = temp;
}