#pragma once

class PipeGrid {
 public:
	PipeGrid(int width, int height);
	int width;
	int height;
 private:
  std::vector<Cell> cells;
}
