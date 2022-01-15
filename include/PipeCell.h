#pragma once

#include <tuple>
#include <vector>

enum PipeType {
  PIPE_EMPTY = 0,
  PIPE_END = 1,
  PIPE_SOURCE = 2,
  PIPE_CONNECTOR = 3,
};

struct Connections {
  int up = 0;
  int right = 0;
  int down = 0;
  int left = 0;
};

class PipeCell {
public:
  Connections connections;
  int type;
  int time;
  int checked;

  PipeCell();



  void rotate();

 private:
};