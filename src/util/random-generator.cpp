#include <random>
#include <stdexcept>
#include <exception>
#include "util/random-generator.h"


RandomGenerator::RandomGenerator() : gen(std::random_device{}()) {}

RandomGenerator::RandomGenerator(unsigned seed) : gen(seed) {}

int RandomGenerator::nextInt(int low, int high) {
    if (high < low) {
        throw std::invalid_argument("nextInt: first argument must be smaller than the second.");
    }

    std::uniform_int_distribution<> dis(low, high);
    return dis(gen);
}

double RandomGenerator::nextDouble(double low, double high) {
    if (high <= low) {
        throw std::invalid_argument("nextDouble: first argument must be strictly less than the second.");
    }

    std::uniform_real_distribution<> dis(low, high);
    return dis(gen);
}

bool RandomGenerator::nextBool(double probability) {
    if (probability < 0 || probability > 1) {
        throw std::invalid_argument("nextBool: argument must be in [0.0, 1.0]");
    }

    return probability == 1 || nextDouble(0, 1) < probability;
}

