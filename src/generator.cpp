#include <iostream>

#include "PipeGrid.h"
#include "PipeCell.h"
#include "directions.h"

PipeGrid createPipes(int width, int height);

void createSource(int width, int height, PipeGrid& grid);

int main(int argc, char** argv) {
  PipeGrid grid = PipeGrid(12, 12);
}

PipeGrid createPipes(int width, int height) {
  PipeGrid grid = PipeGrid(width, height);
  createSource(width, height, grid);

  while (grid.hasEmptyCell()) {
    grid.time += 1;
    // First select either a random empty cell or one we want to start from right away.
    // Like a cell with only 1 directions it can access the source from.
    PipeCell* c = grid.getCellWithOneOpenDirectionToSource();
    if (c == nullptr) {
      c = grid.getRandomEmptyCell();
    }
    c->makeEndpoint(grid.time);
    grid.createPathToSource(c);
  }
  return grid;
}

void createSource(int width, int height, PipeGrid& grid) {
  const int SOURCE_X = width / 2;
  const int SOURCE_Y = height / 2;
  grid.getCell(SOURCE_X, SOURCE_Y)->makeSource(grid.time);
  grid.source = Point{ SOURCE_X, SOURCE_Y };
}