/**
 * @file Task1.cpp
 * @brief Реализация Task1. Подробные описания методов находятся в заголовочном файле.
 */
#include "Task1.h"
#include <algorithm>

miit::algebra::Task1::Task1(
    const Matrix<int>& matrix, const Generator& generator
) : Exercise(matrix, generator) {}

miit::algebra::Matrix<int> miit::algebra::Task1::solve() const {
    Matrix<int> result = matrix_;

    if (result.columns() == 0)
        return result;

    for (std::size_t i = 0; i < result.rows(); ++i) {
        const auto row = result[i];

        const auto maximum = std::max_element(
            row,
            row + result.columns()
        );

        *maximum = 0;
    }

    return result;
}