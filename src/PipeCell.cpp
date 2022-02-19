#include "PipeCell.h"
#include "directions.h"

PipeCell::PipeCell() {
  this->checked = 0;
  this->connections = { 0, 0, 0, 0 };
  this->type = 0;
  this->time = 0;
  this->solved = false;

  this->possibleConnections = { -1, -1, -1, -1 };
  this->correct = false;
}

void PipeCell::rotate() {
  int temp = this->connections.up;
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

bool PipeCell::hasConnection(int d) {
  if (d == UP) return this->connections.up;
  if (d == RIGHT) return this->connections.right;
  if (d == DOWN) return this->connections.down;
  if (d == LEFT) return this->connections.left;
  return false;
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
  return ((c.up && c.right) || (c.right && c.down) || (c.down && c.left) || (c.left && c.up));
}

bool PipeCell::hasOppositeConnections() {
  Connections c = this->connections;
  return ((c.up && c.down) || (c.right && c.left));
}

bool PipeCell::isElbow() {
  return (this->countConnections() == 2 && this->hasAdjacentConnections());
}

bool PipeCell::isStraight() {
  return (this->countConnections() == 2 && this->hasOppositeConnections());
}

bool PipeCell::isT() {
  return (this->countConnections() == 3);
}

bool PipeCell::isEnd() {
  return (this->countConnections() == 1);
}

bool PipeCell::isConnectorOrSource() {
  return (this->type == PIPE_CONNECTOR || this->type == PIPE_SOURCE);
}
