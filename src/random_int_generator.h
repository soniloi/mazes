#ifndef RANDOM_INT_GENERATOR_H
#define RANDOM_INT_GENERATOR_H

#include <random>

#include "int_generator.h"

class RandomIntGenerator : public IntGenerator {
public:
    RandomIntGenerator(int seed);
    int generate(int min, int max);

private:
    std::mt19937 engine;
};

#endif
