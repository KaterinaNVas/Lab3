#include "RandomGenerator.h"

#include <stdexcept>

miit::algebra::RandomGenerator::RandomGenerator(
    const int min,
    const int max
) {
    if (min > max) {
        throw std::invalid_argument(
            "Min must not be greater than max"
        );
    }

    generator_ = std::mt19937(
        std::random_device{}()
    );

    distribution_ =
        std::uniform_int_distribution<int>(
            min,
            max
        );
}

int miit::algebra::RandomGenerator::generate() {
    return distribution_(generator_);
}