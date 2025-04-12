#include "util/random_generator.h"
#include <exception>
#include <random>
#include <stdexcept>

random_generator::random_generator() : gen(std::random_device{}()) {}

random_generator::random_generator(unsigned seed) : gen(seed) {}

int random_generator::nextInt(int low, int high) {
  if (high < low) {
    throw std::invalid_argument(
        "nextInt: first argument must be smaller than the second.");
  }

  std::uniform_int_distribution<> dis(low, high);
  return dis(gen);
}

double random_generator::nextDouble(double low, double high) {
  if (high <= low) {
    throw std::invalid_argument(
        "nextDouble: first argument must be strictly less than the second.");
  }

  std::uniform_real_distribution<> dis(low, high);
  return dis(gen);
}

bool random_generator::nextBool(double probability) {
  if (probability < 0 || probability > 1) {
    throw std::invalid_argument("nextBool: argument must be in [0.0, 1.0]");
  }

  return probability == 1 || nextDouble(0, 1) < probability;
}
