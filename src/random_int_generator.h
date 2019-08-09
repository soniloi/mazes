#ifndef RANDOM_INT_GENERATOR_H
#define RANDOM_INT_GENERATOR_H

#include <random>

#include "int_generator.h"

class RandomIntGenerator : public IntGenerator {
public:
    RandomIntGenerator(int seed);
    int generate(unsigned int max);

private:
    static const int min = 1;
    std::mt19937 engine;
};

#endif
