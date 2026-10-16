/**
 * @file GeneratorTests.cpp
 * @brief Проверки генераторов целых чисел.
 */
#include "../Lab3.Library/ConstantGenerator.h"
#include "../Lab3.Library/IStreamGenerator.h"
#include "../Lab3.Library/RandomGenerator.h"
#include "../Lab3.Library/ZeroGenerator.h"

#include <cassert>
#include <functional>
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace miit::algebra;

/**
 * @brief Проверки генераторов целых чисел.
 * @details Целые значения сравниваются через std::equal_to; размеры — через
 * std::equal_to<std::size_t>, элементы и результаты генераторов — через std::equal_to<int>.
 * @note Проверки используют assert и должны выполняться без определения NDEBUG.
 */
void runGeneratorTests() {
    const ConstantGenerator constantGenerator(17);

    assert(std::equal_to<int>{}(constantGenerator.generate(), 17));
    assert(std::equal_to<int>{}(constantGenerator.generate(), 17));

    const ZeroGenerator zeroGenerator;

    assert(std::equal_to<int>{}(zeroGenerator.generate(), 0));

    std::istringstream input("-4 8 12");
    const IStreamGenerator inputGenerator(input);

    assert(std::equal_to<int>{}(inputGenerator.generate(), -4));
    assert(std::equal_to<int>{}(inputGenerator.generate(), 8));
    assert(std::equal_to<int>{}(inputGenerator.generate(), 12));

    const RandomGenerator randomGenerator(-3, 3);

    for (int i = 0; i < 100; ++i) {
        const int value = randomGenerator.generate();

        assert(value >= -3);
        assert(value <= 3);
    }

    bool exceptionCaught = false;

    try {
        const RandomGenerator incorrectGenerator(10, 5);
    } catch (const std::invalid_argument&) {
        exceptionCaught = true;
    }

    assert(exceptionCaught);

    std::cout << "Тесты генераторов пройдены.\n";
}