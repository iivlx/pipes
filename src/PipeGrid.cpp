#include <tuple>
#include <vector>

#include "random.h"
#include "PipeGrid.h"
#include "PipeCell.h"

PipeGrid::PipeGrid() {
  this->width = 0;
  this->height = 0;
  this->time = 0;
  this->checkTime = 0;
  this->source = Point{ 0, 0 };
}

PipeGrid::PipeGrid(int width, int height) {
  this->width = width;
  this->height = height;
  this->time = 0;
  this->checkTime = 0;
  this->source = Point{ 0, 0 };
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      this->cells.push_back(PipeCell());
    }
  }
}

bool PipeGrid::isValidCoordinate(int x, int y) {
  if ((x < 0 || x >= this->width) || (y < 0 || y >= this->height)) return false;
  return true;
}

PipeCell* PipeGrid::getCell(int x, int y) {
  if (!isValidCoordinate(x, y))
    return nullptr;
  return &this->cells[y * this->width + x];
}

PipeCell* PipeGrid::getCell(int x, int y, int d) {
  PipeCell* c = nullptr;
  if (d == UP) c = getCell(x, y - 1);
  if (d == RIGHT) c = getCell(x + 1, y);
  if (d == DOWN) c = getCell(x, y + 1);
  if (d == LEFT) c = getCell(x - 1, y);
  if (d < 0) c = getCell(x, y);
  return c;
}

PipeCell* PipeGrid::getCell(PipeCell* c, int d) {
  Point p = getCellCoordinates(c);
  return getCell(p.x, p.y, d);
}

PipeCell* PipeGrid::getCellSource() {
  return getCell(this->source.x, this->source.y);
}

PipeCell* PipeGrid::getCellTopLeft() {
  return getCell(0, 0);
}

PipeCell* PipeGrid::getCellTopRight() {
  return getCell(this->width-1, 0);
}

PipeCell* PipeGrid::getCellBottomLeft() {
  return getCell(0, this->height-1);
}

PipeCell* PipeGrid::getCellBottomRight() {
  return getCell(this->width - 1, this->height-1);
}

int PipeGrid::getCellType(PipeCell* c, int d) {
  PipeCell* n = getCell(c, d);
  if (n == nullptr) return -1;
  return n->type;
}

Point PipeGrid::getCellCoordinates(PipeCell* c) {
  int index = c - &(this->cells[0]);
  return Point{ index % this->width, index / this->width };
}

bool PipeGrid::hasEmptyCell() {
  for (PipeCell& c : this->cells)
    if (c.type == PIPE_EMPTY) return true;
  return false;
}

PipeCell* PipeGrid::getRandomCell() {
  int cCells = this->width * this->height;
  int idxRandomCell = randint(0, cCells - 1)();
  return &this->cells[idxRandomCell];
}

PipeCell* PipeGrid::getRandomEmptyCell() {
  if (hasEmptyCell() == false) return nullptr;
  PipeCell* c;
  do {
    c = getRandomCell();
  } while (c->type != PIPE_EMPTY);
  return c;
}

// Check if there are any empty cells in the grid that are blocked on 3 sides.
bool PipeGrid::hasCellWithOneOpenDirectionToSource() {
  PipeCell* c = getCellWithOneOpenDirectionToSource();
  return (c != nullptr) ? true : false;
}

// Get an empty cell in the grid that is blocked on 3 sides.
PipeCell* PipeGrid::getCellWithOneOpenDirectionToSource() {
  for (PipeCell& c : this->cells)
    if (c.type == PIPE_EMPTY && countConnections(getOpenDirectionsToSource(&c)) <= 1)
      return &c;
  return nullptr;
}


void PipeGrid::setCellsCheckedFalse() {
  for (PipeCell& c : this->cells)
    c.checked = false;
}

void PipeGrid::createPathToSource(PipeCell* c) {
  int newSide = getRandomSide(getOpenDirectionsToSource(c));
  // If every side is blocked we have to steal an endpoint.
  if (newSide < 0) return stealEndpoint(c);

  PipeCell* next = getCell(c, newSide);
  c->addConnection(newSide);
  next->addConnectionFrom(newSide);

  if (next->type == PIPE_EMPTY) {
    next->makeConnector(this->time);
    createPathToSource(next);
  }
}

