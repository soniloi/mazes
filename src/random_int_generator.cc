#include "random_int_generator.h"

RandomIntGenerator::RandomIntGenerator(int seed) {
    this->engine.seed(seed);
}

int RandomIntGenerator::generate(unsigned int max) {
    std::uniform_int_distribution<uint32_t> dist(this->min, max);
    return dist(this->engine);
}
