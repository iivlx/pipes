#pragma once

#include "PipeCell.h"

enum Directions {
	NO_DIR = -1,
	UP = 0,
	RIGHT = 1,
	DOWN = 2,
	LEFT = 3,
};

struct Point {
	int x = 0;
	int y = 0;
};

int countConnections(Connections c);
int getRandomSide(Connections c);