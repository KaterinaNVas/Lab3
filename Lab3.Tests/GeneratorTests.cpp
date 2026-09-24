#include "../Lab3.Library/ConstantGenerator.h"
#include "../Lab3.Library/IStreamGenerator.h"
#include "../Lab3.Library/RandomGenerator.h"
#include "../Lab3.Library/ZeroGenerator.h"

#include <cassert>
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace miit::algebra;

void runGeneratorTests() {
    ConstantGenerator constantGenerator(17);

    assert(constantGenerator.generate() == 17);
    assert(constantGenerator.generate() == 17);

    ZeroGenerator zeroGenerator;

    assert(zeroGenerator.generate() == 0);

    std::istringstream input("-4 8 12");
    IStreamGenerator inputGenerator(input);

    assert(inputGenerator.generate() == -4);
    assert(inputGenerator.generate() == 8);
    assert(inputGenerator.generate() == 12);

    RandomGenerator randomGenerator(-3, 3);

    for (int i = 0; i < 100; ++i) {
        const int value = randomGenerator.generate();

        assert(value >= -3);
        assert(value <= 3);
    }

    bool exceptionCaught = false;

    try {
        RandomGenerator incorrectGenerator(10, 5);
    } catch (const std::invalid_argument&) {
        exceptionCaught = true;
    }

    assert(exceptionCaught);

    std::cout << "Тесты генераторов пройдены.\n";
}