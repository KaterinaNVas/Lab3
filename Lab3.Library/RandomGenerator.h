/**
 * @file RandomGenerator.h
 * @brief Объявления RandomGenerator.
 */
#pragma once
#include "Generator.h"
#include <random>

namespace miit::algebra {
/**
 * @brief Генератор случайных целых чисел в заданном диапазоне.
 */
class RandomGenerator final : public Generator {
    /**
     * @brief Распределение случайных чисел; изменяется при генерации.
     */
    mutable std::uniform_int_distribution<int> distribution_;
    /**
     * @brief Состояние случайного генератора; изменяется при генерации.
     */
    mutable std::mt19937 generator_;
public:
    /**
     * @brief Создаёт генератор случайных чисел.
     * @param min Минимальное значение включительно.
     * @param max Максимальное значение включительно.
     * @throws std::invalid_argument Если min больше max.
     */
    RandomGenerator(const int min, const int max);
    /**
     * @brief Получает случайное целое число в заданном диапазоне.
     * @return Сгенерированное целое число.
     */
    int generate() const override;
};
}
