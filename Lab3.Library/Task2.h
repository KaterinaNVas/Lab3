/**
 * @file Task2.h
 * @brief Объявления Task2.
 */
#pragma once
#include "Exercise.h"

namespace miit::algebra {
/**
 * @brief Задание вставки нулевых строк перед строками с первым элементом, кратным трём.
 */
class Task2 final : public Exercise {
public:
    /**
     * @brief Создаёт задание с копией готовой матрицы.
     * @param matrix Исходная матрица.
     * @param generator Генератор, который должен существовать дольше задания.
     */
    Task2(Matrix<int>& matrix, const Generator& generator);
    /**
     * @brief Вставляет нулевые строки перед строками с первым элементом, кратным трём.
     * @return Матрица результата; исходная матрица не изменяется.
     */
    Matrix<int> solve() const override;
};
}
