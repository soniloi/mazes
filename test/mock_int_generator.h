#ifndef MOCK_INT_GENERATOR_H
#define MOCK_INT_GENERATOR_H

#include "gmock/gmock.h"

#include "int_generator.h"

class MockIntGenerator : public IntGenerator {
public:
    MOCK_METHOD2(generate, int(int min, int max));
};

#endif
