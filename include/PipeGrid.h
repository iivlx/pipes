#pragma once

#include "PipeCell.h"
#include "directions.h"

class PipeGrid {
 public:
  int width;
  int height;
  int time;
  int checkTime;
  Point source;

  PipeGrid();
  PipeGrid(int width, int height);
  PipeCell* getCell(int x, int y);
  PipeCell* getCell(int x, int y, int d);
  PipeCell* getCell(PipeCell*, int d);
  PipeCell* getCellSource();
  PipeCell* getCellTopLeft();
  PipeCell* getCellTopRight();
  PipeCell* getCellBottomLeft();
  PipeCell* getCellBottomRight();
  int getCellType(PipeCell* c, int d);
  Point getCellCoordinates(PipeCell* c);
  bool isValidCoordinate(int x, int y);
  bool hasEmptyCell();
  PipeCell* getRandomEmptyCell();
  PipeCell* getRandomCell();
  bool hasCellWithOneOpenDirectionToSource();
  PipeCell* getCellWithOneOpenDirectionToSource();
  Connections getOpenDirectionsToSource(PipeCell* c);
  void createPathToSource(PipeCell* c);
  bool canCreatePathToSource(PipeCell* c, int d);
  int isConnectedToSource(PipeCell* c);
  int isConnectedToSource(PipeCell* c, int d, bool check = false);
  bool isConnectedToSourceUp(PipeCell* c, int d, bool check);
  bool isConnectedToSourceDown(PipeCell* c, int d, bool check);
  bool isConnectedToSourceLeft(PipeCell* c, int d, bool check);
  bool isConnectedToSourceRight(PipeCell* c, int d, bool check);
  bool doesSourceLoop();

 protected:
  std::vector<PipeCell> cells;
  bool canCreatePathToSource_(PipeCell* c);
  void stealEndpoint(PipeCell* c);
  void convertEndpointIntoConnector(PipeCell* c, int d);
  void setCellsCheckedFalse();
  Connections getEndpoints(PipeCell* c); 
};

