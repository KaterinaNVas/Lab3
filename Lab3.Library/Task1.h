/**
 * @file Task1.h
 * @brief Объявления Task1.
 */
#pragma once
#include "Exercise.h"

namespace miit::algebra {
/**
 * @brief Задание замены первого максимального элемента каждой строки нулём.
 */
class Task1 final : public Exercise {
public:
    /**
     * @brief Создаёт задание с копией готовой матрицы.
     * @param matrix Исходная матрица.
     * @param generator Генератор, который должен существовать дольше задания.
     */
    Task1(const Matrix<int>& matrix, const Generator& generator);
    /**
     * @brief Заменяет первый максимум каждой строки нулём.
     * @return Матрица результата; исходная матрица не изменяется.
     */
    Matrix<int> solve() const override;
};
}
