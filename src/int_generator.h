#ifndef INT_GENERATOR_H
#define INT_GENERATOR_H

class IntGenerator {
public:
    IntGenerator() {};
    virtual int generate(int min, int max) = 0;
};

#endif
