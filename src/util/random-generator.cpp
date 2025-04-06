#include <random>
#include <exception>
#include "util/random-generator.h"

using namespace std;

random_device RandomGenerator::rd;
mt19937 RandomGenerator::gen(RandomGenerator::rd());

int RandomGenerator::nextInt(int low, int high) {
    if (high < low) {
        throw "RandomGenerator::nextInt: first argument must be smaller than the second.";
    }

    uniform_int_distribution<> dis(low, high);
    return dis(gen);
}

double RandomGenerator::nextDouble(double low, double high) {
    if (high <= low) {
        throw "RandomGenerator::nextDouble: first argument must be strictly less than the second.";
    }

    uniform_real_distribution<> dis(low, high);
    return dis(gen);
}

bool RandomGenerator::nextBool(double probability) {
    if (probability < 0 || probability > 1) {
        throw "RandomGenerator::nextBool: argument must be in [0.0, 1.0]";
    }

    return probability == 1 || nextDouble(0, 1) < probability;
}

