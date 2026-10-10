/**
 * @file ConstantGenerator.h
 * @brief Объявления ConstantGenerator.
 */
#pragma once
#include "Generator.h"

namespace miit::algebra {
/**
 * @brief Генератор, возвращающий заданное постоянное число.
 */
class ConstantGenerator final : public Generator {
    /**
     * @brief Постоянное значение, возвращаемое генератором.
     */
    const int value_;
public:
    /**
     * @brief Создаёт генератор постоянного значения.
     * @param value Возвращаемое значение.
     */
    explicit ConstantGenerator(const int value);
    /**
     * @brief Возвращает заданное постоянное число.
     * @return Сгенерированное целое число.
     */
    int generate() const override;
};
}
