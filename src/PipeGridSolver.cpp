#include "PipeGridSolver.h"
#include "PipeGrid.h"
#include "PipeCell.h"

PipeGridSolver::PipeGridSolver() {
  grid = nullptr;
}

PipeGridSolver::PipeGridSolver(PipeGrid* g) {
  grid = g;
}

void PipeGridSolver::solve(){
  clearCorrectFlags();
  removeEdgeConnections();
  removeCornerConnections();
  solveCells();
}

void PipeGridSolver::removeEdgeConnections() {
  removeTopEdgeConnections();
  removeRightEdgeConnections();
  removeBottomEdgeConnections();
  removeLeftEdgeConnections();
}

void PipeGridSolver::removeTopEdgeConnections() {
  for (int x = 1; x < this->grid->width - 1; x++)
    removeConnections(this->grid->getCell(x, 0), Connections{ 1, 0, 0, 0 });
}

void PipeGridSolver::removeBottomEdgeConnections() {
  for (int x = 1; x < this->grid->width - 1; x++)
    removeConnections(this->grid->getCell(x, this->grid->height-1), Connections{ 0, 0, 1, 0 });
}

void PipeGridSolver::removeRightEdgeConnections() {
  for (int y = 1; y < this->grid->height - 1; y++)
    removeConnections(this->grid->getCell(this->grid->width-1, y), Connections{ 0, 1, 0, 0 });
}

void PipeGridSolver::removeLeftEdgeConnections() {
  for (int y = 1; y < this->grid->height - 1; y++)
    removeConnections(this->grid->getCell(0, y), Connections{ 0, 0, 0, 1 });
}

void PipeGridSolver::removeCornerConnections() {
  removeConnections(this->grid->getCellTopLeft(), Connections{ 1,0,0,1 });
  removeConnections(this->grid->getCellTopRight(), Connections{ 1,1,0,0 });
  removeConnections(this->grid->getCellBottomRight(), Connections{ 0,1,1,0 });
  removeConnections(this->grid->getCellBottomLeft(), Connections{ 0,0,1,1 });
}

void PipeGridSolver::solveCells() {
  PipeCell* c;
  bool unchanged = false;
  bool check;

  while (!unchanged) {
    unchanged = true;
    for (int x = 0; x < this->grid->width; x++) {
      for (int y = 0; y < this->grid->height; y++) {
        check = solveCell(this->grid->getCell(x, y));
        unchanged = check ? false : true;
      }
    }
  }
}

bool PipeGridSolver::solveCell(PipeCell* c) {
  if (c->correct)
    return false;

  if (c->isEnd())
    return solveEnd(c);
  else if (c->isElbow())
    return solveElbow(c);
  else if (c->isStraight())
    return solveStraight(c);
  else if (c->isT())
    return solveT(c);
}

bool PipeGridSolver::solveEnd(PipeCell* c) {
  if (c->isEnd()) {
    Connections* d = &c->possibleConnections;
    if (countConnections(c) == 1)
      return useConnections(c);

    if (d->up == 1) return useConnections(c, Connections{ 1, 0, 0, 0 });
    if (d->right == 1) return useConnections(c, Connections{ 0, 1, 0, 0 });
    if (d->down == 1) return useConnections(c, Connections{ 0, 0, 1, 0 });
    if (d->left == 1) return useConnections(c, Connections{ 0, 0, 0, 1 });

    if (d->up != 0 && d->right == 0 && d->down == 0 && d->left == 0) return useConnections(c, Connections{ 1, 0, 0, 0 });
    if (d->up == 0 && d->right != 0 && d->down == 0 && d->left == 0) return useConnections(c, Connections{ 0, 1, 0, 0 });
    if (d->up == 0 && d->right == 0 && d->down != 0 && d->left == 0) return useConnections(c, Connections{ 0, 0, 1, 0 });
    if (d->up == 0 && d->right == 0 && d->down == 0 && d->left != 0) return useConnections(c, Connections{ 0, 0, 0, 1 });
  }
  return false;
}

