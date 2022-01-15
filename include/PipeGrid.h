#pragma once

#include "PipeCell.h"
#include "directions.h"

class PipeGrid {
 public:
  int width;
  int height;
  int time;
  Point source;

  PipeGrid(int width, int height);
  PipeCell* getCell(int x, int y);
  PipeCell* getCell(int x, int y, int d);
  PipeCell* getCell(PipeCell*, int d);
  int getCellType(int x, int y, int d);
  Point getCellCoordinates(PipeCell* c);
  bool isValidCoordinate(int x, int y);

  bool hasEmptyCell();
  PipeCell* getRandomEmptyCell();
  PipeCell* getRandomCell();

  bool hasCellWithOneOpenDirectionToSource();
  PipeCell* getCellWithOneOpenDirectionToSource();
  Connections getOpenDirectionsToSource(int x, int y);
  bool createPathToSource(int x, int y);
  bool createPathToSource(PipeCell* c);

 private:
  std::vector<PipeCell> cells;
  static int checkTime;
};

