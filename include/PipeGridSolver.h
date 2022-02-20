#pragma once

#include "PipeGrid.h"
#include "directions.h"

class PipeGridSolver {
public:
  PipeGridSolver();
  PipeGridSolver(PipeGrid* g);

  void solve();
  void solveCells();
  bool solveCell(PipeCell* c);
  bool solveEnd(PipeCell* c);
  bool solveElbow(PipeCell* c);
  bool solveStraight(PipeCell* c);
  bool solveT(PipeCell* c);
  void clearCorrectFlags();
  int countPossibleConnections(PipeCell* c);
  int countCorrectConnections(PipeCell* c);
  Connections possibleConnections(Connections d);
  void addConnections(PipeCell* c, Connections d);
  void removeConnections(PipeCell* c, Connections d);
  void removeEdgeConnections();
  void removeTopEdgeConnections();
  void removeBottomEdgeConnections();
  void removeRightEdgeConnections();
  void removeLeftEdgeConnections();
  void removeCornerConnections();
  bool useConnections(PipeCell* c);
  bool useConnections(PipeCell* c, Connections d);
  bool usePossibleConnections(PipeCell* c);
  void updateConnections(PipeCell* c);
  int PipeGridSolver::countConnections(PipeCell* c);

private:
  PipeGrid* grid;
};