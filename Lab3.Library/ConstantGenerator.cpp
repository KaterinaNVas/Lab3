#include "ConstantGenerator.h"

miit::algebra::ConstantGenerator::ConstantGenerator(int value) : value_(value) {}
int miit::algebra::ConstantGenerator::generate() { return value_; }
