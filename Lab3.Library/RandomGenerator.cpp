#include "RandomGenerator.h"
#include <stdexcept> //Standard exception library

miit::algebra::RandomGenerator::RandomGenerator(const int min, const int max)
    : distribution_(min, max), generator_(std::random_device{}()) {
    if (min > max) throw std::invalid_argument("Min must not be greater than max");
}

int miit::algebra::RandomGenerator::generate() {
    return distribution_(generator_);
}
