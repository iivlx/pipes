#pragma once

#include "PipeWindow.h"
#include "PipeGrid.h"
#include "PipeCell.h"

void createNewPuzzle(PipeWindow* window, PipeGrid* g, int width, int height);
void randomizePuzzle(PipeGrid* g);
void solvePuzzle(PipeGrid* g);
void moveCursor(PipeWindow* window, PipeGrid* g, int c);
void rotateCellAtCursor(PipeWindow* window, PipeGrid* g);
void markSolvedCellAtCursor(PipeWindow* window, PipeGrid* g);