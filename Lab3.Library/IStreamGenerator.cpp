#include "IStreamGenerator.h"
#include <istream>
#include <stdexcept>

miit::algebra::IStreamGenerator::IStreamGenerator(std::istream& in) : in_(in) {}

int miit::algebra::IStreamGenerator::generate() {
    int value{};
    if (!(in_ >> value)) throw std::runtime_error("Cannot read an integer");
    return value;
}
