#pragma once

enum Directions {
  NO_DIR = -1,
  UP = 0,
  RIGHT = 1,
  DOWN = 2,
  LEFT = 3,
};

struct Connections {
  int up = 0;
  int right = 0;
  int down = 0;
  int left = 0;
};

struct Point {
  int x = 0;
  int y = 0;
};

const Connections Up = Connections{ 1,0,0,0 };
const Connections UpRight = Connections{ 1, 1, 0, 0 };
const Connections UpDown = Connections{ 1, 0, 1, 0 };
const Connections UpLeft = Connections{ 1, 0, 0, 1 };
const Connections UpRightDown = Connections{ 1, 1, 1, 0 };
const Connections UpRightDownLeft = Connections{ 1, 1, 1, 1 };
const Connections UpRightLeft = Connections{ 1, 1, 0, 1 };
const Connections UpDownLeft = Connections{ 1, 0, 1, 1 };

const Connections Right = Connections{ 0,1,0,0 };
const Connections RightDown = Connections{ 0,1,1,0 };
const Connections RightLeft = Connections{ 0,1,0,1 };
const Connections RightDownLeft = Connections{ 0,1,1,1 };

const Connections Down = Connections{ 0,0,1,0 };
const Connections DownLeft = Connections{ 0,0,1,1 };

const Connections Left = Connections{ 0,0,0,1 };

int countConnections(Connections c);
int getRandomSide(Connections c);