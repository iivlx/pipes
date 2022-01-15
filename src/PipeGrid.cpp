#include <tuple>
#include <vector>

#include "random.h"
#include "PipeGrid.h"

PipeGrid::PipeGrid(int width, int height) {
  this->width = width;
  this->height = height;
  this->time = 0;
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

int PipeGrid::getCellType(int x, int y, int d) {
	PipeCell* c = getCell(x, y, d);
	if (c == nullptr) return -1;
	return c->type;
}

Point PipeGrid::getCellCoordinates(PipeCell* c) {
	int index = c - &(this->cells[0]);
	return Point{ index % this->width, index / this->width };
}

// Check if there are any empty cells in the grid that are blocked on 3 sides.
bool PipeGrid::hasCellWithOneOpenDirectionToSource() {
	PipeCell* c = getCellWithOneOpenDirectionToSource();
	return (c != nullptr) ? true : false;
}

// Get an empty cell in the grid that is blocked on 3 sides.
PipeCell* PipeGrid::getCellWithOneOpenDirectionToSource() {
	for (int y = 0; y < this->height; y++) {
		for (int x = 0; x < this->width; x++) {
			PipeCell* c = getCell(x, y);
			if (c->type == PIPE_EMPTY) {
				if (countConnections(getOpenDirectionsToSource(x, y)) <= 1)
					return c;
			}
		}
	}
	return nullptr;
}


bool PipeGrid::createPathToSource(int x, int y) {
	return false;
}


Connections PipeGrid::getOpenDirectionsToSource(int x, int y) {
	Connections c = { 0, 0, 0, 0 };
	/*
	c.left = checkPathToSource(x, y, LEFT);
	c.right = checkPathToSource(x, y, RIGHT);
	c.up = checkPathToSource(x, y, UP);
	c.down = checkPathToSource(x, y, DOWN);
	*/
	return c;
}