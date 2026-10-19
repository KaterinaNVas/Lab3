/**
 * @file Generator.h
 * @brief Объявления Generator.
 */
#pragma once

namespace miit::algebra {
/**
 * @brief Абстрактный генератор целых чисел.
 */
class Generator {
public:
    /**
     * @brief Обеспечивает корректное уничтожение объекта через базовый класс.
     */
    virtual ~Generator() = default;
    /**
     * @brief Получает следующее целое число.
     * @return Сгенерированное целое число.
     */
    virtual int generate() const = 0;
};
}
