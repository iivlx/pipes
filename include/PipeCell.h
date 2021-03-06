#pragma once

#include <tuple>
#include <vector>

#include "directions.h"

enum PipeType {
  PIPE_EMPTY = 0,
  PIPE_END = 1,
  PIPE_SOURCE = 2,
  PIPE_CONNECTOR = 3,
};

class PipeCell {
public:
  Connections connections;
  int type;
  int time;
  int checked;
  bool solved;

  bool correct;
  Connections possibleConnections;

  PipeCell();

  int countConnections();
  void addConnection(int d);
  void addConnectionFrom(int d);
  bool hasConnection(int d);

  void makeEndpoint(int t);
  void makeConnector(int t);
  void makeSource(int t);

  bool isElbow();
  bool isT();
  bool isEnd();
  bool isStraight();
  bool isConnectorOrSource();

  void rotate();

 protected:
  bool hasAdjacentConnections();
  bool hasOppositeConnections();
  void makeType(int type, int t);
};