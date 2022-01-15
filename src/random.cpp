#include <random>
#include "random.h"

randint::randint(int low, int high)
  : random_engine{ std::random_device{}() }
  , distribution{ low, high } {
}

int randint::operator()() {
  return distribution(random_engine);
}

int randint::get() {
  return distribution(random_engine);
}