bool PipeGrid::canCreatePathToSource(PipeCell* c, int d) {
  this->checkTime += 1;
  return canCreatePathToSource_(getCell(c, d));
}

bool PipeGrid::canCreatePathToSource_(PipeCell* c) {
  if (c == nullptr) return false;
  if (c->checked == this->checkTime) return false;
  c->checked = this->checkTime;

  if (c->isConnectorOrSource() && c->countConnections() < 3)
    if (c->time < this->time)
      return true;

  if (c->type != PIPE_EMPTY) return false;
  if (canCreatePathToSource_(getCell(c, UP))) return true;
  if (canCreatePathToSource_(getCell(c, RIGHT))) return true;
  if (canCreatePathToSource_(getCell(c, DOWN))) return true;
  if (canCreatePathToSource_(getCell(c, LEFT))) return true;
  return false;
}

int PipeGrid::isConnectedToSource(PipeCell* c) {
  setCellsCheckedFalse();
  return isConnectedToSource(c, -1);
}

int PipeGrid::isConnectedToSource(PipeCell* c, int d, bool check) {
  if (c == nullptr) return false;
  if (c->checked) return check;
  c->checked = true;
  // Recursively check each connection until they all reuslt in a dead end, or we reach the source.
  if (c->type == PIPE_SOURCE && check == false) return true;
  if (isConnectedToSourceUp(c, d, check)) return true;
  if (isConnectedToSourceDown(c, d, check)) return true;
  if (isConnectedToSourceRight(c, d, check)) return true;
  if (isConnectedToSourceLeft(c, d, check)) return true;
  return false;
}

bool PipeGrid::isConnectedToSourceUp(PipeCell* c, int d, bool check) {
  if (c->connections.up && d != UP) {
    PipeCell* n = getCell(c, UP);
    if (n == nullptr) return false;
    if (n->connections.down && isConnectedToSource(n, DOWN, check))
      return true;
  }
  return false;
}

bool PipeGrid::isConnectedToSourceDown(PipeCell* c, int d, bool check) {
  if (c->connections.down && d != DOWN) {
    PipeCell* n = getCell(c, DOWN);
    if (n == nullptr) return false;
    if (n->connections.up && isConnectedToSource(n, UP, check))
      return true;
  }
  return false;
}

bool PipeGrid::isConnectedToSourceRight(PipeCell* c, int d, bool check) {
  if (c->connections.right && d != RIGHT) {
    PipeCell* n = getCell(c, RIGHT);
    if (n == nullptr) return false;
    if (n->connections.left && isConnectedToSource(n, LEFT, check))
      return true;
  }
  return false;
}

bool PipeGrid::isConnectedToSourceLeft(PipeCell* c, int d, bool check) {
  if (c->connections.left && d != LEFT) {
    PipeCell* n = getCell(c, LEFT);
    if (n == nullptr) return false;
    if (n->connections.right && isConnectedToSource(n, RIGHT, check))
      return true;
  }
  return false;
}

bool PipeGrid::doesSourceLoop() {
  setCellsCheckedFalse();
  return isConnectedToSource(getCellSource(), -1, true);
}

Connections PipeGrid::getOpenDirectionsToSource(PipeCell* c) {
  Connections d;
  d.left = canCreatePathToSource(c, LEFT);
  d.right = canCreatePathToSource(c, RIGHT);
  d.up = canCreatePathToSource(c, UP);
  d.down = canCreatePathToSource(c, DOWN);
  return d;
}

void PipeGrid::stealEndpoint(PipeCell* c) {
  int newSide = getRandomSide(getEndpoints(c));
  c->addConnection(newSide);
  convertEndpointIntoConnector(getCell(c, newSide), newSide);
}

void PipeGrid::convertEndpointIntoConnector(PipeCell* c, int d) {
  if (c == nullptr) return;
  c->makeConnector(this->time);
  c->addConnectionFrom(d);
}

Connections PipeGrid::getEndpoints(PipeCell* c) {
  Connections d = { 0, 0, 0, 0 };
  d.up = getCellType(c, UP) == PIPE_END;
  d.right = getCellType(c, RIGHT) == PIPE_END;
  d.down = getCellType(c, DOWN) == PIPE_END;
  d.left = getCellType(c, LEFT) == PIPE_END;
  return d;
}