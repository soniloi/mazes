#ifndef MOCK_INT_GENERATOR_H
#define MOCK_INT_GENERATOR_H

#include "gmock/gmock.h"

#include "int_generator.h"

class MockIntGenerator : public IntGenerator {
public:
    MOCK_METHOD1(generate, int(unsigned int max));
};

#endif
