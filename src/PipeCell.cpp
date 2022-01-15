#include "PipeCell.h"
#include "directions.h"

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

int PipeCell::countConnections() {
  Connections c = this->connections;
  return c.up + c.right + c.down + c.left;
}

void PipeCell::addConnection(int d) {
  if (d == UP) this->connections.up = 1;
  if (d == RIGHT) this->connections.right = 1;
  if (d == DOWN) this->connections.down = 1;
  if (d == LEFT) this->connections.left = 1;
}

// Add a new connection to the cell from the direction. The connection will be on the opposite side.
void PipeCell::addConnectionFrom(int d) {
  if (d == UP) this->connections.down = 1;
  if (d == RIGHT) this->connections.left = 1;
  if (d == DOWN) this->connections.up = 1;
  if (d == LEFT) this->connections.right = 1;
}

void PipeCell::makeType(int type, int t) {
  this->type = type;
   this->time = t;
}

void PipeCell::makeEndpoint(int time) {
  makeType(PIPE_END, time);
}

void PipeCell::makeSource(int time) {
  makeType(PIPE_SOURCE, time);
}

void PipeCell::makeConnector(int time) {
  makeType(PIPE_CONNECTOR, time);
}

bool PipeCell::hasAdjacentConnections() {
  Connections c = this->connections;
  return ((c.up && c.right) || (c.right && c.down) || (c.down && c.left) || (c.left && c.up)) ? true : false;
}

bool PipeCell::hasOppositeConnections() {
  Connections c = this->connections;
  return ((c.up && c.down) || (c.right && c.left)) ? true : false;
}

bool PipeCell::isElbow() {
  if (this->countConnections() == 2 && this->hasAdjacentConnections()) {
    return true;
  }
  return false;
}

bool PipeCell::isStraight() {
  if (this->countConnections() == 2 && this->hasOppositeConnections()) {
    return true;
  }
  return false;
}

bool PipeCell::isT() {
  if (this->countConnections() == 3) return true;
  return false;
}

bool PipeCell::isEnd() {
  if (this->countConnections() == 1) return true;
  return false;
}
