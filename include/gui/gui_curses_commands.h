#pragma once

#include "PipeWindow.h"
#include "PipeGrid.h"
#include "PipeCell.h"

void moveCursor(PipeWindow* window, PipeGrid* g, int c);
void rotateCellAtCursor(PipeWindow* window, PipeGrid* g);