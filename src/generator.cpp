#include "generator.h"
#include "PipeGrid.h"
#include "PipeCell.h"
#include "directions.h"

void createEndpoint(PipeGrid& grid) {
  grid.time += 1;
  PipeCell* c = grid.getCellWithOneOpenDirectionToSource(); // Create these cells first.
  if (c == nullptr)
    c = grid.getRandomEmptyCell();
  c->makeEndpoint(grid.time);
  grid.createPathToSource(c);
}

PipeGrid createPipes(int width, int height) {
  PipeGrid grid = PipeGrid(width, height);
  createSource(width, height, grid);
  while (grid.hasEmptyCell())
    createEndpoint(grid);
  return grid;
}

void createSource(int width, int height, PipeGrid& grid) {
  const int SOURCE_X = width / 2;
  const int SOURCE_Y = height / 2;
  grid.getCell(SOURCE_X, SOURCE_Y)->makeSource(grid.time);
  grid.source = Point{ SOURCE_X, SOURCE_Y };
}