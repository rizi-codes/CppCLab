#ifndef RANDOM_GENERATOR_H
#define RANDOM_GENERATOR_H

#include <random>

class RandomGenerator {
public:
    RandomGenerator();
    explicit RandomGenerator(unsigned seed);
    
    int nextInt(int low, int high);
    double nextDouble(double low, double high);
    bool nextBool(double probability = 0.5);

private:
    std::mt19937 gen;
};

#endif