bool PipeGridSolver::solveElbow(PipeCell* c) {
  if (c->isElbow()) {
    Connections* d = &c->possibleConnections;

    if (d->up == 1) d->down = 0;
    if (d->down == 1) d->up = 0;
    if (d->right == 1) d->left = 0;
    if (d->left == 1) d->right = 0;

    if (countPossibleConnections(c) == 2)
      return usePossibleConnections(c);

    if (countCorrectConnections(c) == 2)
      return useConnections(c);
  }
  return false;
}

bool PipeGridSolver::solveStraight(PipeCell* c) {
  if (c->isStraight()) {
    Connections* d = &c->possibleConnections;

    if (countPossibleConnections(c) == 2)
      return usePossibleConnections(c);

    if ((d->up == 1) || (d->down == 1) || d->right == 0 || d->left == 0)
      return useConnections(c, Connections{ 1, 0, 1, 0 });

    if ((d->right == 1) || (d->left == 1) || d->up == 0 || d->down == 0)
      return useConnections(c, Connections{ 0, 1, 0, 1 });
  }
  return false;
}

bool PipeGridSolver::solveT(PipeCell* c) {
  if (c->isT()) {
    Connections* d = &c->possibleConnections;
    
    if ((d->right == 1 && d->down == 1 && d->left == 1) || (d->up == 0)) useConnections(c, Connections{ 0, 1, 1, 1 });
    if ((d->down == 1 && d->left == 1 && d->up == 1) || (d->right == 0)) useConnections(c, Connections{ 1, 0, 1, 1 });
    if ((d->left == 1 && d->up == 1 && d->right == 1) || (d->down == 0)) useConnections(c, Connections{ 1, 1, 0, 1 });
    if ((d->up == 1 && d->right == 1 && d->down == 1) || (d->left == 0)) useConnections(c, Connections{ 1, 1, 1, 0 });
  }
  return false;
}

void PipeGridSolver::clearCorrectFlags() {
  for (int x = 0; x < this->grid->width; x++) {
    for (int y = 0; y < this->grid->height; y++) {
      this->grid->getCell(x, y)->correct = false;
    }
  }
}

int PipeGridSolver::countPossibleConnections(PipeCell* c) {
  Connections d = c->possibleConnections;
  return (d.up != 0) + (d.right != 0) + (d.down != 0) + (d.left != 0);
}

int PipeGridSolver::countCorrectConnections(PipeCell* c) {
  Connections d = c->possibleConnections;
  return (d.up == 1) + (d.right == 1) + (d.down == 1) + (d.left == 1);
}

Connections PipeGridSolver::possibleConnections(Connections d) {
  return Connections{ (d.up != 0), (d.right != 0), (d.down != 0), (d.left != 0) };
}

void PipeGridSolver::addConnections(PipeCell* c) {

}

bool PipeGridSolver::useConnections(PipeCell* c) {
  c->connections.up = c->possibleConnections.up == 1;
  c->connections.right = c->possibleConnections.right == 1;
  c->connections.down = c->possibleConnections.down == 1;
  c->connections.left = c->possibleConnections.left == 1;
  c->correct = true;
  updateConnections(c);
  return true;
}

bool PipeGridSolver::useConnections(PipeCell* c, Connections connections) {
  c->possibleConnections = connections;
  return useConnections(c);
}

bool PipeGridSolver::usePossibleConnections(PipeCell* c) {
  return useConnections(c, possibleConnections(c->possibleConnections));
}

void PipeGridSolver::updateConnections(PipeCell* c) {
  //Point p = grid->getCellCoordinates(c);




}

void PipeGridSolver::removeConnections(PipeCell* c, Connections connections) {
  if (connections.up) c->possibleConnections.up = 0;
  if (connections.right) c->possibleConnections.right = 0;
  if (connections.down) c->possibleConnections.down = 0;
  if (connections.left) c->possibleConnections.left = 0;
}

int PipeGridSolver::countConnections(PipeCell* c) {
  Connections p = c->possibleConnections;
  return p.up + p.right + p.down + p.left;
}