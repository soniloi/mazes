#ifndef INT_GENERATOR_H
#define INT_GENERATOR_H

class IntGenerator {
public:
    IntGenerator() {};
    virtual int generate(unsigned int max) = 0;
};

#endif
