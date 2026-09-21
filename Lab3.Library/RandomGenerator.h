#pragma once
#include "Generator.h"
#include <random>

namespace miit::algebra {
class RandomGenerator final : public Generator {
    std::uniform_int_distribution<int> distribution_;
    std::mt19937 generator_;
public:
    RandomGenerator(const int min, const int max);
    int generate() override;
};
}
