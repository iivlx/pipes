#pragma once

#include <random>

class randint {
 public:
  int operator()();
  int get();
  randint(int low, int high);
 private:
  std::mt19937 random_engine;
  std::uniform_int_distribution<int> distribution;
};