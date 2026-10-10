/**
 * @file ConstantGenerator.cpp
 * @brief Реализация ConstantGenerator. Подробные описания методов находятся в заголовочном файле.
 */
#include "ConstantGenerator.h"

miit::algebra::ConstantGenerator::ConstantGenerator(const int value) : value_(value) {}
int miit::algebra::ConstantGenerator::generate() const { return value_; }
